// GrapherView.h : interface of the CGrapherView class
//
/////////////////////////////////////////////////////////////////////////////
// shik96@samung.co.kr

#include "blob.h"
#include "ZoomView.h"
#include "GrLogDialog.h"
#include "BCMenu.h"

/////////////////////////////////////////////////////////////////////////////

class CGrapherView : public CZoomView
{
protected: // create from serialization only
	CGrapherView();
	DECLARE_DYNCREATE(CGrapherView)

// Attributes
public:
	CGrapherDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrapherView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetGrFileName();
	CString GetGrFolder();
	void AddFileStatusOfGargamelFiles();
	void DeleteTemporaryFilesOnDisk();
	void AddFileStatusOfTemporaryFiles(CString sTemporaryFiles);
	BCMenu m_PopUpMenu;
   void OnFileOpenByAlien() { OnFileOpen(); }
	BOOL OnFileSaveOnDestroy();
	BOOL m_bGrScriptModified;
	BOOL LoadGrFile( const char *qFile );
	void OnGrPropertyPage(int nID);
   friend int mySetFrameWindowText( const char *string );
   CFont *m_pFont;
   int m_nWinScaleType;
   int m_nEvent,m_nEventX,m_nEventY,m_nEventWidth,m_nEventHeight;
	double m_dEventFactor;
	BOOL m_bLandscape;
	void OnExecGr();
   enum {GR_EMPTY,GR_FAILED,GR_ENROLLED} m_nGrPlotStatus;
	BLOBLIST *m_pGrBlobList;
   CFileStatus m_FileStatus;
   CPtrArray m_FileStatusOfGargamelFiles;
   CPtrArray m_FileStatusOfTemporaryFiles;
   CString m_sGrLog;
   CString m_sGrScript;
   CString m_sGrFile;
	virtual ~CGrapherView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	CGrLogDialog *m_LogDialogModeless;
	//{{AFX_MSG(CGrapherView)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnViewLeft();
	afx_msg void OnViewDown();
	afx_msg void OnViewRight();
	afx_msg void OnViewUp();
	afx_msg void OnViewTranslate();
	afx_msg void OnRedraw();
	afx_msg void OnFitToObject();
	afx_msg void OnFitToCanvas();
	afx_msg void OnUpdateFitToObject(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFitToCanvas(CCmdUI* pCmdUI);
	afx_msg void OnViewCanvasA4h();
	afx_msg void OnUpdateViewCanvasA4h(CCmdUI* pCmdUI);
	afx_msg void OnViewCanvasA4v();
	afx_msg void OnUpdateViewCanvasA4v(CCmdUI* pCmdUI);
	afx_msg void OnWindowsFont();
	afx_msg void OnViewZoomIn();
	afx_msg void OnViewZoomOut();
	afx_msg void OnViewFull();
	afx_msg void OnUpdateViewZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnViewHand();
	afx_msg void OnUpdateViewHand(CCmdUI* pCmdUI);
	afx_msg void OnViewMag25();
	afx_msg void OnUpdateViewMag25(CCmdUI* pCmdUI);
	afx_msg void OnViewMag50();
	afx_msg void OnUpdateViewMag50(CCmdUI* pCmdUI);
	afx_msg void OnViewMag100();
	afx_msg void OnUpdateViewMag100(CCmdUI* pCmdUI);
	afx_msg void OnViewMag200();
	afx_msg void OnUpdateViewMag200(CCmdUI* pCmdUI);
	afx_msg void OnViewMag400();
	afx_msg void OnUpdateViewMag400(CCmdUI* pCmdUI);
	afx_msg void OnViewMag75();
	afx_msg void OnUpdateViewMag75(CCmdUI* pCmdUI);
	afx_msg void OnViewMag125();
	afx_msg void OnUpdateViewMag125(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveasEmf();
	afx_msg void OnFileSaveasHpglf();
	afx_msg void OnFileSaveasPsf();
	afx_msg void OnFileSaveasWmf();
	afx_msg void OnUpdateFileSaveasEmf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveasHpglf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveasPsf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveasWmf(CCmdUI* pCmdUI);
	afx_msg void OnViewLog();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnGrPlotDefaultsymbol();
	afx_msg void OnViewScript();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnHomemadeFont();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnViewZoomOff();
	afx_msg void OnUpdateViewZoomOff(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char *m_pGrForPrint;
};

#ifndef _DEBUG  // debug version in GrapherView.cpp
inline CGrapherDoc* CGrapherView::GetDocument()
   { return (CGrapherDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
