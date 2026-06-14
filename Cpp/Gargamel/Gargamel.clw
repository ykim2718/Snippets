; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGargamelPatternFrameDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gargamel.h"
LastPage=0

ClassCount=8
Class1=CExecute
Class2=CGargamelApp
Class3=CAboutDlg
Class4=CGargamelDlg
Class5=CGargamelPatternForMatrixFrameDialog
Class6=CGargamelPatternFrameDialog
Class7=CGargamelSplitFrameDialog
Class8=CGargamelTabCtrl

ResourceCount=7
Resource1=IDD_GARGAMEL_EXECUTE (Korean)
Resource2=IDD_GARGAMEL_SPLIT (Korean)
Resource3=IDD_GARGAMEL (Korean)
Resource4=IDD_GARGAMEL_PATTERN (Korean)
Resource5=IDD_ABOUTBOX (Korean)
Resource6=IDD_CDIRTREEDLG (Korean)
Resource7=IDD_GARGAMEL_PATTERNFORMATRIX (Korean)

[CLS:CExecute]
Type=0
BaseClass=CDialog
HeaderFile=Execute.h
ImplementationFile=Execute.cpp
Filter=D
VirtualFilter=dWC
LastObject=CExecute

[CLS:CGargamelApp]
Type=0
BaseClass=CWinApp
HeaderFile=Gargamel.h
ImplementationFile=Gargamel.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=GargamelDlg.cpp
ImplementationFile=GargamelDlg.cpp
LastObject=CAboutDlg

[CLS:CGargamelDlg]
Type=0
BaseClass=CDialog
HeaderFile=GargamelDlg.h
ImplementationFile=GargamelDlg.cpp

[CLS:CGargamelPatternForMatrixFrameDialog]
Type=0
BaseClass=CDialog
HeaderFile=GargamelPatternForMatrixFrameDialog.h
ImplementationFile=GargamelPatternForMatrixFrameDialog.cpp
LastObject=ID_GARGAMEL_PATTERNFORMATRIX_OCX

[CLS:CGargamelPatternFrameDialog]
Type=0
BaseClass=CDialog
HeaderFile=GargamelPatternFrameDialog.h
ImplementationFile=GargamelPatternFrameDialog.cpp
LastObject=CGargamelPatternFrameDialog
Filter=D
VirtualFilter=dWC

[CLS:CGargamelSplitFrameDialog]
Type=0
BaseClass=CDialog
HeaderFile=GargamelSplitFrameDialog.h
ImplementationFile=GargamelSplitFrameDialog.cpp
LastObject=CGargamelSplitFrameDialog

[CLS:CGargamelTabCtrl]
Type=0
BaseClass=CTabCtrl
HeaderFile=GargamelTabCtrl.h
ImplementationFile=GargamelTabCtrl.cpp
LastObject=CGargamelTabCtrl

[DLG:IDD_GARGAMEL_EXECUTE]
Type=1
Class=CExecute

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_GARGAMEL]
Type=1
Class=CGargamelDlg

[DLG:IDD_GARGAMEL_PATTERNFORMATRIX]
Type=1
Class=CGargamelPatternForMatrixFrameDialog

[DLG:IDD_GARGAMEL_PATTERN]
Type=1
Class=CGargamelPatternFrameDialog

[DLG:IDD_GARGAMEL_SPLIT]
Type=1
Class=CGargamelSplitFrameDialog

[DLG:IDD_GARGAMEL (Korean)]
Type=1
Class=?
ControlCount=1
Control1=ID_TABCTRL,SysTabControl32,1342177280

[DLG:IDD_GARGAMEL_EXECUTE (Korean)]
Type=1
Class=CExecute
ControlCount=34
Control1=IDC_DEFF_ENV_GB,button,1342177287
Control2=ID_EXECUTE_LOAD,button,1342242816
Control3=ID_EXECUTE_SAVE,button,1342242816
Control4=ID_EXECUTE_SAVEAS,button,1342242816
Control5=ID_SYNCHRONIZE_OUTFILENAME,button,1342242819
Control6=IDC_DEFF_EXTRACT_GB,button,1342177287
Control7=ID_EXECUTE_GARGAMEL,button,1342242816
Control8=IDC_STATIC,static,1342308864
Control9=ID_OPTION_SEARCH_ABSOLUTE,button,1342177289
Control10=ID_OPTION_SEARCH_SEQUENTIAL,button,1342177289
Control11=ID_OPTION_SEARCH_WILD,button,1342177289
Control12=ID_OPTION_SEARCH_BLOCK,button,1342177289
Control13=IDC_STATIC,static,1342177296
Control14=IDC_STATIC,static,1342308864
Control15=ID_OPTION_COLUMNARMTX_NO,button,1342177289
Control16=ID_OPTION_COLUMNARMTX_BYPATTERN,button,1342177289
Control17=ID_OPTION_COLUMNARMTX_BYPATTERN2,button,1342177289
Control18=ID_OPTION_COLUMNARMTX_BYSPLIT,button,1342177289
Control19=IDC_STATIC,static,1342177296
Control20=IDC_STATIC,static,1342308864
Control21=ID_OPTION_NUMPOSTPROCESS,combobox,1344339971
Control22=ID_OPTION_NUMERICALIAS,button,1342246147
Control23=ID_OPTION_COMPOSITE,button,1342246147
Control24=ID_PROGRESS,msctls_progress32,1350565889
Control25=IDC_DEFF_SAVE_GB,button,1342177287
Control26=ID_EXECUTE_DUMP,button,1342242816
Control27=ID_EXECUTE_DUMPAS,button,1342242816
Control28=ID_EXECUTE_DUMPANDVIEW,button,1342242816
Control29=ID_EXECUTE_VIEW,button,1342242816
Control30=ID_DUMPFILENAME,edit,1350631552
Control31=ID_TIMER_TEXT,static,1342308865
Control32=ID_GARGAMEL_PICTURE,static,1342179331
Control33=ID_EXECUTE_EXAMPLE,button,1342242816
Control34=ID_DISMISS,button,1342242816

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

[DLG:IDD_ABOUTBOX (Korean)]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308993
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308353
Control6=ID_GARGAMEL_VERSION,static,1342312961

[DLG:IDD_GARGAMEL_PATTERN (Korean)]
Type=1
Class=?
ControlCount=0

[DLG:IDD_GARGAMEL_SPLIT (Korean)]
Type=1
Class=?
ControlCount=2
Control1=ID_GARGAMEL_SPLIT_OCX,{3731EFA6-F83D-11D4-9E85-0000E8C3064A},1342242816
Control2=ID_PROVERB,static,1342308353

[DLG:IDD_GARGAMEL_PATTERNFORMATRIX (Korean)]
Type=1
Class=?
ControlCount=1
Control1=ID_GARGAMEL_PATTERNFORMATRIX_OCX,{941C461F-8BA3-406A-B09B-98D4C39FC524},1342242816

