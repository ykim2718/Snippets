@echo off

set count=0

:R
echo %count%
set /a count+=1
goto :R

pause