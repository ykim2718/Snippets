:: y, 2017.5.21

:: How to split a string in a Windows batch file?
:: http://stackoverflow.com/questions/1707058/how-to-split-a-string-in-a-windows-batch-file
set a=AAA BBB CCC DDD EEE FFF
set a=%a:~6,3%

:: Windows Batch File - Split String With String As Delimiter
:: http://stackoverflow.com/questions/23600775/windows-batch-file-split-string-with-string-as-delimiter
for /f "tokens=1,3 delims=," %%a in ("AA, BB B ,C") do (
   echo %%a %%b
)

:: Windows batch file - splitting a string to set variables
:: http://stackoverflow.com/questions/18820913/windows-batch-file-splitting-a-string-to-set-variables
set SERVER_HOST_PORT=10.0.2.15:8080
set SERVER_HOST_PORT=%SERVER_HOST_PORT::=,%
for /F "tokens=1* delims=," %%a in ("%SERVER_HOST_PORT%") do (
   set SERVER_HOST=%%a
   set SERVER_PORT=%%b
)
echo SERVER_HOST=%SERVER_HOST%
echo SERVER_PORT=%SERVER_PORT%

:: Windows batch file - splitting a string to set variables
:: http://stackoverflow.com/questions/18820913/windows-batch-file-splitting-a-string-to-set-variables
set MYSTRING=USER=Andy,IP=1.2.3.4,HOSTNAME=foobar,PORT=1234
setlocal EnableDelayedExpansion
set varName=
for %%a in (%MYSTRING%) do (
   if not defined varName (
      set varName=%%a
   ) else (
      set !varName!=%%a
      set varName=
   )
)
echo USER=%USER%, IP=%IP%, HOSTNAME=%HOSTNAME%, PORT=%PORT%