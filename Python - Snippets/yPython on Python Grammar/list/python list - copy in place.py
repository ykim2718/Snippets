"""
y, 2022.5.11
python list - copy in place.py
"""

a = []
print(f"{id(a)=}, {a=}")
b = [1, 2, 3]
a[:] = b
print(f"{id(a)=}, {a=}")
a = b
print(f"{id(a)=}, {a=}")

a.append(4)
print(f"{id(a)=}, {a=}")

"""
id(a)=1558839573056, a=[]
id(a)=1558839573056, a=[1, 2, 3]
id(a)=1558839586432, a=[1, 2, 3]
id(a)=1558839586432, a=[1, 2, 3, 4]
"""
