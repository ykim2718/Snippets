"""
y, 2024.10.7
pyqt5 - moveToThread.py
"""

from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QObject, QThread, QTimer, QCoreApplication, QMetaObject, Qt, pyqtSlot
import sys


class Worker(QObject):

    # pyqtSlot is used to mark the run method as a slot, making it invokable from other threads or from QML12.
    @pyqtSlot()
    def run(self):
        print(f"{QThread.currentThread()=} in Worker")
        QCoreApplication.instance().quit()


def show_message():
    print('show_message()')
    QCoreApplication.instance().quit()


app = QApplication(sys.argv)  # Can see 'end...'


delay = 2
if False:
    QTimer.singleShot(delay * 1000, show_message)
else:
    # Create a Worker object
    worker = Worker()
    # Create a QThread object
    thread = QThread()
    # Move the Worker object to the thread
    worker.moveToThread(thread)
    # Start the new thread
    thread.start()
    print(f"{QThread.currentThread()=}")
    # QTimer.singleShot(delay * 1000, thread.run)  # NOT WORKING
    QMetaObject.invokeMethod(worker, "run", Qt.QueuedConnection)


# app = QApplication(sys.argv)  # Can't see 'end...'
app.exec_()
print('end...')