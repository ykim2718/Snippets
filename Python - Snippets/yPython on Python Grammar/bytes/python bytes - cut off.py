"""
y, 2020.7.26
python bytes - cut off.py
"""

a = b'Hello bytes ...'
for j in reversed(range(len(a))):
    print(a)
    a = a[:j]