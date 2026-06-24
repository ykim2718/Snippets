cls
del *.pyd
set SWIGPATH="c:\Coding\swigwin-3.0.8"
set path=%SWIGPATH%
swig.exe -python -debug-tmsearch yswig4.i || pause
set PYTHONPATH="c:\Coding\WinPython-32bit-3.4.3.7Qt5\python-3.4.3"
set PATH=%PYTHONPATH%;%PYTHONPATH%\scripts;c:\windows\system32;c:\windows
python.exe setup(yDrillSWIG4).py build_ext --inplace || pause
dir *.pyd | findstr pyd
python -c "import yDrillSWIG4 as y; print(dir(y))"
python call_yDrillSWIG4.py
pause
