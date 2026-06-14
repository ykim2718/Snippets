// EttoolPlus.h : main header file for the ETTOOLPLUS application
//

#if !defined(AFX_ETTOOLPLUS_H__50051FC4_F950_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_ETTOOLPLUS_H__50051FC4_F950_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include <process.h>
#include <errno.h>

#define RegKeySettings        "Settings"
#define RegKeyExecCount       "nExecCount"
#define RegKeyEttoolFile      "sEttoolFile"
#define RegKeyM4File          "sM4File"
#define RegKeyEditorFile      "sEditorFile"
#define RegKeyScriptFile      "sScriptFile"
#define RegKeyInputFolder     "sInputFolder"
#define RegKeyInputFolderFileFilter "sInputFolderFileFilter"
#define RegKeyOutputFolder    "sOutputFolder"
#define RegKeyNumberFormat    "sNumberFormat"
#define RegKeyFormatDat       "bFormatDat"
#define RegKeyFormatDat2      "bFormatDat2"
#define RegKeyFormatLot       "bFormatLot"
#define RegKeyFormatLot2      "bFormatLot2"
#define RegKeyFormatLot3      "bFormatLot3"
#define RegKeyFormatLot4      "bFormatLot4"
#define RegKeyFormatMap       "bFormatMap"
#define RegKeyFormatMap2      "bFormatMap2"
#define RegKeyFormatPlt       "bFormatPlt"
#define RegKeyFormatRpt       "bFormatRpt"
#define RegKeyFormatSum       "bFormatSum"
#define RegKeyFormatLog       "bFormatLog"
#define RegKeyFormatCvs       "bFormatCvs"

#define RegKeyFrameLeft       "nFrameLeft"
#define RegKeyFrameTop        "nFrameTop"
#define RegKeyFrameRight      "nFrameRight"
#define RegKeyFrameBottom     "nFrameBottom"

/////////////////////////////////////////////////////////////////////////////
// CEttoolPlusApp:
// See EttoolPlus.cpp for the implementation of this class
//

class CEttoolPlusApp : public CWinApp
{
public:
	CEttoolPlusApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEttoolPlusApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEttoolPlusApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETTOOLPLUS_H__50051FC4_F950_11D4_9E85_0000E8C3064A__INCLUDED_)
