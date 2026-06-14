#if !defined(AFX_XYZLISTBOX_H__A833E55F_70DA_4011_BC94_8C476CCF213C__INCLUDED_)
#define AFX_XYZLISTBOX_H__A833E55F_70DA_4011_BC94_8C476CCF213C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XYZListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXYZListBox window

class CXYZListBox : public CListBox
{
// Construction
public:
	CXYZListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXYZListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXYZListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXYZListBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XYZLISTBOX_H__A833E55F_70DA_4011_BC94_8C476CCF213C__INCLUDED_)
