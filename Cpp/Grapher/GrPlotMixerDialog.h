#if !defined(AFX_GRPLOTMIXERDIALOG_H__A49DD981_FD7B_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_GRPLOTMIXERDIALOG_H__A49DD981_FD7B_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrPlotMixerDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "Options.h"
#include "OptionsTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CGrPlotMixerDialog dialog

class CGrPlotMixerDialog : public CDialog
{
// Construction
public:
	const char * GetScriptBelongsToAView( const CString &qName );
	COptions m_Options;
	CGrPlotMixerDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrPlotMixerDialog)
	enum { IDD = IDD_GR_PLOT_MIXER };
	COptionsTreeCtrl	m_OptionsTreeCtrl;
	BOOL	m_bRelayout;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrPlotMixerDialog)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrPlotMixerDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPLOTMIXERDIALOG_H__A49DD981_FD7B_11D4_9E85_0000E8C3064A__INCLUDED_)
