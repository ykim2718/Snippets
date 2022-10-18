"""
y, 2022.10.18
pywinauto - find_elements.py
"""

import pywinauto as pwa

for e in pwa.findwindows.find_elements():
    print(f"{e=}")

"""
e=<win32_element_info.HwndElementInfo - '', Shell_TrayWnd, 66244>
e=<win32_element_info.HwndElementInfo - '', NotifyIconOverflowWindow, xxxxx>  <<< ????
e=<win32_element_info.HwndElementInfo - '', Shell_SecondaryTrayWnd, xxxxx>  <<< ????
e=<win32_element_info.HwndElementInfo - 'yStudy on code - Python – pywinauto - find_elements.py Administrator', SunAwtFrame, 524722>
e=<win32_element_info.HwndElementInfo - 'Y^ - Total Commander (x64) 9.0a - NOT REGISTERED', TTOTAL_CMD, 262776>
e=<win32_element_info.HwndElementInfo - '내게쓰기 : 네이버 메일 - Chrome', Chrome_WidgetWin_1, 1510398>
e=<win32_element_info.HwndElementInfo - '', ApplicationFrameWindow, 1771058>
e=<win32_element_info.HwndElementInfo - '', Windows.UI.Core.CoreWindow, 1246368>
e=<win32_element_info.HwndElementInfo - '설정', ApplicationFrameWindow, 657328>
e=<win32_element_info.HwndElementInfo - 'NVIDIA GeForce Overlay', CEF-OSC-WIDGET, 263518>
e=<win32_element_info.HwndElementInfo - '', NarratorHelperWindow, 1575806>
e=<win32_element_info.HwndElementInfo - 'PDSTYLEAGENT', PDSTYLEAGENT, 132476>
e=<win32_element_info.HwndElementInfo - 'Microsoft Text Input Application', Windows.UI.Core.CoreWindow, 263254>
e=<win32_element_info.HwndElementInfo - '', EdgeUiInputTopWndClass, 1771864>
e=<win32_element_info.HwndElementInfo - '', DummyDWMListenerWindow, 66464>
e=<win32_element_info.HwndElementInfo - '', DummyDWMListenerWindow, 66414>
e=<win32_element_info.HwndElementInfo - '', DummyDWMListenerWindow, 66412>
e=<win32_element_info.HwndElementInfo - '관리자:  control_daily_op.bat : daily-operation', ConsoleWindowClass, 789618>
e=<win32_element_info.HwndElementInfo - '관리자:  measure_korea_on_weekdays_with_ebest.bat : update_consensus_price_from_ebest  ~2h50m', ConsoleWindowClass, 10947754>
e=<win32_element_info.HwndElementInfo - 'Program Manager', Progman, 131840>
"""

app = pwa.Application(backend='uia').connect(path='explorer.exe')
app_icons = app.window(class_name='Shell_SecondaryTrayWnd')
app_icons.dump_tree()

"""
?
"""