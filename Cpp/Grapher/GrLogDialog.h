#if !defined(AFX_SCRIPTDIALOG_H__B90CCE62_FAC2_11D3_AA81_CAE7D57E1250__INCLUDED_)
#define AFX_SCRIPTDIALOG_H__B90CCE62_FAC2_11D3_AA81_CAE7D57E1250__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrLogDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrLogDialog dialog

class CGrLogDialog : public CDialog
{

//shik(
public:
   virtual BOOL Create() { return CDialog::Create(CGrLogDialog::IDD,NULL); }
   virtual void PostNcDestroy() { delete this; };
   void SetStream(const char *stream) {
      m_sLog=stream;
      m_sLog.Replace("\r\n","\n");
      m_sLog.Replace("\n","\r\n");
      UpdateData(FALSE);
   }
protected:
private:
//shik)

// Construction
public:
	CBitmap m_bmpGripper;
	int m_nHeight;
	int m_nWidth;
	CGrLogDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrLogDialog)
	enum { IDD = IDD_GR_LOG };
	CStatic	m_Gripper;
	CString	m_sLog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrLogDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_MyFont;

	// Generated message map functions
	//{{AFX_MSG(CGrLogDialog)
	afx_msg void OnScriptDialogSaveas();
	afx_msg void OnScriptDialogClear();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnScriptDialogPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTDIALOG_H__B90CCE62_FAC2_11D3_AA81_CAE7D57E1250__INCLUDED_)
