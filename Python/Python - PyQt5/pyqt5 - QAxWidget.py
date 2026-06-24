"""
y, 2020.6.9 - 10
pyqt5 - QAxWidget.py.py
https://sdk.trueconf.com/examples/callx-python-example.html
"""

from PyQt5.QAxContainer import QAxWidget  # pip install pyqt5==5.12.3 PyQtWebEngine==5.12.1
from PyQt5.QtWidgets import QApplication
import sys

# HKEY_CLASSES_ROOT\EPADM2.EpAdm2Ctrl.1
# CLSID={C63E3330-049F-4C31-B47E-425C84A5A725}
# File=C:\Windows\SysWOW64\EpAdm2.ocx
# regsvr32 EpAdm2.ocx


if __name__ == '__main__':

    app = QApplication(sys.argv)
    if False:
        ocx = QAxWidget('EPADM2.EpAdm2Ctrl.1')
    else:
        ocx = QAxWidget('{C63E3330-049F-4C31-B47E-425C84A5A725}')
    print(ocx)
    print(ocx.dynamicCall("GetSecureBox()"))
    print(ocx.dynamicCall("IsLoggedin()"))
