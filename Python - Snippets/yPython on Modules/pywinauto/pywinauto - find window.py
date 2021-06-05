"""
y, pywinauto - find window.py, 2018.8.29
"""

import pywinauto

w_handle = pywinauto.findwindows.find_windows(title=u'coStarter', class_name='#32770')[0]
window = pwa_app.window_(handle=w_handle)
window.Click()