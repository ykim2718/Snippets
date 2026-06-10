"""
y, 2025.4.26
python Literal - dynamic Literal.py
"""

from typing import Literal
from typing_extensions import get_args

# Example: Your string array
string_array = ["apple", "banana", "cherry"]

# Convert the array to a Literal type using unpacking
# MyLiteral = Literal[string_array]  # Dynamically define Literal
MyLiteral = Literal[tuple(string_array)]  # Dynamically define Literal
print(f"{MyLiteral=}")  # typing.Literal['apple', 'banana', 'cherry']


# Example usage
def fruit_choice(fruit: MyLiteral) -> str:
    return f"You chose: {fruit}"


print(fruit_choice('apple'))
