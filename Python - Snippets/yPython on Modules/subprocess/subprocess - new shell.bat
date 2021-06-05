@echo off
rem echo %1 %2
rem ping 127.0.0.1 -w 1000 -n 3 > null
c:\windows\system32\timeout 3  > nul 2>&1
echo %2 ^>^> %ZZ%