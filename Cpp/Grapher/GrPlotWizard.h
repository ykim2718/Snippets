#if !defined(AFX_GRPLOTWIZARD_H__898BD822_3492_11D4_BE58_A20F38F42D3F__INCLUDED_)
#define AFX_GRPLOTWIZARD_H__898BD822_3492_11D4_BE58_A20F38F42D3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrPlotWizard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrPlotWizard dialog

class CGrPlotWizard : public CDialog
{
// Construction
public:
   enum {FILETYPE_EXT_GR=0,FILETYPE_EXT_GRXY=1,FILETYPE_EXT_DAT=2};
	CString GetGrTemporaryFileName( int nFileType=FILETYPE_EXT_GR );
	int GetGrPlotDefaultSymbol(CString &sDefaultSymbol);
	void ComboBoxAddString(CComboBox *pBox,const CString &String);
	void ComboBoxSetDroppedWidth(CComboBox *pBox);
   void MyUpdateDataTrue();
   void MyUpdateDataFalse();
   CString m_sGargamelTemporaryFile; // out file
	CString m_sSplitAlias;
	CString m_sPatternAlias;
	int m_bNumericAlias;
	int m_nCol;
	int m_nRow;
	int m_nColCountPerBlock;
	int m_nColumnarMatrixType;
	int m_nPostProcessType;
	int m_nSearchType;
	int m_nSplit;
	int m_nPattern;
	CString GetGrPlotScript();
	void ResetViewportCount();
	BOOL SetViewportCount();
   int m_nPlotMap;
	int m_nPlotScatter;
	int m_nPlotSeries;
   BOOL m_bPlotMap;
	BOOL m_bPlotScatter;
	BOOL m_bPlotSeries;
	void SetCheckButtons();
	~CGrPlotWizard();
	CGrPlotWizard(CWnd* pParent = NULL);   // standard constructor
   virtual BOOL Create() { return CDialog::Create(CGrPlotWizard::IDD,NULL); }
   virtual void PostNcDestroy() { delete this; }

// Dialog Data
	//{{AFX_DATA(CGrPlotWizard)
	enum { IDD = IDD_GR_PLOT_WIZARD };
	CComboBox	m_SplitFile;
	CComboBox	m_PatternFile;
	CComboBox	m_PostProcessType;
	CString	m_sMapFile;
	BOOL	m_bCompositeMap;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrPlotWizard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGrPlotWizard)
	afx_msg void OnGrplotwizardReadPattern();
	afx_msg void OnGrplotwizardDraw();
	virtual BOOL OnInitDialog();
	afx_msg void DoGargamel();
	afx_msg void OnGrplotwizardReadsplit();
	afx_msg void OnChangeGrplotwizardPatternfile();
	afx_msg void OnChangeGrplotwizardSplitfile();
	afx_msg void OnGrplotwizardExecpattern();
	afx_msg void OnGrplotwizardExecsplit();
	afx_msg void OnGrplotwizardMap01Read();
	afx_msg void OnEditchangeGrplotwizardPatternfile();
	afx_msg void OnEditchangeGrplotwizardSplitfile();
	afx_msg void OnGrplotwizardMap01Create();
	afx_msg void OnGrplotwizardWritescript();
	afx_msg void OnDropdownGrplotwizardSplitfile();
	afx_msg void OnDropdownGrplotwizardPatternfile();
	afx_msg void OnGrplotwizardMapComposite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_sSplitFile;
	CString m_sPatternFile;
	void OnGrplotwizardRadioButtonHandler(UINT nID);
	BOOL CreateXYFileFromKJTETFormat(const char *pETFile,const char *pOutFile);
	void FindFileInScriptFile(const char *pScriptFile,CString &rFile);
	int GetViewportCount();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPLOTWIZARD_H__898BD822_3492_11D4_BE58_A20F38F42D3F__INCLUDED_)
