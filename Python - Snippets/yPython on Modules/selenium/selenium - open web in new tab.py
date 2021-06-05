"""
y, selenium - open web in new tab.py, 2018.8.19
https://stackoverflow.com/questions/28431765/open-web-in-new-tab-selenium-python
"""

driver_path = r'c:\Y\ChromeDriver win32\chromedriver.exe'

from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

options = webdriver.ChromeOptions()
options.add_argument("start-maximized")
options.add_argument('disable-infobars')
driver = webdriver.Chrome(chrome_options=options, executable_path=driver_path)
driver.get("http://www.google.co.in")
print("Initial Page Title is : %s" %driver.title)
windows_before = driver.current_window_handle
print("First Window Handle is : %s" %windows_before)
driver.execute_script("window.open('https://www.yahoo.com')")
WebDriverWait(driver, 10).until(EC.number_of_windows_to_be(2))
windows_after = driver.window_handles
new_window = [x for x in windows_after if x != windows_before][0]
driver.switch_to.window(new_window)
print("Page Title after Tab Switching is : %s" %driver.title)
print("Second Window Handle is : %s" %new_window)