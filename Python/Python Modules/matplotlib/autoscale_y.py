"""
http://stackoverflow.com/questions/29461608/matplotlib-fixing-x-axis-scale-and-autoscale-y-axis
"""


def autoscale_y(ax, margin=0.1):
    """This function rescales the y-axis based on the data that is visible given the current xlim of the axis.
    ax -- a matplotlib axes object
    margin -- the fraction of the total height of the y-data to pad the upper and lower ylims"""

    import numpy as np

    def get_bottom_top(line):
        xd = line.get_xdata()
        yd = line.get_ydata()
        lo, hi = ax.get_xlim()
        y_displayed = yd[((xd > lo) & (xd < hi))]
        h = np.max(y_displayed) - np.min(y_displayed)
        bot = np.min(y_displayed) - margin * h
        top = np.max(y_displayed) + margin * h
        return bot, top

    lines = ax.get_lines()
    bot, top = np.inf, -np.inf

    for line in lines:
        new_bot, new_top = get_bottom_top(line)
        if new_bot < bot: bot = new_bot
        if new_top > top: top = new_top

    ax.set_ylim(bot, top)


if __name__ == "__main__":

    import numpy as np
    import matplotlib.pyplot as plt

    x = np.linspace(-100, 100, 1000)
    y = x ** 2 + np.cos(x) * 100

    fig, axs = plt.subplots(1, 2, figsize=(8, 5))

    for ax in axs:
        ax.plot(x, y)
        ax.plot(x, y * 2)
        ax.plot(x, y * 10)
        ax.set_xlim(-10, 10)

    autoscale_y(axs[1])

    axs[0].set_title('Rescaled x-axis')
    axs[1].set_title('Rescaled x-axis\nand used "autoscale_y"')

    plt.show()
