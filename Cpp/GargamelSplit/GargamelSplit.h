#if !defined(AFX_GARGAMELSPLIT_H__3731EFAC_F83D_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELSPLIT_H__3731EFAC_F83D_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GargamelSplit.h : main header file for GARGAMELSPLIT.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitApp : See GargamelSplit.cpp for implementation.

class CGargamelSplitApp : public COleControlModule
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

#endif // !defined(AFX_GARGAMELSPLIT_H__3731EFAC_F83D_11D4_9E85_0000E8C3064A__INCLUDED)
