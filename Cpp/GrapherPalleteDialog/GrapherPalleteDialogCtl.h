#if !defined(AFX_GRAPHERPALLETEDIALOGCTL_H__0F24C359_4552_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRAPHERPALLETEDIALOGCTL_H__0F24C359_4552_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GrapherPalleteDialogCtl.h : Declaration of the CGrapherPalleteDialogCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogCtrl : See GrapherPalleteDialogCtl.cpp for implementation.

class CGrapherPalleteDialogCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGrapherPalleteDialogCtrl)

// Constructor
public:
	CGrapherPalleteDialogCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrapherPalleteDialogCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CGrapherPalleteDialogCtrl();

	DECLARE_OLECREATE_EX(CGrapherPalleteDialogCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGrapherPalleteDialogCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGrapherPalleteDialogCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGrapherPalleteDialogCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CGrapherPalleteDialogCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CGrapherPalleteDialogCtrl)
	afx_msg void DoModal();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CGrapherPalleteDialogCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGrapherPalleteDialogCtrl)
	dispidDoModal = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHERPALLETEDIALOGCTL_H__0F24C359_4552_11D5_9E85_0000E8C3064A__INCLUDED)
