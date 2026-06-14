#if !defined(AFX_GRRENOVATORDIALOG_H__D2A2B601_2140_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRRENOVATORDIALOG_H__D2A2B601_2140_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrRenovatorDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "ListCtrlEx2.h"

/////////////////////////////////////////////////////////////////////////////
// CGrRenovatorDialog dialog

#include <afxext.h>
// In this example we use the CBitmapButton AutoLoad member function.
//  Autoload uses the text/title of the button as the base resource name.
//  For this trivial example the buttons are called "OK" and "CANCEL",
//  which use the bitmaps "OKU", "OKD", "OKF", "CANCELU", "CANCELD"
//  and "CANCELF" respectively for the up, down and focused images.
#define ID_BUTTON_MIN IDOK
#define N_BUTTONS     (IDCANCEL-ID_BUTTON_MIN+1)

class CGrRenovatorDialog : public CDialog
{
// Construction
public:
   CImageList m_SmallImageList;
	CString m_sDirectory;
	CGrRenovatorDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrRenovatorDialog)
	enum { IDD = IDD_GR_RENOVATOR };
	CListCtrlEx2	m_ListCtrlEx2;
	CString	m_sOutFolder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrRenovatorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   // array of buttons constructed with no attached bitmap images
	CBitmapButton Buttons[N_BUTTONS];

	// Generated message map functions
	//{{AFX_MSG(CGrRenovatorDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnRenovatorAdd();
	afx_msg void OnRenovatorDelete();
	afx_msg void OnRenovatorOutfolderBrowser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRRENOVATORDIALOG_H__D2A2B601_2140_11D5_9E85_0000E8C3064A__INCLUDED_)
