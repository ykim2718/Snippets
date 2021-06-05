"""
y, python try except - my exception.py, 2018.9.14
"""

class MyException(Exception):
    def __init__(self, *args, **kwargs):
        Exception.__init__(self, *args, **kwargs)


try:
    raise MyException('details here ..')
except Exception as ex:
# except MyException as ex:
    print(ex.__class__.__name__, ':', str(ex))


