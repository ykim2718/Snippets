"""
y, python dictionary - alternative update.py, 2019.10.5
"""


a = dict(a=1, b=2)
# c = dict(b=20, **a)  # TypeError: type object got multiple values for keyword argument 'b'
c = (a.update(dict(b=20)) or a)
print(c)