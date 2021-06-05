"""
y, numpy - random choice w prob.py, 2019.1.18
https://docs.scipy.org/doc/numpy/reference/generated/numpy.random.choice.html
"""

import numpy as np

texts = list('abc')
weights = [0.5, 0.2, 0.1]

assert (np.array(weights) > 0).all()
normalized_weights = np.array(weights)/sum(weights)
print(normalized_weights)

choices = []
for j in range(9):
    choice = np.random.choice(texts, p=normalized_weights)
    choices.append(choice)

for text in texts:
    print(text, '=', choices.count(text))