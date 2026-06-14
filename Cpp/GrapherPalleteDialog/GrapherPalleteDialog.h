#if !defined(AFX_GRAPHERPALLETEDIALOG_H__0F24C352_4552_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRAPHERPALLETEDIALOG_H__0F24C352_4552_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GrapherPalleteDialog.h : main header file for GRAPHERPALLETEDIALOG.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogApp : See GrapherPalleteDialog.cpp for implementation.

class CGrapherPalleteDialogApp : public COleControlModule
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

#endif // !defined(AFX_GRAPHERPALLETEDIALOG_H__0F24C352_4552_11D5_9E85_0000E8C3064A__INCLUDED)
