// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Grapher.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "MainFrm.h" // 2001.0426
#include "GrapherDoc.h"
#include "GrapherView.h"

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	;
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
   CGrapherView *pView=(CGrapherView*)GetActiveView();
   if (!pView->OnFileSaveOnDestroy()) return;
	CMDIChildWnd::OnClose();
}

void CChildFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CMDIChildWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here

   // 2001.0426
   CMainFrame *pFrame=(CMainFrame*)GetMDIFrame();
   CDocument *pDoc=this->GetActiveDocument();
   CDocTemplate* pDocTemplate=pDoc->GetDocTemplate();
   POSITION xPosition=pDocTemplate->GetFirstDocPosition();
   int nCount=0;
   while (xPosition &&(pDoc=pDocTemplate->GetNextDoc(xPosition))) nCount++;
   if (nCount>1) return;
   pFrame->ShowControlBar(&(pFrame->m_wndGrapherBar),bShow,FALSE);
   pFrame->ShowControlBar(&(pFrame->m_wndToolBar),!bShow,FALSE);
   /*
   CMDIFrameWnd *pFrame=GetMDIFrame();
   CControlBar *pBar=pFrame->GetControlBar(IDR_MAINFRAME);
   pFrame->ShowControlBar(pBar,bShow,FALSE);
   pBar=pFrame->GetControlBar(IDR_GRAPHER);
   pFrame->ShowControlBar(pBar,!bShow,FALSE);
   */
}

