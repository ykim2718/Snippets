#if !defined(AFX_GRAPHERRENOVATORDIALOGCTL_H__9FF3AC68_4612_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRAPHERRENOVATORDIALOGCTL_H__9FF3AC68_4612_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GrapherRenovatorDialogCtl.h : Declaration of the CGrapherRenovatorDialogCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogCtrl : See GrapherRenovatorDialogCtl.cpp for implementation.

class CGrapherRenovatorDialogCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGrapherRenovatorDialogCtrl)

// Constructor
public:
	CGrapherRenovatorDialogCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrapherRenovatorDialogCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CGrapherRenovatorDialogCtrl();

	DECLARE_OLECREATE_EX(CGrapherRenovatorDialogCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGrapherRenovatorDialogCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGrapherRenovatorDialogCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGrapherRenovatorDialogCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CGrapherRenovatorDialogCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CGrapherRenovatorDialogCtrl)
	afx_msg long DoModal();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CGrapherRenovatorDialogCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGrapherRenovatorDialogCtrl)
	dispidDoModal = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHERRENOVATORDIALOGCTL_H__9FF3AC68_4612_11D5_9E85_0000E8C3064A__INCLUDED)
