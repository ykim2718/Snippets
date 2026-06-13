@echo off
:: y, 2017.9.28
:: https://technet.microsoft.com/en-us/library/bb490909.aspx
:: https://stackoverflow.com/questions/138497/iterate-all-files-in-a-directory-using-for-a-loop

title %~0
for /D %%d in (.\*) do (
    cls
    echo %%d
    pushd %%d
    python setup.py install
    popd
)
timeout 9