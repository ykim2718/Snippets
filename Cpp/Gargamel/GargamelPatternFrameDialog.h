#if !defined(AFX_GARGAMELPATTERNFRAMEDIALOG_H__2193A361_ED74_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GARGAMELPATTERNFRAMEDIALOG_H__2193A361_ED74_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GargamelPatternFrameDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Yongshik Kim

#include "stdafx.h"

const CLSID CLSID_GargamelPattern=
   {0x33406922,0xF75F,0x11D4,{0x9E,0x85,0x00,0x00,0xE8,0xC3,0x06,0x4A}};

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternFrameDialog dialog

class CGargamelPatternFrameDialog : public CDialog
{
// Construction
public:
	void OnGargamelUpdateData(WPARAM wParam, LPARAM lParam);
	CString m_sStream;
	void GetScript(CString &sReturn);
	void SetScript(CString String);

   IDispatch *m_pIDGargamel;
   IPropertyPagePtr m_pPropertyPage;
	CWnd * m_pWndControl;

	CGargamelPatternFrameDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGargamelPatternFrameDialog)
	enum { IDD = IDD_GARGAMEL_PATTERN };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelPatternFrameDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

   virtual void OnOK() {}; //shik96,2001.0204
   virtual void OnCancel() {}; //shik96,2001.0204

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGargamelPatternFrameDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   DECLARE_INTERFACE_MAP()  //Kim,Yongshik
	BEGIN_INTERFACE_PART( PropertyPageSite, IPropertyPageSite )  //Kim,Yongshik
      STDMETHOD( OnStatusChange )( DWORD dwFlags );  //Kim,Yongshik
      STDMETHOD( GetLocaleID )( LCID *pLocaleID );  //Kim,Yongshik
      STDMETHOD( GetPageContainer )( IUnknown **ppUnk );  //Kim,Yongshik
      STDMETHOD( TranslateAccelerator )( MSG *pMsg );  //Kim,Yongshik
	END_INTERFACE_PART( PropertyPageSite )  //Kim,Yongshik
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELPATTERNFRAMEDIALOG_H__2193A361_ED74_11D4_9E85_0000E8C3064A__INCLUDED_)
