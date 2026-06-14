#if !defined(AFX_GRPLOTPAGE_H__55266FA4_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
#define AFX_GRPLOTPAGE_H__55266FA4_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrPlotPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrPlotPage dialog

class CGrPlotPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrPlotPage)

// Construction
public:
	void DelTreeCtrlSelection(int nIndex);
	void SetTreeCtrlSelection(int nIndex);
	int GetTreeCtrlCurrentSelection();
	HENHMETAFILE GetEnhMetaFileOfGr( int nPlotIndex );
	CPtrArray m_aEMF;
   CUIntArray m_aEMFIndex;
	CString GetScriptPlotString(CString &Script,int nPlot);
	CWnd *m_pSheet;
	CGrPlotPage();
	~CGrPlotPage();

// Dialog Data
	//{{AFX_DATA(CGrPlotPage)
	enum { IDD = IDD_GR_PLOT_PAGE };
	CTreeCtrl	m_TreeCtrl;
	CStatic	m_EmfCanvas;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrPlotPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGrPlotPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnGrplotAdd();
	afx_msg void OnGrplotDelete();
	afx_msg void OnGrplotToemf();
	afx_msg void OnSelchangedGrplotTreectrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGrplotCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPLOTPAGE_H__55266FA4_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
