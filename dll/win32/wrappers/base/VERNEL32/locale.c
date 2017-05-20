/*++

Copyright (c) 2017 Shorthorn Project.

Module Name:

    locale.c

Abstract:

    This file contains functions that return information about a
    language group, a UI language, a locale, or a calendar.

Revision History:

    22-03-2017

--*/

#include "main.h"
#include "locale.h"

#define LOCALE_WINDOWS              0x01
#define LOCALE_NEUTRALDATA          0x10
#define LOCALE_SPECIFICDATA         0x20
#define MUI_LANGUAGE_ID             0x04
#define MUI_LANGUAGE_NAME           0x08
#define MUI_MACHINE_LANGUAGE_SETTINGS       0x400
#define MUI_MERGE_USER_FALLBACK 0x20
#define MUI_MERGE_SYSTEM_FALLBACK 0x10
#define MUI_THREAD_LANGUAGES                0x40
#define MUI_UI_FALLBACK                     MUI_MERGE_SYSTEM_FALLBACK | MUI_MERGE_USER_FALLBACK
#define MAX_STRING_LEN 256

WINE_DEFAULT_DEBUG_CHANNEL(locale); 

struct locale_name
{
    WCHAR  win_name[128];   /* Windows name ("en-US") */
    WCHAR  lang[128];       /* language ("en") (note: buffer contains the other strings too) */
    WCHAR *country;         /* country ("US") */
    WCHAR *charset;         /* charset ("UTF-8") for Unix format only */
    WCHAR *script;          /* script ("Latn") for Windows format only */
    WCHAR *modifier;        /* modifier or sort order */
    LCID   lcid;            /* corresponding LCID */
    int    matches;         /* number of elements matching LCID (0..4) */
    UINT   codepage;        /* codepage corresponding to charset */
};

struct enum_locale_ex_data
{
    LOCALE_ENUMPROCEX proc;
    DWORD             flags;
    LPARAM            lparam;
};


static WORD get_default_sublang(LCID lang)
{
    switch (PRIMARYLANGID(lang))
    {
    case LANG_SPANISH:
        return SUBLANG_SPANISH_MODERN;
    case LANG_CHINESE:
        return SUBLANG_CHINESE_SIMPLIFIED;
    default:
        return SUBLANG_DEFAULT;
    }
}

/***********************************************************************
 *           find_locale_id_callback
 */
static BOOL CALLBACK find_locale_id_callback( HMODULE hModule, LPCWSTR type,
                                              LPCWSTR name, WORD LangID, LPARAM lParam )
{
    struct locale_name *data = (struct locale_name *)lParam;
    WCHAR buffer[128];
    int matches = 0;
    LCID lcid = MAKELCID( LangID, SORT_DEFAULT );  /* FIXME: handle sort order */

    if (PRIMARYLANGID(LangID) == LANG_NEUTRAL) return TRUE; /* continue search */

    /* first check exact name */
    if (data->win_name[0] &&
        GetLocaleInfoW( lcid, LOCALE_SNAME | LOCALE_NOUSEROVERRIDE,
                        buffer, sizeof(buffer)/sizeof(WCHAR) ))
    {
        if (!strcmpiW( data->win_name, buffer ))
        {
            matches = 4;  /* everything matches */
            goto done;
        }
    }

    if (!GetLocaleInfoW( lcid, LOCALE_SISO639LANGNAME | LOCALE_NOUSEROVERRIDE,
                         buffer, sizeof(buffer)/sizeof(WCHAR) ))
        return TRUE;
    if (strcmpiW( buffer, data->lang )) return TRUE;
    matches++;  /* language name matched */

    if (data->country)
    {
        if (GetLocaleInfoW( lcid, LOCALE_SISO3166CTRYNAME|LOCALE_NOUSEROVERRIDE,
                            buffer, sizeof(buffer)/sizeof(WCHAR) ))
        {
            if (strcmpiW( buffer, data->country )) goto done;
            matches++;  /* country name matched */
        }
    }
    else  /* match default language */
    {
        if (SUBLANGID(LangID) == get_default_sublang( LangID )) matches++;
    }

    if (data->codepage)
    {
        UINT unix_cp;
        if (GetLocaleInfoW( lcid, LOCALE_IDEFAULTUNIXCODEPAGE | LOCALE_RETURN_NUMBER,
                            (LPWSTR)&unix_cp, sizeof(unix_cp)/sizeof(WCHAR) ))
        {
            if (unix_cp == data->codepage) matches++;
        }
    }

    /* FIXME: check sort order */

done:
    if (matches > data->matches)
    {
        data->lcid = lcid;
        data->matches = matches;
    }
    return (data->matches < 4);  /* no need to continue for perfect match */
}

