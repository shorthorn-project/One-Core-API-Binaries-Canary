IF EXIST SchTasks /QUERY /TN "Root Certificate Update"  ( 
    GOTO NEXT 
) ELSE IF NOT EXIST SCHTASKS /CREATE /SC MONTHLY /TN "Root Certificate Update" /TR "C:\Windows\System32\certupdate.exe /Y /C /Q"
