"""
y, 2023.11.10
python try except - raise.py
"""

try:
    raise ConnectionError
except Exception as ex:
    print(f"{ex=}")