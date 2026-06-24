"""
y, pyqt5 - simple dialog for un and pw input.py, 2018.8.16
"""

import sys
from PyQt5.QtWidgets import (QApplication, QDialog, QLabel, QLineEdit, QPushButton,
                             QHBoxLayout, QVBoxLayout)
from PyQt5.QtCore import (pyqtSlot, Qt)


class MyUnPwInputDialog(QDialog):
    """ y, 2018.8.16 """

    un, pw = None, None

    def __init__(self, title="Prompt dialog ..."):
        super().__init__()
        self.setWindowTitle(title)

        col1 = QVBoxLayout()
        self.label1 = QLabel(self)
        self.label1.setText("un")
        self.label1.setAlignment(Qt.AlignRight | Qt.AlignVCenter)
        self.label2 = QLabel(self)
        self.label2.setText("pw")
        self.label2.setAlignment(Qt.AlignRight | Qt.AlignVCenter)
        self.ok = QPushButton('ok', self)
        self.ok.setFixedWidth(40)
        self.ok.clicked.connect(self.ok_click)
        col1.addWidget(self.label1)
        col1.addWidget(self.label2)
        col1.addWidget(self.ok)

        col2 = QVBoxLayout()
        self.le1 = QLineEdit()
        self.le2 = QLineEdit()
        self.cancel = QPushButton('cancel', self)
        self.cancel.setFixedWidth(60)
        self.cancel.clicked.connect(self.cancel_click)
        col2.addWidget(self.le1)
        col2.addWidget(self.le2)
        col2.addWidget(self.cancel)

        hbox = QHBoxLayout()
        hbox.addLayout(col1)
        hbox.addLayout(col2)

        self.setLayout(hbox)

    @pyqtSlot()
    def ok_click(self):
        self.un = self.le1.text()
        self.pw = self.le2.text()
        print('ok', self.un, self.pw)
        self.close()

    @pyqtSlot()
    def cancel_click(self):
        self.un = self.pw = None
        print('cancel')
        self.close()

app = QApplication(sys.argv)
ex = MyUnPwInputDialog()
ex.show()
app.exec_()
print(ex.un, ex.pw)
