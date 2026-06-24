cls
del *.pyd
set SWIGPATH="c:\Coding\swigwin-3.0.8"
set path=%SWIGPATH%
swig.exe -python -debug-tmsearch example.i || pause
set PYTHONPATH="c:\Coding\WinPython-32bit-3.4.3.7Qt5\python-3.4.3"
set PATH=%PYTHONPATH%;%PYTHONPATH%\scripts;c:\windows\system32;c:\windows
python.exe setup(yDrillSWIG3).py build_ext --inplace || pause
dir *.pyd | findstr pyd
python -c "import yDrillSWIG3 as y; print(dir(y))"
python call_yDrillSWIG3.py
pause
