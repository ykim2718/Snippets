"""
y, 2020.3.10
gzip - how to gzip compress an existing file.py
https://docs.python.org/3/library/gzip.html
"""

import gzip
import shutil
import pathlib

file_path = pathlib.Path(__file__).with_suffix('.txt')
file_path.write_text('Hello world ...')
with open(file_path, 'rb') as f_in:
    with gzip.open(file_path.with_suffix('.gz'), 'wb') as f_out:
        shutil.copyfileobj(f_in, f_out)
