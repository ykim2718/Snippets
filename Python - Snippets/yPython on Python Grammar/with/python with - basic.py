"""
y, 2022.2.22
python with - basic.py
"""


class Klass:
    def __init__(self, value):
        self.value = value

    def __enter__(self):
        print('enter')
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        print('exit')


with Klass(999) as k:
    print(f"{k.value=}")
