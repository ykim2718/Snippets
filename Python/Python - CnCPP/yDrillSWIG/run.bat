cls
del *.pyd
set SWIGPATH="c:\Coding\swigwin-3.0.8"
set path=%SWIGPATH%
swig.exe -python yDrillSWIG.i
set PYTHONPATH="c:\Coding\WinPython-32bit-3.4.3.7Qt5\python-3.4.3"
set PATH=%PYTHONPATH%;%PYTHONPATH%\scripts;c:\windows\system32;c:\windows
python.exe setup(yDrillSWIG).py build_ext --inplace || pause
dir *.pyd | findstr pyd
python -c "import yDrillSWIG as y; print(dir(y))"
python call_yDrillSWIG.py
pause

