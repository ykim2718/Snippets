"""
y, 2021.1.20
context - class.py
"""


class Klass:

    def __init__(self, name):
        self._name = name

    def __enter__(self):
        pass

    def __exit__(self, exc_type, exc_val, exc_tb):
        if exc_type:
            print(f"{self._name} .. exited with error")
            return False
        else:
            print(f"{self._name} .. exited successfully")


with Klass('my_context_1') as k:
    pass

with Klass('my_context_2') as k:
    0/0
