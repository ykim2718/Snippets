"""
y, 2020.5.14
selenium - window position and size.py
https://stackoverflow.com/questions/16180428/can-selenium-webdriver-open-browser-windows-silently-in-background
"""

from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time


driver_path = r'c:\Y\IE driver\IEDriverServer.exe'

ie_options = webdriver.IeOptions()
ie_options._options[ie_options.IGNORE_PROTECTED_MODE_SETTINGS] = True
ie_options._options[ie_options.IGNORE_ZOOM_LEVEL] = True  # to avoid error below
# + selenium.common.exceptions.SessionNotCreatedException: Message: Unexpected error launching Internet Explorer. Browser zoom level was set to 105%. It should be set to 100%
# ie_options.add_argument('--headless')  # not working
# ie_options.add_argument('--window-size=100,100')  # not working
driver = webdriver.Ie(driver_path, ie_options=ie_options)

driver.set_window_position(0, 0)
driver.set_window_size(100, 100)
driver.get("http://www.msn.com")
# driver.refresh()

for j in range(99):
    time.sleep(1)
    print(f"\r{j}", end=' ')
driver.quit()
