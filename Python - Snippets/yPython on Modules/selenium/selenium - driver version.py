"""
y, 2020.11.8
https://stackoverflow.com/questions/58979318/is-it-possible-to-check-chromedriver-exe-version-at-runtime-in-python
https://chromedriver.chromium.org/downloads
"""

from selenium import webdriver
import pprint

driver = webdriver.Chrome('c:\Y\Chrome driver\chromedriver.exe')
print(f"driver.capabilities=\n{pprint.pformat(driver.capabilities, indent=2, width=80, compact=True)}")
if 'browserVersion' in driver.capabilities:
    version = driver.capabilities['browserVersion']
else:
    version = driver.capabilities['version']
print(f"chrome_browser_version={version}")
version = driver.capabilities['chrome']['chromedriverVersion'].split(' ')[0]
print(f"chrome_driver_version={version}")
