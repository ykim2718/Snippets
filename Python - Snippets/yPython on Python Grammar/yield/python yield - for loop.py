"""
y, 2021.2.4, 5.15
python yield - for loop.py
"""


def my_numbers():
    for j in range(4):
        yield j
    print('end')


for k in my_numbers():
    print(k)
