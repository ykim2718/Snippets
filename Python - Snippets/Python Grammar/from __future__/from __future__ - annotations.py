"""
y, 2025.10.20
from __future__ - annotations.py
"""

from __future__ import annotations  # In Python 3.14 the annotation expression evaluation is deferred.
# avoid "NameError: name 'Node' is not defined. Did you mean: 'None'?"


class Node:
    def __init__(self, value: int, next: Node):  # forward reference
        self.value = value
        self.next = next


def process(node: Node):
    pass
