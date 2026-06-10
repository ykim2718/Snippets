"""
y, 2023.7.25
sklearn - cosine_similarity.py
https://www.learndatasci.com/glossary/cosine-similarity/
"""

from sklearn.metrics.pairwise import cosine_similarity
import numpy as np
import pandas as pd


a = np.arange(12).reshape(3, 4)
print(f"{a=}")

cs = cosine_similarity(a)
print(f"{cs=}")
print(f"{cs[-1]=}")

"""
a=array([[ 0,  1,  2,  3],
       [ 4,  5,  6,  7],
       [ 8,  9, 10, 11]])
cs=array([[1.        , 0.9047619 , 0.86613807],
       [0.9047619 , 1.        , 0.99652445],
       [0.86613807, 0.99652445, 1.        ]])
cs[-1]=array([0.86613807, 0.99652445, 1.        ])
"""

print(pd.DataFrame(a, index=list('abc'), columns=list('ABCD')))
"""
   A  B   C   D
a  0  1   2   3
b  4  5   6   7
c  8  9  10  11
"""