"""
http://docs.activestate.com/activepython/2.6/pywin32/html/com/win32com/HTML/QuickStartServerCom.html
"""


class HelloWorld:
    _reg_clsid_ = "{7CC9F362-486D-11D1-BB48-0000E838A65F}"
    _reg_desc_ = "Python Test COM Server"
    _reg_progid_ = "testPythonCOM2.demo"
    _public_methods_ = ['Say']

    def Say(self):
        "say Hello"
        return "Hello World!"


if __name__ == '__main__':
    import win32com.server.register

    win32com.server.register.UseCommandLine(HelloWorld)
