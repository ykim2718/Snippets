"""
y, 2016.5.6; 2022.6.21
http://stackoverflow.com/questions/458209/is-there-a-way-to-detach-matplotlib-plots-so-that-the-computation-can-continue
https://www.tutorialspoint.com/how-to-clear-the-memory-completely-of-all-matplotlib-plots
"""

import matplotlib.pyplot as plt
import pathlib
import time

plt.ion()
fig = plt.figure(pathlib.Path(__file__).name)
ax1 = fig.add_subplot()

for j in range(9):
    text = f"{j=}"
    ax1.scatter([j], [j])
    ax1.set_title(text, loc='center')
    fig.canvas.draw()
    fig.canvas.flush_events()
    print(text)
    time.sleep(j)
    # not working # plt.clf()  # Clear the current figure.
    plt.cla()
