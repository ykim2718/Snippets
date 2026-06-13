@echo off
rem 2017-2-5
rem https://www.windows-commandline.com/get-date-time-batch-file/

for /F "tokens=2" %%i in ('date /t') do set mydate=%%i
set mytime=%time%
echo Current time is %mydate%:%mytime%

pause