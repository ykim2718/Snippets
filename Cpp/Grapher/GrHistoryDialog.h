#if !defined(AFX_GRHISTORYDIALOG_H__08D81E46_1BA6_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRHISTORYDIALOG_H__08D81E46_1BA6_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrHistoryDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrHistoryDialog dialog

class CGrHistoryDialog : public CDialog
{
// Construction
public:
   CBitmap m_bmpGripper;
	CGrHistoryDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrHistoryDialog)
	enum { IDD = IDD_GR_HISTORY };
	CStatic	m_Gripper;
	CString	m_sHistory;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrHistoryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrHistoryDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRHISTORYDIALOG_H__08D81E46_1BA6_11D5_9E85_0000E8C3064A__INCLUDED_)
