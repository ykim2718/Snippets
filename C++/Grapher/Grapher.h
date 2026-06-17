// Grapher.h : main header file for the Grapher application
//

#if !defined(AFX_Grapher_H__236879A5_E21F_11D4_9E85_0000E8C3064A__INCLUDED_)
#define AFX_Grapher_H__236879A5_E21F_11D4_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include <afxcmn.h>
#include <afxdlgs.h>
#include <afxext.h>

#include "plot.h" //20030222
#include "GrPlotWizard.h"

#define RegKeyRecentFileList         "Recent File List"
#define RegKeyRecentFile1            "File1"

#define RegKeySettings               "Settings"
#define RegKeyVersion                "sVersion"
#define RegKeyExecCount              "nExecCount"
#define RegKeyProcessID              "nProcessID"
#define RegKeyFileDirectory          "sFileDirectory"
#define RegKeyHomeDirectory          "sHomeDirectory"
#define RegKeyGargamelFile           "sGargamelFile"
#define RegKeySmurfetteFile          "sSmurfettePath"
#define RegKeyExampleFolder          "sExampleFolder"
#define RegKeyFrameLeft              "nFrameLeft"
#define RegKeyFrameTop               "nFrameTop"
#define RegKeyFrameRight             "nFrameRight"
#define RegKeyFrameBottom            "nFrameBottom"
#define RegKeyPageLandscape          "bPageLandscape"
#define RegKeyDbiViewer              "sDbiViewer"
#define RegKeyTextViewer             "sTextViewer"
#define RegKeyPlotWizardPatternFile0 "sPlotWizardPatternFile0"
#define RegKeyPlotWizardPatternFile1 "sPlotWizardPatternFile1"
#define RegKeyPlotWizardPatternFile2 "sPlotWizardPatternFile2"
#define RegKeyPlotWizardPatternFile3 "sPlotWizardPatternFile3"
#define RegKeyPlotWizardPatternFile4 "sPlotWizardPatternFile4"
#define RegKeyPlotWizardPatternFile5 "sPlotWizardPatternFile5"
#define RegKeyPlotWizardPatternFile6 "sPlotWizardPatternFile6"
#define RegKeyPlotWizardPatternFile7 "sPlotWizardPatternFile7"
#define RegKeyPlotWizardPatternFile8 "sPlotWizardPatternFile8"
#define RegKeyPlotWizardPatternFile9 "sPlotWizardPatternFile9"
#define RegKeyPlotWizardSplitFile0   "sPlotWizardSplitFile0"
#define RegKeyPlotWizardSplitFile1   "sPlotWizardSplitFile1"
#define RegKeyPlotWizardSplitFile2   "sPlotWizardSplitFile2"
#define RegKeyPlotWizardSplitFile3   "sPlotWizardSplitFile3"
#define RegKeyPlotWizardSplitFile4   "sPlotWizardSplitFile4"
#define RegKeyPlotWizardSplitFile5   "sPlotWizardSplitFile5"
#define RegKeyPlotWizardSplitFile6   "sPlotWizardSplitFile6"
#define RegKeyPlotWizardSplitFile7   "sPlotWizardSplitFile7"
#define RegKeyPlotWizardSplitFile8   "sPlotWizardSplitFile8"
#define RegKeyPlotWizardSplitFile9   "sPlotWizardSplitFile9"
#define RegKeyPlotWizardMapFile      "sPlotWizardMapFile"

#define RegKeyGrAttributes           "Attributes"
#define RegKeyDefaultSymbolFormat    "sDefaultSymbolScript%02d"

/////////////////////////////////////////////////////////////////////////////
// CGrapherApp:
// See Grapher.cpp for the implementation of this class
//

class CGrapherApp : public CWinApp
{
public:   
	CGrPlotWizard *m_PlotWizardDialogModeless;
	void OnSample( UINT nID );
	CString GetPathOfHome();
	CString GetPathOfGargamel();
	CString GetPathOfSmurfette();
	BOOL IsAnotherExecutingAlready();
	void SetPageOrientation(BOOL isLandscape);
	CGrapherApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrapherApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGrapherApp)
	afx_msg void OnAppAbout();
	afx_msg void OnPallete();
	afx_msg void OnPreference();
	afx_msg void OnUpdateFileSaveas(CCmdUI* pCmdUI);
	afx_msg void OnGargamel();
	afx_msg void OnBrainy();
	afx_msg void OnSmurfette();
	afx_msg void OnGrplotWizardThruGargamel();
	afx_msg void OnGrMixder();
	afx_msg void OnFileOpen();
	afx_msg void OnHistory();
	afx_msg void OnGrRenovator();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Grapher_H__236879A5_E21F_11D4_9E85_0000E8C3064A__INCLUDED_)
