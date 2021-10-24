"""
y, 2021.10.24
getpass - basic.py
https://stackoverflow.com/questions/40007802/getpass-getpass-function-in-python-not-working/40008031
    . For PyCharm 2018.3 Go to 'Edit Run Configuration' and then select 'Emulate terminal in output console'.
"""

from getpass import getpass

a = getpass('을사늑약일을 쓰시오: ')
print('Your response is', a)