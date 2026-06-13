:: y, 2019.12.15
:: https://stackoverflow.com/questions/659647/how-to-get-folder-path-from-file-path-with-cmd/659672

@echo off
setlocal enabledelayedexpansion enableextensions

set myPath=C:\Somewhere\Somewhere\SomeFile.txt
call :file_name_from_path result !myPath!
echo %result%
goto :eof

:file_name_from_path <resultVar> <pathVar>
(
    set "%~1=%~nx2"
    exit /b
)

:eof
endlocal