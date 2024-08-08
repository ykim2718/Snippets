"""
y, 2024.1.11
stem - multiple requests session.py
https://stem.torproject.org/api/control.html
"""

from stem import Signal
from stem.control import Controller
import requests
import typing
import re
import time


class SingletonClass(object):
    """
    y,  2023.2.18
        2024.1.11

    References
    ----------
    [1] https://www.geeksforgeeks.org/singleton-pattern-in-python-a-complete-guide/
    """
    
    def __new__(cls, *args, **kwargs):
        if not hasattr(cls, 'instance'):
            cls.instance = super(SingletonClass, cls).__new__(cls)
        return cls.instance


class MultipleRequestsSession(SingletonClass):
    """ y, 2023.12.21 - 22 """

    _ip_address_pattern = \
        "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"

    def __init__(self, session_count=5, max_session_count=100, skip_my_ip=True):
        """
        y,  2023.12.21 - 22
            2024.1.11
        """

        print(f"{session_count=}")

        self.my_ip = self.get_session_ip_address()  # 118.220.52.143
        self.my_sessions = self.generate_sessions(
            session_count=session_count, max_session_count=max_session_count, skip_my_ip=skip_my_ip)
        
    def generate_sessions(self, session_count=5, max_session_count=100, skip_my_ip=True):
        """ y, 2024.1.11 """
        # generate sessions with different ips up to session_count, but very lazy process, 2024.1.11

        port1, port2 = 9050, 9051

        def _get_session_and_ip(port=9050) -> typing.Tuple[str, str]:
            # Tor uses the 9050 port as the default socks port
            session = requests.session()
            session.proxies = {
                'http': f"socks5://127.0.0.1:{port}",
                'https': f"socks5://127.0.0.1:{port}"
            }
            ip_address = self.get_session_ip_address(session)
            if not re.match(self._ip_address_pattern, ip_address):
                session = ''
            return session, ip_address

        def _renew_ip(port=9050):
            with Controller.from_port(port=port) as c:
                # print(f"{c.is_newnym_available()=}")
                c.authenticate(password="ad3ld!axsf2" + str(port))
                c.signal(Signal.NEWNYM)
                delay = c.get_newnym_wait()  # 10 sec
            return delay

        sessions = dict()
        for j in range(max_session_count):
            session, ip_address = _get_session_and_ip(port1)
            if session:
                if skip_my_ip and ip_address == self.my_ip:
                    continue
                sessions[ip_address] = session
                if len(sessions) == session_count:
                    break
            delay = _renew_ip(port2)
            time.sleep(delay)

        return sessions

    def __repr__(self):
        """ y, 2024.1.11 """

        text = f"{self.__class__.__name__}("
        text += f"my_ip={self.my_ip}, "
        text += f"count={len(self.my_sessions)}, ip={tuple(self.my_sessions)}"
        text += ")"
        return text

    def get_session_ip_address(self, session=None) -> str:
        """
        y,  2023.12.21 - 22
            2024.1.11
        """

        if isinstance(session, requests.sessions.Session):
            try:
                r = session.get('https://api.myip.com/')
                if r.status_code == 200:
                    return r.json()['ip']
            except Exception as ex:
                r = session.get('https://ident.me')
                return r.text
        else:
                r = requests.get('https://ident.me')
        return r.text


mrs = MultipleRequestsSession(session_count=5)
print(f"{mrs=}")