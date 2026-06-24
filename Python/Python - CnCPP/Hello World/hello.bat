cls
del *.pyd
set SWIGPATH="c:\Coding\swigwin-3.0.8"
set path=%SWIGPATH%
swig.exe -python hello.i
set PYTHONPATH="c:\Coding\WinPython-32bit-3.4.3.7Qt5\python-3.4.3"
set PATH=%PYTHONPATH%;%PYTHONPATH%\scripts;c:\windows\system32;c:\windows
python.exe setup(hello).py build_ext --inplace
dir *.pyd | findstr pyd
python -c "import hello as y; print(dir(y))"
pause