@echo off
for %%t in ('a', 'bb', ccc) do (
    echo token=%%t
    for %%k in (1 2 3) do (
       echo %%t%%k
    )
)
pause