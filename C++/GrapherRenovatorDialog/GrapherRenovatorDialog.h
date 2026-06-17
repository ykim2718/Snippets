#if !defined(AFX_GRAPHERRENOVATORDIALOG_H__9FF3AC61_4612_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRAPHERRENOVATORDIALOG_H__9FF3AC61_4612_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GrapherRenovatorDialog.h : main header file for GRAPHERRENOVATORDIALOG.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogApp : See GrapherRenovatorDialog.cpp for implementation.

class CGrapherRenovatorDialogApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHERRENOVATORDIALOG_H__9FF3AC61_4612_11D5_9E85_0000E8C3064A__INCLUDED)
