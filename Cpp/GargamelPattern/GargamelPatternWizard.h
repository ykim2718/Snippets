#if !defined(AFX_SEARCHSTRINGSWIZARD_H__8FF43760_9F60_11D3_9A00_0000E8C3064A__INCLUDED_)
#define AFX_SEARCHSTRINGSWIZARD_H__8FF43760_9F60_11D3_9A00_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GargamelPatternWizard.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternWizard dialog

class CGargamelPatternWizard : public CDialog
{

//shik
private:
   CWnd *m_pParent;
public:
   virtual BOOL Create()
   { return CDialog::Create(CGargamelPatternWizard::IDD,NULL); };
   virtual void PostNcDestroy()
   { delete this; };
   void SetParentCWnd( CWnd *parent )
   { m_pParent=parent; }
//eoShik

// Construction
public:
	CString m_sFile;
	CString m_sLastDirectory;
   ~CGargamelPatternWizard();
	CGargamelPatternWizard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGargamelPatternWizard)
	enum { IDD = IDD_GARGAMEL_PATTERN_WIZARD };
	CListBox	m_ListBox;
	UINT	m_nFixedWidthNo;
	CString	m_sSpecialString;
	BOOL	m_bSpecialCharOthers;
	BOOL	m_bSpecialCharSpace;
	BOOL	m_bSpecialCharTab;
	UINT	m_nLineScopeNo;
	CString	m_sFilter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelPatternWizard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGargamelPatternWizard)
	afx_msg void OnGargamelPatternWizardOpenfile();
	virtual BOOL OnInitDialog();
	afx_msg void OnGargamelPatternWizardConfirm();
	afx_msg void OnDblclkGargamelPatternWizardListbox();
	afx_msg void OnGargamelPatternWizardReopen();
	afx_msg void OnDeltaposGargamelPatternwizardLinescopeSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHSTRINGSWIZARD_H__8FF43760_9F60_11D3_9A00_0000E8C3064A__INCLUDED_)
