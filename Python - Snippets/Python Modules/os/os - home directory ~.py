"""
y, os - home directory ~.py,  2019.10.5
"""


import os


home_directory = os.path.expanduser('~')
print('home_directory=', home_directory)

print('HOME=', os.environ.get('HOME', None))
# print('HOMEDRIVE=', os.environ['HOMEDRIVE'])
# print('HOMEPATH=', os.environ['HOMEPATH'])

cwd = os.getcwd()
print('cwd=', cwd)

# drive, path = os.path.splitdrive(cwd)
# print('drive=', drive)
# print('path=', path)
# os.environ['HOMEDRIVE'] = drive
# os.environ['HOMEPATH'] = path
os.environ['HOME'] = cwd

home_directory = os.path.expanduser('~')
print('home_directory=', home_directory)
