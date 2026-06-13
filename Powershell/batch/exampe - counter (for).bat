@echo off

rem Counting in a FOR loop using Windows Batch script
rem http://stackoverflow.com/questions/7522740/counting-in-a-for-loop-using-windows-batch-script

setlocal enableextensions enabledelayedexpansion

set count=0

for %%d in (0 1 2) do (
   echo !count!
   set /a count+=1
)

pause