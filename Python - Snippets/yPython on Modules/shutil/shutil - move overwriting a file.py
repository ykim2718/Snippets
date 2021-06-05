"""
y, shutil - move overwriting a file.py, 2018.9.9
"""

import os
import shutil

temp_folder_path = r'.\temp'
if os.path.isdir(temp_folder_path) is False:
    os.mkdir(temp_folder_path)

a_file = 'test.txt'

for j in range(2):
    f = open(r".\%s" % a_file, 'w')
    f.write('hello shutil ..')
    f.close()
    # shutil.move(a_file, temp_folder_path)  # raise an exception: already exists ...
    shutil.move(a_file, os.path.join(temp_folder_path, a_file))  # do not get an exception raised: already exits ...


