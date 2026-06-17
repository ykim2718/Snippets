#if !defined(AFX_GRUFUNPAGE_H__55266FA7_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
#define AFX_GRUFUNPAGE_H__55266FA7_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrUfunPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrUfunPage dialog

class CGrUfunPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrUfunPage)

// Construction
public:
	CGrUfunPage();
	~CGrUfunPage();

// Dialog Data
	//{{AFX_DATA(CGrUfunPage)
	enum { IDD = IDD_GR_UFUN_PAGE };
	CString	m_sText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrUfunPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   CFont m_MyFont;

	// Generated message map functions
	//{{AFX_MSG(CGrUfunPage)
	afx_msg void OnGrufunHelp();
	afx_msg void OnGrufunClear();
	afx_msg void OnGrufunTry();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRUFUNPAGE_H__55266FA7_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
