#if !defined(AFX_GARGAMELPATTERN_H__33406940_F75F_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELPATTERN_H__33406940_F75F_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GargamelPattern.h : main header file for GARGAMELPATTERN.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternApp : See GargamelPattern.cpp for implementation.

class CGargamelPatternApp : public COleControlModule
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

#endif // !defined(AFX_GARGAMELPATTERN_H__33406940_F75F_11D4_9E85_0000E8C3064A__INCLUDED)
