// GargamelDlg.h : header file
//

#if !defined(AFX_GARGAMELDLG_H__EAB7D7A7_6D38_11D4_9622_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELDLG_H__EAB7D7A7_6D38_11D4_9622_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "Resource.h"
#include "GargamelTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CGargamelDlg dialog

class CGargamelDlg : public CDialog
{
// Construction
public:
	CGargamelDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGargamelDlg)
	enum { IDD = IDD_GARGAMEL };
	CGargamelTabCtrl	m_TabCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGargamelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELDLG_H__EAB7D7A7_6D38_11D4_9622_0000E8C3064A__INCLUDED_)
