"""
y, pandas - dataframe to html table (2).py, 2018.10.19, 11.7 - 8, 11.25
    2019.1.10 - 11

Reference
---------
https://pandas.pydata.org/pandas-docs/stable/style.html#Styling
https://pandas.pydata.org/pandas-docs/stable/api.html#styler-attributes
https://stackoverflow.com/questions/36897366/pandas-to-html-using-the-style-options-or-custom-css
https://stackoverflow.com/questions/48038897/how-to-set-spacing-in-html-export-of-a-pandas-dataframe?noredirect=1&lq=1

"""

import pandas as pd
import numpy as np
import lxml.html


def dataframe_to_html(frame, styles=None):
    """
    y,  2018.10.19, 11.7, 11.25
        2019.1.10 - 11

    yGetDataframeHtml()

    Usage
    -----

    import pandas as pd
    import numpy as np

    arrays = [np.array(['bar', 'bar', 'baz', 'baz', 'foo', 'foo', 'qux', 'qux']),
              np.array(['one', 'two', 'one', 'two', 'one', 'two', 'one', 'two'])]
    df = pd.DataFrame(np.random.randn(8, 4), index=arrays)
    df.columns = list('ABCD')
    df.index.names = list('PQ')
    print(df)

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

    styles = {}
    styles['applymap'] = {'args': (color_negative_red,), 'kwargs': dict(subset=['C', 'D'])}
    styles['format'] = {'args': ({'B': "{:.2%}"},)}
    styles['set_table_styles'] = {
        'args': ([dict(selector="th", props=th_props),
                  dict(selector="td", props=td_props),
                  dict(props=[('border-collapse', 'collapse'),
                              # ('border-collapse', 'separate'), ('border-spacing', '10px 5px')
                              ])
                  ],)
    }
    styles['set_precision'] = {'args': (3,)}

    html = dataframe_to_html(df, styles)

    import os
    module_name = os.path.basename(__file__)
    f = open(module_name.replace('.py', '.html'), 'w')
    f.write(html)
    f.close()

    """

    assert isinstance(frame, pd.DataFrame)
    if styles is None:
        styles = {}
    elif styles == 'default':
        th_props = [
            ('font-size', '11px'),
            ('text-align', 'right'),
            ('border', '0.1px gray solid'),
        ]
        td_props = th_props.copy()
        styles = {
            'set_table_styles': {
                'args': ([dict(selector="th", props=th_props),
                          dict(selector="td", props=td_props),
                          dict(props=[('border-collapse', 'collapse')])],)
            }
        }
    assert isinstance(styles, dict)

    index_names = frame.index.names
    frame.index.names = [None] * len(index_names)
    frame_style = frame.style
    for key, value in styles.items():
        assert hasattr(frame_style, key) and callable(getattr(frame_style, key))
        args = value.get('args', ())
        assert isinstance(args, tuple)
        kwargs = value.get('kwargs', {})
        assert isinstance(kwargs, dict)
        frame_style = getattr(frame_style, key)(*args, **kwargs)
    html = frame_style.render()
    for j, name in enumerate(index_names):
        if j == 0:
            html = html.replace('<th class="blank" ></th>', '<th class="blank">{}</th>'.format(name))
        else:
            html = html.replace('<th class="blank level{k}" ></th>'.format(k=j-1),
                                '<th class="blank level{k}">{n}</th>'.format(k=j-1, n=name))

    # 2019.1.11
    tree = lxml.html.fromstring(html)
    table = tree.find('body/table')
    table.attrib['style'] = 'width:fit-content;height:fit-content'
    html = lxml.html.tostring(tree, pretty_print=True).decode('utf-8')

    return html


if __name__ == '__main__':

    arrays = [np.array(['bar', 'bar', 'baz', 'baz', 'foo', 'foo', 'qux', 'qux']),
              np.array(['one', 'two', 'one', 'two', 'one', 'two', 'one', 'two'])]
    df = pd.DataFrame(np.random.randn(8, 4), index=arrays)
    df.columns = list('ABCD')
    df.index.names = list('PQ')
    print(df)

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

    styles = {}
    styles['applymap'] = {'args': (color_negative_red,), 'kwargs': dict(subset=['C', 'D'])}
    styles['format'] = {'args': ({'B': "{:.2%}"},)}
    styles['set_table_styles'] = {
        'args': ([dict(selector="th", props=th_props),
                  dict(selector="td", props=td_props),
                  dict(props=[('border-collapse', 'collapse'),
                              # ('border-collapse', 'separate'), ('border-spacing', '10px 5px')
                              ])
                  ],)
    }
    styles['set_precision'] = {'args': (3,)}

    html = dataframe_to_html(df, styles)

    import os
    module_name = os.path.basename(__file__)
    f = open(module_name.replace('.py', '.html'), 'w')
    f.write(html)
    f.close()



