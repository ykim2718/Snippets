#if !defined(AFX_GRAXISPAGE_H__55266FA1_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
#define AFX_GRAXISPAGE_H__55266FA1_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrAxisPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "ColorBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CGrAxisPage dialog

class CGrAxisPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrAxisPage)

// Construction
public:
	CFont m_MyFont;
	void GetAxisDataFromDialog(int nIndex);
	void SetAxisDataToDialog(int nIndex);
   enum {TYPE_X=0,TYPE_Y} m_nAxisType;
   enum {LOC_LOW,LOC_MIDDLE,LOC_HIGH,LOC_ANY} m_nAxisLocationType;
	CColorBtn m_AxisColorBtn;
   CColorBtn m_LabelColorBtn;
   CColorBtn m_TitleColorBtn;
   CColorBtn m_MajorGridColorBtn;
   CColorBtn m_MinorGridColorBtn;
	CGrAxisPage();
	~CGrAxisPage();

// Dialog Data
	//{{AFX_DATA(CGrAxisPage)
	enum { IDD = IDD_GR_AXIS_PAGE };
	CComboBox	m_ID;
	BOOL	m_bAxisDisplay;
	BOOL	m_bLabelDisplay;
	BOOL	m_bTitleDisplay;
	double	m_dTitleSpaceFactor;
	CString	m_sLabelEquation;
	CString	m_sTitle;
	double	m_dLocAnyFrom;
	double	m_dLocAnyTo;
	double	m_dLocAnyAt;
	BOOL	m_bMajorTickDisplay;
	BOOL	m_bMajorTickInside;
	BOOL	m_bMajorTickOutside;
	BOOL	m_bMajorTickStepAuto;
	BOOL	m_bMinorTickDisplay;
	BOOL	m_bMinorTickInside;
	BOOL	m_bMinorTickOutside;
	BOOL	m_bMinorTickStepAuto;
	BOOL	m_bMajorGridDisplay;
	BOOL	m_bMinorGridDisplay;
	CString	m_sLabelFormat;
	UINT	m_nAxleThickness;
	CString	m_sMajorTickStep;
	CString	m_sMinorTickStep;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrAxisPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnGraxisOnoffTool( int nID );
	void SetComboBoxStringsOfLineStyle( int nID );
	void GetCheckButtonsOfAxisLocationAny();
	void GetCheckButtonsOfAxisLocation();
	void SetCheckButtonsOfAxisLocation();
	void GetCheckButtonsOfAxisType();
	void SetCheckButtonsOfAxisType();
	// Generated message map functions
	//{{AFX_MSG(CGrAxisPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeGraxisId();
	afx_msg void OnGraxisAdd();
	afx_msg void OnGraxisDel();
	afx_msg void OnGraxisTypeX();
	afx_msg void OnGraxisTypeY();
	afx_msg void OnGraxisLocLowboundary();
	afx_msg void OnGraxisLocMiddle();
	afx_msg void OnGraxisLocHighboundary();
	afx_msg void OnGraxisLocAny();
	afx_msg void OnDeltaposGraxisTitleSpacefactorSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGraxisLabelFontattr();
	afx_msg void OnGraxisTitleFontattr();
	afx_msg void OnGraxisAxisDisplay();
	afx_msg void OnGraxisTickmajorStepAuto();
	afx_msg void OnGraxisTickminorStepAuto();
	afx_msg void OnDeltaposGraxisAxlethicknessSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nPrecedingComboBoxSelection;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAXISPAGE_H__55266FA1_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
