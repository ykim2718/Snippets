"""
y, seaborn - lmplot basic.py, 2019.10.15
https://seaborn.pydata.org/generated/seaborn.lmplot.html
"""

import matplotlib.pyplot as plt
import pandas as pd

import seaborn as sns; sns.set(color_codes=True)
if False:
    tips = sns.load_dataset("tips")
    tips.to_csv('tips.csv')
else:
    # tips = pd.DataFrame(dict(total_bill=[1, 2, 3, 4], tip=[2, 3, 4.4, 5]))
    tips = pd.read_csv('tips.csv')
g = sns.lmplot(x="total_bill", y="tip", data=tips)

plt.show()
