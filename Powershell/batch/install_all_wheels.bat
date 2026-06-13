@echo off
:: 2018.6.25

title %~0
pip install --no-index --find-links=. "msgpack-0.5.6-cp36-cp36m-win_amd64.whl"
for /r %%f in (*.whl) do (
    echo.
    echo ^<%%f^>
    pip install --no-index --find-links=. "%%f"
)
pause
timeout 9