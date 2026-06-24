"""
y, 2024.10.28
pyqt5 - pythoncom.py
Q):
    com dynamicCall causes to create QObject ?
A by copilot):
    Yes, dynamicCall in PyQt5 can indeed cause the creation of QObjects indirectly,
    especially when dealing with COM objects in a multi-threaded environment.
    When you make a dynamicCall, it may internally involve creating or manipulating QObjects,
    which must happen in the same thread as the QApplication.
    To avoid thread issues with COM objects in PyQt5, you typically need to ensure that all COM interactions occur
    within the main thread or use proper signaling to transfer data between threads.
"""

import sys
import pythoncom
import PyQt5.QtCore as QtCore
import PyQt5.QtWidgets as QtWidgets
import threading


class Worker(QtCore.QThread):
    resultReady = QtCore.pyqtSignal(object)

    def run(self):
        pythoncom.CoInitialize()
        print(f"Worker {threading.get_ident()=}")
        # Your COM interactions here
        # Assume result is the object you get from COM interaction
        result = "Your COM result"
        self.resultReady.emit(result)
        pythoncom.CoUninitialize()


class MainWindow(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        print(f"MainWindow {threading.get_ident()=}")
        self.worker = Worker()
        self.worker.resultReady.connect(self.handleResult)
        self.worker.start()

    def initUI(self):
        self.label = QtWidgets.QLabel("Waiting for COM result...", self)
        layout = QtWidgets.QVBoxLayout(self)
        layout.addWidget(self.label)
        self.setLayout(layout)

    def handleResult(self, result):
        self.label.setText(f"COM Result: {result}")


app = QtWidgets.QApplication(sys.argv)
mainWin = MainWindow()
mainWin.show()
sys.exit(app.exec_())
