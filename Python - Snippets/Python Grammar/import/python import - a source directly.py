"""
y, python import - a source directly.py, 2018.10.3
https://docs.python.org/3/library/importlib.html
"""

import importlib.util
import sys

file_path = r'.\sa mple.py'
module_name = 'sample'

spec = importlib.util.spec_from_file_location(module_name, file_path)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
# Optional; only necessary if you want to be able to import the module
# by name later.
sys.modules[module_name] = module

module.f()

import sample

print(sample.a)
print(sample.b)
print(sample.c)
print(sample.d)
print(sample.e)
sample.f()
