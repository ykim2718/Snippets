"""
y, 2024.10.23 - 28
pyqt5 - moveToThread (3).py
"""

from PyQt5.QtCore import QObject, QThread, pyqtSignal
import sys
from PyQt5.QtWidgets import QApplication
import pandas as pd
import time
import threading


class Child(QObject):
    def __init__(self, parent):
        super().__init__(parent=parent)
        print(f"Child {threading.get_ident()=}")


class MyThread(QThread):

    def __init__(self):
        super().__init__()
        print(f"MyThread.init {threading.get_ident()=}")

    def run(self):
        print(f"MyThread.run {threading.get_ident()=}")
        child = Child(parent=self)  # TODO 2024.10.26, try to cause following error but failed
        # QObject: Cannot create children for a parent that is in a different thread error.
        for j in range(2):
            time.sleep(1)
            print(f"MyThread ({j}) {pd.Timestamp.now()}, {threading.get_ident()=}")
        QApplication.quit()  # QApplication.exit()


class Home(QObject):
    def __init__(self):
        super().__init__()
        print(f"Home {threading.get_ident()=}")
        self.thread = MyThread()
        # self.moveToThread(self.thread)
        self.thread.start()

    def task_finished(self, result):
        print(result)


app = QApplication(sys.argv)
print(f"app {threading.get_ident()=}")
parent = Home()
sys.exit(app.exec_())

