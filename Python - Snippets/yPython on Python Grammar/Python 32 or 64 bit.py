import ctypes

Python32or64bit = ctypes.sizeof(ctypes.c_voidp) * 8
print("Python shell executing in ", Python32or64bit, "bit mode...")
