cls
rmdir dist /s /q
set PYTHONPATH="c:\Coding\WinPython-32bit-3.4.3.7Qt5\python-3.4.3"
set PATH=%PYTHONPATH%;%PYTHONPATH%\scripts;c:\windows\system32;c:\windows
python py2exe_setup.py py2exe
pause