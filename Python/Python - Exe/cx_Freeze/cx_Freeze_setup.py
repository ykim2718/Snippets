# -*- coding: utf-8 -*-
"""
Created on Tue Mar  8 00:51:28 2016

@author: user
"""

from cx_Freeze import setup, Executable

setup(name='Name here',
      version='0.1',
      description='Description here',
      executables=[Executable(r"..\say_hello.py")])
