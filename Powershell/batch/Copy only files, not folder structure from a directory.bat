:: https://www.petri.com/forums/forum/windows-scripting/general-scripting/25394-copy-only-files-not-folder-structure-from-a-directory

@echo off
title WAIT !

Set "sourceDir=c:\1234"
Set "destinationFolder=c:\SHOEBOX"
Set "_report=c:\logxcopy.txt"

IF NOT EXIST "%sourceDir%" (echo.Could not find %sourceDir% &GoTo:done)

:: overwrite previous log
>"%_report%" (
      echo.%date% - %time%
      echo.---------------------------------------------------
      echo.
)

:: copy files
For /F "Delims=" %%! in ('Dir "%sourceDir%\" /b /s /a-d 2^>nul') do (
   @echo.%%! &(
   @xcopy "%%!" "%destinationFolder%\" /i /y /h /f /c >>"%_report%",2>&1)
)

:done
title,Done.......

echo.&pause>nul