:: y, 2017.5.22
:: How to remove trailing and leading whitespace for user-provided input in a batch file?
:: https://stackoverflow.com/questions/3001999/how-to-remove-trailing-and-leading-whitespace-for-user-provided-input-in-a-batch

@ECHO OFF

SET /p NAME=- NAME ? 
ECHO "%NAME%"
CALL :TRIM %NAME%
SET NAME=%TRIMRESULT%
ECHO "%NAME%"

:TRIM
  SET TRIMRESULT=%*
GOTO :EOF

pause