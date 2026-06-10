"""
y, 2020.9.6
tempfile - basic.py
"""

import tempfile
import pathlib

f = tempfile.NamedTemporaryFile(suffix='.txt', delete=False)
f.close()
print(f"f.name={f.name}")
f_path = pathlib.Path(f.name)
f_path.write_text('written by pathlib.Path().write_text()')
f_path.unlink()
