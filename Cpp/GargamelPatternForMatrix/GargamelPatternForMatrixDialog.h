#if !defined(AFX_GARGAMELPATTERNFORMATRIXDIALOG_H__03589E1C_4492_4AB2_A243_A646546A4F33__INCLUDED_)
#define AFX_GARGAMELPATTERNFORMATRIXDIALOG_H__03589E1C_4492_4AB2_A243_A646546A4F33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GargamelPatternForMatrixDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixDialog dialog

class CGargamelPatternForMatrixDialog : public CDialog
{
// Construction
public:
   CFont m_MyFont;
	CString m_sLastScriptOnDestory;
	CString GetScriptFromDialog();
	void SetScriptToDialog(const CString &sScript);
	CGargamelPatternForMatrixDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGargamelPatternForMatrixDialog)
	enum { IDD = IDD_GARGAMEL_PATTERNFORMATRIX };
	CString	m_sBeginning;
	CString	m_sEnding;
	CString	m_sBlockSelections;
	BOOL	m_bBlockSelectionAll;
	int		m_n1stColumn;
	CString	m_sOtherColumns;
	CString	m_sFormat;
	CString	m_sEquation;
	CString	m_sCutHigh;
	CString	m_sCutLow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelPatternForMatrixDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void TrimLeftRight(CString &sStuff);

	// Generated message map functions
	//{{AFX_MSG(CGargamelPatternForMatrixDialog)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnFormatHelp();
	afx_msg void OnBlockSelectionAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELPATTERNFORMATRIXDIALOG_H__03589E1C_4492_4AB2_A243_A646546A4F33__INCLUDED_)
