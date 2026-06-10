"""
y, selenium - save and load cookies.py, 2018.9.18
https://stackoverflow.com/questions/15058462/how-to-save-and-load-cookies-using-python-selenium-webdriver
https://www.seleniumhq.org/download/
"""

import pickle
from selenium import webdriver

_web_driver_path = r'd:\Wolf\Computer - IDE\IExplorer driver\IEDriverServer.exe'
_knox_login_url = 'http://wwww.samsung.net'

ie_options = webdriver.IeOptions()
ie_options._options[ie_options.IGNORE_PROTECTED_MODE_SETTINGS] = True
driver = webdriver.Ie(_web_driver_path, ie_options=ie_options)
driver.get(_knox_login_url)
if False:
    pickle.dump( driver.get_cookies() , open("cookies.pkl", "wb"))
else:
    cookies = pickle.load(open("cookies.pkl", "rb"))
    for cookie in cookies:
        driver.add_cookie(cookie)