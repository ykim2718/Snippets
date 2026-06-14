#if !defined(AFX_MYTABCTRL_H__D1BA9982_6D52_11D4_9622_0000E8C3064A__INCLUDED_)
#define AFX_MYTABCTRL_H__D1BA9982_6D52_11D4_9622_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GargamelTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "stdafx.h"

static unsigned int const
GargamelUpdateDataMessage=RegisterWindowMessage(_T("GargmelUpdateDataMessage"));

/////////////////////////////////////////////////////////////////////////////
// CGargamelTabCtrl window

class CGargamelTabCtrl : public CTabCtrl
{
// Construction
public:
	CGargamelTabCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelTabCtrl)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	int IsActivatedDialogInTabControl(int nDialogID);
	int SetTabArrayItemProperty(int nDialogID,int nTabIndex,int bShow);
   CDialog *GetDialogClassPtr(int nDialogID);
	void Commence();
	virtual ~CGargamelTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGargamelTabCtrl)
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	int GetTabArrayIndexFromTabIndex(int nTabIndex);
	int GetTabArrayIndexFromDialogID(int nDialogID);
	void SetWindowCustomizedFirst();
	int GetTabArrayCount();
	void AddToTapArray(CString sText,CDialog *pDialog,int nDialogID,int bShow);
   int m_nTabArrayIndex;
   CUIntArray m_aTabDialogIDs;
   CPtrArray m_aTabDialogs;
   CStringArray m_aTabTexts;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTABCTRL_H__D1BA9982_6D52_11D4_9622_0000E8C3064A__INCLUDED_)
