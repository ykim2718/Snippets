# Microsoft Developer Studio Project File - Name="Grapher" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Grapher - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Grapher.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Grapher.mak" CFG="Grapher - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Grapher - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Grapher - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Grapher - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MSWINDOW_" /D "_MSC_" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /fo"Debug/Grapher.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Grapher - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_WINDOWS" /D "_AFXDLL" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_MSWINDOW_" /D "_MSC_" /Fr /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Grapher - Win32 Release"
# Name "Grapher - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AnyfindClient.c
# End Source File
# Begin Source File

SOURCE=..\myMFC\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\colorbtn.cpp
# End Source File
# Begin Source File

SOURCE=..\myCpp\CreateProcessWithRedirectedIO.cpp
# End Source File
# Begin Source File

SOURCE=..\myCpp\CreateProcessWithRedirectedIO2.cpp
# End Source File
# Begin Source File

SOURCE=..\DialogAggregate\DialogAggregate_i.c
# End Source File
# Begin Source File

SOURCE=..\myMFC\FileDialogEx.cpp
# End Source File
# Begin Source File

SOURCE=..\myMFC\GetFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\Grapher.cpp
# End Source File
# Begin Source File

SOURCE=.\Grapher.rc
# End Source File
# Begin Source File

SOURCE=.\GrapherDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\grapherpalletedialog.cpp
# End Source File
# Begin Source File

SOURCE=.\grapherrenovatordialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GrapherView.cpp
# End Source File
# Begin Source File

SOURCE=.\GrAttrPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GrAxisPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GrDataPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GrDefaultSymbolDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GrGlobPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GrHistoryDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GrLogDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\grpathenvironmentdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GrPlotMixerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GrPlotPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GrPlotSymbolBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\GrPlotWizard.cpp
# End Source File
# Begin Source File

SOURCE=.\GrPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\GrSlctPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GrTextPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GrUfunPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GrViewPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GrXyzbPage.cpp
# End Source File
# Begin Source File

SOURCE=..\myMFC\ListBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=..\myMFC\ListCtrlEx2.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\myMFC\MYorkPrint.cpp
# End Source File
# Begin Source File

SOURCE=..\myMFC\Options.cpp
# End Source File
# Begin Source File

SOURCE=..\myMFC\OptionsTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SmallFontAttrDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\myMFC\ToggleBtn.cpp
# End Source File
# Begin Source File

SOURCE=..\myCpp\Token.cpp
# End Source File
# Begin Source File

SOURCE=.\XYZListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Zoomview.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AnyfindClient.h
# End Source File
# Begin Source File

SOURCE=..\myMFC\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\colorbtn.h
# End Source File
# Begin Source File

SOURCE=..\myCpp\CreateProcessWithRedirectedIO2.h
# End Source File
# Begin Source File

SOURCE=..\DialogAggregate\DialogAggregate.h
# End Source File
# Begin Source File

SOURCE=..\myMFC\FileDialogEx.h
# End Source File
# Begin Source File

SOURCE=..\myCpp\GetFolder.h
# End Source File
# Begin Source File

SOURCE=.\Grapher.h
# End Source File
# Begin Source File

SOURCE=.\grapherdialogs.h
# End Source File
# Begin Source File

SOURCE=.\GrapherDoc.h
# End Source File
# Begin Source File

SOURCE=.\grapherpalletedialog.h
# End Source File
# Begin Source File

SOURCE=.\grapherrenovatordialog.h
# End Source File
# Begin Source File

SOURCE=.\GrapherView.h
# End Source File
# Begin Source File

SOURCE=.\GrAttrPage.h
# End Source File
# Begin Source File

SOURCE=.\GrAxisPage.h
# End Source File
# Begin Source File

SOURCE=.\GrDataPage.h
# End Source File
# Begin Source File

SOURCE=.\GrDefaultSymbolDialog.h
# End Source File
# Begin Source File

SOURCE=.\GrGlobPage.h
# End Source File
# Begin Source File

SOURCE=.\GrHistoryDialog.h
# End Source File
# Begin Source File

SOURCE=.\GrLogDialog.h
# End Source File
# Begin Source File

SOURCE=.\grpathenvironmentdialog.h
# End Source File
# Begin Source File

SOURCE=.\GrPlotMixerDialog.h
# End Source File
# Begin Source File

