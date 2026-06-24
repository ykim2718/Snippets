"""
y, 2021.9.16
pyqt5 - read url.py
https://stackoverflow.com/questions/33236358/problems-with-connect-in-pyqt5
"""

import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QtNetwork import QNetworkAccessManager, QNetworkRequest, QNetworkReply
from PyQt5.QtCore import QEventLoop, QUrl

app = QApplication(sys.argv)
url = 'https://stackoverflow.com'
url = 'https://www.google.com'
manager = QNetworkAccessManager()
response = manager.get(QNetworkRequest(QUrl(url)))
event = QEventLoop()
response.finished.connect(event.quit)
event.exec()
html = str(response.readAll())  # in Python3 all strings are unicode, so QString is not defined
print(html)
