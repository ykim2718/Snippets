"""
y, mpl - font names.py, 2019.10.6
"""


import matplotlib.font_manager as fm


names = sorted([(f.name, f.fname) for f in fm.fontManager.ttflist], key=lambda x: x[0])
for name in names:
    print(name)