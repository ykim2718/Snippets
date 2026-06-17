#if !defined(AFX_SMALLREPLACEDIALOG_H__F46468C1_1EFC_11D4_BE58_A2A1EB8A383F__INCLUDED_)
#define AFX_SMALLREPLACEDIALOG_H__F46468C1_1EFC_11D4_BE58_A2A1EB8A383F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GargamelPatternSuperseding.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternSuperseding dialog

class CGargamelPatternSuperseding : public CDialog
{
// Construction
public:
	CGargamelPatternSuperseding( // standard constructor
      CWnd* pParent = NULL,
      const char *pFindWhat = NULL,
      const char *pReplaceWith = NULL
   );

// Dialog Data
	//{{AFX_DATA(CGargamelPatternSuperseding)
	enum { IDD = IDD_GARGAMEL_PATTERN_SUPERSEDING };
	CString	m_sFindWhat;
	CString	m_sReplaceWith;
	BOOL	m_bFindWhatInAlias;
	BOOL	m_bFindWhatInEquation;
	BOOL	m_bFindWhatInPattern;
	BOOL	m_bFindWhatInFormat;
	BOOL	m_bFindWhatIn1stNo;
	BOOL	m_bFindWhatInLastNo;
	BOOL	m_bFindWhatInLC;
	BOOL	m_bFindWhatInUC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelPatternSuperseding)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGargamelPatternSuperseding)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMALLREPLACEDIALOG_H__F46468C1_1EFC_11D4_BE58_A2A1EB8A383F__INCLUDED_)
