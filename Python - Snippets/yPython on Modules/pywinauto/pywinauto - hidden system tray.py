"""
y, 2021.1.26, ~2.19; 2022.10.16 - 18
pywinauto - hidden system tray.py.py
https://stackoverflow.com/questions/50464576/how-to-get-specific-system-tray-icon-using-pywinauto
https://pywinauto.readthedocs.io/en/latest/HowTo.html?highlight=context%20menu#how-to-access-the-system-tray-aka-systray-aka-notification-area
https://stackoverflow.com/questions/67657837/cant-send-keys-to-the-background-window-error-atttributeerror-neither-gui-el
    form.keyboard.send_keys('{a down}')
    form.keyboard.send_keys('{a up}')
https://github.com/pywinauto/pywinauto/issues/247
    Do not use TypeKeys, ClickInput and derived functions which require active desktop.
    Other methods just send window messages that work without active desktop and often for a minimized window.
"""

# import sys
# sys.coinit_flags = 2  # COINIT_APARTMENTTHREADED

import pywinauto as pwa
from pywinauto import taskbar
import time

print(f"{pwa.__version__=}")

case = 4

if case == 1:  # NOT WORKING
    # https://pywinauto.readthedocs.io/en/latest/HowTo.html#how-to-access-the-system-tray-aka-systray-aka-notification-area
    import pywinauto.application as pwa
    app = pwa.Application().connect(path='explorer')
    systray_icons = app.ShellTrayWnd.NotificationAreaToolbar
    print(systray_icons)
    # systray_icons.ClickSystemTrayIcon(0)
    systray_icons.ClickHiddenSystemTrayIcon(0)
    # systray_icons.ClickHiddenSystemTrayIcon('Robo3T 1.4.0', exact=True, double=True).click()
elif case == 2:  # WORKING at office >> NOT at home 2022.10.17
    # https://stackoverflow.com/questions/72905986/pywinauto-how-to-right-click-in-systemtray-select-an-item-then-subitem
    # https://pywinauto.readthedocs.io/en/latest/code/pywinauto.findwindows.html  ★★★
    d = pwa.Desktop(backend='uia')
    for window in d.windows():
        print(f"{window.window_text()=}")
    if False:  # working at office, not at home, 2022.10.18
        d['작업 표시줄'].dump_tree()
        d['작업 표시줄'].child_window(title='알림 펼침').click()
    else:  # working at home as well as headless mode, 2022.10.18 ^__^;;
        d.window(title='작업 표시줄', top_level_only=False, visible_only=False).child_window(title='알림 펼침').click()
elif case == 3:  # WORKING at office >> NOT at home 2022.10.16
    # https://stackoverflow.com/questions/62190055/handling-context-menu-of-the-taskbar-icon-with-pywinauto
    app = pwa.Application(backend="uia").connect(path="explorer.exe")
    sti = app.window(class_name="Shell_TrayWnd")
    # sti.child_window(title="Notification Chevron").wrapper_object().click()  # 갈매기형 펼침 단추
    sti.child_window(title="알림 펼침").wrapper_object().click()  # 갈매기형 펼침 단추  << working
    time.sleep(1)
    app = pwa.Application(backend="uia").connect(class_name="NotifyIconOverflowWindow")  # 오버플로 알림 영역
    app_icons = app.window(class_name="NotifyIconOverflowWindow")
    app_icons.wait('visible', timeout=30, retry_interval=3)
    # app_icons.dump_tree()  # << working
    app_icon = app_icons.child_window(title='Realtek HD 오디오 관리자')
    if False:  # working in headful model, not in headless mode
        app_icon.click_input(button='right')
        app = pwa.Application(backend='uia').connect(path=r'C:\Program Files\Realtek\Audio\HDA\RAVCpl64.exe')
        app['Menu']['사운드 관리자'].click_input()  # .click() is not working
    else:  # for headless mode
        """
        0x600ec '' 'Shell_TrayWnd' Fri Feb 19 13:55:31 2021
        0x1015c '' 'NotifyIconOverflowWindow' Fri Feb 19 13:55:32 2021
        0x2006c 'Realtek HD Audio CPL for Vista' 'Afx:0000000140000000:0' Fri Feb 19 13:55:34 2021
        """
        'Realtek HD Audio CPL for Vista'
        # app_icon.dump_tree()
        app_icon.double_click_input(button='right')  # working only in headful mode, 2022.10.17
        # app_icon.send_chars('{ENTER}')  # not working
        time.sleep(1)
        app = pwa.Application(backend='uia').connect(path=r'C:\Program Files\Realtek\Audio\HDA\RAVCpl64.exe')
        app['Menu'].print_control_identifiers()  # << working
        app['Menu'].dump_tree()  # << working
        app['Menu']['사운드 관리자'].click_input()  # .click() is not working
