#if !defined(AFX_EXECUTE_H__7609C143_97B2_11D3_9A00_0000E8C3064A__INCLUDED_)
#define AFX_EXECUTE_H__7609C143_97B2_11D3_9A00_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Execute.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "stdafx.h"
#include "../Anyfind/Iface.h"
#include "TextProgressCtrl.h" //2001.0412
#include "GargamelTabCtrl.h"
#include "GargamelPatternFrameDialog.h"
#include "GargamelPatternForMatrixFrameDialog.h"
#include "GargamelSplitFrameDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CExecute dialog

class CExecute : public CDialog
{
	DECLARE_DYNCREATE(CExecute)

//shik
private:
   AFLIST *m_AFlist;
   char ***m_string2d;
   int m_nrl,m_nrh,m_ncl,m_nch;
   CString m_lfsPattern; // Prefix 'lfs' stands for string array
   CString m_lfsSplit;   // whose delimiter is line feed (new line).
//eoShik

// Construction
public:
	void OnGargamelUpdateData(WPARAM wParam, LPARAM lParam);
	CString m_sGargamelVersion;
	void GetDataFromPages( char **strings,char **files );
	void SaveSettings(CString &script);
	int LoadSettings(const char *qStream);
	BOOL MyUpdateDataFalse();
	BOOL MyUpdateDataTrue();
	CString m_sLastDirectory;
	CString m_sInputFile;
	CString m_sOutputFileHeader;
   friend int AFExtractExSynchronizer(char*sFileName);
   int m_nSearchType; // AF_ABSOLUTE,AF_SEQUENTIAL,AF_WILD,AF_BLOCK
	int m_nColumnarMatrixType; // NO,BYPATTERN,BYSPLIT
   //enum {DATAUNIT_FILE,DATAUNIT_FILES};
	int m_nPostProcessType; //0=none,***
	CExecute(CWnd* pParent = NULL);
	~CExecute();

// Dialog Data
	//{{AFX_DATA(CExecute)
	enum { IDD = IDD_GARGAMEL_EXECUTE };
	CComboBox	m_PostProcessType;
	CTextProgressCtrl	m_Progress;
	CString	m_sDumpFileName;
	BOOL	m_bNumericAlias;
	BOOL	m_bSynchronizeOutFileName;
	BOOL	m_bComposite;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CExecute)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
   
   virtual void OnOK() {}; //shik96,2001.0204
   virtual void OnCancel() {}; //shik96,2001.0204

// Implementation
protected:
   //Y.Kim,20030208
   CGargamelApp *m_pApp;
   CGargamelTabCtrl *m_pTab;
   //
	void SetComboBoxStringsOfNumPostProcess();
	// Generated message map functions
	//{{AFX_MSG(CExecute)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnExecuteGargamel();
	afx_msg void OnSynchronizeOutfilename();
	afx_msg void OnExecuteLoad();
	afx_msg void OnExecuteSave();
	afx_msg void OnExecuteSaveAs();
	afx_msg void OnExecuteDump();
	afx_msg void OnExecuteDumpAs();
	afx_msg void OnExecuteDumpAndView();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnExecuteView();
	afx_msg void OnSelchangeOptionNumpostprocess();
	afx_msg void OnExecuteExample();
	afx_msg void OnDismiss();
	//}}AFX_MSG
   
	afx_msg void OnOptionSearchWays(); //Y.Kim,20030206

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXECUTE_H__7609C143_97B2_11D3_9A00_0000E8C3064A__INCLUDED_)
