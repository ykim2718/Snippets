#if !defined(AFX_GRVIEWPAGE_H__55266FA8_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
#define AFX_GRVIEWPAGE_H__55266FA8_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrViewPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrViewPage dialog

class CGrViewPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrViewPage)

// Construction
public:
	CGrViewPage();
	~CGrViewPage();

// Dialog Data
	//{{AFX_DATA(CGrViewPage)
	enum { IDD = IDD_GR_VIEW_PAGE };
	CSpinButtonCtrl	m_SpinY2;
	CSpinButtonCtrl	m_SpinX2;
	CSpinButtonCtrl	m_SpinY1;
	CSpinButtonCtrl	m_SpinX1;
	double	m_dX1;
	double	m_dX2;
	double	m_dY1;
	double	m_dY2;
	double	m_dStep;
	UINT	m_nRow;
	UINT	m_nCol;
	UINT	m_nRCIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrViewPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RoundCoordinateAtTwoDecimalPoint();
	// Generated message map functions
	//{{AFX_MSG(CGrViewPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposGrviewSpinAll(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGrviewRclapply();
	//}}AFX_MSG

   void OnGrviewMove( UINT nID );
   void OnGrviewResize( UINT nID );
   void OnGrviewPresetSize( UINT nID );

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRVIEWPAGE_H__55266FA8_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
