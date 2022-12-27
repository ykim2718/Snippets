"""
y, selenium - short selling query in korea.py, 2016.9.4, 2017.7.30

python selenium, find out when a download has completed?
--------------------------------------------------------
http://www.obeythetestinggoat.com/how-to-get-selenium-to-wait-for-page-load-after-a-click.html
https://stackoverflow.com/questions/34338897/python-selenium-find-out-when-a-download-has-completed  ★

"""

import os
import sys
import datetime as dt
import re
import time
from warnings import warn


def get_files_in_a_folder(folder_path, recursive=False):
    """ y (copyRight) 2016.7.25, 9.21 """

    all_files = []
    for root, dirs, files in os.walk(folder_path, topdown=True):
        if recursive is False:
            if root != folder_path:
                continue
        for name in files:
            all_files.append(os.path.join(root, name))
    return all_files


def get_files_at_a_given_time_range(file_pattern, folder_path, time_range=(), time_for='modification'):
    """ y, 2017.7.30 """

    assert os.path.isdir(folder_path)
    if len(time_range):
        assert len(time_range) == 2
        assert all([isinstance(a_time, dt.datetime) for a_time in time_range])
        assert time_range[0] < time_range[1], '{!s} < {!s}'.format(*time_range)
    assert time_for in ['creation', 'modification']

    get_file_time = {
        'creation': os.path.getctime,
        'modification': os.path.getmtime,
    }[time_for]

    files = get_files_in_a_folder(folder_path)
    matched_files = []
    for a_file in files:
        if re.match(file_pattern, os.path.basename(a_file)):
            mtime = get_file_time(a_file)
            if time_range[0] <= dt.datetime.fromtimestamp(mtime) <= time_range[1]:
                matched_files.append(a_file)

    return matched_files


################################################################################

chrome_download_folder_path = r'c:\Users\ykim7\Downloads'

from selenium import webdriver
# from selenium.webdriver.support.ui import WebDriverWait
# from selenium.webdriver.support import expected_conditions

chrome_driver_path = r"c:\Y\Chromedriver win32\chromedriver.exe"
driver = webdriver.Chrome(chrome_driver_path)
# http://selenium-python.readthedocs.io/waits.html
# An implicit wait tells WebDriver to poll the DOM for a certain amount of time when trying to
# find any element (or elements) not immediately available. The default setting is 0.
# Once set, the implicit wait is set for the life of the WebDriver object.
driver.implicitly_wait(10)

driver.get("http://short.krx.co.kr/contents/SRT/02/02030100/SRT02030100.jsp")
button_total_for_search = '//*[@id="allSchBtna87ff679a2f3e71d9181a67b7542122c"]'
button_1m_xpath = '//*[@id="formc4ca4238a0b923820dcc509a6f75849b"]/dl[3]/dd/div/button[3]'
button_6m_xpath = '//*[@id="formc4ca4238a0b923820dcc509a6f75849b"]/dl[3]/dd/div/button[4]'
button_excel_xpath = '// *[ @ id = "1679091c5a880faf6fb5e6087eb1b2dc"] / button'

try:
    # btn6m = driver.find_element_by_css_selector("button-mdi-group")
    driver.find_element_by_xpath(button_total_for_search).click()
    driver.find_element_by_xpath(button_1m_xpath).click()
    driver.find_element_by_xpath(button_excel_xpath).click()
except Exception as ex:
    warn(ex)
    sys.exit(1)
else:
    driver.quit()
    start_time = dt.datetime.now()
    stop_time = start_time + dt.timedelta(seconds=30)
    while dt.datetime.now() < stop_time:
        files = get_files_at_a_given_time_range(
            'data\s*(\(\d+\))*.xls[x]*', chrome_download_folder_path, time_range=(start_time, stop_time))
        if len(files):
            if len(files) == 1:
                print(files)
                break
            else:
                sys.exit(3)
        else:
            time.sleep(1)
    else:
        sys.exit(2)

sys.exit(0)


