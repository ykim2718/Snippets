import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


class Form(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.label = QLabel("Hello, PyQt")
        layout = QVBoxLayout()
        layout.addWidget(self.label)
        self.setLayout(layout)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = Form()
    form.show()
    app.exec_()