elif case == 4:  # SHOULD BE WORKING !!!!
    app = pwa.Application(backend="uia").connect(path="explorer.exe")
    for window in app.windows():
        print(f"{window.window_text()=}")
    if False:  # working
        app.window(title='작업 표시줄', top_level_only=False, visible_only=False).child_window(title='알림 펼침').click()
        for window in app.windows():
            print(f"{window.window_text()=}")
    else:  # stable working
        w = app.window(title='작업 표시줄', top_level_only=False, visible_only=False).child_window(title='알림 펼침')
        w.click()
        w.wait('visible', timeout=30, retry_interval=3)
    print('NotifyIconOverflowWindow'.ljust(32, '-'))
    app = pwa.Application(backend="uia").connect(class_name="NotifyIconOverflowWindow")  # 오버플로 알림 영역
    app_icons = app.window(class_name="NotifyIconOverflowWindow")
    app_icons.wait('visible', timeout=30, retry_interval=3)
    print(81)
    app_icons.dump_tree()  # << working; informative to get hovering text
    """
    Control Identifiers:

    Pane - '알림 오버플로'    (L1596, T852, R1734, B990)
    ['Pane', '알림 오버플로Pane', '알림 오버플로']
    child_window(title="알림 오버플로", control_type="Pane")
       | 
       | Toolbar - '오버플로 알림 영역'    (L1596, T852, R1734, B990)
       | ['Toolbar', '오버플로 알림 영역Toolbar', '오버플로 알림 영역']
       | child_window(title="오버플로 알림 영역", auto_id="1504", control_type="ToolBar")
       |    | 
       |    | Button - 'AhnLab Online Security 실행 중'    (L1596, T852, R1642, B898)
       |    | ['Button', 'AhnLab Online Security 실행 중', 'AhnLab Online Security 실행 중Button', 'Button0', 'Button1']
       |    | child_window(title="AhnLab Online Security 실행 중", control_type="Button")
       |    | 
       |    | Button - 'Windows 보안 - 작업이 권장됩니다.'    (L1642, T852, R1688, B898)
       |    | ['Button2', 'Windows 보안 - 작업이 권장됩니다.Button', 'Windows 보안 - 작업이 권장됩니다.']
       |    | child_window(title="Windows 보안 - 작업이 권장됩니다.", auto_id="{BA82E2DC-F405-47AD-B032-CF0FAA0E3933}", control_type="Button")
       |    | 
       |    | Button - 'AhnLab V3 Lite (엔진 버전: 2022.10.18.00)\r- PC 실시간 검사가 실행 중입니다.'    (L1688, T852, R1734, B898)
       |    | ['Button3', 'AhnLab V3 Lite (엔진 버전: 2022.10.18.00)\r- PC 실시간 검사가 실행 중입니다.Button', 'AhnLab V3 Lite (엔진 버전: 2022.10.18.00)\r- PC 실시간 검사가 실행 중입니다.']
       |    | child_window(title="AhnLab V3 Lite (엔진 버전: 2022.10.18.00)\r- PC 실시간 검사가 실행 중입니다.", control_type="Button")
       |    | 
       |    | Button - ''    (L1596, T898, R1642, B944)
       |    | ['Button4']
       |    | 
       |    | Button - 'Java Update 사용 가능'    (L1642, T898, R1688, B944)
       |    | ['Button5', 'Java Update 사용 가능', 'Java Update 사용 가능Button']
       |    | child_window(title="Java Update 사용 가능", control_type="Button")
       |    | 
       |    | Button - '이베스트투자증권(버전확인필수)_20210928'    (L1688, T898, R1734, B944)
       |    | ['Button6', '이베스트투자증권(버전확인필수)_20210928Button', '이베스트투자증권(버전확인필수)_20210928', '이베스트투자증권(버전확인필수)_20210928Button0', '이베스트투자증권(버전확인필수)_20210928Button1', '이베스트투자증권(버전확인필수)_202109280', '이베스트투자증권(버전확인필수)_202109281']
       |    | child_window(title="이베스트투자증권(버전확인필수)_20210928", control_type="Button")
       |    | 
       |    | Button - '이베스트투자증권(버전확인필수)_20210928'    (L1596, T944, R1642, B990)
       |    | ['Button7', '이베스트투자증권(버전확인필수)_20210928Button2', '이베스트투자증권(버전확인필수)_202109282']
       |    | child_window(title="이베스트투자증권(버전확인필수)_20210928", control_type="Button")
       |    | 
       |    | Button - 'NVIDIA GeForce Game Ready 드라이버 업데이트를 사용할 수 있습니다'    (L1642, T944, R1688, B990)
       |    | ['Button8', 'NVIDIA GeForce Game Ready 드라이버 업데이트를 사용할 수 있습니다Button', 'NVIDIA GeForce Game Ready 드라이버 업데이트를 사용할 수 있습니다']
       |    | child_window(title="NVIDIA GeForce Game Ready 드라이버 업데이트를 사용할 수 있습니다", control_type="Button")
       |    | 
       |    | Button - '2022.6.56 버전으로 업그레이드 할 수 있습니다.'    (L1688, T944, R1734, B990)
       |    | ['Button9', '2022.6.56 버전으로 업그레이드 할 수 있습니다.Button', '2022.6.56 버전으로 업그레이드 할 수 있습니다.']
       |    | child_window(title="2022.6.56 버전으로 업그레이드 할 수 있습니다.", control_type="Button"
    """
    print('CreonPlus Start'.ljust(32, '-'))
    app_icon = app_icons.child_window(title='CreonPlus Start')  # working at home, 2022.10.18
    # app_icon = app_icons.button  # working at home, 2022.10.18
    # app_icon = app_icons.child_window(title='Java Update 사용 가능')  # workin at home, 2022.10.18
    app_icon.double_click_input(button='right')  # working only in headful mode, 2022.10.17