/***********************************************************************
 *		parse_locale_name
 *
 * Parse a locale name into a struct locale_name, handling both Windows and Unix formats.
 * Unix format is: lang[_country][.charset][@modifier]
 * Windows format is: lang[-script][-country][_modifier]
 */
static void parse_locale_name( const WCHAR *str, struct locale_name *name )
{
    static const WCHAR sepW[] = {'-','_','.','@',0};
    static const WCHAR winsepW[] = {'-','_',0};
    static const WCHAR posixW[] = {'P','O','S','I','X',0};
    static const WCHAR cW[] = {'C',0};
    static const WCHAR latinW[] = {'l','a','t','i','n',0};
    static const WCHAR latnW[] = {'-','L','a','t','n',0};
    WCHAR *p;

    name->country = name->charset = name->script = name->modifier = NULL;
    name->lcid = MAKELCID( MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT), SORT_DEFAULT );
    name->matches = 0;
    name->codepage = 0;
    name->win_name[0] = 0;
    lstrcpynW( name->lang, str, sizeof(name->lang)/sizeof(WCHAR) );

    if (!*name->lang)
    {
        name->lcid = LOCALE_INVARIANT;
        name->matches = 4;
        return;
    }

    if (!(p = strpbrkW( name->lang, sepW )))
    {
        if (!strcmpW( name->lang, posixW ) || !strcmpW( name->lang, cW ))
        {
            name->matches = 4;  /* perfect match for default English lcid */
            return;
        }
        strcpyW( name->win_name, name->lang );
    }
    else if (*p == '-')  /* Windows format */
    {
        strcpyW( name->win_name, name->lang );
        *p++ = 0;
        name->country = p;
        if (!(p = strpbrkW( p, winsepW ))) goto done;
        if (*p == '-')
        {
            *p++ = 0;
            name->script = name->country;
            name->country = p;
            if (!(p = strpbrkW( p, winsepW ))) goto done;
        }
        *p++ = 0;
        name->modifier = p;
    }
done:
    EnumResourceLanguagesW( NULL, (LPCWSTR)RT_STRING, (LPCWSTR)LOCALE_ILANGUAGE,
                            find_locale_id_callback, (LPARAM)name );
}

/***********************************************************************
 *           LocaleNameToLCID  (KERNEL32.@)
 */
LCID 
WINAPI 
LocaleNameToLCID( 
	LPCWSTR name, 
	DWORD flags 
)
{
    int i;

    if (name == LOCALE_NAME_USER_DEFAULT)
        return GetUserDefaultLCID();

	for(i=0;i<LOCALE_TABLE_SIZE;i++){
		if(wcscmp(name, locale_table[i].localeName)==0){
			return locale_table[i].lcid;
		}
	}
	
    return GetSystemDefaultLCID();
}

/***********************************************************************
 *           LCIDToLocaleName  (KERNEL32.@)
 */
INT 
WINAPI 
LCIDToLocaleName( 
	LCID lcid, 
	LPWSTR lpName, 
	INT count, 
	DWORD flags 
)
{
	int i;
	int length = 0;
	for(i=0;i<LOCALE_TABLE_SIZE;i++){
		if(lcid == locale_table[i].lcid){
			length = (wcslen(locale_table[i].localeName)+1);
			if(lpName){
				memcpy(lpName, locale_table[i].localeName, sizeof(WCHAR)*(length));
				lpName[length-1] = 0;
			}			
			return length;
		}
	}
	return length;
}

