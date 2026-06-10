"""
y, 2016.5.15
https://wiki.python.org/moin/UsingPickle
"""
import pickle


# import cPickle as pickle


class Test:
    A = []  # a class attribute

    def __init__(self):
        self.a = []  # an instance attribute

    def print(self):
        print(self.a)


x = Test()
for i in range(5):
    x.A.append(i)
    x.a.append(i)

file = __file__[:-3] + '.pickle'

with open(file, 'wb') as f:
    pickle.dump(x, f)

with open(file, 'rb') as f:
    y = pickle.load(f)

print(y.A, y.print)
print(Test.A, Test.print)
