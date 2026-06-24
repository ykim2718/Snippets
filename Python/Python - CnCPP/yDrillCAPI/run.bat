cls
del *.pyd
set PYTHONPATH="c:\Coding\WinPython-32bit-3.4.3.7Qt5\python-3.4.3"
set PATH=%PYTHONPATH%;%PYTHONPATH%\scripts;c:\windows\system32;c:\windows
python.exe setup(sample).py build_ext --inplace || pause
dir *.pyd | findstr pyd
python -c "import _sample as y; print(dir(y))"
python call_C_ext_module.py
pause