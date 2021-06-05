"""
y, 2020.4.9
tempfile - application folder.py
https://stackoverflow.com/questions/13184414/how-can-i-get-the-path-to-the-appdata-directory-in-python
"""

import tempfile
import os
import pathlib

tempfile.gettempdir()
folder_name = 'my_folder'
folder_path = os.path.expandvars(rf"%LOCALAPPDATA%\\{folder_name}")
folder_path = pathlib.Path(folder_path)
print(folder_path)
folder_path.mkdir(parents=True, exist_ok=True)
