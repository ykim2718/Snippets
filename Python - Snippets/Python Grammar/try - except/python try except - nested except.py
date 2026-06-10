"""
y, 2020.3.14, 3.29; 2025.10.19
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
        print('except and 2/0')
        2/0
    except:
        print('3/0')
        3/0
    # 4/0
else:
    print('else')
finally:
    print('finally')
