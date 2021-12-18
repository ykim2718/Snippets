"""
y, python - check iterable.py, 2017.8.19

https://stackoverflow.com/questions/4668621/how-to-check-if-an-object-is-iterable-in-python

"""

def isiterable(p_object):

    try:
        it = iter(p_object)
    except TypeError:
        return False
    return True

print(isiterable(range(1, 2, 1)))
