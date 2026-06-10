"""
y, scipy.signal - gausspulse.py, 2019.8.31
https://docs.scipy.org/doc/scipy-0.14.0/reference/generated/scipy.signal.gausspulse.html
"""

import numpy as np
from scipy import signal
import matplotlib.pyplot as plt

t = np.linspace(-1, 1, 2 * 100, endpoint=False)
i, q, e = signal.gausspulse(t, fc=5, retquad=True, retenv=True)
plt.plot(t, i, t, q, t, e, '--')
plt.show()