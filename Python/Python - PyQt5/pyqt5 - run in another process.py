"""
y, 2021.9.16
pyqt5 - run in another process.py
https://docs.python.org/3/library/multiprocessing.html#the-process-class
https://stackoverflow.com/questions/33236358/problems-with-connect-in-pyqt5
"""

import multiprocessing as mp
import os
from PyQt5.QtWidgets import QApplication
from PyQt5.QtNetwork import QNetworkAccessManager, QNetworkRequest, QNetworkReply
from PyQt5.QtCore import QEventLoop, QUrl


def f(url=None, _queue_for_returning=None):

    print(f"{__name__}.id={os.getpid()}")
    app = QApplication([])
    manager = QNetworkAccessManager()
    response = manager.get(QNetworkRequest(QUrl(url)))
    event = QEventLoop()
    response.finished.connect(event.quit)
    event.exec()
    html = str(response.readAll())  # in Python3 all strings are unicode, so QString is not defined
    if _queue_for_returning:
        _queue_for_returning.put(dict(pid=os.getpid(), html=html))


if __name__ == '__main__':

    print(f"{__name__}.id={os.getpid()}")
    url = 'https://stackoverflow.com'
    url = 'https://www.google.com'
    manager = mp.Manager()
    queue = manager.Queue()
    p = mp.Process(target=f, kwargs=dict(url=url, _queue_for_returning=queue))
    p.start()
    p.join()

    print(f"p.pid={p.pid}")
    print(f"p.name={p.name}")
    print(f"p.exitcode={p.exitcode}")

    if not queue.empty():
        result = queue.get()
        print(type(result), list(result), result['pid'], result['html'][:50])
