#if !defined(AFX_GARGAMELPATTERNPPG_H__3340694A_F75F_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELPATTERNPPG_H__3340694A_F75F_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GargamelPatternPpg.h : Declaration of the CGargamelPatternPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "Token.h"
#include "ListCtrlEx1.h"
#include "FileDialogEx.h"
#include "GargamelPatternWizard.h"
#include "GargamelPatternSuperseding.h"

#include "../Anyfind/Iface.h"

#if !defined(SWAP)
#define SWAP(x,y)   ((x)^=(y)^=(x)^=(y))
#endif

static char *qPatternAttributeString[]={"No attribute","Tracking","Calculating"};
#define PATTERN_ATTRIBUTE_NONE        0
#define PATTERN_ATTRIBUTE_TRACKING    1
#define PATTERN_ATTRIBUTE_CALCULATING 2

static char *qAliasMethodString[]={"Token","Offset","Pattern"};
#define ALIAS_METHOD_TOKEN   0
#define ALIAS_METHOD_OFFSET  1
#define ALIAS_METHOD_PATTERN 2

static char *qDataFormatString[]={"%s","%.0f","%.3f","%.3e","%.3z"};

#define GARGAMEL_SCRIPT_LINE_END "\r\n"

#define GARGAMEL_PATTERN_SAVE_FORMAT "\"%s\" \t%s \t%s %s %s %s %s %s"
        // pattern alias format firstNo lastNo equation lc uc
#define GARGAMEL_INDEXOF_PATTERN  0
#define GARGAMEL_INDEXOF_ALIAS    1
#define GARGAMEL_INDEXOF_FIRSTNO  2
#define GARGAMEL_INDEXOF_LASTNO   3
#define GARGAMEL_INDEXOF_FORMAT   4
#define GARGAMEL_INDEXOF_EQUATION 5
#define GARGAMEL_INDEXOF_LOWERCUT 6
#define GARGAMEL_INDEXOF_UPPERCUT 7

#define RegKeySettings               _T("Settings")
#define RegKeyExecCount              _T("nExecCount")
#define RegKeyLastDirectoryAtPattern _T("sLastDirectory@Pattern")
#define RegKeyLastDirectoryOfPatternWizard _T("sLastDirectoryOfPatternWizard")

////////////////////////////////////////////////////////////////////////////
// CGargamelPatternPropPage : See GargamelPatternPpg.cpp.cpp for implementation.

class CGargamelPatternPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGargamelPatternPropPage)
	DECLARE_OLECREATE_EX(CGargamelPatternPropPage)

// Constructor
public:
	void SetEnableDisableButtons();
	CString StringCompact(const char *qString);
   CString m_sFindWhat,m_sReplaceWith;
	CString GetScriptFromDialog();
	void SetRemotely(CString aString);
	void SetScriptToDialog(const CString &Stream,BOOL bAttachment);
	CString m_sLastDirectory;
	CString GetStringToBeAdded();
	CString GetAliasString(CString String, int nMethod, int nFrom, int nTo);
   CGargamelPatternWizard *m_WizardModeless;
   ~CGargamelPatternPropPage();
	CGargamelPatternPropPage();

// Dialog Data
	//{{AFX_DATA(CGargamelPatternPropPage)
	enum { IDD = IDD_PROPPAGE_GARGAMELPATTERN };
	CComboBox	m_Attribute;
	CComboBox	m_AliasAutoMethod;
	CListCtrlEx1	m_ListCtrl;
	CString	m_sPatternText;
	CString	m_sPatternAlias;
	CString	m_sEquation;
	BOOL	m_bAliasAuto;
	CString	m_sFormat;
	int		m_nAliasFrom;
	int		m_nAliasTo;
	CString	m_sCutHighNo;
	CString	m_sCutLowNo;
	unsigned	m_nGrabFirstNo;
	unsigned	m_nGrabLastNo;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CGargamelPatternPropPage)
	afx_msg void OnPatternAdd();
	afx_msg void OnPatternAddWizard();
	afx_msg void OnPatternIns();
	afx_msg void OnPatternDel();
	afx_msg void OnPatternClear();
	afx_msg void OnPatternMoveup();
	afx_msg void OnPatternMovedown();
	afx_msg void OnPatternAliasChange();
	afx_msg void OnPatternSuperseding();
	afx_msg void OnPatternScriptReadAttach();
	virtual BOOL OnInitDialog();
	afx_msg void OnPatternAliasAutoTb();
	afx_msg void OnPatternAliasAutoTry();
	afx_msg void OnSelchangePatternAliasMethod();
	afx_msg void OnPatternFormatHelp();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDblclkPatternListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELPATTERNPPG_H__3340694A_F75F_11D4_9E85_0000E8C3064A__INCLUDED)
