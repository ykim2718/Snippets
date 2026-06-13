@echo off
:: 2018.8.18; 2020.2.8

title %~0
set pip=c:\y\Anaconda3_64\Scripts\pip.exe install --no-index --find-links=.
%pip% "pydot-1.4.1-py2.py3-none-any.whl"
%pip% "graphviz-0.13.2-py2.py3-none-any.whl"

pause
timeout 9