"""
y, 2025.9.11 (Austin)
dataclass - basic.py
"""

from dataclasses import dataclass


@dataclass
class User:
    id: int
    name: str
    is_admin: bool = False


u1 = User(1, "Alice")
u2 = User(1, "Alice")
print(u1 == u2)  # True
print(u1)  # User(id=1, name='Alice', is_admin=False)