/***********************************************************************
 *		GetSystemDefaultLocaleName (KERNEL32.@)
 */
INT 
WINAPI 
GetSystemDefaultLocaleName(
	LPWSTR localename, 
	INT len
)
{
    LCID lcid = GetSystemDefaultLCID();
    return LCIDToLocaleName(lcid, localename, len, 0);
}

/******************************************************************************
 *           IsValidLocaleName   (KERNEL32.@)
 */
BOOL 
WINAPI 
IsValidLocaleName( 
	LPCWSTR locale 
)
{
	int i;
    if (!locale)
        return FALSE;

	for(i=0;i<LOCALE_TABLE_SIZE;i++){
		if(wcscmp(locale, locale_table[i].localeName)==0){
			return TRUE;
		}
	}	

    return FALSE;
}

/***********************************************************************
  *              GetThreadUILanguage (KERNEL32.@)
  *
  * Get the current thread's language identifier.
  *
  * PARAMS
  *  None.
  *
  * RETURNS
  *  The current thread's language identifier.
*/
LANGID 
WINAPI 
GetThreadUILanguage( void )
{
     LANGID lang;
     //NtQueryDefaultUILanguage( &lang );
     //DbgPrint("GetThreadUILanguage is UNIMPLEMENTED, returning default language.\n");
	 //Windows XP and Server 2003 doesn't use really LANGIID passed how paremeter on SetThreadUILanguage, so, we 
	 //can use to get Thread UI Language;	 
     return SetThreadUILanguage(0);
}

BOOL 
WINAPI 
GetFileMUIPath(
	DWORD dwFlags, 
	PCWSTR pcwszFilePath, 
	PWSTR pwszLanguage, 
	PULONG pcchLanguage, 
	PWSTR pwszFileMUIPath,
	PULONG pcchFileMUIPath, 
	PULONGLONG pululEnumerator
)
{
	SetLastError(ERROR_CALL_NOT_IMPLEMENTED);		
	return FALSE;
}

/*
 * @implemented - need test
 */
/******************************************************************************
 *           CompareStringEx    (KERNEL32.@)
 */
INT 
WINAPI 
CompareStringEx(
	LPCWSTR locale, 
	DWORD flags, 
	LPCWSTR str1, 
	INT len1,
    LPCWSTR str2, 
	INT len2, 
	LPNLSVERSIONINFO version, 
	LPVOID reserved, 
	LPARAM lParam
)
{
    INT ret;

    if (version) DbgPrint("unexpected version parameter\n");
    if (reserved) DbgPrint("unexpected reserved value\n");
    if (lParam) DbgPrint("unexpected lParam\n");

    if (!str1 || !str2)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;
    }

    if( flags & ~(NORM_IGNORECASE|NORM_IGNORENONSPACE|NORM_IGNORESYMBOLS|
        SORT_STRINGSORT|NORM_IGNOREKANATYPE|NORM_IGNOREWIDTH|LOCALE_USE_CP_ACP|0x10000000) )
    {
        SetLastError(ERROR_INVALID_FLAGS);
        return 0;
    }

    /* this style is related to diacritics in Arabic, Japanese, and Hebrew */
    if (flags & 0x10000000)
        DbgPrint("Ignoring unknown flags 0x10000000\n");

    if (len1 < 0) len1 = strlenW(str1);
    if (len2 < 0) len2 = strlenW(str2);

    ret = wine_compare_string(flags, str1, len1, str2, len2);

    if (ret) /* need to translate result */
        return (ret < 0) ? CSTR_LESS_THAN : CSTR_GREATER_THAN;
    return CSTR_EQUAL;
}

/*************************************************************************
 *           LCMapStringEx   (KERNEL32.@)
 *
 * Map characters in a locale sensitive string.
 *
 * PARAMS
 *  name     [I] Locale name for the conversion.
 *  flags    [I] Flags controlling the mapping (LCMAP_ constants from "winnls.h")
 *  src      [I] String to map
 *  srclen   [I] Length of src in chars, or -1 if src is NUL terminated
 *  dst      [O] Destination for mapped string
 *  dstlen   [I] Length of dst in characters
 *  version  [I] reserved, must be NULL
 *  reserved [I] reserved, must be NULL
 *  lparam   [I] reserved, must be 0
 *
 * RETURNS
 *  Success: The length of the mapped string in dst, including the NUL terminator.
 *  Failure: 0. Use GetLastError() to determine the cause.
 */
