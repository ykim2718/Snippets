@echo on
:: y, ~ 2017.7.15, 7.19, 8.5, 8.6, 8.15 - 16; 2019.11.23, 12.14

title %~0
set log_file=%~n0.log
if exist "%log_file%" (del "%log_file%")
:: if exist \\MYPC\d (set target=\\MYPC\d)
:: if exist \\192.168.0.13\d (set target=\\192.168.0.13\d)
set target=x:
echo target="%target%"
if not exist %target% (pause)
robocopy "d:\Wolf\Homo academicus\yStudy on code - Python" ^
         "%target%\wolf\Homo academicus\yStudy on code - Python" ^
         /E /XJD /MIR /LOG+:"%log_file%" ^
         /XD .git .idea .vscode
robocopy "d:\Wolf\Homo academicus\yStudy on code - Database" ^
         "%target%\wolf\Homo academicus\yStudy on code - Database" ^
         /E /XJD /MIR /LOG+:"%log_file%" ^
         /XD .git .idea .vscode
robocopy "d:\Wolf\Homo academicus\yStudy on code - Powershell" ^
         "%target%\wolf\Homo academicus\yStudy on code - Powershell" ^
         /E /XJD /MIR /LOG+:"%log_file%" ^
         /XD .git .idea .vscode
timeout 10
