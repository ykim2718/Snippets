#if !defined(AFX_GARGAMELSPLITPPG_H__3731EFB6_F83D_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELSPLITPPG_H__3731EFB6_F83D_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GargamelSplitPpg.h : Declaration of the CGargamelSplitPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CGargamelSplitPropPage : See GargamelSplitPpg.cpp.cpp for implementation.

class CGargamelSplitPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGargamelSplitPropPage)
	DECLARE_OLECREATE_EX(CGargamelSplitPropPage)

// Constructor
public:
	CGargamelSplitPropPage();

// Dialog Data
	//{{AFX_DATA(CGargamelSplitPropPage)
	enum { IDD = IDD_PROPPAGE_GARGAMELSPLIT };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CGargamelSplitPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELSPLITPPG_H__3731EFB6_F83D_11D4_9E85_0000E8C3064A__INCLUDED)
