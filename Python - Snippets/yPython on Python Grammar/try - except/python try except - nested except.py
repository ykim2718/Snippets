"""
y, 2020.3.14, 3.29
python try except - nested.py
"""

try:
    try:
        print('0/0')
        0/0
    except:
        print('1/0')
        1/0
except:
    try:
        print('except')
        2/0
    except:
        3/0
    # 4/0
else:
    print('else')
finally:
    print('finally')
