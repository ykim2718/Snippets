#if !defined(AFX_GRPATHENVIRONEMNTDIALOG_H__58954600_AAB4_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRPATHENVIRONEMNTDIALOG_H__58954600_AAB4_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrPathEnvironemntDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrPathEnvironmentDialog dialog

class CGrPathEnvironmentDialog : public CDialog
{
// Construction
public:
	CGrPathEnvironmentDialog(CWnd* pParent = NULL);   // standard constructor
   ~CGrPathEnvironmentDialog();

// Dialog Data
	//{{AFX_DATA(CGrPathEnvironmentDialog)
	enum { IDD = IDD_GR_PATH_ENVIRONMENT };
	CString	m_sPathOfEditor;
	CString	m_sPathOfGargamel;
	CString	m_sPathOfSample;
	CString	m_sPathOfSmurfette;
	CString	m_sHomeDirectory;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrPathEnvironmentDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrPathEnvironmentDialog)
	afx_msg void OnPathenvEditorBrowser();
	afx_msg void OnPathenvGargamelBrowser();
	afx_msg void OnPathenvSampleBrowser();
	afx_msg void OnPathenvSmurfetteBrowser();
	afx_msg void OnClose();
	afx_msg void OnPathenvHomeDirectory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPATHENVIRONEMNTDIALOG_H__58954600_AAB4_11D4_9E85_0000E8C3064A__INCLUDED_)
