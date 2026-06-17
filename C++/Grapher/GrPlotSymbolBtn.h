#if !defined(AFX_PLOTSYMBOLBTN_H__3FFBFAC0_0CD6_11D4_AA81_DAC9A7943584__INCLUDED_)
#define AFX_PLOTSYMBOLBTN_H__3FFBFAC0_0CD6_11D4_AA81_DAC9A7943584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrPlotSymbolBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#define WM_PLOTSYMBOLBTNMESSAGE (WM_USER+2)

#define ID_GR_PLOT_SYMBOL_BUTTON_01 (10001)
#define ID_GR_PLOT_SYMBOL_BUTTON_71 (10071)

/////////////////////////////////////////////////////////////////////////////
// CGrPlotSymbolBtnDlg dialog

class CGrPlotSymbolBtnDlg : public CDialog
{
// Construction
public:
	//int m_nSymbolIndex;
	CButton *m_pParent;
	CGrPlotSymbolBtnDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrPlotSymbolBtnDlg)
	enum { IDD = IDD_GR_PLOT_SYMBOL_PORTFOLIO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrPlotSymbolBtnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrPlotSymbolBtnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

   void EndDialog( int nResult );
   void OnSymbolButton( UINT nID );

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGrPlotSymbolBtn window

class CGrPlotSymbolBtn : public CButton
{
// Construction
public:
	CGrPlotSymbolBtn();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrPlotSymbolBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	unsigned int m_nSymbolIndex;
   BOOL m_bFillSymbol;
	BOOL m_bStrokeSymbol;
   COLORREF m_nSymbStrokeColor;
   COLORREF m_nSymbFillColor;
	CGrPlotSymbolBtnDlg m_SubDialog;
	virtual ~CGrPlotSymbolBtn();

	// Generated message map functions
protected:
   void DrawItem(LPDRAWITEMSTRUCT);
	//{{AFX_MSG(CGrPlotSymbolBtn)
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTSYMBOLBTN_H__3FFBFAC0_0CD6_11D4_AA81_DAC9A7943584__INCLUDED_)
