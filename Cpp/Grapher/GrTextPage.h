#if !defined(AFX_GRTEXTPAGE_H__55266FA6_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
#define AFX_GRTEXTPAGE_H__55266FA6_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrTextPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "ListCtrlEx2.h"

/////////////////////////////////////////////////////////////////////////////
// CGrTextPage dialog

class CGrTextPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrTextPage)

// Construction
public:
	void SetTextFontAttributeFromDialog(int nType,int nIndexOfTheSameType=1);
	void GetTextDataFromDialog();
	void SetTypeMatchedTextOfScript(
      const char *pScript,int nScript,int nPlotIndex,
      int nType,int nIndexOfTheSameType,const char *pPara);
	CGrTextPage();
	~CGrTextPage();

// Dialog Data
	//{{AFX_DATA(CGrTextPage)
	enum { IDD = IDD_GR_TEXT_PAGE };
	CListCtrlEx2	m_ListCtrlEx;
	CString	m_sText01;
	CString	m_sText02;
	CString	m_sText03;
	CString	m_sText04;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrTextPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGrTextPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnGrtextText01Btn();
	afx_msg void OnGrtextText02Btn();
	afx_msg void OnGrtextText03Btn();
	afx_msg void OnGrtextText04Btn();
	afx_msg void OnGrtextListctrlAdd();
	afx_msg void OnGrtextListctrlDelete();
	afx_msg void OnGrtextListctrlBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRTEXTPAGE_H__55266FA6_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
