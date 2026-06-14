//{{AFX_INCLUDES()
#include "gargamelpatternformatrixocx.h"
//}}AFX_INCLUDES
#if !defined(AFX_GARGAMELPATTERNFORMATRIXFRAMEDIALOG_H__0C860CB5_7D34_4CFB_995E_B4B0FCD0F7A4__INCLUDED_)
#define AFX_GARGAMELPATTERNFORMATRIXFRAMEDIALOG_H__0C860CB5_7D34_4CFB_995E_B4B0FCD0F7A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GargamelPatternForMatrixFrameDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixFrameDialog dialog

class CGargamelPatternForMatrixFrameDialog : public CDialog
{
// Construction
public:
	void GetScript(CString &sReturn);
	void SetScript(const CString &sForwarding);
	void OnGargamelUpdateData(WPARAM wParam, LPARAM lParam);
	CGargamelPatternForMatrixFrameDialog(CWnd* pParent = NULL);   // standard constructor
   CString m_sStream;

// Dialog Data
	//{{AFX_DATA(CGargamelPatternForMatrixFrameDialog)
	enum { IDD = IDD_GARGAMEL_PATTERNFORMATRIX };
	CGargamelPatternForMatrixOcx	m_GargamelPatternForMatrixOcx;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGargamelPatternForMatrixFrameDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGargamelPatternForMatrixFrameDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARGAMELPATTERNFORMATRIXFRAMEDIALOG_H__0C860CB5_7D34_4CFB_995E_B4B0FCD0F7A4__INCLUDED_)
