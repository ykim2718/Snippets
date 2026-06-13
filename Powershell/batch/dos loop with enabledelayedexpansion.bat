@echo off

setlocal enabledelayedexpansion
for %%t in ('a', 'bb', 
 ccc) do (
    set token=%%t
    echo token=!token!
)
pause