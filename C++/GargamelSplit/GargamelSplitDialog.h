#if !defined(AFX_GARGAMELSPLITDIALOG_H__4CFFBB60_43B4_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELSPLITDIALOG_H__4CFFBB60_43B4_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GargamelSplitDialog.h : header file
//

////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

//{ // DialogAggregate_i.c
const IID IID_IFileFolderTreeSelectionDialog = {0x48F0701D,0xF94A,0x11D4,{0x9E,0x85,0x00,0x00,0xE8,0xC3,0x06,0x4A}};
const IID LIBID_DIALOGAGGREGATELib = {0x48F0700E,0xF94A,0x11D4,{0x9E,0x85,0x00,0x00,0xE8,0xC3,0x06,0x4A}};
const CLSID CLSID_FileFolderTreeSelectionDialog = {0x48F0701E,0xF94A,0x11D4,{0x9E,0x85,0x00,0x00,0xE8,0xC3,0x06,0x4A}};
//}   DialogAggregate_i.c

#include "ListBoxEx.h"
#include "FileDialogEx.h"
#include "Token.h"
#include "WriteFileListToSynchronize.h"

#include "../Anyfind/Iface.h"

#define RegKeySettings             "Settings"
#define RegKeyExecCount            "nExecCount"
#define RegKeyLastDirectoryAtSplit "sLastDirectory@Split"
#define RegKeyLastScriptDirectoryAtSplit "sLastScriptDirectory@Split"
#define RegKeyTextViewer           "sTextViewer"

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitDialog dialog

class CGargamelSplitDialog : public CDialog
{
// Construction
public:
	BOOL m_bCheckFileExistance;
   CString GetScriptFromDialog();
	void SetScriptToDialog(const CString &Stream);
	BOOL WriteCurrentListToAFile(const char *qFile);
   void ListDelete( int nIDList );
	int ListChkAddedBefore(int nIDList,const char *pString);
   void SetEnableDisableButtons();

	IAnyfind *m_pAnyfind;
	CString m_sLastScriptOnDestory;
	CString m_sLastDirectory;
   CString m_sLastScriptDirectory;

   ~CGargamelSplitDialog();
	CGargamelSplitDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGargamelSplitDialog)
	enum { IDD = IDD_GARGAMEL_SPLIT };
	CButton	m_MenuButtonClear;
	CListBoxEx	m_ListBox;
	UINT	m_nTailCountForAlias;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelSplitDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGargamelSplitDialog)
	afx_msg void OnSplitAdd();
	afx_msg void OnSplitInsert();
	afx_msg void OnSplitDelete();
	afx_msg void OnSplitClear();
	afx_msg void OnSplitCutpaste();
	afx_msg void OnSplitMoveUp();
	afx_msg void OnSplitMoveDown();
	afx_msg void OnSplitSort();
	afx_msg void OnSplitAliasInsert();
	afx_msg void OnDeltaposSplitAliasInsertTailcountSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSplitChangeDirectory();
	afx_msg void OnSplitReadFilelist();
	afx_msg void OnSplitWriteFilelist();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSplitViewEditor();
	afx_msg void OnSplitView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELSPLITDIALOG_H__4CFFBB60_43B4_11D5_9E85_0000E8C3064A__INCLUDED_)
