#if !defined(AFX_GARGAMELPATTERNCTL_H__33406948_F75F_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELPATTERNCTL_H__33406948_F75F_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GargamelPatternCtl.h : Declaration of the CGargamelPatternCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternCtrl : See GargamelPatternCtl.cpp for implementation.

class CGargamelPatternCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGargamelPatternCtrl)

// Constructor
public:
	CGargamelPatternCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelPatternCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CGargamelPatternCtrl();

	DECLARE_OLECREATE_EX(CGargamelPatternCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGargamelPatternCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGargamelPatternCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGargamelPatternCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CGargamelPatternCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CGargamelPatternCtrl)
	afx_msg BSTR GetPatternScript();
	afx_msg void SetPatternScript(LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CGargamelPatternCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGargamelPatternCtrl)
	dispidPatternScript = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELPATTERNCTL_H__33406948_F75F_11D4_9E85_0000E8C3064A__INCLUDED)