INT 
WINAPI 
LCMapStringEx(
	LPCWSTR name, 
	DWORD flags, 
	LPCWSTR src, 
	INT srclen, 
	LPWSTR dst, 
	INT dstlen,
    LPNLSVERSIONINFO version, 
	LPVOID reserved, 
	LPARAM lparam
)
{
    LPWSTR dst_ptr;
	
	DbgPrint("LCMapStringEx called\n");		

    if (version) DbgPrint("unsupported version structure %p\n", version);
    if (reserved) DbgPrint("unsupported reserved pointer %p\n", reserved);
    if (lparam) DbgPrint("unsupported lparam %lx\n", lparam);

    if (!src || !srclen || dstlen < 0)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;
    }

    /* mutually exclusive flags */
    if ((flags & (LCMAP_LOWERCASE | LCMAP_UPPERCASE)) == (LCMAP_LOWERCASE | LCMAP_UPPERCASE) ||
        (flags & (LCMAP_HIRAGANA | LCMAP_KATAKANA)) == (LCMAP_HIRAGANA | LCMAP_KATAKANA) ||
        (flags & (LCMAP_HALFWIDTH | LCMAP_FULLWIDTH)) == (LCMAP_HALFWIDTH | LCMAP_FULLWIDTH) ||
        (flags & (LCMAP_TRADITIONAL_CHINESE | LCMAP_SIMPLIFIED_CHINESE)) == (LCMAP_TRADITIONAL_CHINESE | LCMAP_SIMPLIFIED_CHINESE))
    {
        SetLastError(ERROR_INVALID_FLAGS);
        return 0;
    }

    if (!dstlen) dst = NULL;

    if (flags & LCMAP_SORTKEY)
    {
        INT ret;
        if (src == dst)
        {
            SetLastError(ERROR_INVALID_FLAGS);
            return 0;
        }

        if (srclen < 0) srclen = strlenW(src);

        DbgPrint("(%s,0x%08x,%s,%d,%p,%d)\n",
              debugstr_w(name), flags, debugstr_wn(src, srclen), srclen, dst, dstlen);

        ret = wine_get_sortkey(flags, src, srclen, (char *)dst, dstlen);
        if (ret == 0)
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
        else
            ret++;
        return ret;
    }

    /* SORT_STRINGSORT must be used exclusively with LCMAP_SORTKEY */
    if (flags & SORT_STRINGSORT)
    {
        SetLastError(ERROR_INVALID_FLAGS);
        return 0;
    }

    if (srclen < 0) srclen = strlenW(src) + 1;

    DbgPrint("(%s,0x%08x,%s,%d,%p,%d)\n",
          debugstr_w(name), flags, debugstr_wn(src, srclen), srclen, dst, dstlen);

    if (!dst) /* return required string length */
    {
        INT len;

        for (len = 0; srclen; src++, srclen--)
        {
            WCHAR wch = *src;
            /* tests show that win2k just ignores NORM_IGNORENONSPACE,
             * and skips white space and punctuation characters for
             * NORM_IGNORESYMBOLS.
             */
            if ((flags & NORM_IGNORESYMBOLS) && (get_char_typeW(wch) & (C1_PUNCT | C1_SPACE)))
                continue;
            len++;
        }
        return len;
    }

    if (flags & LCMAP_UPPERCASE)
    {
        for (dst_ptr = dst; srclen && dstlen; src++, srclen--)
        {
            WCHAR wch = *src;
            if ((flags & NORM_IGNORESYMBOLS) && (get_char_typeW(wch) & (C1_PUNCT | C1_SPACE)))
                continue;
            *dst_ptr++ = toupperW(wch);
            dstlen--;
        }
    }
    else if (flags & LCMAP_LOWERCASE)
    {
        for (dst_ptr = dst; srclen && dstlen; src++, srclen--)
        {
            WCHAR wch = *src;
            if ((flags & NORM_IGNORESYMBOLS) && (get_char_typeW(wch) & (C1_PUNCT | C1_SPACE)))
                continue;
            *dst_ptr++ = tolowerW(wch);
            dstlen--;
        }
    }
    else
    {
        if (src == dst)
        {
            SetLastError(ERROR_INVALID_FLAGS);
            return 0;
        }
        for (dst_ptr = dst; srclen && dstlen; src++, srclen--)
        {
            WCHAR wch = *src;
            if ((flags & NORM_IGNORESYMBOLS) && (get_char_typeW(wch) & (C1_PUNCT | C1_SPACE)))
                continue;
            *dst_ptr++ = wch;
            dstlen--;
        }
    }

    if (srclen)
    {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return 0;
    }

    return dst_ptr - dst;
}

