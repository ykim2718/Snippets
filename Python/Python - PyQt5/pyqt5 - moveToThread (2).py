"""
y, 2024.10.23 - 28
pyqt5 - moveToThread (2).py
"""

from PyQt5.QtCore import QObject, QThread, pyqtSignal
import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QAxContainer import QAxWidget  # pip install PyQt5 --user
import time
import pandas as pd
import pythoncom


class MyThread(QThread):

    def __init__(self):
        super().__init__()

    def run(self):
        for j in range(3):
            print(f"({j}) {pd.Timestamp.now()}")
            time.sleep(1)
        QApplication.quit()  # QApplication.exit()


class Parent(QObject):
    def __init__(self, _threads=[0]):
        super().__init__()

        j = 0
        self.thread = MyThread()  # local variable thread is not working 2024.10.23
        self.moveToThread(self.thread)
        self.thread.start()


class Child(QObject):
    def __init__(self, parent):
        super().__init__(parent=parent)


app = QApplication(sys.argv)
parent = Parent()
child = Child(parent)
sys.exit(app.exec_())

