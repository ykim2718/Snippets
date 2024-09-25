"""
y, 2024.9.24
lambda - recursion.py
"""

a = 1
b = lambda: a
print(f"{b()=}")
a = lambda: a
print(f"{a()=}")
print(f"{b()=}")

"""
b()=1
a()=<function <lambda> at 0x0000023D56F2CCA0>
b()=<function <lambda> at 0x0000023D56F2CCA0>
"""