INT 
WINAPI 
GetUserDefaultLocaleName(
	LPWSTR localename, 
	int buffersize
)
{
     LCID userlcid;
   
	userlcid = GetUserDefaultLCID();
    return LCIDToLocaleName(userlcid, localename, buffersize, 0);
}

static BOOL CALLBACK enum_locale_ex_proc( HMODULE module, LPCWSTR type,
                                          LPCWSTR name, WORD lang, LONG_PTR lparam )
{
    struct enum_locale_ex_data *data = (struct enum_locale_ex_data *)lparam;
    WCHAR buffer[256];
    DWORD neutral;
    unsigned int flags;

    GetLocaleInfoW( MAKELCID( lang, SORT_DEFAULT ), LOCALE_SNAME | LOCALE_NOUSEROVERRIDE,
                    buffer, sizeof(buffer) / sizeof(WCHAR) );
    if (!GetLocaleInfoW( MAKELCID( lang, SORT_DEFAULT ),
                         LOCALE_INEUTRAL | LOCALE_NOUSEROVERRIDE | LOCALE_RETURN_NUMBER,
                         (LPWSTR)&neutral, sizeof(neutral) / sizeof(WCHAR) ))
        neutral = 0;
    flags = LOCALE_WINDOWS;
    flags |= neutral ? LOCALE_NEUTRALDATA : LOCALE_SPECIFICDATA;
    if (data->flags && !(data->flags & flags)) return TRUE;
    return data->proc( buffer, flags, data->lparam );
}

/******************************************************************************
 *           EnumSystemLocalesEx  (KERNEL32.@)
 */
BOOL 
WINAPI 
EnumSystemLocalesEx( 
	LOCALE_ENUMPROCEX proc, 
	DWORD flags, 
	LPARAM lparam, 
	LPVOID reserved )
{
    struct enum_locale_ex_data data;

    if (reserved)
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        return FALSE;
    }
    data.proc   = proc;
    data.flags  = flags;
    data.lparam = lparam;
    EnumResourceLanguagesW( kernel32_handle, (LPCWSTR)RT_STRING,
                            (LPCWSTR)MAKEINTRESOURCE((LOCALE_SNAME >> 4) + 1),
                            enum_locale_ex_proc, (LONG_PTR)&data );
    return TRUE;
}

//Wrapper to special cases of GetLocaleInfoW
int 
WINAPI 
GetpLocaleInfoW(
    LCID Locale,
    LCTYPE LCType,
    LPWSTR lpLCData,
    int cchData)
{
	switch(LCType){
		case ( LOCALE_SNAME ) :
			return LCIDToLocaleName(Locale, lpLCData, LOCALE_NAME_MAX_LENGTH, 0);
		default:
			return GetLocaleInfoW(Locale, LCType, lpLCData, cchData);
	}
}

