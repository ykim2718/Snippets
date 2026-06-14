#if !defined(AFX_GARGAMELSPLITDIALOG_H__75D1A740_F924_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELSPLITDIALOG_H__75D1A740_F924_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GargamelSplitFrameDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "stdafx.h"
#include "GargamelSplitOcx.h"

/*
const CLSID CLSID_GargamelSplit=
{0x3731EFA6,0xF83D,0x11D4,{0x9E,0x85,0x00,0x00,0xE8,0xC3,0x06,0x4A}};
const GUID IID_GargamelSplit=
{0x3731EFA4,0xF83D,0x11D4,{0x9E,0x85,0x00,0x00,0xE8,0xC3,0x06,0x4A}};
*/

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitFrameDialog dialog

class CGargamelSplitFrameDialog : public CDialog
{
// Construction
public:
	void OnGargamelUpdateData(WPARAM wParam, LPARAM lParam);
	void OnOK();
   void OnCancel();
	void GetScript(CString &sReturn);
	void SetScript(const CString &sForwarding);

	CString m_sStream;
   /* IDispatch *m_pIDGargamel; */

	CGargamelSplitFrameDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGargamelSplitFrameDialog)
	enum { IDD = IDD_GARGAMEL_SPLIT };
	CGargamelSplitOcx	m_GargamelSplitOcx;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelSplitFrameDialog)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGargamelSplitFrameDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELSPLITDIALOG_H__75D1A740_F924_11D4_9E85_0000E8C3064A__INCLUDED_)
