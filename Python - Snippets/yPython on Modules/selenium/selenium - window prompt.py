"""
y, selenium - window prompt.py, 2018.8.16, 8.20
"""

from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time

driver_path = r'c:\Y\IEDriver\IEDriverServer.exe'

ie_options = webdriver.IeOptions()
ie_options._options[ie_options.IGNORE_PROTECTED_MODE_SETTINGS] = True
driver = webdriver.Ie(driver_path, ie_options=ie_options)
driver.get("http://www.samsung.net")


# selenium (3.4.1), python (3.5.1)
# https://stackoverflow.com/questions/8175328/how-can-i-prompt-for-input-using-selenium-webdriver-and-use-the-result
# driver.execute_script("var u = prompt('Enter username', 'pasystem');document.body.setAttribute('_username_', u)")
# username = driver.find_element_by_tag_name('body').get_attribute(('_username_'))
driver.execute_script("var u = prompt('Enter username', 'pa_username');"
                      "var p = prompt('Enter password', 'pa_password');"
                      "document.body.setAttribute('_username_', u);"
                      "document.body.setAttribute('_password_', p);")
time.sleep(3)  # must
un = driver.find_element_by_tag_name('body').get_attribute('_username_')
pw = driver.find_element_by_tag_name('body').get_attribute('_password_')
print('un:', un)
print('pw:', pw)

driver.refresh()
"""
1. driver.get(driver.current_url)
2. driver.find_element_by_tag_name('body').send_keys(Keys.F5)
3. driver.refresh()
4. driver.find_element_by_tag_name('body').send_keys("\uE035")
"""

driver.quit()
