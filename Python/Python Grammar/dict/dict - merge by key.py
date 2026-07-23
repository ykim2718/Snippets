"""
y, 2026.7.22
dict - merge by key.py
"""

common = dict(a=1, b=2)
data = {
    "A": {'A.a': 'a'},
    "B": {'B.b': 'b'},
}

key = 'B'
merged = {**common, **data[key]}
print(merged)