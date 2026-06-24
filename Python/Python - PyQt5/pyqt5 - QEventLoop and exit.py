"""
y, 2024.2.28 - 29
pyqt5 - QEventLoop and exit.py
"""

from PyQt5.QtCore import QEventLoop, pyqtSignal, QTimer, QObject
from PyQt5.QtWidgets import QApplication


class EventLoop(QObject):
    on_end_signal = pyqtSignal()

    def __init__(self):
        super().__init__()
        self._loop = QEventLoop()

    def __call__(self, signal):
        signal.connect(self.quit)
        print(1000)
        self._loop.exec_()
        print(1003)
        self.on_end_signal.emit()
        print(1005)

    def set_callback(self, callback):
        self.on_end_signal.connect(callback)

    def quit(self):
        self._loop.exit()
        print(1001)


class Signaller(QObject):  # Qt signals only work with classes deriving from QObject
    terminate_signal = pyqtSignal()

    def __init__(self, delay=2):
        super().__init__()
        QTimer.singleShot(int(delay * 1000), self.terminate)

    def terminate(self):
        print(f"class={self.__class__.__name__}.terminate()")
        self.terminate_signal.emit()
        print(1002)

    def on_end(self):
        print(1004)


if __name__ == '__main__':

    app = QApplication([])
    signal_holder = Signaller()
    loop = EventLoop()
    loop.set_callback(signal_holder.on_end)
    loop(signal_holder.terminate_signal)
    app.exec_()
