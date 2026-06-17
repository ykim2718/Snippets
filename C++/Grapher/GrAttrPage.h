#if !defined(AFX_GRATTRPAGE_H__55266FA0_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
#define AFX_GRATTRPAGE_H__55266FA0_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrAttrPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrAttrPage dialog

class CGrAttrPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrAttrPage)

// Construction
public:
	void SetCheckButtonsOfZScale();
   enum { Genetic=0,GeneticPlus,Moment,Flat3D,Area,Bar,Column,Pie } m_attrType;
   enum { TwoDimension=0,ThreeDimension } m_dimension;
   enum { Linear=0,Logarithmic,Series,Normal,Weibull } m_xScale,m_yScale,m_zScale;
	CGrAttrPage();
	~CGrAttrPage();

// Dialog Data
	//{{AFX_DATA(CGrAttrPage)
	enum { IDD = IDD_GR_ATTR_PAGE };
	BOOL	m_bAttrPrevious;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrAttrPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   void SetCheckButtonsOfType();
   void GetCheckButtonsOfType();
   void SetCheckButtonsOfDimension();
   void GetCheckButtonsOfDimension();
   void SetCheckButtonsOfXScale();
   void GetCheckButtonsOfXScale();
   void SetCheckButtonsOfYScale();
   void GetCheckButtonsOfYScale();
	// Generated message map functions
	//{{AFX_MSG(CGrAttrPage)
	afx_msg void OnGrattrTypeGenetic();
	afx_msg void OnGrattrTypeMoment();
	afx_msg void OnGrattrTypeArea();
	afx_msg void OnGrattrTypeBar();
	afx_msg void OnGrattrTypeColumn();
	afx_msg void OnGrattrTypePie();
	afx_msg void OnGrattrDim2d();
	afx_msg void OnGrattrDim3d();
	afx_msg void OnGrattrScaleXLinear();
	afx_msg void OnGrattrScaleXLogarithmic();
	afx_msg void OnGrattrScaleXNormal();
	afx_msg void OnGrattrScaleXWeibull();
	afx_msg void OnGrattrScaleXSeries();
	afx_msg void OnGrattrScaleYLinear();
	afx_msg void OnGrattrScaleYLogarithmic();
	afx_msg void OnGrattrScaleYNormal();
	afx_msg void OnGrattrScaleYWeibull();
	virtual BOOL OnInitDialog();
	afx_msg void OnGrattrTypeFlat3d();
	afx_msg void OnGrattrTypeGeneticplus();
	afx_msg void OnGrattrScaleZLinear();
	afx_msg void OnGrattrScaleZLogarithmic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRATTRPAGE_H__55266FA0_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
