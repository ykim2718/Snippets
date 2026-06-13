:: y, 2017.5.24
:: Can a Windows batch file determine its own file name?
:: https://stackoverflow.com/questions/8797983/can-a-windows-batch-file-determine-its-own-file-name
:: Microsoft DOS call command
:: https://www.computerhope.com/call.htm
:: DOS Batch - Function Tutorial
:: http://www.dostips.com/DtTutoFunctions.php

@echo off

echo cwd = %cd%
echo file full path = %~dp0
echo hostname = %computername%

@echo Full path and filename: %~f0
@echo Drive: %~d0
@echo Path: %~p0
@echo Drive and path: %~dp0
@echo Filename without extension: %~n0
@echo Filename with    extension: %~nx0
@echo Extension: %~x0
@echo Filename as given on command line: %0
@echo Filename as given on command line minus quotes: %~0


pause