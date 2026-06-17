#if !defined(AFX_GRPROPERTYSHEET_H__5083D121_0104_11D4_AA81_9F311B65DE20__INCLUDED_)
#define AFX_GRPROPERTYSHEET_H__5083D121_0104_11D4_AA81_9F311B65DE20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrPropertySheet.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// shik96

#include "GrPlotPage.h"
#include "GrGlobPage.h"
#include "GrAttrPage.h"
#include "GrDataPage.h"
#include "GrXyzbPage.h"
#include "GrSlctPage.h"
#include "GrAxisPage.h"
#include "GrTextPage.h"
#include "GrUfunPage.h"
#include "GrViewPage.h"

#include "plotse.h"

/////////////////////////////////////////////////////////////////////////////
// CGrPropertySheet

class CGrPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CGrPropertySheet)

// Construction
public:
	CGrPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CGrPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrPropertySheet)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetFolderFromFilePath(const char *qFilePath);
	void RefreshWindowTitleText();
	void OnButtonPlotNext();
	void OnButtonPlotPrevious();
	CButton m_ButtonPlotNext;
	CButton m_ButtonPlotPrev;
	BOOL m_bOk;
	int m_nPlotIndex;
	int m_nPlotTotal;
   CString m_sGrFile; // 20030216
   CString m_sGrLog; // 2001.0423
   CString m_sGrScriptHead,m_sGrScriptTail; // 20020211
	CString m_sGrScript;
   CGrPlotPage m_PlotPage; // 0
   CGrAttrPage m_AttrPage; // 1
	CGrDataPage m_DataPage; // 2
	CGrXyzbPage m_XyzbPage; // 3 // 20030417
	CGrSlctPage m_SlctPage; // 4
	CGrAxisPage m_AxisPage; // 5
	CGrTextPage m_TextPage; // 6
	CGrUfunPage m_UfunPage; // 7
	CGrViewPage m_ViewPage; // 8
	CGrGlobPage m_GlobPage; // 9
	void AddControlPages();
	virtual ~CGrPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGrPropertySheet)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPROPERTYSHEET_H__5083D121_0104_11D4_AA81_9F311B65DE20__INCLUDED_)
