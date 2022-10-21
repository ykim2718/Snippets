"""
y, 2022.10.19
ctypes - messagebox.py
https://docs.python.org/ko/3/library/ctypes.html
"""

from ctypes import c_int, WINFUNCTYPE, windll
from ctypes.wintypes import HWND, LPCWSTR, UINT

prototype = WINFUNCTYPE(c_int, HWND, LPCWSTR, LPCWSTR, UINT)
paramflags = (1, "hwnd", 0), (1, "text", "Hi"), (1, "caption", "Hello from ctypes"), (1, "flags", 0)
MessageBox = prototype(("MessageBoxW", windll.user32), paramflags)

# MessageBox()
# MessageBox(text="Spam, spam, spam")
MessageBox(flags=2, text="foo bar")
