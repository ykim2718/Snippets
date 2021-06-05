"""
y, 2020.1.14
hands-on recurrence plot.py
https://m.blog.naver.com/rkdwnsdud555/221381428891
https://laszukdawid.com/tag/recurrence-plot/
"""

import pylab as plt
import numpy as np


def rec_plot(s, eps=0.01, steps=10):
    # S = np.repeat(s[None, :], s.size, axis=0)
    S = np.repeat(s[np.newaxis, :], s.size, axis=0)
    Z = np.floor(np.abs(S - S.T) / eps)
    Z[Z > steps] = steps
    return Z


s = np.random.random(1000)
image = rec_plot(s)
plt.imshow(image)
plt.show()
