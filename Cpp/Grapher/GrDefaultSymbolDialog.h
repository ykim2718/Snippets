#if !defined(AFX_GRDEFAULTSYMBOLDIALOG_H__83288982_3288_11D4_AA81_A2F84DB0C2F0__INCLUDED_)
#define AFX_GRDEFAULTSYMBOLDIALOG_H__83288982_3288_11D4_AA81_A2F84DB0C2F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrDefaultSymbolDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CGrDefaultSymbolDialog dialog

#include "ColorBtn.h"
#include "GrPlotSymbolBtn.h"

class CGrDefaultSymbolDialog : public CDialog
{
// Construction
public:
	CWinApp * m_pApp;
	CString GetCurrentScript();
	BOOL GetParameterValue(CString &string,const char *parameter,CString &value);
	void UpdateMemberData();
	void UpdateDialogControl();
	int m_nDefaultSymbolIndex;
   int m_nDefaultSymbolTotal;
	void SetComboBoxStringsOfLineStyle(int nID);
	void SetComboBoxStringsOfLineWidth(int nID);
   CColorBtn m_SymbFillColorBtn;
   CColorBtn m_SymbStrokeColorBtn;
	CGrPlotSymbolBtn m_SymbTypeBtn;

	CGrDefaultSymbolDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrDefaultSymbolDialog)
	enum { IDD = IDD_GR_DEFAULT_SYMBOL };
	CSliderCtrl	m_Slider;
	BOOL	m_bLineConnection;
	UINT	m_nLegendSize;
	CString	m_sLegendText;
	UINT	m_nSymbSize;
	BOOL	m_bSymbSolid;
	CString	m_sLineStyle;
	CString	m_sLineWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrDefaultSymbolDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   void OnMyMessage(WPARAM wParam,LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CGrDefaultSymbolDialog)
	afx_msg void OnGrdefaultsymbolLoad();
	afx_msg void OnGrdefaultsymbolSave();
	afx_msg void OnGrdefaultsymbolAdd();
	afx_msg void OnGrdefaultsymbolDel();
	virtual BOOL OnInitDialog();
	afx_msg void OnGrdefaultsymbolSolid();
	afx_msg void OnDeltaposGrdefaultsymbolSizeSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposGrdefaultsymbolLegendSizeSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnGrdefaultsymbolDefault();
	afx_msg void OnGrdefaultsymbolPrev();
	afx_msg void OnGRDEFAULTSYMBOLNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRDEFAULTSYMBOLDIALOG_H__83288982_3288_11D4_AA81_A2F84DB0C2F0__INCLUDED_)
