"""
y, 2024.8.5
twocaptcha - selenium.py
https://2captcha.com/blog/captcha-bypass-in-selenium
"""

import ctypes
assert ctypes.sizeof(ctypes.c_voidp) * 8 == 32

from selenium.webdriver.common.by import By
from twocaptcha import TwoCaptcha
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from selenium import webdriver

import my_api


api_key = my_api.api_key
captcha_page_url = "https://recaptcha-demo.appspot.com/recaptcha-v2-checkbox.php"
captcha_page_site_key = '6LfW6wATAAAAAHLqO2pb8bDBahxlMxNdo9g947u9'


# Instantiate the WebDriver
options = Options()
# options.add_argument('--start-maximized')
options.add_experimental_option('detach', True)  # leave the browser open after WebDriver session has ended.
service = Service(ChromeDriverManager().install())
driver = webdriver.Chrome(service=service, options=options)

# Load the target page
driver.get(captcha_page_url)

# Solve the Captcha
print("Solving Captcha")
solver = TwoCaptcha(api_key)
response = solver.recaptcha(sitekey=captcha_page_site_key, url=captcha_page_url)
recaptcha_code = response['code']
print(f"Solved the Captcha; {recaptcha_code=}")

# Set the solved Captcha
recaptcha_response_element = driver.find_element(By.ID, 'g-recaptcha-response')
driver.execute_script(f'arguments[0].value = "{recaptcha_code}";', recaptcha_response_element)

# Submit the form
submit_btn = driver.find_element(By.CSS_SELECTOR, 'button[type="submit"]')
submit_btn.click()

# Pause the execution so you can see the screen after submission before closing the driver
# input("Press enter to continue")
driver.close()