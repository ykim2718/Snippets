"""
y, 2022.5.28
python dict - update bug.py
"""

k = 2

if False:
    d = {}
    for j in range(k):
        d.update({j: lambda x: f"<{j}>{x:.1f}"})
else:
    d = {j: lambda x: f"<{j}>{x:.1f}" for j in range(k)}

for j, f in enumerate(d.values()):
    print(f"{j=}, {f(j)=}")

print(d[0](1))
print(d[1](2))

"""
j=0, f(j)='<0>0.0'
j=1, f(j)='<1>1.0'
<1>1.0  <<< BUG
<1>2.0
"""

print('- ' * 16)
d = {
    0: lambda x: f"<0>{x:.1f}",
    1: lambda x: f"<1>{x:.1f}",
}

print(d[0](1))
print(d[1](2))
"""
<0>1.0  <<< GOOD
<1>2.0
"""

print('- ' * 16)
d = [lambda x: f"<{j}>{x:.1f}" for j in range(k)]

print(d[0](1))
print(d[1](2))

"""
<1>1.0  <<< BUG
<1>2.0
"""


print('- ' * 16)
import functools
d = [functools.partial(lambda x, j: f"<{j}>{x:.1f}", j=j) for j in range(k)]

print(d[0](1))
print(d[1](2))

"""
<1>1.0  <<< GOOD
<1>2.0
"""

