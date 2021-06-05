import pandas as pd
import os
import sys
# sys.setdefaultencoding('utf-8')

"""
import locale

print("LOCALE %s.%s" % locale.getlocale())
locale.setlocale(category=locale.LC_ALL, locale="Korean")
print("LOCALE %s.%s" % locale.getlocale())
"""

file = "d:\늑대\Homo academicus\yStudy on code - Python\Python - Y\yEvalPandas\sample.csv"
# file = file.encode(sys.getfilesystemencoding())
# file = os.path.decode('utf8')

"""
b = bytearray()
b.extend(file.encode())
file = b.decode('utf-8')
print(file)
"""

print('os.path.exists() =', os.path.exists(file))

with open(file, 'r') as f:
    f.seek(0, os.SEEK_END)
    size = f.tell()
    print('file size =', size)


import platform

if platform.system() == 'Windows' and platform.release() == '10':
   df = pd.read_csv(file, engine='python')  # ok
   print('with python engine', df.shape)
else:
   df = pd.read_csv(file, engine='c')  # looks like a bug in matching python with windows 10
   print('with c engine', df.shape)

df = pd.read_csv(file)  # looks like a bug in matching python with windows 10
print('with c engine', df.shape)

