; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGargamelSplitCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gargamelsplit.h"
LastPage=0
CDK=Y

ClassCount=6
Class1=CGargamelSplitCtrl
Class2=CGargamelSplitDialog
Class3=CGargamelSplitPropPage
Class4=CWriteFileListToSynchronize
Class5=CInPlaceEdit
Class6=CListBoxEx

ResourceCount=7
Resource1=IDD_ABOUTBOX_GARGAMELSPLIT (Korean)
Resource2=IDD_PROPPAGE_GARGAMELSPLIT (Korean)
Resource3=IDR_WRITE_LIST_MENU (Korean)
Resource4=IDD_CDIRTREEDLG (Korean)
Resource5=IDD_GARGAMEL_WRITEFILELISTTOSYNCHRONIZE (Korean)
Resource6=IDD_GARGAMEL_SPLIT (Korean)
Resource7=IDR_CLEAR_LIST_MENU (Korean)

[CLS:CGargamelSplitCtrl]
Type=0
BaseClass=COleControl
HeaderFile=GargamelSplitCtl.h
ImplementationFile=GargamelSplitCtl.cpp
LastObject=CGargamelSplitCtrl
Filter=W

[CLS:CGargamelSplitDialog]
Type=0
BaseClass=CDialog
HeaderFile=GargamelSplitDialog.h
ImplementationFile=GargamelSplitDialog.cpp

[CLS:CGargamelSplitPropPage]
Type=0
BaseClass=COlePropertyPage
HeaderFile=GargamelSplitPpg.h
ImplementationFile=GargamelSplitPpg.cpp
Filter=D

[CLS:CWriteFileListToSynchronize]
Type=0
BaseClass=CDialog
HeaderFile=WriteFileListToSynchronize.h
ImplementationFile=WriteFileListToSynchronize.cpp

[CLS:CInPlaceEdit]
Type=0
BaseClass=CEdit
HeaderFile=\HOME\CD2-Code\CnCPP\myCpp\ListBoxEx.h
ImplementationFile=\HOME\CD2-Code\CnCPP\myCpp\ListBoxEx.cpp
LastObject=CInPlaceEdit

[CLS:CListBoxEx]
Type=0
BaseClass=CDragListBox
HeaderFile=\HOME\CD2-Code\CnCPP\myCpp\ListBoxEx.h
ImplementationFile=\HOME\CD2-Code\CnCPP\myCpp\ListBoxEx.cpp
LastObject=CListBoxEx
Filter=W
VirtualFilter=bWC

[DLG:IDD_GARGAMEL_SPLIT]
Type=1
Class=CGargamelSplitDialog

[DLG:IDD_PROPPAGE_GARGAMELSPLIT]
Type=1
Class=CGargamelSplitPropPage

[DLG:IDD_GARGAMEL_WRITEFILELISTTOSYNCHRONIZE]
Type=1
Class=CWriteFileListToSynchronize

[DLG:IDD_ABOUTBOX_GARGAMELSPLIT (Korean)]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_GARGAMELSPLIT (Korean)]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_CDIRTREEDLG (Korean)]
Type=1
Class=?
ControlCount=6
Control1=IDC_DIRTREE,SysTreeView32,1350631463
Control2=IDOK,button,1342242816
Control3=IDCANCEL,button,1342242816
Control4=IDC_FOLDERS_AND_FILES,button,1342177289
Control5=IDC_FOLDERS_ONLY,button,1342177289
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_GARGAMEL_WRITEFILELISTTOSYNCHRONIZE (Korean)]
Type=1
Class=?
ControlCount=7
Control1=ID_GARGAMEL_WRITEFILELIST_ADD,button,1342242816
Control2=ID_GARGAMEL_WRITEFILELIST_CLEAR,button,1342242816
Control3=ID_GARGAMEL_WRITEFILELIST_REPLACE,button,1342242816
Control4=ID_GARGAMEL_WRITEFILELIST_FILTER,button,1342242816
Control5=ID_GARGAMEL_WRITEFILELIST_FILTER_STRING,edit,1350631552
Control6=IDOK,button,1342242816
Control7=ID_GARGAMEL_ETCETRA_LIST,listbox,1353778561

[DLG:IDD_GARGAMEL_SPLIT (Korean)]
Type=1
Class=?
ControlCount=18
Control1=ID_SPLIT_LISTBOX,listbox,1353778641
Control2=ID_SPLIT_ADD,button,1342243073
Control3=ID_SPLIT_INSERT,button,1342243072
Control4=ID_SPLIT_DELETE,button,1342243072
Control5=ID_SPLIT_CLEAR,button,1342243072
Control6=ID_SPLIT_CUTPASTE,button,1342243072
Control7=ID_SPLIT_MOVE_UP,button,1342243072
Control8=ID_SPLIT_MOVE_DOWN,button,1342243072
Control9=ID_SPLIT_SORT,button,1342243072
Control10=ID_SPLIT_CHANGE_DIRECTORY,button,1342243072
Control11=ID_SPLIT_ALIAS_INSERT,button,1342243072
Control12=ID_SPLIT_ALIAS_INSERT_TAILCOUNT,edit,1350639618
Control13=ID_SPLIT_ALIAS_INSERT_TAILCOUNT_SPIN,msctls_updown32,1342177312
Control14=ID_SPLIT_READ_FILELIST,button,1342243072
Control15=ID_SPLIT_WRITE_FILELIST,button,1342243072
Control16=ID_SPLIT_VIEW,button,1342243072
Control17=ID_SPLIT_VIEW_EDITOR,button,1342243584
Control18=IDC_STATIC,static,1342308354

[MNU:IDR_WRITE_LIST_MENU (Korean)]
Type=1
Class=?
Command1=IDM_WRITE_LIST_TO_A_FILE
Command2=IDM_WRITE_LIST_TO_FILES
CommandCount=2

[MNU:IDR_CLEAR_LIST_MENU (Korean)]
Type=1
Class=?
Command1=IDM_CLEAR_LIST_ALL
Command2=IDM_CLEAR_LIST_ALIASES
CommandCount=2

