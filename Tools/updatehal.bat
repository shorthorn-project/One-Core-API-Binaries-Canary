::[Bat To Exe Converter]
::
::YAwzoRdxOk+EWAnk
::fBw5plQjdG8=
::YAwzuBVtJxjWCl3EqQJgSA==
::ZR4luwNxJguZRRnk
::Yhs/ulQjdF+5
::cxAkpRVqdFKZSDk=
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
::Zh4grVQjdCyDJGyX8VAjFChVQRGHMFeeA6YX/Ofr0/+XpkwJUeo+dMHewrHu
::YB416Ek+ZG8=
::
::
::978f952a14a936cc963da21a135fa983
@echo off

SET HAL=
SET FOUND_MESSAGE="1 matching device(s) found."

devcon.exe /find E_ISA_UP | find %FOUND_MESSAGE% && SET HAL=E_ISA_UP
devcon.exe /find ACPIPIC_UP | find %FOUND_MESSAGE% && SET HAL=ACPIPIC_UP
devcon.exe /find ACPIAPIC_UP | find %FOUND_MESSAGE% && SET HAL=ACPIAPIC_UP
devcon.exe /find ACPIAPIC_MP | find %FOUND_MESSAGE% && SET HAL=ACPIAPIC_MP
devcon.exe /find MPS_UP | find %FOUND_MESSAGE% && HAL=MPS_UP
devcon.exe /find MPS_MP | find %FOUND_MESSAGE% && HAL=MPS_MP
IF %HAL% == E_ISA_UP (
	copy "%windir%\Driver Cache\i386\hal.dll" "%windir%\System32\hal.dll"
)
IF %HAL% == ACPIPIC_UP (
	copy "%windir%\Driver Cache\i386\halacpi.dll" "%windir%\System32\hal.dll"
)
IF %HAL% == ACPIAPIC_UP (
	copy "%windir%\Driver Cache\i386\halaacpi.dll" "%windir%\System32\hal.dll"
)
IF %HAL% == MPS_UP (
	copy "%windir%\Driver Cache\i386\halapic.dll" "%windir%\System32\hal.dll"
)
IF %HAL% == ACPIAPIC_MP (
	copy "%windir%\Driver Cache\i386\halmacpi.dll" "%windir%\System32\hal.dll"
)
IF %HAL% == MPS_MP (
	copy "%windir%\Driver Cache\i386\halmps.dll" "%windir%\System32\hal.dll"
)
REM devcon.exe sethwid @ROOT\PCI_HAL\0000 := +%HAL%
REM devcon.exe sethwid @ROOT\ACPI_HAL\0000 := +%HAL%
REM devcon.exe update %windir%\inf\hal.inf %HAL%

exit
