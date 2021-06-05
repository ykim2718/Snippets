"""
y, mpl - transformation from data to axis.py, 2018.1.16 (at Kaula Lupur airport rounge), 1.31

https://matplotlib.org/users/transforms_tutorial.html
"""

import matplotlib.pyplot as plt

ax = plt.subplot(111)

ax.set_xlim(0, 10)
ax.set_ylim(-1, 1)

a = ax.transLimits.transform((0, -1))
# Out[84]: array([ 0.,  0.])
print(a)

a = ax.transLimits.transform((10, -1))
# Out[85]: array([ 1.,  0.])
print(a)

a = ax.transLimits.transform((10, 1))
# Out[86]: array([ 1.,  1.])
print(a)

a = ax.transLimits.transform((5, 0))
# Out[87]: array([ 0.5,  0.5])
print(a)

# 2018.1.17, y, on plane close to Melbourne

import numpy as np

ax.set_xlim(10, 1000)
ax.set_xscale('log')
print('xlim =', ax.get_xlim())
print('xscale =', ax.get_xscale())
print('yscale =', ax.get_yscale())

xll, xul = ax.get_xlim()

# 2018.1.16 - 1.31
a = ax.transLimits.transform((np.log10(xll), 0))[0], ax.transLimits.transform((np.log10(xul), 0))[0]
# a = ax.transLimits.transform((np.log10(xll * 10), 0))[0], ax.transLimits.transform((np.log10(xul * 10), 0))[0]  # *10 ??
# a = ax.transLimits.transform_affine((xll, 0))[0], ax.transLimits.transform_affine((xul, 0))[0]
# a = ax.transLimits.transform((xll, 0))[0], ax.transLimits.transform((xul, 0))[0]
# a = ax.transLimits.transform_point((xll, 0))[0], ax.transLimits.transform_point((xul, 0))[0]
print("xll={:g}, xul={:g}".format(*a))  # expect [0, 1]

import matplotlib
print('matplotlib version =', matplotlib.__version__)  # 2.1.0



