# Microsoft Developer Studio Project File - Name="Gargamel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Gargamel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Gargamel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gargamel.mak" CFG="Gargamel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gargamel - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Gargamel - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gargamel - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_MSWINDOW_" /D "_MSC_" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Gargamel - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_MSC_" /FR /YX"stdafx.h" /FD /GZ /c
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

# Name "Gargamel - Win32 Release"
# Name "Gargamel - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Execute.cpp
# End Source File
# Begin Source File

SOURCE=..\myCpp\FileDialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Gargamel.cpp
# End Source File
# Begin Source File

SOURCE=.\Gargamel.rc
# End Source File
# Begin Source File

SOURCE=.\GargamelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GargamelPatternForMatrixFrameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GargamelPatternForMatrixOcx.cpp
# End Source File
# Begin Source File

SOURCE=.\GargamelPatternFrameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GargamelSplitFrameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GargamelSplitOcx.cpp
# End Source File
# Begin Source File

SOURCE=.\GargamelTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Anyfind\guids.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\myCpp\TextProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\myCpp\Token.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Execute.h
# End Source File
# Begin Source File

SOURCE=..\myCpp\FileDialogEx.h
# End Source File
# Begin Source File

SOURCE=.\Gargamel.h
# End Source File
# Begin Source File

SOURCE=.\GargamelDlg.h
# End Source File
# Begin Source File

SOURCE=.\GargamelPatternForMatrixFrameDialog.h
# End Source File
# Begin Source File

SOURCE=.\gargamelpatternformatrixocx.h
# End Source File
# Begin Source File

SOURCE=.\GargamelPatternFrameDialog.h
# End Source File
# Begin Source File

SOURCE=.\GargamelSplitFrameDialog.h
# End Source File
# Begin Source File

SOURCE=.\GargamelSplitOcx.h
# End Source File
# Begin Source File

SOURCE=.\GargamelTabCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Anyfind\Iface.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\myCpp\TextProgressCtrl.h
# End Source File
# Begin Source File

SOURCE=..\myCpp\Token.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Gargamel.ico
# End Source File
# Begin Source File

SOURCE=.\res\Gargamel.rc2
# End Source File
# Begin Source File

SOURCE=.\res\proverb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\proverb1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Gargamel : {3731EFA6-F83D-11D4-9E85-0000E8C3064A}
# 	2:21:DefaultSinkHeaderFile:gargamelsplitocx.h
# 	2:16:DefaultSinkClass:CGargamelSplitOcx
# End Section
# Section Gargamel : {3731EFA4-F83D-11D4-9E85-0000E8C3064A}
# 	2:5:Class:CGargamelSplitOcx
# 	2:10:HeaderFile:gargamelsplitocx.h
# 	2:8:ImplFile:gargamelsplitocx.cpp
# End Section
# Section Gargamel : {941C461F-8BA3-406A-B09B-98D4C39FC524}
# 	2:21:DefaultSinkHeaderFile:gargamelpatternformatrixocx.h
# 	2:16:DefaultSinkClass:CGargamelPatternForMatrixOcx
# End Section
# Section Gargamel : {2025CFCD-058A-4B3E-AB84-AF1D8453EBA6}
# 	2:5:Class:CGargamelPatternForMatrixOcx
# 	2:10:HeaderFile:gargamelpatternformatrixocx.h
# 	2:8:ImplFile:gargamelpatternformatrixocx.cpp
# End Section
