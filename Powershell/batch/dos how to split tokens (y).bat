:: y, 2017.5.21
@echo off

setlocal enableextensions enabledelayedexpansion
set index=1
for %%t in (
   "key=a, run=b1/c1 d"
   "key=a2, run=b2 ccc2 d:d\d"
) do (
   echo index=!index!, line=%%t
   for /f "tokens=2,4 delims=,=" %%a in (%%t) do (
      echo k=%%a, r=%%b
   )
   set /a index+=1 
)