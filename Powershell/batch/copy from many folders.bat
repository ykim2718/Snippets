@echo off
:: y, 2018.1.1

title,WAIT !!

set source_folder=\\Y20170707\d\Wolf\Homo academicus\yData of Finance\yFinImprove

IF NOT EXIST "%source_folder%" (echo Could not find %source_folder% &GoTo:done)

setlocal enabledelayedexpansion
for %%y in (
    2000 2001 2002 2003 2004 2005 2006 2007 2008 2009
    2010 2011 2012 2013 2014 2015 2016
) do (
    @echo %source_folder%\%%y
    if not exist %%y (mkdir %%y)
    set path_pattern=%source_folder%\%%y\*
    for /f "delims=" %%f in ('dir /a:a /b "!path_pattern!"') do (
        copy "%source_folder%\%%y\%%f" %%y
    )
)

:done
title,Done.......

pause
