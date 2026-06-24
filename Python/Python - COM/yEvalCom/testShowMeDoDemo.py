"""
http://showmedo.com/videotutorials/video?name=2190050&fromSeriesID=219
"""


class ShowMeDoDemo:
    _public_methods_ = ['Factorial', 'Hello']
    _reg_progid_ = "testPythonCOM.demo"  # "ShowMeDo.Demo"
    # use
    # import pythoncom
    # print pythoncom.CreateGuid()
    # to make a GUID as they are machine-specific
    _reg_clsid_ = "{3F004234-0E4A-430B-85F0-0109DDAD6FBD}"

    # e.g. "{4D93DCBC-DE99-4D5A-ACFC-44F82BDB9889}"

    def Hello(self):
        "say Hello"
        return "Hello World!"

    def Factorial(self, n):
        "calculate n!"
        result = 1
        for value in range(2, n + 1):
            result = result * value
        # 1/0 # generates a ZeroDivision exception
        return result


if __name__ == "__main__":
    # use 'python com.py' to register the COM server
    # use 'python com.py --unregister' to unregister it
    print("Registering COM server...")
    import win32com.server.register

    win32com.server.register.UseCommandLine(ShowMeDoDemo)



    # In [2]: import pythoncom
    # In [3]: pythoncom.CreateGuid()
    # Out[3]: IID('{4D93DCBC-DE99-4D5A-ACFC-44F82BDB9889}')

    # C:\pyWin32_tutorial>python com.py
    # Registering COM server...
    # Registered: ShowMeDo.Demo


    # In Excel
    # Alt-F8 brings up the Macros dialog
    # Give it a name of 'Test', press Create
    # Make the code look like:
    # Sub Test()
    # Set Demo = CreateObject("ShowMeDo.Demo")
    # MsgBox Demo.Hello()
    # response = Demo.Factorial(1)
    # MsgBox response
    # End Sub
    # Use F5 to execute it

    # To develop code, we can edit live
    # but we have to close the VBA editor and Excel each time
    # we don't need to re-register (or unreg then reg) our COM server
