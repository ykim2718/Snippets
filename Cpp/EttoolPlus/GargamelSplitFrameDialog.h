//{{AFX_INCLUDES()
#include "gargamelsplitctrl.h"
//}}AFX_INCLUDES
#if !defined(AFX_GARGAMELSPLITDIALOG_H__75D1A740_F924_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELSPLITDIALOG_H__75D1A740_F924_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GargamelSplitFrameDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "stdafx.h"
#include "resource.h" // shik96@samsung.co.kr

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitFrameDialog dialog

class CGargamelSplitFrameDialog : public CDialog
{
// Construction
public:
	CString m_sDirectory;
	void OnOK();
   void OnCancel();
	CString m_sStream;

	CGargamelSplitFrameDialog( CWnd* pParent=NULL ); // standard constructor

// Dialog Data
	//{{AFX_DATA(CGargamelSplitFrameDialog)
	enum { IDD = IDD_GARGAMEL_SPLIT };
	CGargamelSplitCtrl	m_GargamelSplitCtrl;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelSplitFrameDialog)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGargamelSplitFrameDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAnotherok();
	afx_msg void OnAnothercancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELSPLITDIALOG_H__75D1A740_F924_11D4_9E85_0000E8C3064A__INCLUDED_)
