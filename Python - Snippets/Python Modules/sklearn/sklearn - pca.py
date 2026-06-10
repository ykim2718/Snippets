"""
y, sklearn - pca.py, 2018.12.14 - 15, 12.25
    2019.1.1, 1.29

Reference
---------
https://scikit-learn.org/stable/modules/generated/sklearn.decomposition.PCA.html
https://scikit-learn.org/stable/modules/decomposition.html#pca
http://jotterbach.github.io/2016/03/24/Principal_Component_Analysis/
https://github.com/jotterbach/Data-Exploration-and-Numerical-Experimentation/blob/master/Data-Analytics/PCA_Pitfalls.ipynb

Note
----
Inverse transformation from reduced dimension is possible amazingly, 2018.12.14, y, ★★★

"""

import numpy as np
from sklearn.decomposition import PCA


def rank_indices(a_list):
    """ y, 2018.12.16 """

    return [sorted(a_list).index(x) for x in a_list]


def n_components_satisfying_coverage_ratio(pca, pca_coverage_ratio):
    """ y, ~2018.12.25 """

    j = 0
    r = 0.0
    while r < pca_coverage_ratio:
        j += 1
        r = np.sum(pca.explained_variance_ratio_[:j])
    n_components = j
    coverage_ratio = r
    return n_components, coverage_ratio


if __name__ == '__main__':

    pca_coverage_ratio = 0.9

    X = np.array([[-1, -1, 1], [-2, -1, 2], [-3, -2, 3], [1, 1, 4], [2, 1, 5], [3, 2, 6]])
    # X = np.array([[1, -1, 1], [2, -1, 2], [3, -2, 3], [2, 1, 4], [-1, 1, 5], [-3, 2, 6]])
    print('X.shape =', X.shape)
    pca = PCA(n_components=None)  # can reduce dimension by setting n_components less than input column count, 2018.12.14
    pca.fit(X)
    print('pca.get_params() =', pca.get_params())
    print('pca.explained_variance_ =\n', pca.explained_variance_)
    print('pca.explained_variance_ratio_ =\n', pca.explained_variance_ratio_, '<< Coverage ratio')
    print('pca.components_ =\n', pca.components_)
    print('pca.components_[0] =\n', pca.components_[0], '<< Principal component 1')
    print('pca.components_.mean(axis=0)=\n', pca.components_.mean(axis=0), '<< Feature contribution')
    # print('pca.inverse_transform(np.eye(X.shape[1])) =\n', pca.inverse_transform(np.eye(X.shape[1])))  # = pca.components_
    feature_contributions = pca.components_.mean(axis=0)
    print('rank of feature contribution = ', rank_indices(feature_contributions))

    if False:
        import matplotlib.pyplot as plt
        pca_inversed = pca.inverse_transform(np.eye(X.shape[1]))
        fig = plt.figure(figsize=(10, 6.5))
        plt.plot(pca_inversed.mean(axis=0), '--o', label='mean')
        plt.plot(np.square(pca_inversed.std(axis=0)), '--o', label='variance')
        plt.ylabel('feature contribution', fontsize=20)
        plt.xlabel('feature index', fontsize=20)
        plt.tick_params(axis='both', which='major', labelsize=18)
        plt.tick_params(axis='both', which='minor', labelsize=12)
        plt.xlim([0, 29])
        plt.legend(loc='upper right', fontsize=18)
        plt.show()


    n_components, coverage_ratio = n_components_satisfying_coverage_ratio(pca, pca_coverage_ratio)
    print("n_components={n}, coverage_ratio={r:.3g}".format(n=n_components, r=coverage_ratio))
    # reduce dimension by n_components less than input column count, awesome !!!, 2018.12.15
    pca.set_params(n_components=n_components)

    transformed = pca.transform(X)  # Apply dimensionality reduction to X.
    print('pca.transform(X) =\n', transformed)
    transformed = pca.fit_transform(X)  # Fit the model with X and apply the dimensionality reduction on X.
    print('pca.fit_transform(X) =\n', transformed)
    inversed = pca.inverse_transform(transformed[3:])
    print('pca.inverse_transform(transformed[3:]) =\n', inversed)


