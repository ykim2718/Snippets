; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGrapherRenovatorDialogCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GrapherRenovatorDialog.h"
CDK=Y

ClassCount=2
Class1=CGrapherRenovatorDialogCtrl
Class2=CGrapherRenovatorDialogPropPage

ResourceCount=4
LastPage=0
Resource2=IDD_GR_RENOVATOR
Resource3=IDD_PROPPAGE_GRAPHERRENOVATORDIALOG
Resource4=IDR_RENOVATOR

[CLS:CGrapherRenovatorDialogCtrl]
Type=0
HeaderFile=GrapherRenovatorDialogCtl.h
ImplementationFile=GrapherRenovatorDialogCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC

[CLS:CGrapherRenovatorDialogPropPage]
Type=0
HeaderFile=GrapherRenovatorDialogPpg.h
ImplementationFile=GrapherRenovatorDialogPpg.cpp
Filter=D

[DLG:IDD_PROPPAGE_GRAPHERRENOVATORDIALOG]
Type=1
Class=CGrapherRenovatorDialogPropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_GR_RENOVATOR]
Type=1
Class=?
ControlCount=9
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=ID_RENOVATOR_LISTCTRL,SysListView32,1350631437
Control4=ID_RENOVATOR_ADD,button,1342242816
Control5=ID_RENOVATOR_DELETE,button,1342242816
Control6=ID_RENOVATOR_OUTFOLDER_BROWSER,button,1342242816
Control7=ID_RENOVATOR_OUTFOLDER,edit,1350631552
Control8=ID_RENOVATOR_PROGRESS,msctls_progress32,1350565889
Control9=ID_RENOVATOR_CLEAR,button,1342242816

[MNU:IDR_RENOVATOR]
Type=1
Class=?
Command1=IDR_RENOVATOR_OPENGRAPHERFILE
Command2=IDR_RENOVATOR_SAVESCRIPT
Command3=IDR_RENOVATOR_PRINTPLOT
CommandCount=3

