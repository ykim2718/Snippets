"""
y, urllib.parse - urlparse.py, 2018.5.16
https://docs.python.org/3/library/urllib.parse.html
"""

from urllib.parse import urlparse

url = 'http://www.cwi.nl:80/%7Eguido/Python.html'
o = urlparse(url)
print(o)
print(type(o))

o = urlparse('asdef')
print(o)
