# -*- coding: utf-8 -*-
"""
Created on Sat Nov 22 11:14:57 2014

@author: Y
"""

import re

my_str = 'A B=C " D" '"E"' F '
result = re.findall(r'(\w+|".*?")', my_str)
print(result)

import shlex

result = shlex.split(my_str)
print(result)
