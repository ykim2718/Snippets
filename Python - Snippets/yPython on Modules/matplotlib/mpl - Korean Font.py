"""
y, 2021.4.27
mpl - Korean font.py
http://corazzon.github.io/matpolotlib_font_setting
Refer to mpl - font names.py  !!!
"""

import matplotlib.font_manager as font_manager
import pathlib

fonts = font_manager.findSystemFonts(fontpaths=None, fontext='ttf')
t = len(fonts)
font_paths = sorted(fonts, key=lambda x: pathlib.Path(x).stem)
font_names = []
for j, font_path in enumerate(font_paths):
    font_name = font_manager.FontProperties(fname=font_path, size=50).get_name()
    # print(f"{j+1}/{t}, {font_path} >> {font_name}")
    font_names.append(font_name)
font_names = sorted(set(font_names))
t = len(font_names)
for j, font_name in enumerate(font_names):
    print(f"{j+1}/{t}, {font_name}")
