"""
y, 2022.2.22; 2024.10.7
pyqt5 - quit by qthread.py
"""

import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QCoreApplication, QThread
import time


class MyThread(QThread):
    def __init__(self, parent=None):
        super().__init__(parent)

    def run(self):
        print('run() ... sleeping')
        print(f"{QThread.currentThread()=} in MyThread")
        for j in range(3):
            print(f"sleeping .. {j}")
            time.sleep(1)
        QCoreApplication.instance().quit()


my_thread = MyThread()
print('before start')
my_thread.start()
print('after start')

app = QApplication(sys.argv)

if False:
    sys.exit(app.exec_())
else:
    app.exec_()
print('end')
