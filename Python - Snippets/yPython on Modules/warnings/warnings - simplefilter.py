"""
y, warnings - simplefilter.py, 2017.8.18

https://docs.python.org/2/library/warning.html#the-warnings-filter

"""

import warnings

warnings.warn('warning ... 1')
warnings.simplefilter('ignore')
warnings.warn('warning ... 2')
# warnings.simplefilter('always')
warnings.simplefilter('module')
warnings.warn('warning ... 3')
