#if !defined(AFX_GRSLCTPAGE_H__55266FA5_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
#define AFX_GRSLCTPAGE_H__55266FA5_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrSlctPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "ColorBtn.h"
#include "GrPlotSymbolBtn.h"
#include "ToggleBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CGrSlctPage dialog

class CGrSlctPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGrSlctPage)

// Construction
public:
	CFont m_MyFont;
	double GetValueFromGrLog(const char *qPara,double dDefault);
	void InitToolTipsOnInitDialog();
   CToolTipCtrl m_ToolTipForBatch;
	CToolTipCtrl m_ToolTipForPrev;
	CToolTipCtrl m_ToolTipForNext;
	void SetSymbolScriptFromDialog(int nIndex);
	void SetSymbolScriptToDialog(int nIndex);
	CToolTipCtrl m_LegendCountSliderToolTip;
	void SetListBoxStringsOfBatchJob();
	void SetComboBoxStringsOfLineStyle(int nID);
	CColorBtn m_SymbColorBtn;
   CColorBtn m_SymbLineColorBtn;
	CGrPlotSymbolBtn m_SymbTypeBtn;
	CColorBtn	m_EtcMapColorMinBtn;
	CColorBtn	m_EtcMapColorMaxBtn;

	CGrSlctPage();
	~CGrSlctPage();

// Dialog Data
	//{{AFX_DATA(CGrSlctPage)
	enum { IDD = IDD_GR_SYMB_PAGE };
	CStatic	m_LegendSliderLabel;
	CSliderCtrl	m_LegendSlider;
	BOOL	m_bSymbSolid;
	CString	m_sLegendText;
	UINT	m_nSymbPenNo;
	BOOL	m_bLegend;
	BOOL	m_bLineConnection;
	BOOL	m_bSymbol;
	UINT	m_nEtcMapColorTotal;
	UINT	m_nEtcMomentRange;
	UINT	m_nLegendSize;
	UINT	m_nSymbSize;
	CString	m_sEtcMapNoFormat;
	UINT	m_nSymbRepetition;
	UINT	m_nLineWidth;
	BOOL	m_bLegendXLocAuto;
	BOOL	m_bLegendYLocAuto;
	CString	m_sXVariable;
	CString	m_sYVariable;
	CString	m_sZVariable;
	CString	m_sLegendX;
	CString	m_sLegendY;
	//}}AFX_DATA
	//CRadialCtrl	m_RotaryCtrl;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGrSlctPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnGrsymbOnoffTool( int nID );
	int GetXYZVariableColumnCount( int nType );
	void OnHScrollForSlider();
   void OnMyMessage(WPARAM wParam,LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CGrSlctPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnGrslctSymbolSolid();
	afx_msg void OnGrslctAdd();
	afx_msg void OnGrslctAddall();
	afx_msg void OnGrslctDelete();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnGrslctSymbolCb();
	afx_msg void OnDeltaposOfAllSpins(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGrslctLegendTextFontattr();
	afx_msg void OnGrslctPrev();
	afx_msg void OnGrslctNext();
	afx_msg void OnGrslctLegendXLocAuto();
	afx_msg void OnGrslctLegendYLocAuto();
	afx_msg void OnSelchangeGrslctBatchjob();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nPrecedingSliderPosition;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRSLCTPAGE_H__55266FA5_0AF3_11D4_BE58_AB1E7D37713F__INCLUDED_)
