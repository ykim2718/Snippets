"""
y, 2020.11.30
python - inner or nested.py
https://www.datacamp.com/community/tutorials/inner-classes-python
"""


class Outer:
    x = 1

    class Inner:
        x = 2

    def __init__(self):
        self._inner = self.Inner()


a = Outer()
a.x *= 10
# a.Inner.x *= 10
a._inner.x *= 10
print(f"a.x={a.x}, a.Inner.x={a.Inner.x}, a._inner.x={a._inner.x}")

b = Outer()
print(f"b.x={b.x}, b.Inner.x={b.Inner.x}, b._inner.x={b._inner.x}")
print(Outer.Inner)
