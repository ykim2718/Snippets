#if !defined(AFX_SMALLFONTATTRDIALOG_H__16F27F80_1D4F_11D4_AA81_D5B89D3D3039__INCLUDED_)
#define AFX_SMALLFONTATTRDIALOG_H__16F27F80_1D4F_11D4_AA81_D5B89D3D3039__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmallFontAttrDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "colorbtn.h"

/////////////////////////////////////////////////////////////////////////////
// CSmallFontAttrDialog dialog

class CSmallFontAttrDialog : public CDialog
{
// Construction
public:
	void SetWindowGravityPos(int xPos, int yPos);
	void SetWindowGravityPos(CPoint Point);
	CColorBtn m_ColorBtn;
	CSmallFontAttrDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSmallFontAttrDialog)
	enum { IDD = IDD_GR_SMALL_FONT_SELECTION };
	CString	m_sAlignment;
	UINT	m_nAngle;
	UINT	m_nHeight;
	UINT	m_nWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmallFontAttrDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nY;
	int m_nX;
	// Generated message map functions
	//{{AFX_MSG(CSmallFontAttrDialog)
	afx_msg void OnFontdDefault();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposFontdHeightSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMALLFONTATTRDIALOG_H__16F27F80_1D4F_11D4_AA81_D5B89D3D3039__INCLUDED_)
