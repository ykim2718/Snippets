#if !defined(AFX_GRDATAPAGE_H__55266FA2_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
#define AFX_GRDATAPAGE_H__55266FA2_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrDataPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrDataPage dialog

class CGrDataPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrDataPage)

// Construction
public:
	void HandleAChangeOfRadioButtons();
   enum {MATRIX_FILE=0,MATRIX_PREV,MATRIX_PREVCLONE,MATRIX_BYUSERFUNCTION,
      MATRIX_BYSCRIPT} m_nMatrixSourceType;
	CGrDataPage();
	~CGrDataPage();

// Dialog Data
	//{{AFX_DATA(CGrDataPage)
	enum { IDD = IDD_GR_DATA_PAGE };
	BOOL	m_bExchangeRowColumn;
	CString	m_sFromDataName;
	CString	m_sFromScriptOption;
	CString	m_sFromScriptPattern;
	CString	m_sFromScriptSplit;
	BOOL	m_bSortByXColumn;
	BOOL	m_bReuseFilesOnADisk;
	CString	m_sGrxyFile;
	CString	m_sDataBlockIndex;
	CString	m_sGrFolder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrDataPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGrDataPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnGrdataFromFile();
	afx_msg void OnGrdataFromUserFunction();
	afx_msg void OnGrdataFromPreviousMatrix();
	afx_msg void OnGrdataFromPreviousCloneMatrix();
	afx_msg void OnGrdataFromScript();
	afx_msg void OnGrdataFromFileFileBrowser();
	afx_msg void OnGrdataFromScriptPatternBrowser();
	afx_msg void OnGrdataFromScriptSplitBrowser();
	afx_msg void OnGrdataGrxyFileBrowser();
	afx_msg void OnGrdataFromfileFileViewer();
	afx_msg void OnGrdataFileGetdbi();
	afx_msg void OnGrdataFileApplyall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRDATAPAGE_H__55266FA2_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
