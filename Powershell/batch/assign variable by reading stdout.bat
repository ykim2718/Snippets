@echo off
:: y, 2019.3.21
:: https://stackoverflow.com/questions/6359820/how-to-set-commands-output-as-a-variable-in-a-batch-file

FOR /F "tokens=*" %g IN ('where python.exe') do (SET python_path=%g)
echo $python_path%

pause
