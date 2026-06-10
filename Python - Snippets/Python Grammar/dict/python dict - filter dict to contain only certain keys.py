"""
y, python dict - filter dict to contain only certain keys.py, 2018.9.2
"""

sample = dict(a=1, b=2, c=3, d=4, e=5)
filters = ['a', 'b', 'f']
filtered = {key: sample[key] for key in sample.keys() if key in filters}
print(filtered)