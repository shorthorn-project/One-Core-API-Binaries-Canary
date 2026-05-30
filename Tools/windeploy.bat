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
::YxY4rhs+aU+IeA==
::cxY6rQJ7JhzQF1fEqQJlZEkYH1PbbCfrUOZFuIg=
::ZQ05rAF9IBncCkqN+0xwdVsBAFbObzzjVvlNvruiv4o=
::ZQ05rAF9IAHYFVzEqQIdIRhGQxeNOn+GHpQ5qN/y4e6ItV4hTMMaOKDL36aPNOkd7QXXbIU503c6
::eg0/rx1wNQPfEVWB+kM9LVsJDDOLMk+/FrkT8ab+9+/n
::fBEirQZwNQPfEVWB+kM9LVsJDDOLMk+/FrkT8Yg=
::cRolqwZ3JBvQF1fEqQIHIRVQQxORfG+/FrkT8eX+4f7HrkIcUOctGA==
::dhA7uBVwLU+EWHSN91A/OxRSWEShM3mqCacd/OH04Yo=
::YQ03rBFzNR3SWATElA==
::dhAmsQZ3MwfNWATEyFoRcVt5RQeQM3i1AKFcy+fp/+WVo1kUW+xxOK7X1vScKecb/lakZ5M+02hMnc9s
::ZQ0/vhVqMQ3MEVWAtB9wSA==
::Zg8zqx1/OA3MEVWAtB9wSA==
::dhA7pRFwIByZRRnk
::Zh4grVQjdCqDJG6N+kY/PwgUbwuMOmK+A7sI4en309iCskIOXfacq53S1Yi5Ke4X5VL3NaUowm9KpP8DAxdLQgWiYAsxuWJNryqAL8L8
::YB416Ek+ZG8=
::
::
::978f952a14a936cc963da21a135fa983
reg add "HKLM\SYSTEM\Setup" /v "SystemSetupInProgress" /t REG_DWORD /d "0" /f >nul
reg add "HKLM\SYSTEM\Setup" /v "OobeInProgress" /t REG_DWORD /d "0" /f >nul

timeout 3 > nul

for /f "tokens=2 delims==" %%d in ('wmic logicaldisk where "size<=1048535040 and drivetype=3" get name /format:value') do bootice /DEVICE=%%d /partitions /delete_letter

%Systemroot%\System32\oobe\setupdeploy.exe

del /q /s /f %Systemdrive%\$WINDOWS.~BT
del /q /s /f %Systemdrive%\$WINDOWS.~LS
rmdir /q /s %Systemdrive%\$WINDOWS.~BT
rmdir /q /s %Systemdrive%\$WINDOWS.~LS
del /q /a /s /f %Systemdrive%\WinPEpge.sys
del /q /a /s /f %Systemdrive%\$bootdrive$
del /q /a /s /f %Systemdrive%\$DRVLTR$
del /q /a /s /f %Systemdrive%\$dwnlvldrive$
del /q /a /s /f %Systemdrive%\$installdrive$
del /q /a /s /f %Systemdrive%\$lsdrive$
del /q /a /s /f %Systemdrive%\BOOT.BAK
del /q /a /s /f %Systemdrive%\BOOTSECT.BAK

bcdedit /set {default} detecthal false
bcdedit /delete {cbd971bf-b7b8-4885-951a-fa03044f5d71}
bcdedit /timeout 30

REM Obtém o valor da chave do registro
for /f "tokens=3" %%a in ('reg query "HKEY_LOCAL_MACHINE\System\ControlSet001\Control\ProductOptions" /v ProductType 2^>nul') do (
    set ProductType=%%a
)

REM Remove espaços em branco ao redor do valor
set ProductType=%ProductType: =%

REM Compara o valor obtido com "ServerNT"
if "%ProductType%"=="WinNT" (
	reg add "HKLM\SYSTEM\Setup" /v "OobeInProgress" /t REG_DWORD /d "1" /f >nul
	reg add "HKLM\SYSTEM\Setup" /v "SetupType" /t REG_DWORD /d "2" /f >nul
	reg add "HKLM\SYSTEM\Setup" /v "CmdLine" /t REG_SZ /d "%SystemRoot%\System32\oobe\msoobe.exe /f /retail" /f >nul
)