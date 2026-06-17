// Gargamel.h : main header file for the GARGAMEL application
//

#if !defined(AFX_GARGAMEL_H__EAB7D7A5_6D38_11D4_9622_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMEL_H__EAB7D7A5_6D38_11D4_9622_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "../Anyfind/Iface.h"
#include "Token.h"

#define RegKeySettings        "Settings"
#define RegKeyVersion         "sVersion"
#define RegKeyExecCount       "nExecCount"
#define RegKeyExample         "sExample"
#define RegKeyLastDirectory   "sLastDirectory"
#define RegKeyLastDirectoryAtExecute "sLastDirectory@Execute"
#define RegKeyLastWorkWithout "sLastWorkWithoutWindow"
#define RegKeyFrameLeft       "nFrameLeft"
#define RegKeyFrameTop        "nFrameTop"
#define RegKeyFrameRight      "nFrameRight"
#define RegKeyFrameBottom     "nFrameBottom"
#define RegKeyTextViewer      "sTextViewer"
#define RegKeySynchOutFileName "bSynchronizeOutFileName"

#define GARGAMEL_PATTERN_SAVE_FORMAT "\"%s\" \t%s \t%s %s %s %s %s %s"
        // pattern alias format firstNo lastNo equation lc uc

/////////////////////////////////////////////////////////////////////////////
// CGargamelApp:
// See Gargamel.cpp for the implementation of this class
//

class CGargamelApp : public CWinApp
{
public:
	IAnyfind* m_pAnyfind;
public:
	CGargamelApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGargamelApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMEL_H__EAB7D7A5_6D38_11D4_9622_0000E8C3064A__INCLUDED_)
