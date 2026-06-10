"""
y, 2020.5.14, 6.9
requests - basic.py
"""

import requests
import types

urls = types.SimpleNamespace(
    **{
        'loginUrl': 'https://www.samsung.net/portal/login/login.do',
        'trayLoginCheckUrl': 'https://www.samsung.net/portal/login/traylogin_check.do',
        'ssoLoginUrl': 'https://www.samsung.net/portal/login/ssologin.do',
        'abLogoutUrl': 'https://www.samsung.net/portal/login/abnormal_logout.do',
        'groupLoginDomain': 'http://www.samsung.net',
        'bigdata': 'http://bigdata.samsungds.net:8080',
    }
)
url = 'http://www.samsung.net/portal/default.jsp'
url = urls.groupLoginDomain
url = 'http://kr2.samsung.net/portal/desktop/main.do'
response = requests.get(url)
print(f"text={response.text.strip()}")
print(f"status_code={response.status_code}")
