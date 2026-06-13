@echo off

:: Created by: Shawn Brink
:: Created on: May 23rd 2017
:: Tutorial: https://www.tenforums.com/tutorials/5313-hide-show-notification-area-icons-taskbar-windows-10-a.html


REG ADD "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced" /V UseTabletModeNotificationIcons /T REG_DWORD /D 0 /F

:: To kill and restart explorer
taskkill /f /im explorer.exe
start explorer.exe