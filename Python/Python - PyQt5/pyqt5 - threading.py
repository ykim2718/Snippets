"""
y, 2024.9.30, 10.25
pyqt5 - threading.py
"""

from PyQt5.QtCore import QThread, pyqtSignal
import time
from PyQt5.QtCore import QObject
from PyQt5.QtWidgets import QApplication
import sys
import threading


class Worker(QThread):
    result = pyqtSignal(object)

    def __init__(self, obj, parent=None):
        super().__init__(parent)
        self.obj = obj

    def run(self):
        # Simulate a long-running task
        for i in range(5):
            time.sleep(1)
            self.result.emit(f'Iteration {i} with {self.obj}, {threading.get_ident()=}')
        QApplication.quit()  # QApplication.exit()


class MyQObject(QObject):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def __str__(self):
        return self.name


class App:
    def __init__(self):
        self.app = QApplication(sys.argv)
        self.my_object = MyQObject('TestObject')
        self.worker = Worker(self.my_object)
        self.worker.result.connect(self.handle_result)
        self.worker.start()

    def handle_result(self, value):
        print(value)

    def run(self):
        sys.exit(self.app.exec_())


if __name__ == '__main__':
    app = App()
    print(f'main {threading.get_ident()=}')
    app.run()
