"""
y, 2020.1.16
pyts - joint recurrence.py
https://pyts.readthedocs.io/en/latest/auto_examples/multivariate/plot_joint_rp.html#sphx-glr-auto-examples-multivariate-plot-joint-rp-py
https://pyts.readthedocs.io/en/latest/generated/pyts.multivariate.image.JointRecurrencePlot.html
"""

import matplotlib.pyplot as plt
from pyts.multivariate.image import JointRecurrencePlot
from pyts.datasets import load_basic_motions

X, _, _, _ = load_basic_motions(return_X_y=True)

# Recurrence plot transformation
jrp = JointRecurrencePlot(threshold='point', percentage=50)
X_jrp = jrp.fit_transform(X)

# Show the results for the first time series
plt.figure(figsize=(5, 5))
plt.imshow(X_jrp[0], cmap='binary', origin='lower')
plt.title('Joint Recurrence Plot', fontsize=18)
plt.tight_layout()
plt.show()
