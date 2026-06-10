"""
y, Python - how to track the number of times a function is called.py, 2017.8.30

https://stackoverflow.com/questions/21716940/is-there-a-way-to-track-the-number-of-times-a-function-is-called

"""

def f1(counter=[0]):
    counter[0] += 1
    print(counter)

f1()
f1()
f1()