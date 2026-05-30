::[Bat To Exe Converter]
::
::YAwzoRdxOk+EWAnk
::fBw5plQjdG8=
::YAwzuBVtJxjWCl3EqQJgSA==
::ZR4luwNxJguZRRnk
::Yhs/ulQjdF+5
::cxAkpRVqdFKZSzk=
::cBs/ulQjdF+5
::ZR41oxFsdFKZSDk=
::eBoioBt6dFKZSDk=
::cRo6pxp7LAbNWATEpCI=
::egkzugNsPRvcWATEpCI=
::dAsiuh18IRvcCxnZtBJQ
::cRYluBh/LU+EWAnk
::YxY4rhs+aU+JeA==
::cxY6rQJ7JhzQF1fEqQJQ
::ZQ05rAF9IBncCkqN+0xwdVs0
::ZQ05rAF9IAHYFVzEqQJQ
::eg0/rx1wNQPfEVWB+kM9LVsJDGQ=
::fBEirQZwNQPfEVWB+kM9LVsJDGQ=
::cRolqwZ3JBvQF1fEqQJQ
::dhA7uBVwLU+EWDk=
::YQ03rBFzNR3SWATElA==
::dhAmsQZ3MwfNWATElA==
::ZQ0/vhVqMQ3MEVWAtB9wSA==
::Zg8zqx1/OA3MEVWAtB9wSA==
::dhA7pRFwIByZRRnk
::Zh4grVQjdCyDJGyX8VAjFChVQRGHMFeeA6YX/Ofr0+WEo1kcR+ksLtuV36yLQA==
::YB416Ek+ZW8=
::
::
::978f952a14a936cc963da21a135fa983
@echo off
setlocal

REM Unidade do Windows
set "SYS_DRIVE=%SystemDrive%"

REM Caminhos
set "DOTNET64_PATH=%SYS_DRIVE%\Windows\Microsoft.NET\Framework64\\"
set "DOTNET32_PATH=%SYS_DRIVE%\Windows\Microsoft.NET\Framework\\"

REM Chaves
set "NETFX_KEY=HKLM\SOFTWARE\Microsoft\.NETFramework"
set "NETFX_WOW64_KEY=HKLM\SOFTWARE\WOW6432Node\Microsoft\.NETFramework"

echo Verificando .NET Framework...

REM =========================================================
REM HKLM\SOFTWARE\Microsoft\.NETFramework
REM =========================================================

reg query "%NETFX_KEY%" >nul 2>&1

if errorlevel 1 (
    echo Criando chave principal...

    reg add "%NETFX_KEY%" /f

    reg add "%NETFX_KEY%" /v "Enable64Bit" /t REG_DWORD /d 0x1 /f
    reg add "%NETFX_KEY%" /v "InstallRoot" /t REG_SZ /d "%DOTNET64_PATH%" /f
) else (
    echo Chave principal ja existe.

    REM Verifica Enable64Bit
    reg query "%NETFX_KEY%" /v "Enable64Bit" >nul 2>&1
    if errorlevel 1 (
        reg add "%NETFX_KEY%" /v "Enable64Bit" /t REG_DWORD /d 0x1 /f
    )

    REM Verifica InstallRoot
    reg query "%NETFX_KEY%" /v "InstallRoot" >nul 2>&1
    if errorlevel 1 (
        reg add "%NETFX_KEY%" /v "InstallRoot" /t REG_SZ /d "%DOTNET64_PATH%" /f
    )
)

REM =========================================================
REM HKLM\SOFTWARE\WOW6432Node\Microsoft\.NETFramework
REM =========================================================

reg query "%NETFX_WOW64_KEY%" >nul 2>&1

if errorlevel 1 (
    echo Criando chave WOW6432Node...

    reg add "%NETFX_WOW64_KEY%" /f

    reg add "%NETFX_WOW64_KEY%" /v "InstallRoot" /t REG_SZ /d "%DOTNET32_PATH%" /f
) else (
    echo Chave WOW6432Node ja existe.

    reg query "%NETFX_WOW64_KEY%" /v "InstallRoot" >nul 2>&1
    if errorlevel 1 (
        reg add "%NETFX_WOW64_KEY%" /v "InstallRoot" /t REG_SZ /d "%DOTNET32_PATH%" /f
    )
)

echo Finalizado.

endlocal
exit /b 0