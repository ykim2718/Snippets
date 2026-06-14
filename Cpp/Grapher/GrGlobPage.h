#if !defined(AFX_GRGLOBPAGE_H__55266FA3_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
#define AFX_GRGLOBPAGE_H__55266FA3_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrGlobPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "ListBoxEx.h"

/////////////////////////////////////////////////////////////////////////////
// CGrGlobPage dialog

class CGrGlobPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrGlobPage)

// Construction
public:
   enum { Landscape=0,Portrait } m_nPageDirection;
	CGrGlobPage();
	~CGrGlobPage();

// Dialog Data
	//{{AFX_DATA(CGrGlobPage)
	enum { IDD = IDD_GR_GLOB_PAGE };
	CString	m_sHeader;
	double	m_dTitleSpaceFactor;
	BOOL	m_bEchoPlotPoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrGlobPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void GetCheckButtonsOfPageDirection();
	void SetCheckButtonsOfPageDirection();
	// Generated message map functions
	//{{AFX_MSG(CGrGlobPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnGrglobHeaderAttribute();
	afx_msg void OnDeltaposGrglobHeaderSpacefactorSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRGLOBPAGE_H__55266FA3_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
