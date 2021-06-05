"""
y, pandas - html table w chart image cell.py, 2018.9.28, 9.30

https://pandas.pydata.org/pandas-docs/stable/generated/pandas.set_option.html
https://matplotlib.org/api/_as_gen/matplotlib.axes.Axes.get_window_extent.html

"""

import io
import os
import pandas as pd
import matplotlib.pyplot as plt
from email.mime.image import MIMEImage

module_name = os.path.basename(__file__)

# create ax as a sample chart

X = [1, 2, 3, 4, 5, 6, 7, 8, 9]
Y = [-x**2-3 for x in X]
fig, ax = plt.subplots(1, 1)
ax.plot(X, Y, 'o', markersize=3)
plt.xlabel('x')
plt.ylabel('y')
ax.axis('off')

# take ax and create img_html

bbox = ax.get_window_extent().transformed(fig.dpi_scale_trans.inverted())
img_stream = io.BytesIO()
fig.savefig(img_stream, format='png', bbox_inches=bbox)
img_stream.read()
img_string = MIMEImage(img_stream.getvalue())
img_stream.close()
img_string = img_string._payload

img_html = '<img alt="Chart_image" src="data:/image/jpeg;base64, {} " />'.format(img_string)
img_html = img_html.replace('\n', '')

# put html to dataframe

df = pd.DataFrame.from_dict(data={'lot': ['A', 'B'], 'wafer': [1, 2], 'rank': [2, 3]})
df.loc[df.index[1], 'image'] = img_html
df['image'].fillna('no image', inplace=True)

# save dataframe as html

pd.set_option('display.max_colwidth', -1)
df_html = df.to_html(header=True, classes=None, index=False, bold_rows=False)
df_html = df_html.replace('&lt;', '<').replace('/&gt;', '>')
pd.reset_option('display.max_colwidth')

# print(df_html)
with open(module_name.replace('.py', '.html'), 'w') as f:
    f.write(df_html)