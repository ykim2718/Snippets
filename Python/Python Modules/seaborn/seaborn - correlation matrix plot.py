"""
y, 2020.11.1
seaborn - correlation matrix plot.py
https://stackoverflow.com/questions/48139899/correlation-matrix-plot-with-coefficients-on-one-side-scatterplots-on-another?noredirect=1&lq=1
http://seaborn.pydata.org/generated/seaborn.pairplot.html
https://seaborn.pydata.org/introduction.html
"""

import matplotlib.pyplot as plt
import matplotlib as mpl
import seaborn as sns
import itertools
import pathlib


def corrdot(*args, **kwargs):
    corr_r = args[0].corr(args[1], 'pearson')
    corr_text = f"{corr_r:2.2f}".replace("0.", ".")
    ax = plt.gca()
    ax.set_axis_off()
    marker_size = abs(corr_r) * 10000
    ax.scatter([.5], [.5], marker_size, [corr_r], alpha=0.6, cmap="coolwarm",
               vmin=-1, vmax=1, transform=ax.transAxes)
    font_size = abs(corr_r) * 40 + 5
    ax.annotate(corr_text, [.5, .5, ], xycoords="axes fraction", ha='center', va='center', fontsize=font_size)


def corr_coef_r2(*args, **kwargs):
    r2 = args[0].corr(args[1], 'pearson') ** 2
    ax = plt.gca()
    ax.annotate(f"$r^2={r2:.3g}$", [0.05, 0.9, ], xycoords="axes fraction", ha='left', va='center', fontsize='xx-small')
    if r2 > 0.8:
        ax.patch.set_facecolor('yellow')
        # ax.patch.set_alpha(0.2)


def annotate_colname(x, label=None, color=None, **kwargs):
    x_name = next(kwargs['column_name_iterator'])
    ax = plt.gca()
    ax.set_title(x_name, y=0.05, va='bottom', loc='center', size='x-small')


sns.set(style='white', font_scale=1.6)
iris = sns.load_dataset('iris')
print(f"iris.shape={iris.shape}")
print(f"iris.columns={iris.columns}")

chart_height = 1  # height (in inches) of each facet in the domain of seaborn
chart_aspect_ratio = 1.4  # aspect ratio: the ratio of the width to the height of an image or screen.
chart_count = len(iris.columns)

g = sns.PairGrid(iris, height=chart_height, aspect=chart_aspect_ratio, diag_sharey=False)
g.fig.canvas.manager.set_window_title(pathlib.Path(__file__).name)
g.fig.set_size_inches(chart_height * chart_count * chart_aspect_ratio, chart_height * chart_count)
g.fig.subplots_adjust(wspace=0, hspace=0)  # , left=0.1, bottom=0.1)
print(f"g.fig={type(g.fig)}, isinstance(g.fig, mpl.Figure)={isinstance(g.fig, mpl.figure.Figure)}")

# g.map_lower(sns.regplot, lowess=True, ci=False, line_kws={'color': 'black'})
g.map_lower(sns.regplot, lowess=False, line_kws={'color': 'black'})
g.map_lower(corr_coef_r2)
g.map_diag(sns.distplot, kde_kws={'color': 'black'})
g.map_diag(annotate_colname, ax=plt.gca(), column_name_iterator=itertools.cycle(iris.columns))
# g.map_upper(corrdot)
g.map_upper(sns.kdeplot, cmap='Blues_d')

for ax in g.axes.flatten():
    ax.set_ylabel('')
    ax.set_xlabel('')
    plt.setp(ax.get_xticklabels(), fontsize='xx-small')
    plt.setp(ax.get_yticklabels(), fontsize='xx-small')

plt.show()
