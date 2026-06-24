# Microsoft Developer Studio Project File - Name="myC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=myC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "myC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "myC.mak" CFG="myC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "myC - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "myC - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "myC - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "_LIB" /D "_MSC_" /D "_MSWINDOW_" /D "WIN32" /D "NDEBUG" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "myC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_LIB" /D "_MSWINDOW_" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_MSC_" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "myC - Win32 Release"
# Name "myC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\any.c
# End Source File
# Begin Source File

SOURCE=.\anyfind.c
# End Source File
# Begin Source File

SOURCE=.\blob.c
# End Source File
# Begin Source File

SOURCE=.\gecore.c
# End Source File
# Begin Source File

SOURCE=.\gefont.c
# End Source File
# Begin Source File

SOURCE=.\geprint.c
# End Source File
# Begin Source File

SOURCE=.\geresource.c
# End Source File
# Begin Source File

SOURCE=.\geWindowMS.c
# End Source File
# Begin Source File

SOURCE=.\geWindowSunview.c
# End Source File
# Begin Source File

SOURCE=.\geWindowX.c
# End Source File
# Begin Source File

SOURCE=.\myAlloc.c
# End Source File
# Begin Source File

SOURCE=.\mygr.c
# End Source File
# Begin Source File

SOURCE=.\nr.c
# End Source File
# Begin Source File

SOURCE=.\nr2.c
# End Source File
# Begin Source File

SOURCE=.\nr3.c
# End Source File
# Begin Source File

SOURCE=.\nr_.c
# End Source File
# Begin Source File

SOURCE=.\nrecipe.c
# End Source File
# Begin Source File

SOURCE=.\parser.c
# End Source File
# Begin Source File

SOURCE=.\plot.c
# End Source File
# Begin Source File

SOURCE=.\plotcv.c
# End Source File
# Begin Source File

SOURCE=.\plotio.c
# End Source File
# Begin Source File

SOURCE=.\plotse.c
# End Source File
# Begin Source File

SOURCE=.\plotsymb.c
# End Source File
# Begin Source File

SOURCE=.\semiconductor.c
# End Source File
# Begin Source File

SOURCE=.\skeleton.c
# End Source File
# Begin Source File

SOURCE=.\sort.c
# End Source File
# Begin Source File

SOURCE=.\str.c
# End Source File
# Begin Source File

SOURCE=.\tools.c
# End Source File
# Begin Source File

SOURCE=.\uDataPointReformer.c
# End Source File
# Begin Source File

SOURCE=.\uEEPROM2T.c
# End Source File
# Begin Source File

SOURCE=.\uIdealMosCapacitor.c
# End Source File
# Begin Source File

SOURCE=.\uIdealMosCapacitorEx.c
# End Source File
# Begin Source File

SOURCE=.\uJunctionDiodeRegressor.c
# End Source File
# Begin Source File

SOURCE=.\uMaserjianModel.c
# End Source File
# Begin Source File

SOURCE=.\uMosCapacitorRegressor.c
# End Source File
# Begin Source File

SOURCE=.\uMosDiodeRegressor.c
# End Source File
# Begin Source File

SOURCE=.\uMOSFETIdVg.c
# End Source File
# Begin Source File

SOURCE=.\uNormConductance.c
# End Source File
# Begin Source File

SOURCE=.\uPolynomialFit.c
# End Source File
# Begin Source File

SOURCE=.\uShiftAndRatioMethod.c
# End Source File
# Begin Source File

SOURCE=.\uSplitCV.c
# End Source File
# Begin Source File

SOURCE=.\usrfunc.c
# End Source File
# Begin Source File

SOURCE=.\uTwoFreqCapacitanceModel.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\any.h
# End Source File
# Begin Source File

SOURCE=.\anyfind.h
# End Source File
# Begin Source File

SOURCE=.\anyfind_def.h
# End Source File
# Begin Source File

SOURCE=.\blob.h
# End Source File
# Begin Source File

SOURCE=.\gecore.h
# End Source File
# Begin Source File

SOURCE=.\gefont.h
# End Source File
# Begin Source File

SOURCE=.\geplot.h
# End Source File
# Begin Source File

SOURCE=.\geprint.h
# End Source File
# Begin Source File

SOURCE=.\geresource.h
# End Source File
# Begin Source File

SOURCE=.\geWindow.h
# End Source File
# Begin Source File

SOURCE=.\geWindowMy.h
# End Source File
# Begin Source File

SOURCE=.\geWindowSunview.h
# End Source File
# Begin Source File

SOURCE=.\keydef.h
# End Source File
# Begin Source File

SOURCE=.\motif.h
# End Source File
# Begin Source File

SOURCE=.\myAlloc.h
# End Source File
# Begin Source File

SOURCE=.\myCore.h
# End Source File
# Begin Source File

SOURCE=.\mygr.h
# End Source File
# Begin Source File

SOURCE=.\nr.h
# End Source File
# Begin Source File

SOURCE=.\nr2.h
# End Source File
# Begin Source File

SOURCE=.\nr3.h
# End Source File
# Begin Source File

SOURCE=.\nrecipe.h
# End Source File
# Begin Source File

SOURCE=.\number.h
# End Source File
# Begin Source File

SOURCE=.\parser.h
# End Source File
# Begin Source File

SOURCE=.\plot.h
# End Source File
# Begin Source File

SOURCE=.\plotse.h
# End Source File
# Begin Source File

SOURCE=.\plotsymb.h
# End Source File
# Begin Source File

SOURCE=.\semiconductor.h
# End Source File
# Begin Source File

SOURCE=.\skeleton.h
# End Source File
# Begin Source File

SOURCE=.\str.h
# End Source File
# Begin Source File

SOURCE=.\tools.h
# End Source File
# Begin Source File

SOURCE=.\usrfunc.h
# End Source File
# End Group
# End Target
# End Project
