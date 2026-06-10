"""
http://stackoverflow.com/questions/15114843/accessing-dictionary-value-by-index-in-python
"""

d = {'a': 1, 'b': 2, 'c': 3, 'd': 4}
value = next(v for i, v in enumerate(d.itervalues()) if i == index)  # much faster
value = d.values()[index]
