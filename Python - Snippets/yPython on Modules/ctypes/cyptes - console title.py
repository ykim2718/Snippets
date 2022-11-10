"""
y, 2022.11.10
cyptes - console title.py
https://stackoverflow.com/questions/387276/set-windows-command-line-terminal-title-in-python
"""

import ctypes

ctypes.windll.kernel32.SetConsoleTitleW(__file__)