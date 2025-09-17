"""
y, 2025.9.16
dataclass - basic.py
"""

from typing import Union
from dataclasses import dataclass


@dataclass
class Parameter:

    price: float
    quantity: Union[int, float]


p = Parameter(quantity=1.0, price=2.0)
print(p)
print(f"{p.price=}, {p.quantity=}")
print(f"{vars(p)=}")
q = Parameter(2.0, 1.0)
print(q)
print(f"{p==q=}")
