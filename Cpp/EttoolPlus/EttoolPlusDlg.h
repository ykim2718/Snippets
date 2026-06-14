// EttoolPlusDlg.h : header file
//

#if !defined(AFX_ETTOOLPLUSDLG_H__50051FC6_F950_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_ETTOOLPLUSDLG_H__50051FC6_F950_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "../DialogAggregate/DialogAggregate.h"
#include "EttoolAmbienceDlg.h"
#include "GargamelSplitFrameDialog.h"
#include "Token.h"

/////////////////////////////////////////////////////////////////////////////
// CEttoolPlusDlg dialog

class CEttoolPlusDlg : public CDialog
{
// Construction
public:
	void Run(const char *qEttoolPath,const char*qScriptPath);
   void OnChildStdOutWrite(LPCSTR lpszBuffer) {
      m_sStdout+=lpszBuffer;
      //UpdateData(FALSE);
      //CEdit *pEdit=(CEdit*)GetDlgItem(ID_STDOUT);
      //pEdit->SetWindowText(m_sStdout);
   }
	void SetGroupNamesInTheOtherScript(const char* pFile);
	BOOL DoesFileExist(const char *pFile);
   IFileFolderTreeSelectionDialog* m_pFileFolderTreeSelectionDialog;
   ~CEttoolPlusDlg();
	CEttoolPlusDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEttoolPlusDlg)
	enum { IDD = IDD_ETTOOLPLUS_DIALOG };
	CListBox	m_SplitListBox;
	BOOL	m_bFormatDat;
	BOOL	m_bFormatDat2;
	BOOL	m_bFormatLog;
	BOOL	m_bFormatLot;
	BOOL	m_bFormatLot2;
	BOOL	m_bFormatMap;
	BOOL	m_bFormatMap2;
	BOOL	m_bFormatPlt;
	BOOL	m_bFormatRpt;
	CString	m_sScriptFolder;
	CString	m_sAggregation;
	CString	m_sInputFolder;
	CString	m_sOutputFolder;
	CString	m_sInputFolderFileFilter;
	CString	m_sNumberFormat;
	BOOL	m_bFormatSum;
	CString	m_sStdout;
	BOOL	m_bFormatCvs;
	BOOL	m_bFormatLot3;
	BOOL	m_bFormatLot4;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEttoolPlusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEttoolPlusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEnvironment();
	afx_msg void OnExecute();
	afx_msg void OnScriptBrowser();
	afx_msg void OnInputfolderBrowser();
	afx_msg void OnOutputfolderBrowser();
	afx_msg void OnScriptEdit();
	virtual void OnCancel();
	afx_msg void OnSplitWizard();
	afx_msg void OnEditchangeNumberFormat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETTOOLPLUSDLG_H__50051FC6_F950_11D4_9E85_0000E8C3064A__INCLUDED_)
