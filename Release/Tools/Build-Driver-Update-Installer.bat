@echo off

cls

if "%arch%" == "" (
	call choose-arch.bat
	call setenv.bat
)

%ProjectDir%\Release\Tools\SFXCAB.exe "%output%\%driver-update-exe%" "%root%\%driver-update%" -r:update/update.exe -ipd -iswu

ECHO Done!

timeout /T 3>nul

cls