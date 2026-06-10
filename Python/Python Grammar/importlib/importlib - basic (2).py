"""
y, ~2018.12.25; 2021.10.22
importlib - basic (2).py
"""

import importlib.util
import sys


def load_module_from_file(module_path, module_name):
    spec = importlib.util.spec_from_file_location(module_name, module_path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    sys.modules[module_name] = module


module_path = 'my module.py'
module_name = 'my_module'
load_module_from_file(module_path, module_name)
import my_module


my_module.hello()
