"""
y,  2025.4.26
python Literal - convert to array.py
"""

from typing import Literal
from typing_extensions import get_args

# Define a Literal type
MyLiteral = Literal["apple", "banana", "cherry"]

# Convert Literal to array
string_array = list(get_args(MyLiteral))

# Example usage
print(string_array)  # Output: ['apple', 'banana', 'cherry']
