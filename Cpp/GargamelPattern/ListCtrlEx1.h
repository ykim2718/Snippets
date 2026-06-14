#if !defined(AFX_LISTCTRLEX1_H__15098060_88B5_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_LISTCTRLEX1_H__15098060_88B5_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlEx1.h : header file
//

// Derived from the work of Zafir Anjum (1998/08/06) at www.codeguru.com

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx1Edit window

class CListCtrlEx1Edit : public CEdit
{
// Construction
public:
   CListCtrlEx1Edit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx1Edit)
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_height;
	int m_width;
	int m_y;
	int m_x;
	virtual ~CListCtrlEx1Edit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx1Edit)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx1 window

typedef struct {
   char *pLabel;
   int nWidth;
} LCEX_COLUMHEADER;

class CListCtrlEx1 : public CListCtrl
{
// Construction
public:
	CListCtrlEx1();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx1)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
   void SetColumnHeaders(int nColumn,LCEX_COLUMHEADER *pColumns);
   void AddRow(const char *qString);
   void InsertRow(const char *qString,int nPos=-1); // add before current top most selection
   void DeleteRows(); // delete current selections
   void Clear();
   CString GetRow(int nRow);
   int  GetRowCount();
   int  GetColumnCount();
   BOOL CopyRow(int nFrom,int nTo);
   BOOL MoveRow(int nFrom,int nTo);

	int m_nColumn;
	CString m_sRowStringDivider;
	BOOL m_bLCEEdit;
	CListCtrlEx1Edit m_LCEEdit;
	virtual ~CListCtrlEx1();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx1)
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLEX1_H__15098060_88B5_11D5_9E85_0000E8C3064A__INCLUDED_)
