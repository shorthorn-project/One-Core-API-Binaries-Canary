::[Bat To Exe Converter]
::
::YAwzoRdxOk+EWAnk
::fBw5plQjdG8=
::YAwzuBVtJxjWCl3EqQJgSA==
::ZR4luwNxJguZRRnk
::Yhs/ulQjdF+5
::cxAkpRVqdFKZSTk=
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
::Zh4grVQjdCyDJGyX8VAjFChVQRGHMFeeA6YX/Ofr0+WEo1kcR+ksNorD39Q=
::YB416Ek+ZW8=
::
::
::978f952a14a936cc963da21a135fa983
@echo off
setlocal

REM Obtém a unidade do Windows
set "SYS_DRIVE=%SystemDrive%"

REM Caminhos
set "COMMON_FILE_DIR_PATH=%SYS_DRIVE%\Program Files\Common Files"
set "PROGRAM_FILE_DIR_PATH=%SYS_DRIVE%\Program Files"
set "DOTNET_PATH=%SYS_DRIVE%\Windows\Microsoft.NET\Framework\\"

REM =========================================================
REM .NET Framework InstallRoot
REM =========================================================

reg query "HKLM\SOFTWARE\Microsoft\.NETFramework" /v "InstallRoot" >nul 2>&1

if errorlevel 1 (
    reg add "HKLM\SOFTWARE\Microsoft\.NETFramework" /v "InstallRoot" /t REG_SZ /d "%DOTNET_PATH%" /f
)

REM =========================================================
REM CommonFilesDir (x86)
REM =========================================================

reg query "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion" /v "CommonFilesDir (x86)" >nul 2>&1

if errorlevel 1 (
    reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion" /v "CommonFilesDir (x86)" /t REG_SZ /d "%COMMON_FILE_DIR_PATH%" /f
)

REM =========================================================
REM ProgramFilesDir (x86)
REM =========================================================

reg query "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion" /v "ProgramFilesDir (x86)" >nul 2>&1

if errorlevel 1 (
    reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion" /v "ProgramFilesDir (x86)" /t REG_SZ /d "%PROGRAM_FILE_DIR_PATH%" /f
)

endlocal
exit /b 0
exit