#if !defined(AFX_ETTOOLAMBIENCEDLG_H__C31415A0_FA2E_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_ETTOOLAMBIENCEDLG_H__C31415A0_FA2E_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EttoolAmbienceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "../DialogAggregate/DialogAggregate.h"

/////////////////////////////////////////////////////////////////////////////
// CEttoolAmbienceDlg dialog

class CEttoolAmbienceDlg : public CDialog
{
// Construction
public:
   IFileFolderTreeSelectionDialog* m_pFileFolderTreeSelectionDialog;
	CEttoolAmbienceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEttoolAmbienceDlg)
	enum { IDD = IDD_AMBIENCES };
	CString	m_sPathOfEttool;
	CString	m_sPathOfM4;
	CString	m_sPathOfEditor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEttoolAmbienceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEttoolAmbienceDlg)
	afx_msg void OnApply();
	afx_msg void OnEttoolPathBrowser();
	afx_msg void OnM4PathBrowser();
	afx_msg void OnEditorPathBrowser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETTOOLAMBIENCEDLG_H__C31415A0_FA2E_11D4_9E85_0000E8C3064A__INCLUDED_)
