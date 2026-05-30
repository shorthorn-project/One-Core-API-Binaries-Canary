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
::Zh4grVQjdCqDJG6N+kY/PwgUbwuMOmK+A7sI4en309iCskIOXfacq53S1Yi5Ke4X5VL3NaUowm9KpP8DAxdLQhWuYAomqGJLrGGuMtWStgPJS0SRsB9+Hn1x5w==
::YB416Ek+ZG8=
::
::
::978f952a14a936cc963da21a135fa983

	@ECHO OFF

	if exist "%windir%\Driver Cache\amd64\sp1.cab" (
		SET mainCab=sp1.cab
	)
	
	if exist "%windir%\Driver Cache\amd64\sp2.cab" (
		SET mainCab=sp2.cab
	)

	if exist "%windir%\Driver Cache\amd64\sp3.cab" (
		SET mainCab=sp3.cab
	)
	
	if exist "%windir%\Driver Cache\amd64\sp4.cab" (
		SET mainCab=sp4.cab
	)	

	if "%mainCab%" == "" (
		SET mainCab=driver.cab
	)		

	if not exist "%windir%\Driver Cache\amd64\hal.dll" (	
		cmd.exe /C expand "%windir%\Driver Cache\amd64\%mainCab%" -F:hal.dll "%windir%\Driver Cache\amd64" 
	)
	cmd.exe /C copy /y "%windir%\Driver Cache\i386\halmacpi.dll" "%windir%\system32"
	cmd.exe /C copy /y "%windir%\Driver Cache\i386\halmacpi.dll" "%windir%\system32\hal.dll"
	
	if not exist "%windir%\Driver Cache\amd64\ntkrnlmp.exe" (
		cmd.exe /C expand "%windir%\Driver Cache\amd64\%mainCab%" -F:ntkrnlmp.exe "%windir%\Driver Cache\amd64" 
	)	
	cmd.exe /C copy /y "%windir%\Driver Cache\amd64\ntkrnlmp.exe" "%windir%\system32"
	cmd.exe /C copy /y "%windir%\System32\ntkrnlmp.exe" "%windir%\system32\ntoskrnl.exe"
	
	
	if not exist "%windir%\Driver Cache\amd64\ntoskrnl.exe" (
		cmd.exe /C expand "%windir%\Driver Cache\amd64\%mainCab%" -F:ntoskrnl.exe "%windir%\Driver Cache\amd64" 
	)	
	cmd.exe /C copy /y "%windir%\Driver Cache\amd64\ntoskrnl.exe" "%windir%\system32\ntkrnlup.exe"
