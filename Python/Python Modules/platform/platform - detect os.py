"""
y, platform - detect os.py, 2018.8.30
"""

import platform

r = platform.architecture()
print(r, r[0].startswith('32'), r[0].startswith('64'))
r = platform.machine()
print(r)
