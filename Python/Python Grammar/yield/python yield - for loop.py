"""
y, 2021.2.4, 5.15; 2022.7.25
python yield - for loop.py
"""


def my_numbers(k):
    for j in range(k):
        yield j
    print('end')


for k in my_numbers(3):
    print(k)


for j, k in zip(range(2), my_numbers(4)):
    print(j, k)
