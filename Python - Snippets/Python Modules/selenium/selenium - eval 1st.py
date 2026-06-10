"""
y, selenium - eval 1st.py, 2017.5.31
"""

from selenium import webdriver
from bs4 import BeautifulSoup

driver = webdriver.Chrome('d:\Wolf\Homo academicus\yStudy on code - IDE\Chrome driver\chromedriver.exe')
driver.implicitly_wait(3)

# Login
driver.get('https://nid.naver.com/nidlogin.login')  # Naver login url
driver.get('http://short.krx.co.kr/contents/SRT/02/02030100/SRT02030100.jsp')
driver.find_element_by_name('id').send_keys('yyyyyy')
driver.find_element_by_name('pw').send_keys('yyyyyy')
driver.find_element_by_xpath('//*[@id="frmNIDLogin"]/fieldset/input').click()  # click button
driver.get('https://www.naver.com')
html = driver.page_source
soup = BeautifulSoup(html, 'html.parser')
notices = soup.select('div.p_inr > div.p_info > a > span')

for n in notices:
    print(n.text.strip())