"""
y, mpl - figure to html.py, 2019.1.10 - 11, 1.13
"""

import io
import matplotlib.pyplot as plt
import email.mime.image as emi

import importlib
spec = importlib.util.spec_from_file_location('pandas_snippet', '../pandas/pandas - dataframe to html table (2).py')
pandas_snippet = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pandas_snippet)


def figure_to_html(figure, window='full', axes_index=0, image_type='svg', image_width='100%', dpi=96,
                   **savefig_kwargs):
    """
    y, 2019.1.10 - 11, 1.13

    Note
    ----
    . 96 dpi = 1920 x 1080 monitor screen

    Reference
    ---------
    https://en.wikipedia.org/wiki/Scalable_Vector_Graphics
    https://stackoverflow.com/questions/11918977/right-mime-type-for-svg-images-with-fonts-embedded
    https://docs.python.org/2/library/email.mime.html
    """

    assert isinstance(figure, plt.Figure)
    assert axes_index < len(figure.axes)
    image_type = savefig_kwargs.pop('format', image_type)
    assert image_type in ['png', 'svg']
    assert window in ['crop', 'full']

    bounding_box = {
        'crop': figure.axes[axes_index].get_window_extent().transformed(figure.dpi_scale_trans.inverted()),
        'full': 'tight',
    }.get(window)
    buffer = io.BytesIO()
    figure.savefig(buffer, format=image_type, dpi=dpi, bbox_inches=bounding_box, **savefig_kwargs)
    subtype = {
        'png': 'image/png',
        'svg': 'image/svg+xml',
    }.get(image_type)
    mime_image = emi.MIMEImage(buffer.getvalue(), _subtype=subtype)
    buffer.close()
    image_str = mime_image.get_payload()
    html_source = {
        'png': 'data:image/png',
        'svg': 'data:image/svg+xml',
    }.get(image_type)
    img_html = '<img alt="chart" style="width:{image_width:s}" src="{source};base64, {image_str}"/>'.format(
        source=html_source, image_str=image_str, image_width=image_width)
    img_html = img_html.replace('\n', '')  # needed only if img_html is added to dataframe which is going to be html

    return img_html


if __name__ == '__main__':

    import pathlib
    import pandas as pd

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=[3, 1])
    ax1.plot([3, 1, 4, 1, 5], 'ks-', mec='w', mew=2, ms=10)
    ax1.set_ylabel('y1 label')
    ax2.plot([1, 2, 3, 4, 5], 'rs-', mec='w', mew=2, ms=10)
    ax2.tick_params(direction='in')
    ax2.set_xlabel('x2 label')
    # plt.draw()

    image_type = ['png', 'svg'][1]
    image_width = ['100%', '100px'][1]
    window = ['crop', 'full'][0]
    axes_index = 1  # 0 for ax1, 1 for ax2

    figure_html = figure_to_html(fig, image_type=image_type, image_width=image_width,
                                 window=window, axes_index=axes_index)
    # pathlib.Path(__file__).with_suffix('.html').open('w').write(figure_html)

    frame = pd.DataFrame({'A': [1, 2], 'B': [3, 4]}, index=list('ab'))
    frame.loc['b', 'B'] = figure_html

    frame_html = pandas_snippet.dataframe_to_html(frame, styles='default')
    pathlib.Path(__file__).with_suffix('.html').open('w').write(frame_html)

