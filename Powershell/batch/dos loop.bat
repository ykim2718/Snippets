@echo off
for %%t in ('a', 'bb',
 ccc) do (
    echo token=%%t
)
pause