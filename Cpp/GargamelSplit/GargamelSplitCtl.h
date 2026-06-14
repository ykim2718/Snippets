#if !defined(AFX_GARGAMELSPLITCTL_H__3731EFB4_F83D_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELSPLITCTL_H__3731EFB4_F83D_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GargamelSplitCtl.h : Declaration of the CGargamelSplitCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "GargamelSplitDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitCtrl : See GargamelSplitCtl.cpp for implementation.

class CGargamelSplitCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGargamelSplitCtrl)

// Constructor
public:
	CGargamelSplitCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelSplitCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CGargamelSplitCtrl();

	DECLARE_OLECREATE_EX(CGargamelSplitCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGargamelSplitCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGargamelSplitCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGargamelSplitCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CGargamelSplitCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CGargamelSplitCtrl)
	afx_msg BSTR GetSplitScript();
	afx_msg void SetSplitScript(LPCTSTR lpszNewValue);
	afx_msg void NotifyFlagrantDialogOk();
	afx_msg void NotifyFlagrantDialogCancel();
	afx_msg void SetDirectory(LPCTSTR qPath);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CGargamelSplitCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	CGargamelSplitDialog m_Dialog;
	enum {
	//{{AFX_DISP_ID(CGargamelSplitCtrl)
	dispidSplitScript = 1L,
	dispidNotifyFlagrantDialogOk = 2L,
	dispidNotifyFlagrantDialogCancel = 3L,
	dispidSetDirectory = 4L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELSPLITCTL_H__3731EFB4_F83D_11D4_9E85_0000E8C3064A__INCLUDED)
