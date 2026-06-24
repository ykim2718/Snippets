import sys
from PyQt5.QtGui import QApplication, QLabel

app = QApplication(sys.argv)
label = QLabel("Hello PyQt")
label.show()
app.exec_()
