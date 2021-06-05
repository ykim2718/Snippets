"""
y, pyqt5 - fileopen dialog.py, 2019.1.23
https://pythonspot.com/pyqt5-file-dialog/
"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QFileDialog


class FileOpenDialog(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()
        self.openFileNameDialog()

    def initUI(self):
        self.title = 'PyQt5 file dialogs'
        self.left = 10
        self.top = 10
        self.width = 640
        self.height = 480
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

    def openFileNameDialog(self):
        options = QFileDialog.Options()
        options |= QFileDialog.DontUseNativeDialog
        fileName, _ = QFileDialog.getOpenFileName(self, "QFileDialog.getOpenFileName()", "",
                                                  "All Files (*);;Python Files (*.py)", options=options)
        if fileName:
            print(fileName)
            # app.quit()

if __name__ == '__main__':

    app = QApplication(sys.argv)
    FileOpenDialog().show()
    # sys.exit(app.exec_())