SOURCE=.\GrPlotPage.h
# End Source File
# Begin Source File

SOURCE=.\GrPlotSymbolBtn.h
# End Source File
# Begin Source File

SOURCE=.\GrPlotWizard.h
# End Source File
# Begin Source File

SOURCE=.\grpropertysheet.h
# End Source File
# Begin Source File

SOURCE=.\GrSlctPage.h
# End Source File
# Begin Source File

SOURCE=.\GrTextPage.h
# End Source File
# Begin Source File

SOURCE=.\GrUfunPage.h
# End Source File
# Begin Source File

SOURCE=.\GrViewPage.h
# End Source File
# Begin Source File

SOURCE=.\GrXyzbPage.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=..\myMFC\ListCtrlEx2.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\myMFC\Options.h
# End Source File
# Begin Source File

SOURCE=..\myMFC\OptionsTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SmallFontAttrDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\myMFC\ToggleBtn.h
# End Source File
# Begin Source File

SOURCE=..\myCpp\Token.h
# End Source File
# Begin Source File

SOURCE=.\XYZListBox.h
# End Source File
# Begin Source File

SOURCE=.\Zoomview.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\gargamel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Grapher.ico
# End Source File
# Begin Source File

SOURCE=.\res\Grapher.rc2
# End Source File
# Begin Source File

SOURCE=.\res\GrapherDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\handGrapsed.cur
# End Source File
# Begin Source File

SOURCE=.\res\handSpreaded.cur
# End Source File
# Begin Source File

SOURCE=.\res\IDB_ARROW_LEFT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_ARROW_RIGHT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_CLEAR.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_EXEC_GR.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_FILE_OPEN.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_GARGAMEL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_GR_LOG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_GR_MIXER.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_GR_PROPERTYSHEET.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_GR_RENOVATOR.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_GR_SCRIPT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_GR_WIZARD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_OPTIONTREECTRL_CHECKOFF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_OPTIONTREECTRL_CHECKON.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_OPTIONTREECTRL_ITEMS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_OPTIONTREECTRL_RADIOOFF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_OPTIONTREECTRL_RADIOON.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_PALLETE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_PREFERENCE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_SCRIPT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_SMURFETTE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDB_VIEW_LOG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDR_GRAPHER.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IDR_MAINFRAME.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=".\res\RadialCtrl-DialBackground.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\script1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\smurfett.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBar_GRAPHER.bmp
# End Source File
# Begin Source File

SOURCE=.\res\view_log.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zoomIn.cur
# End Source File
# Begin Source File

SOURCE=.\res\zoomOut.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Grapher : {9FF3AC45-4612-11D5-9E85-0000E8C3064A}
# 	2:21:DefaultSinkHeaderFile:grapherrenovatordialog.h
# 	2:16:DefaultSinkClass:CGrapherRenovatorDialog
# End Section
# Section Grapher : {0F24C34C-4552-11D5-9E85-0000E8C3064A}
# 	2:21:DefaultSinkHeaderFile:grapherpalletedialog.h
# 	2:16:DefaultSinkClass:CGrapherPalleteDialog
# End Section
# Section Grapher : {196C8CB9-4542-11D5-9E85-0000E8C3064A}
# 	2:5:Class:CGrapherDialogs
# 	2:10:HeaderFile:grapherdialogs.h
# 	2:8:ImplFile:grapherdialogs.cpp
# End Section
# Section Grapher : {196C8CBB-4542-11D5-9E85-0000E8C3064A}
# 	2:21:DefaultSinkHeaderFile:grapherdialogs.h
# 	2:16:DefaultSinkClass:CGrapherDialogs
# End Section
# Section Grapher : {9FF3AC5A-4612-11D5-9E85-0000E8C3064A}
# 	2:5:Class:CGrapherRenovatorDialog
# 	2:10:HeaderFile:grapherrenovatordialog.h
# 	2:8:ImplFile:grapherrenovatordialog.cpp
# End Section
# Section Grapher : {0F24C34A-4552-11D5-9E85-0000E8C3064A}
# 	2:5:Class:CGrapherPalleteDialog
# 	2:10:HeaderFile:grapherpalletedialog.h
# 	2:8:ImplFile:grapherpalletedialog.cpp
# End Section
