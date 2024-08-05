"""
y, 2024.8.4
twocaptcha - requests.py
https://www.youtube.com/watch?v=R6QddZzCOwM
https://github.com/eupendra/2captcha_demo/blob/main/demo_requests.py
"""

import ctypes
assert ctypes.sizeof(ctypes.c_voidp) * 8 == 32

from twocaptcha import TwoCaptcha  # pip install 2captcha-python
import logging
import requests
from bs4 import BeautifulSoup
import my_api

# TRASS 무역통계 잠정치조회
# captcha_page_url = 'https://www.bandtrass.or.kr/customs/total.do?command=CUS001View&viewCode=CUS00401'
api_key = my_api.api_key
captcha_page_url = 'https://www.scrapebay.com/spam'
captcha_page_site_key = '6LcYC5YoAAAAAHKm7P482kG9YFEjr-igs23SkZPr'


# NOTE: Enabling logging will print the API KEY to the console
logging.basicConfig(level=logging.DEBUG)

solver = TwoCaptcha(api_key)
captcha_page_site_key = '6LfGNEoeAAAAALUsU1OWRJnNsF1xUvoai0tV090n'


def solve(captcha_page_site_key, url):
    try:
        result = solver.recaptcha(sitekey=captcha_page_site_key, url=url)
    except Exception as e:
        exit(e)

    return result.get('code')


def get_csrf_token(url):
    res = requests.get(url)
    soup = BeautifulSoup(res.text, 'lxml')
    csrf_el = soup.select_one('[name="csrfmiddlewaretoken"]')
    csrf_token = csrf_el.get('value')
    return csrf_token


if __name__ == '__main__':
    csrf_token = get_csrf_token(captcha_page_url)
    print('Received CSRF token', csrf_token)
    captcha = solve(captcha_page_site_key, captcha_page_url)
    print('Solved Captcha', captcha)

    payload = 'csrfmiddlewaretoken={}&g-recaptcha-response={}'
    headers = {
        'Content-Type': 'application/x-www-form-urlencoded',
        'Referer': 'https://www.scrapebay.com/spam',
        'Cookie': f'csrftoken={csrf_token}'
    }

    response = requests.post(captcha_page_url, headers=headers, data=payload.format(csrf_token, captcha))
    soup = BeautifulSoup(response.text, 'lxml')
    print('~' * 20)
    print(soup.select_one('td:last-child').get_text())
