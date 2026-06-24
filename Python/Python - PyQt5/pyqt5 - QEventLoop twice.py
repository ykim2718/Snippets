"""
y, 2024.10.29
pyqt5 - QEventLoop twice.py
copilot
"""

from PyQt5.QtCore import QThread, pyqtSignal, QEventLoop, QObject
from PyQt5.QtWidgets import QApplication, QLabel
import sys


class Worker(QThread):
    finished = pyqtSignal()

    def run(self):
        # Simulate some work
        self.msleep(2000)
        self.finished.emit()


class MainApp(QObject):
    def __init__(self):
        super().__init__()
        self.event_loop = QEventLoop()
        self.event_loop_running = False
        self.worker = Worker()
        self.worker.finished.connect(self.on_worker_finished)

    def start_worker(self):
        self.worker.start()
        if not self.event_loop_running:
            self.event_loop.exec_()  # Start the event loop

    def on_worker_finished(self):
        print("Worker finished")
        if self.event_loop_running:
            self.event_loop.quit()  # Quit the event loop


app = QApplication(sys.argv)
main_app = MainApp()

# Start the event loop the first time
print("Starting worker for the first time")
main_app.start_worker()

# Start the event loop again
print("Starting worker for the second time")
main_app.start_worker()

sys.exit(app.exec_())
