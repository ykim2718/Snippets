"""
y, 2020.12.3
sklearn - tsne.py
https://scikit-learn.org/stable/modules/generated/sklearn.manifold.TSNE.html
"""

from sklearn.manifold import TSNE
from sklearn.datasets import load_iris
import pandas as pd

iris = load_iris()
print(f"iris.feature_names={iris.feature_names}")
# iris.feature_names=['sepal length (cm)', 'sepal width (cm)', 'petal length (cm)', 'petal width (cm)']
print(f"iris.target_names={iris.target_names}")
# iris.target_names=['setosa' 'versicolor' 'virginica']

x = pd.DataFrame(iris.data, columns=iris.feature_names)
y = pd.Series(iris.target, name='species')
transformed = TSNE(n_components=2, random_state=777).fit_transform(x.values)
frame = pd.DataFrame(transformed, columns=['x1', 'x2'])
frame = pd.concat([frame, x, y], axis=1)

import matplotlib.pyplot as plt
import matplotlib as mpl
import pathlib

fig = plt.figure()
fig.canvas.set_window_title(pathlib.Path(__file__).name)
fig.suptitle('sklearn.manifold.TSNE()\nt-distributed Stochastic Neighbor Embedding', fontsize='medium')
fig.set_size_inches(7, 7)
fig.subplots_adjust(wspace=0.3)
gs = mpl.gridspec.GridSpec(2, 2)
ax1 = fig.add_subplot(gs[0, 0])
ax2 = fig.add_subplot(gs[0, 1])
ax3 = fig.add_subplot(gs[1, 0])

grouped = frame.groupby('species')
colors = {0: 'C0', 1: 'C1', 2: 'C2'}
for key, index in grouped.groups.items():
    frame.loc[index].plot.scatter(iris.feature_names[0], iris.feature_names[1],
                                  ax=ax1, c=colors[key], label=iris.target_names[key])
ax1.legend(loc='best')
for key, index in grouped.groups.items():
    frame.loc[index].plot.scatter(iris.feature_names[2], iris.feature_names[3],
                                  ax=ax2, c=colors[key], label=iris.target_names[key])
ax2.legend(loc='best')
for key, index in grouped.groups.items():
    frame.loc[index].plot.scatter('x1', 'x2', ax=ax3, c=colors[key], label=iris.target_names[key])
ax3.legend(loc='best')

plt.show()


