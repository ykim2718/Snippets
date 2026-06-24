"""
y, 2016.10.16
http://codeprogress.com/python/libraries/pyqt/showPyQTExample.php?index=375&key=PyQtContextMenuEvent&version=5
"""
from PyQt5 import QtWidgets
from PyQt5 import QtCore
import sys


class myMainWindow(QtWidgets.QMainWindow):
    def contextMenuRequested(self, point):
        menu = QtWidgets.QMenu()

        action1 = menu.addAction("Set Size 100x100")
        action2 = menu.addAction("Set Size 500x500")

        action2.triggered.connect(self.slotShow500x500)
        action1.triggered.connect(self.slotShow100x100)
        menu.exec_(self.mapToGlobal(point))

    def slotShow500x500(self):
        self.setFixedSize(500, 500)
        self.show()

    def slotShow100x100(self):
        self.setFixedSize(100, 100)
        self.show()


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = myMainWindow()
    menu = QtWidgets.QMenu()

    # Resize width and height
    window.resize(250, 250)
    window.setWindowTitle('PyQt Context Menu Example')
    window.setContextMenuPolicy(QtCore.Qt.CustomContextMenu);

    window.customContextMenuRequested[QtCore.QPoint].connect(window.contextMenuRequested)
    window.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()