elif case == 5:
    # https://techinch.com/blog/access-your-windows-system-tray-from-your-keyboard
    # https://stackoverflow.com/questions/57563945/how-to-press-windows-key-r-pywinauto-send-keys-function
    pwa.keyboard.send_keys("{VK_LWIN down}b{VK_LWIN up}")
    pwa.keyboard.send_keys("{ENTER}")
    sub_case = 2
    if sub_case == 1:  # working in headful mode, not headless mode, 2022.10.18
        app = pwa.Application(backend='uia').connect(path='explorer.exe')
        app_icons = app.window(class_name='NotifyIconOverflowWindow')
        app_icon = app_icons.child_window(title='Java Update 사용 가능')  # working at home, 2022.10.18
        app_icon.double_click_input(button='left')  # working only in headful mode, 2022.10.17
    elif sub_case == 2:  # working in headful mode, not headless mode, 2022.10.18
        pwa.keyboard.send_keys("{VK_LWIN down}b{VK_LWIN up}")
        pwa.keyboard.send_keys("{VK_RIGHT}")
        pwa.keyboard.send_keys("{ENTER}")
    elif sub_case == 3:  # ???
        pass
        # TODO 2022.10.18, How to send mouse click event to window ???
        #   win32gui.PostMessage(window, win32con.MOUSEEVENTF_LEFTDOWN, 0, 0)
        #   win32gui.PostMessage(window, win32con.MOUSEEVENTF_LEFTUP, 0, 0)
