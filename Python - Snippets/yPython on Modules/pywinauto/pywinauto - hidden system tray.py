"""
y, 2021.1.26, ~2.19
pywinauto - hidden system tray.py.py
"""

import pywinauto as pwa
import time

case = 3

if case == 1:  # NOT WORKING
    # https://pywinauto.readthedocs.io/en/latest/HowTo.html#how-to-access-the-system-tray-aka-systray-aka-notification-area
    import pywinauto.application as pwa
    app = pwa.Application().connect(path='explorer')
    systray_icons = app.ShellTrayWnd.NotificationAreaToolbar
    print(systray_icons)
    # systray_icons.ClickSystemTrayIcon(0)
    systray_icons.ClickHiddenSystemTrayIcon(0)
    # systray_icons.ClickHiddenSystemTrayIcon('Robo3T 1.4.0', exact=True, double=True).click()
elif case == 2:  # WORKING
    d = pwa.Desktop(backend='uia')
    # d['작업 표시줄'].dump_tree()  # << working
    d['작업 표시줄'].child_window(title='알림 펼침').click()
elif case == 3:  # WORKING
    # https://stackoverflow.com/questions/62190055/handling-context-menu-of-the-taskbar-icon-with-pywinauto
    app = pwa.Application(backend="uia").connect(path="explorer.exe")
    st = app.window(class_name="Shell_TrayWnd")
    # st.child_window(title="Notification Chevron").wrapper_object().click()  # 갈매기형 펼침 단추
    st.child_window(title="알림 펼침").wrapper_object().click()  # 갈매기형 펼침 단추  << working
    time.sleep(1)
    list_box = pwa.Application(backend="uia").connect(class_name="NotifyIconOverflowWindow")  # 오버플로 알림 영역
    list_box_win = list_box.window(class_name="NotifyIconOverflowWindow")
    list_box_win.wait('visible', timeout=30, retry_interval=3)
    # list_box_win.dump_tree()  # << working
    app_icon = list_box_win.child_window(title='Realtek HD 오디오 관리자')
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
        app_icon.send_chars('{ENTER}')
        app_icon.click()
        print(44)
        time.sleep(1)
        print(45)
        app = pwa.Application(backend='uia').connect(path=r'C:\Program Files\Realtek\Audio\HDA\RAVCpl64.exe')
        # app['Menu'].print_control_identifiers()  # << working
        # app['Menu'].dump_tree()  # << working
        app['Menu']['사운드 관리자'].click_input()  # .click() is not working

