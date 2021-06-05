"""
y, pandas - dataframe to html table.py, 2018.10.19

Reference
---------
https://pandas.pydata.org/pandas-docs/stable/style.html#Styling
https://pandas.pydata.org/pandas-docs/stable/api.html#styler-attributes
https://stackoverflow.com/questions/36897366/pandas-to-html-using-the-style-options-or-custom-css
https://stackoverflow.com/questions/48038897/how-to-set-spacing-in-html-export-of-a-pandas-dataframe?noredirect=1&lq=1

"""

import pandas as pd
import numpy as np

arrays = [np.array(['bar', 'bar', 'baz', 'baz', 'foo', 'foo', 'qux', 'qux']),
          np.array(['one', 'two', 'one', 'two', 'one', 'two', 'one', 'two'])]
df = pd.DataFrame(np.random.randn(8, 4), index=arrays)
df.columns = list('ABCD')
df.index.names = list('PQ')
print(df)

trial = 2.5

if trial == 0:
    df_html = df.to_html()

elif trial == 1:

    # Bug: index name and column name are not properly displayed on html page, 2018.10.19

    df_html = df.to_html(index=True, classes='class="w3-table-all" cellSpacing=0 cellPadding=0 border=0 width="Auto"')
    df_html = df_html.replace('valign="top"', 'valign="middle"')

    thead_tag_content = '<tr style="text-align: middle;' +\
        ''.join("<th> %s </th>" % index_col for index_col in df.index.names) + \
        ''.join("<th> %s </th>" % value_col for value_col in df.columns.values)

    from bs4 import BeautifulSoup

    df_html = BeautifulSoup(df_html, 'lxml')
    tag = df_html.find('thead')
    tag.clear()
    tag.insert(1, thead_tag_content)
    df_html = str(df_html)
    df_html = df_html.replace('&gt;', '>').replace('&lt;', '<')
    # print(df_html)

elif trial == 2:

    index_names = df.index.names
    df.index.names = [None, None]
    df_html = (df.style.render())
    df_html = df_html \
        .replace('<th class="blank" ></th>', '<th class="blank">{}</th>'.format(index_names[0])) \
        .replace('<th class="blank level0" ></th>', '<th class="blank level0">{}</th>'.format(index_names[1]))

elif trial == 2.5:

    index_names = df.index.names
    df.index.names = [None, None]
    styles = [
        dict(props=[('border-collapse', 'collapse')]),
        dict(selector='th', props=[('border', '0.1px gray solid')]),
        dict(selector='td', props=[('border', '0.1px gray solid')]),
    ]
    df_html = (df.style.set_table_styles(styles).render())
    df_html = df_html \
        .replace('<th class="blank" ></th>', '<th class="blank">{}</th>'.format(index_names[0])) \
        .replace('<th class="blank level0" ></th>', '<th class="blank level0">{}</th>'.format(index_names[1]))

elif trial == 3:

    def color_negative_red(value):
        color = 'red' if value < 0 else 'black'
        return 'color: %s' % color

    # Set CSS properties for th elements in dataframe
    th_props = [
        ('font-size', '11px'),
        ('text-align', 'right'),
        ('font-weight', 'bold'),
        ('color', '#6d6d6d'),
        ('background-color', '#f7f7f9'),
        ('border', '0.1px gray solid'),
    ]

    # Set CSS properties for td elements in dataframe
    td_props = [
        ('font-size', '11px'),
        ('text-align', 'right'),
        ('border', '0.1px gray solid'),
    ]

    # Set table styles
    styles = [
        dict(selector="th", props=th_props),
        dict(selector="td", props=td_props),
        dict(props=[
            ('border-collapse', 'collapse'),
            # ('border-collapse', 'separate'), ('border-spacing', '10px 5px')
        ])
    ]

    index_names = df.index.names
    df.index.names = [None, None]
    df_html = (df.style.applymap(color_negative_red, subset=['C', 'D'])
               .format({'B': "{:.2%}"})
               .set_table_styles(styles)
               .set_precision(3)
               .render())
    df_html = df_html\
        .replace('<th class="blank" ></th>', '<th class="blank">{}</th>'.format(index_names[0]))\
        .replace('<th class="blank level0" ></th>', '<th class="blank level0">{}</th>'.format(index_names[1]))


import os
module_name = os.path.basename(__file__)
f = open(module_name.replace('.py', '.html'), 'w')
f.write(df_html)
f.close()



