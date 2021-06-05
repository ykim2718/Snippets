"""
y, sklearn - ipca w partial_fit.py, 2018.12.20, 12.24 - 25, 2019.1.29
https://scikit-learn.org/stable/modules/generated/sklearn.decomposition.IncrementalPCA.html#sklearn.decomposition.IncrementalPCA
"""

import numpy as np
from sklearn.datasets import load_digits
from sklearn.decomposition import IncrementalPCA, PCA


def yLoadModuleFromPath(module_name, module_path):
    """
    y, ~2018.12.25

    Usage
    -----
    module_path = r"abc d e f.py"
    module_name = 'abc_d_e_f'
    yLoadModuleFromPath(module_name, module_path)
    import abc_d_e_f

    """

    import importlib.util
    import sys
    spec = importlib.util.spec_from_file_location(module_name, module_path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    sys.modules[module_name] = module

module_path = r"sklearn - pca.py"
module_name = 'y_pca'
yLoadModuleFromPath(module_name, module_path)
import y_pca


X, _ = load_digits(return_X_y=True)
print(X.shape)  # shape=(1797, 64)=(n_data, n_features)

n_components = X.shape[1]
n_components = X.shape[1] // 2
n_components = None
batch_size = None  # 200
ipca = IncrementalPCA(n_components=n_components, batch_size=batch_size)
# ipca = PCA(n_components=n_components)
print('ipca =', ipca)

if True:
    # either partially fit on smaller batches of data
    # print(ipca.partial_fit(X[:100, :]))
    if n_components:
        batch_size = ipca.n_components
        assert batch_size >= ipca.n_components, "batch_size >= ipca.n_components ({nc}), but got {bs}".format(
            bs=batch_size, nc=ipca.n_components)
    else:
        batch_size = 100
    # 2019.1.29 # ipca.set_params(batch_size=batch_size)  # <<< The docs say batch_size is only used when calling fit ..
    batch_count = X.shape[0] // batch_size
    for j in range(batch_count):
        ipca.partial_fit(X[j*batch_size:(j+1)*batch_size, :])
else:
    # or let the fit function itself divide the data into batches
    X_transformed = ipca.fit_transform(X)
    print(X_transformed.shape)  # shape=(1797, 7)=(n_data, n_components)

print('ipca.components_.shape =\n', ipca.components_.shape)
print('ipca.explained_variance.shape =\n', ipca.explained_variance_.shape)
print('ipca.explained_variance_ratio_.shape =\n', ipca.explained_variance_ratio_.shape)
print('ipca.explained_variance_ratio_ =\n', ipca.explained_variance_ratio_, '<< Coverage ratio')
print('np.cumsum(ipca.explained_variance_ratio_) =\n', np.cumsum(ipca.explained_variance_ratio_), '<< Cumulative Coverage')
print('Coverage ratio  =\n', np.cumsum(ipca.explained_variance_ratio_)[-1])

n_components, coverage_ratio = y_pca.n_components_satisfying_coverage_ratio(ipca, 0.95)
print("n_components={n}, coverage_ratio={r:.3g}".format(n=n_components, r=coverage_ratio))
ipca.set_params(n_components=n_components)
print('ipca =', ipca)

a = np.arange(64).reshape(1, 64)
# print('original =\n', a)
transformed = ipca.transform(a)
# print('transformed =\n', transformed, transformed.shape)
inverse_transformed = ipca.inverse_transform(transformed)
# print('inverse transformed =\n', inverse_transformed, inverse_transformed.shape)

import os
import matplotlib.pyplot as plt

fig, ax1 = plt.subplots(nrows=1, sharex=True)
title = os.path.basename(__file__)
fig.suptitle(title, fontsize='large')
fig.canvas.set_window_title(title)

ax1.scatter(a, inverse_transformed)
ax1.set_xlabel('original array')
ax1.set_ylabel('inverse_transformed')
plt.show()



