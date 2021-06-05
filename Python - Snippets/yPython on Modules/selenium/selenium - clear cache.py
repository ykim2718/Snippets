"""
y, selenium - clear cache.py, 2018.10.30
https://intoli.com/blog/clear-the-chrome-browser-cache/
"""

from selenium.webdriver.support.ui import WebDriverWait
from selenium import webdriver


def get_clear_browsing_button(driver):
    """Find the "CLEAR BROWSING BUTTON" on the Chrome settings page."""
    return driver.find_element_by_css_selector('* /deep/ #clearBrowsingDataConfirm')


def clear_cache(driver, timeout=60):
    """Clear the cookies and cache for the ChromeDriver instance."""
    # navigate to the settings page
    driver.get('chrome://settings/clearBrowserData')

    # wait for the button to appear
    wait = WebDriverWait(driver, timeout)
    wait.until(get_clear_browsing_button)

    # click the button to clear the cache
    get_clear_browsing_button(driver).click()

    # wait for the button to be gone before returning
    wait.until_not(get_clear_browsing_button)


driver_path = r"c:\Y\Chromedriver win32\chromedriver.exe"
driver = webdriver.Chrome(driver_path)
driver.implicitly_wait(3)

clear_cache(driver)