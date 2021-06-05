"""
y, 2020.12.7
python try except - except Exception Vs else.py
"""


print('- case 1 -' + '-' * 8)
try:
    2/0
except Exception as ex:
    print('Exception')
except ZeroDivisionError:
    print('ZeroDivisionError')
else:
    print('else')

print('- case 2 -' + '-' * 8)
try:
    2/0
except ZeroDivisionError:
    print('ZeroDivisionError')
except Exception as ex:
    print('Exception')
else:
    print('else')

print('- case 3 -' + '-' * 8)
try:
    2/0
except KeyError as ex:
    print('KeyError')
except Exception as ex:
    print('Exception')
    # raise ex
else:
    print('else')

print('- case 4 -' + '-' * 8)
try:
    2/0
except KeyError as ex:
    print('KeyError')
else:
    print('else')

