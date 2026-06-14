#if !defined(AFX_GRCOLORTABLEDIALOG_H__87BD78C0_857B_11D4_9622_0000E8C3064A__INCLUDED_)
#define AFX_GRCOLORTABLEDIALOG_H__87BD78C0_857B_11D4_9622_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrPalleteDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96

#include <afxwin.h> // CStatic
#include <afxcmn.h> // CSliderCtrl
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CGrPalleteDialog dialog

class CGrPalleteDialog : public CDialog
{
// Construction
public:
	CFont m_MyFont;
	void GetColorRectAndValue(int nColorIndex,CRect& Rect,unsigned long& nColorValue);
	int m_nColorTotal;
	void RefreshControls(int nColorIndex);
	int m_nColorIndex;
	CGrPalleteDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrPalleteDialog)
	enum { IDD = IDD_GR_PALLETE };
	CStatic	m_P0;
	CStatic	m_P9;
	CStatic	m_P8;
	CStatic	m_P7;
	CStatic	m_P6;
	CStatic	m_P5;
	CStatic	m_P4;
	CStatic	m_P3;
	CStatic	m_P2;
	CStatic	m_P1;
	CSliderCtrl	m_SliderCtrl;
	UINT	m_nB4;
	UINT	m_nB1;
	UINT	m_nB2;
	UINT	m_nB3;
	UINT	m_nB5;
	UINT	m_nB6;
	UINT	m_nB7;
	UINT	m_nB8;
	UINT	m_nB9;
	UINT	m_nG1;
	UINT	m_nG2;
	UINT	m_nG3;
	UINT	m_nG4;
	UINT	m_nG5;
	UINT	m_nG6;
	UINT	m_nG7;
	UINT	m_nG8;
	UINT	m_nG9;
	CString	m_sN1;
	CString	m_sN2;
	CString	m_sN3;
	CString	m_sN4;
	CString	m_sN5;
	CString	m_sN6;
	CString	m_sN7;
	CString	m_sN8;
	CString	m_sN9;
	long	m_nV1;
	long	m_nV2;
	UINT	m_nB0;
	UINT	m_nG0;
	CString	m_sN0;
	UINT	m_nR0;
	UINT	m_nR2;
	UINT	m_nR3;
	UINT	m_nR4;
	UINT	m_nR5;
	UINT	m_nR6;
	UINT	m_nR7;
	UINT	m_nR8;
	UINT	m_nR9;
	long	m_nV0;
	long	m_nV3;
	long	m_nV4;
	long	m_nV5;
	long	m_nV6;
	long	m_nV7;
	long	m_nV8;
	long	m_nV9;
	UINT	m_nR1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrPalleteDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrPalleteDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRCOLORTABLEDIALOG_H__87BD78C0_857B_11D4_9622_0000E8C3064A__INCLUDED_)
