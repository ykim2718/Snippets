#if !defined(AFX_GRXYZBPAGE_H__DA7F73C7_6E67_4162_8980_5358AC03FF93__INCLUDED_)
#define AFX_GRXYZBPAGE_H__DA7F73C7_6E67_4162_8980_5358AC03FF93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrXyzbPage.h : header file
//

#include "XYZListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CGrXyzbPage dialog

class CGrXyzbPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrXyzbPage)

// Construction
public:
	void SetGrScript(const char *pScript,int nScript,int nPlotIndex, const char *qPara);
	double GetValueFromGrLog(const char *qPara,double dDefault);
	CGrXyzbPage();
	~CGrXyzbPage();

// Dialog Data
	//{{AFX_DATA(CGrXyzbPage)
	enum { IDD = IDD_GR_XYZB_PAGE };
	CXYZListBox	m_XYZListBox;
	BOOL	m_bXlbAll;
	BOOL	m_bYlbAll;
	BOOL	m_bZlbAll;
	BOOL	m_bXubAll;
	BOOL	m_bYubAll;
	BOOL	m_bZubAll;
	BOOL	m_bXlbAuto;
	BOOL	m_bXubAuto;
	BOOL	m_bYlbAuto;
	BOOL	m_bYubAuto;
	BOOL	m_bZlbAuto;
	BOOL	m_bZubAuto;
	double	m_dXlbData;
	double	m_dXubData;
	double	m_dYlbData;
	double	m_dYubData;
	double	m_dZlbData;
	double	m_dZubData;
	CString	m_sXlb;
	CString	m_sXub;
	CString	m_sYlb;
	CString	m_sYub;
	CString	m_sZlb;
	CString	m_sZub;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrXyzbPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

   CFont m_MyFont;

	// Generated message map functions
	//{{AFX_MSG(CGrXyzbPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	afx_msg void OnGrxyzbAutoButtons( UINT nID );
	afx_msg void OnGrxyzbApplyAll( UINT nID );

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRXYZBPAGE_H__DA7F73C7_6E67_4162_8980_5358AC03FF93__INCLUDED_)
