"""
y, 20201.9.10
pyqt5 - catch exception.py
https://stackoverflow.com/questions/55819330/catching-exceptions-raised-in-application
https://wikidocs.net/21866  >> menubar
https://wikidocs.net/90850
"""


import sys
import traceback
from PyQt5.QtWidgets import (
    QApplication, QSizePolicy, QFileDialog, QMainWindow, QAction, QMessageBox, QTableWidgetItem)
from PyQt5.QtGui import (QIcon)
import pathlib
import datetime as dt


class MyApp(QMainWindow):
    def __init__(self):
        self.app = QApplication(sys.argv)
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle(pathlib.Path(__file__).name)
        self.setGeometry(300, 300, 400, 100)

        raiseError = QAction(QIcon(''), 'Raise', self)
        raiseError.setStatusTip('Raise error intetionally')
        raiseError.triggered.connect(self.raise_error)

        exitAction = QAction(QIcon('exit.png'), 'Exit', self)
        exitAction.setShortcut(('Ctrl+Q'))
        exitAction.setStatusTip('Exit application')
        exitAction.triggered.connect(self.app.quit)

        self.statusBar().showMessage('Ready')

        menuBar = self.menuBar()
        menuBar.setNativeMenuBar(False)
        fileMenu = menuBar.addMenu('&File')
        fileMenu.addAction(raiseError)
        fileMenu.addAction(exitAction)

        self.show()

    def exec(self):
        return self.app.exec()

    def raise_error(self):
        print('raise error ...', dt.datetime.now())
        1/0


def excepthook(exc_type, exc_value, exc_tb):
    tb = ''.join(traceback.format_exception(exc_type, exc_value, exc_tb))
    print('error catched:')
    print('error message:\n', tb)
    QApplication.quit()
    # or QApplication.exit(0)


sys.excepthook = excepthook
my_app = MyApp()
my_app.show()
ret = my_app.exec()
print('event loop exited', f"ret={ret}")
