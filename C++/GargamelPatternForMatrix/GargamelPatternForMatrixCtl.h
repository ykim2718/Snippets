#if !defined(AFX_GARGAMELPATTERNFORMATRIXCTL_H__F043566F_6D93_4EBD_BB6E_DBC2B66986B1__INCLUDED_)
#define AFX_GARGAMELPATTERNFORMATRIXCTL_H__F043566F_6D93_4EBD_BB6E_DBC2B66986B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GargamelPatternForMatrixCtl.h : Declaration of the CGargamelPatternForMatrixCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// Y.Kim,20030207

#include "GargamelPatternForMatrixDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixCtrl : See GargamelPatternForMatrixCtl.cpp for implementation.

class CGargamelPatternForMatrixCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGargamelPatternForMatrixCtrl)

// Constructor
public:
	CGargamelPatternForMatrixCtrl();

   //Y.Kim,20030207
   CGargamelPatternForMatrixDialog m_Dialog;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelPatternForMatrixCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CGargamelPatternForMatrixCtrl();

	DECLARE_OLECREATE_EX(CGargamelPatternForMatrixCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGargamelPatternForMatrixCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGargamelPatternForMatrixCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGargamelPatternForMatrixCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CGargamelPatternForMatrixCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CGargamelPatternForMatrixCtrl)
	afx_msg BSTR GetPatternForMatrixScript();
	afx_msg void SetPatternForMatrixScript(LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CGargamelPatternForMatrixCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGargamelPatternForMatrixCtrl)
	dispidPatternForMatrixScript = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELPATTERNFORMATRIXCTL_H__F043566F_6D93_4EBD_BB6E_DBC2B66986B1__INCLUDED)
