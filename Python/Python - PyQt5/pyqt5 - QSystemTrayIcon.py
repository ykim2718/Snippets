"""
y, 2024.10.26
pyqt5 - QSystemTrayIcon.py
https://stackoverflow.com/questions/36453462/pyqt5-qobject-cannot-create-children-for-a-parent-that-is-in-a-different-thread
https://www.pythonguis.com/faq/built-in-qicons-pyqt/
"""

import time
import sys
import threading
from PyQt5 import QtGui
from PyQt5 import QtWidgets
from PyQt5 import QtCore


class SystemTrayIcon(QtWidgets.QSystemTrayIcon):
    def __init__(self, icon=None, parent=None):
        # https://www.pythonguis.com/faq/built-in-qicons-pyqt/
        icon = QtGui.QIcon(QtWidgets.QApplication.style().standardPixmap(QtWidgets.QStyle.SP_DialogHelpButton))
        QtWidgets.QSystemTrayIcon.__init__(self, icon, parent)

        self.menu = QtWidgets.QMenu(parent)
        self.setContextMenu(self.menu)

        self.build_menu()
        self.show()

        # see http://pyqt.sourceforge.net/Docs/PyQt5/signals_slots.html for more information
        self.signal = MySignal()
        self.signal.sig_no_args.connect(self.build_menu)
        self.signal.sig_with_str.connect(self.print_string)

    def build_menu(self):
        ''' This function should be called in order to rebuild
        the right-click menu for the systray icon'''
        global list_dict_streams
        self.menu.clear()

        exitAction = self.menu.addAction("Exit")
        exitAction.triggered.connect(self._exit)

        for x in list_dict_streams:
            self.menu.addAction(x)

    def print_string(self, str):
        print(str)

    def _exit(self):
        QtCore.QCoreApplication.exit()


class MySignal(QtCore.QObject):
    ''' Why a whole new class? See here:
    https://stackoverflow.com/a/25930966/2441026 '''
    sig_no_args = QtCore.pyqtSignal()
    sig_with_str = QtCore.pyqtSignal(str)


list_dict_streams = ["1"]


def work_thread(trayIcon):
    ''' Will add one menu item to the systray menu every 5 seconds
    and will send a signal with a string '''
    global list_dict_streams

    while True:
        trayIcon.signal.sig_no_args.emit()
        trayIcon.signal.sig_with_str.emit("String emitted")
        list_dict_streams.append(str(len(list_dict_streams) + 1))
        time.sleep(5)


def main():
    app = QtWidgets.QApplication(sys.argv)
    trayIcon = SystemTrayIcon()

    t = threading.Thread(target=work_thread, args=(trayIcon,))
    t.daemon = True  # otherwise the 'Exit' from the systray menu will not work
    t.start()

    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
