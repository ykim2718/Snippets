"""
y, 2025.9.15
python annotation - typing Literal.py
"""

from typing import Literal, List

Weekend = Literal["토요일", "일요일"]
Week = Literal["월요일", "화요일", "수요일", "목요일", "금요일", "토요일", "일요일"]
print(f"{Week.__args__=}")  # tuple

list_of_weekdays: List[Week] = ["월요일", "수요일", "금요일"]
print(f"{list_of_weekdays=} {type(list_of_weekdays)}")