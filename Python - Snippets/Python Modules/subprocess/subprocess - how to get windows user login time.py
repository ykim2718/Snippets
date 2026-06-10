"""
y, 2020.3.27
subprocess - how to get windows user login time.py
https://docs.microsoft.com/ko-kr/windows-server/administration/windows-commands/quser
https://stackoverflow.com/questions/46990857/python-3-7-how-to-get-the-windows-user-login-time
"""

"""
from subprocess import check_output
import sys

get_result = check_output("wmic netlogin get name, fullname, lastlogon", shell=True, stderr=False)

print(get_result)

clean_result = str(get_result).lstrip("b'").rstrip("'").replace("\\r\\r\\n", "\n").replace('\n\n', '\n').split('\n')[2:-1]

for items in clean_result:

    print(items.lstrip().rstrip())

xxxx
"""

case = 3

if case == 1:

    import win32com.client
    import time
    import pandas as pd

    strComputer = "."
    objWMIService = win32com.client.Dispatch("WbemScripting.SWbemLocator")
    objSWbemServices = objWMIService.ConnectServer(strComputer, "root\cimv2")
    colItems = objSWbemServices.ExecQuery("SELECT * FROM Win32_NetworkLoginProfile")

    log_ons = dict()
    for objItem in colItems:
        if objItem.LastLogon is not None:
            host_name, user_name = str(objItem.Name).split('\\')
            try:
                logon_time = pd.to_datetime(objItem.LastLogon.split('+')[0], format="%Y%m%d%H%M%S.%f")
                log_ons[user_name] = logon_time
            except:
                pass

    print(log_ons)

elif case == 2:
    import win32net
    import time

    users, nusers, _ = win32net.NetUserEnum(None, 2)
    for user in users:
        print("%-20s %s" % (user['name'], time.ctime(user['last_logon'])))

elif case == 3:

    import subprocess
    import re
    import pandas as pd
    import sys
    import numpy as np

    # https://www.exefiles.com/ko/exe/quser-exe/
    result = subprocess.check_output("quser", shell=True, stderr=False)
    try:
        result = str(result, 'utf-8')
    except UnicodeDecodeError as ex:
        result = str(result, 'euc-kr')
    result = result.strip()
    result = re.split(r'\W{2,}', result)
    assert len(result) % 6 == 0
    result = np.array(result).reshape(-1, 6)
    frame = pd.DataFrame(result[1:], columns=result[0])
    logon_time = frame.columns[5]  # 로그온 시간
    frame[logon_time] = frame[logon_time].str.replace('오전', 'AM')
    frame[logon_time] = frame[logon_time].str.replace('오후', 'PM')
    frame[logon_time] = pd.to_datetime(frame[logon_time], format="%Y-%m-%d %p %H:%M")
    try:
        print(frame.to_markdown())
    except:
        print(frame)
    print(frame.dtypes)
