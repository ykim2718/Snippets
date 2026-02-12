"""
y, 2026.2.11
enum - hybrid.py
source: webull/core/common/easy_enum.py
source: webull/data/common/category.py
"""

from enum import Enum


class EasyEnum(Enum):
    def __str__(self):
        return self.name

    @classmethod
    def from_string(cls, s):
        for item in cls:
            if item.name == s:
                return item
        raise ValueError(cls.__name__ + ' has no value matching ' + s)

    @classmethod
    def from_code(cls, code):
        for member in cls:
            if member.value[0] == code:
                return member
        return None


class Category(EasyEnum):
    US_STOCK = (1, 'US STOCK')
    US_OPTION = (2, 'US OPTION')
    HK_STOCK = (3, 'HK STOCK')
    US_ETF = (5, 'US ETF')
    HK_ETF = (6, 'HK ETF')
    CN_STOCK = (7, "CN STOCK")
    US_CRYPTO = (8, "US CRYPTO")
    US_FUTURES = (12, "US FUTURES")
    US_EVENT = (13, "US EVENT")


print(f"{Category.from_string('US_STOCK')=}")
print(f"{Category.from_code(1)=}")
r = Category.from_string('US_STOCK') == Category.from_code(1)
print(f"Category.from_string('US_STOCK') == Category.from_code(1) = {r}")
print(f"{str(Category.from_code(1))=}")
