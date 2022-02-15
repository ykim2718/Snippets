"""
y, selenium - crawl websites wo loading images.py, 2018.9.25
https://medium.com/dreamcatcher-its-blog/5-simple-tips-for-improving-automated-web-testing-or-efficient-web-crawling-using-selenium-python-43038d7b7916
"""

from selenium import webdriver

_driver_path = r'c:\Y\Chrome driver\chromedriver.exe'

chromeOptions = webdriver.ChromeOptions()
prefs = {'profile.managed_default_content_settings.images': 2}  # , 'disk-cache-size': 4096}
chromeOptions.add_experimental_option("prefs", prefs)
driver = webdriver.Chrome(chrome_options=chromeOptions, executable_path=_driver_path)
driver.get('http://google.com')