int 
WINAPI
GeptLocaleInfoA(
  _In_      LCID   Locale,
  _In_      LCTYPE LCType,
  _Out_opt_ LPTSTR lpLCData,
  _In_      int    cchData
)
{
    WCHAR pDTmp[MAX_STRING_LEN];  // tmp Unicode buffer (destination)
    LPWSTR pBuf;                  // ptr to destination buffer	
	int numberCharacters;
	
	pBuf = pDTmp;
	switch(LCType){
		case ( LOCALE_SNAME ) :
			numberCharacters = LCIDToLocaleName(Locale, pBuf, LOCALE_NAME_MAX_LENGTH, 0);
			numberCharacters *= sizeof(WCHAR);
            if (lpLCData)
            {
                if (numberCharacters <= cchData) 
				{
					memcpy( lpLCData, pBuf, numberCharacters );
				}					
			}
			return numberCharacters;
		default:
			return GetLocaleInfoA(Locale, LCType, lpLCData, cchData);
	}	
}

/******************************************************************************
 *           GetLocaleInfoEx (KERNEL32.@)
 */
INT 
WINAPI 
GetLocaleInfoEx(
	LPCWSTR locale, 
	LCTYPE info, 
	LPWSTR buffer, 
	INT len
)
{
    LCID lcid = LocaleNameToLCID(locale, 0);

    if (!lcid) return 0;

    /* special handling for neutral locale names */
    if (info == LOCALE_SNAME && locale && strlenW(locale) == 2)
    {
        if (len && len < 3)
        {
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            return 0;
        }

        if (len) strcpyW(buffer, locale);
        return 3;
    }

    return GetpLocaleInfoW(lcid, info, buffer, len);
}

/***********************************************************************
 *             GetSystemPreferredUILanguages (KERNEL32.@)
 */
BOOL 
WINAPI 
GetSystemPreferredUILanguages(
  _In_       DWORD dwFlags,
  _Out_      PULONG pulNumLanguages,
  _Out_opt_  PZZWSTR pwszLanguagesBuffer,
  _Inout_    PULONG pcchLanguagesBuffer
)
{
	  NTSTATUS status;
	  BOOL result;
	  DWORD error; 

	  status = RtlGetSystemPreferredUILanguages(dwFlags, pulNumLanguages, pwszLanguagesBuffer, pcchLanguagesBuffer);
	  if (!NT_SUCCESS(status) )
	  {
		error = RtlNtStatusToDosError(status);
		SetLastError(error);
		result = FALSE;
	  }
	  else
	  {
		result = TRUE;
	  }
	  return result;
}

/***********************************************************************
 *              GetThreadPreferredUILanguages (KERNEL32.@)
 */
BOOL 
WINAPI 
GetThreadPreferredUILanguages( 
  _In_       DWORD dwFlags,
  _Out_      PULONG pulNumLanguages,
  _Out_opt_  PZZWSTR pwszLanguagesBuffer,
  _Inout_    PULONG pcchLanguagesBuffer
)
{
	  NTSTATUS status;
	  BOOL result;
	  DWORD error; 

	  status = RtlGetThreadPreferredUILanguages(dwFlags, pulNumLanguages, pwszLanguagesBuffer, pcchLanguagesBuffer);
	  if (!NT_SUCCESS(status) )
	  {
		error = RtlNtStatusToDosError(status);
		SetLastError(error);
		result = FALSE;
	  }
	  else
	  {
		result = TRUE;
	  }
	  return result;
}

/***********************************************************************
 *              GetThreadPreferredUILanguages (KERNEL32.@)
 */
BOOL 
WINAPI 
GetUserPreferredUILanguages( 
  _In_       DWORD dwFlags,
  _Out_      PULONG pulNumLanguages,
  _Out_opt_  PZZWSTR pwszLanguagesBuffer,
  _Inout_    PULONG pcchLanguagesBuffer
)
{
	  NTSTATUS status;
	  BOOL result;
	  DWORD error; 

	  status = RtlGetUserPreferredUILanguages(dwFlags, FALSE, pulNumLanguages, pwszLanguagesBuffer, pcchLanguagesBuffer);
	  if (!NT_SUCCESS(status) )
	  {
		error = RtlNtStatusToDosError(status);
		SetLastError(error);
		result = FALSE;
	  }
	  else
	  {
		result = TRUE;
	  }
	  return result;
}