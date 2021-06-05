"""
y, 2016.9.11, mpl - secondary axis with twinx.py
Secondary axis with twinx(): how to add to legend?
http://stackoverflow.com/questions/5484922/secondary-axis-with-twinx-how-to-add-to-legend
"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
rc('mathtext', default='regular')

time = np.arange(22.)
temp = 20*np.random.rand(22)
Swdown = 10*np.random.randn(22)+40
Rn = 40*np.random.rand(22)

fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(time, Swdown, '-', label = 'Swdown')
ax.plot(time, Rn, '-', label = 'Rn')
ax2 = ax.twinx()
ax2.plot(time, temp, '-r', label = 'temp')
ax.plot(0, 0, '-r', label = 'temp') # it's here!
ax.legend(loc=0)
ax.grid()
ax.set_xlabel("Time (h)")
ax.set_ylabel(r"Radiation ($MJ\,m^{-2}\,d^{-1}$)")
ax2.set_ylabel(r"Temperature ($^\circ$C)")
ax2.set_ylim(0, 35)
ax.set_ylim(-20,100)
plt.show()
