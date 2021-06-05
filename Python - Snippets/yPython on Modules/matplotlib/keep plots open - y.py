"""
y (copyRight) 2016.5.6
inspired by code snippets below
http://stackoverflow.com/questions/458209/is-there-a-way-to-detach-matplotlib-plots-so-that-the-computation-can-continue
"""

import matplotlib.pyplot as plt

if __name__ == '__main__':
    plt.figure('a')
    plt.plot(list(range(5)), list(range(5)))
    plt.draw()

    plt.figure('b')
    plt.plot(list(range(5)), list(reversed(range(5))))
    plt.draw()

    plt.show()
