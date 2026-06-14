#if !defined(AFX_WRITEFILELISTTOSYNCHRONIZE_H__83288980_3288_11D4_AA81_A2F84DB0C2F0__INCLUDED_)
#define AFX_WRITEFILELISTTOSYNCHRONIZE_H__83288980_3288_11D4_AA81_A2F84DB0C2F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WriteFileListToSynchronize.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "ListBoxEx.h"

/////////////////////////////////////////////////////////////////////////////
// CWriteFileListToSynchronize dialog

class CWriteFileListToSynchronize : public CDialog
{
// Construction
public:
	CString m_sLastDirectory;
   ~CWriteFileListToSynchronize();
	CWriteFileListToSynchronize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWriteFileListToSynchronize)
	enum { IDD = IDD_GARGAMEL_WRITEFILELISTTOSYNCHRONIZE };
	CListBoxEx	m_fList;
	CString	m_sFilter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteFileListToSynchronize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWriteFileListToSynchronize)
	afx_msg void OnGargamelWriteFileListAdd();
	afx_msg void OnGargamelWriteFileListClear();
	afx_msg void OnGargamelWriteFileListReplace();
	afx_msg void OnGargamelWritefilelistFilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWnd* m_pParent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEFILELISTTOSYNCHRONIZE_H__83288980_3288_11D4_AA81_A2F84DB0C2F0__INCLUDED_)
