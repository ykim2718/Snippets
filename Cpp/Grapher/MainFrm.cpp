// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Grapher.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_COMMAND(IDM_CLOSE_ALL_WINDOWS, OnCloseAllWindows)
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_WM_INITMENUPOPUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_EXT,       // shik96,2000.1030
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

   // 2001.0426
   if (!m_wndGrapherBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndGrapherBar.LoadToolBar(IDR_GRAPHER))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
   m_wndGrapherBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndGrapherBar);
   ShowControlBar(&m_wndGrapherBar,FALSE,FALSE);
   //RecalcLayout();
   
   //shik,2000.0512
   CWinApp *pApp=AfxGetApp();
   CRect Rect;
   Rect.left=pApp->GetProfileInt(RegKeySettings,RegKeyFrameLeft,0);
   Rect.top=pApp->GetProfileInt(RegKeySettings,RegKeyFrameTop,0);
   Rect.right=pApp->GetProfileInt(RegKeySettings,RegKeyFrameRight,0);
   Rect.bottom=pApp->GetProfileInt(RegKeySettings,RegKeyFrameBottom,0);
   if (Rect.Width()>10 && Rect.Height()>10) //shik96,2001.0518
      MoveWindow(Rect);
   //shik,2000.1030
   UINT nID,nStyle;
   int cxWidth;
   m_wndStatusBar.GetPaneInfo(1,nID,nStyle,cxWidth);
   CString sText;
   sText.Format(
      "%d",
      pApp->GetProfileInt(RegKeySettings,RegKeyExecCount,0)
      );
   m_wndStatusBar.SetPaneInfo(1,nID,SBPS_NORMAL,7*sText.GetLength());
   m_wndStatusBar.SetPaneText(1,sText);
   //

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

   if (m_bZoomed) // shik,2001.0207
      return CMDIFrameWnd::DestroyWindow();

   
	//shik,2000.0512
	CRect Rect;
   GetWindowRect(Rect);

   //Y.Kim,20031002
   if (Rect.right>10000||Rect.bottom>10000)
      return CMDIFrameWnd::DestroyWindow();

   CWinApp *pApp=AfxGetApp();
   pApp->WriteProfileInt(RegKeySettings,RegKeyFrameLeft,Rect.left);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFrameTop,Rect.top);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFrameRight,Rect.right);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFrameBottom,Rect.bottom);

   //
	return CMDIFrameWnd::DestroyWindow();
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

   // shik96,2001.0110 + 0303
   CMDIChildWnd *pFrame;
   CPtrArray Array;
   int nIndex;
   while (pFrame=(CMDIChildWnd*)MDIGetActive()) {
      for (nIndex=0;nIndex<Array.GetSize();nIndex++) {
         if (Array.GetAt(nIndex)==pFrame) return;
      }
      Array.Add(pFrame);
      ::SendMessage(pFrame->m_hWnd,WM_CLOSE,0,0);
      MDINext();
   }
	
	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

   m_bZoomed=IsZoomed();
}

void CMainFrame::OnCloseAllWindows() 
{
	// TODO: Add your command handler code here
	
   /* 2001.0215
   CMDIChildWnd *pChildFrame;
   while (pChildFrame=(CMDIChildWnd*)this->GetActiveFrame()) {
      if ((CFrameWnd*)pChildFrame==(CFrameWnd*)this) break;
      pChildFrame->MDIDestroy();
   }
   */
   AfxGetApp()->CloseAllDocuments(FALSE);
}

HMENU CMainFrame::NewMenu()
{
   static UINT qToolBars[]={
      IDR_MAINFRAME,
      IDR_GRAPHER
   };
   int nToolBars=sizeof(qToolBars)/sizeof(qToolBars[0]);

   // Load the menu from the resources
   m_Menu.LoadMenu(IDR_CHILDFRAME);

   // Use ModifyODMenu to add a bitmap to a menu options.The first parameter
   // is the menu option text string.If it's NULL, keep the current text
   // string.The second option is the ID of the menu option, or the menu
   // option text (use this for adding bitmaps to popup options) to change.
   // The third option is the resource ID of the bitmap.This can also be a
   // toolbar ID in which case the class searches the toolbar for the
   // appropriate bitmap.Only Bitmap and Toolbar resources are supported.
   /*
   m_Menu.ModifyODMenu(NULL,ID_WINDOW_TILE_HORZ,IDB_WINDOW_TILE);
   m_Menu.ModifyODMenu(NULL,_T("&Rocscience on the Web"),IDB_NET);
   */

   // Instead of a resource you can use a CImageList object with ModifyODMenu
   CImageList ImageList;
   ImageList.Create(16,15,ILC_COLORDDB|ILC_MASK,1,1);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_FILE_OPEN);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_CLEAR);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_ARROW_LEFT);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_ARROW_RIGHT);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_GR_PROPERTYSHEET);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_GR_MIXER);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_GR_RENOVATOR);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_GR_SCRIPT);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_GR_LOG);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_GARGAMEL);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_SMURFETTE);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_PREFERENCE);
   m_Menu.AddBitmapToImageList(&ImageList,IDB_PALLETE);
   m_Menu.ModifyODMenu(NULL,ID_FILE_OPEN_,&ImageList,0);
   m_Menu.ModifyODMenu(NULL,IDM_CLEAR,&ImageList,1);
   m_Menu.ModifyODMenu(NULL,IDM_VIEW_LEFT,&ImageList,2);
   m_Menu.ModifyODMenu(NULL,IDM_VIEW_RIGHT,&ImageList,3);
   m_Menu.ModifyODMenu(NULL,IDM_GR_PLOT_PAGE,&ImageList,4);
   m_Menu.ModifyODMenu(NULL,IDM_GR_MIXER,&ImageList,5);
   m_Menu.ModifyODMenu(NULL,IDM_GR_RENOVATOR,&ImageList,6);
   m_Menu.ModifyODMenu(NULL,IDM_VIEW_SCRIPT,&ImageList,7);
   m_Menu.ModifyODMenu(NULL,IDM_VIEW_LOG,&ImageList,8);
   m_Menu.ModifyODMenu(NULL,IDM_GARGAMEL,&ImageList,9);
   m_Menu.ModifyODMenu(NULL,IDM_SMURFETTE,&ImageList,10);
   m_Menu.ModifyODMenu(NULL,IDM_PREFERENCE,&ImageList,11);
   m_Menu.ModifyODMenu(NULL,IDM_PALLETE,&ImageList,12);

   // Another method for adding bitmaps to menu options is through the
   // LoadToolbars member function.This method allows you to add all
   // the bitmaps in a toolbar object to menu options (if they exist).
   // The first function parameter is an array of toolbar id's.
   // The second is the number of toolbar id's. There is also a
   // function called LoadToolbar that just takes an id.
   m_Menu.LoadToolbars(qToolBars,nToolBars);

   return(m_Menu.Detach());
}

HMENU CMainFrame::NewMenuDefault()
{
   m_MenuDefault.LoadMenu(IDR_MAINFRAME);
   m_MenuDefault.LoadToolbar(IDR_MAINFRAME);

   /* I have no idea why this does not work only in the Release mode.2001.0326
   CImageList ImageList;
   ImageList.Create(16,15,ILC_COLORDDB|ILC_MASK,1,1);
   m_MenuDefault.AddBitmapToImageList(&ImageList,IDB_PREFERENCE);
   m_MenuDefault.AddBitmapToImageList(&ImageList,IDB_GARGAMEL);
   m_MenuDefault.AddBitmapToImageList(&ImageList,IDB_PALLETE);
   m_MenuDefault.ModifyODMenu(NULL,IDM_PREFERENCE,&ImageList,0);
   m_MenuDefault.ModifyODMenu(NULL,IDM_GARGAMEL,&ImageList,1);
   m_MenuDefault.ModifyODMenu(NULL,IDM_PALLETE,&ImageList,2);
   */
#ifdef _DEBUG
   m_MenuDefault.ModifyODMenu(NULL,IDM_PREFERENCE,IDB_PREFERENCE);
   m_MenuDefault.ModifyODMenu(NULL,IDM_GARGAMEL,IDB_GARGAMEL);
#endif
   m_MenuDefault.ModifyODMenu(NULL,IDM_PALLETE,IDB_PALLETE);
   

   return (m_MenuDefault.Detach());
}

void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
   /*
	// TODO: Add your message handler code here and/or call default

   CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
	*/

   BOOL bSetFlag=FALSE;
   if (lpMeasureItemStruct->CtlType==ODT_MENU) {
      if (IsMenu((HMENU)lpMeasureItemStruct->itemID)) {
         CMenu* pMenu=CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
         if (m_Menu.IsMenu(pMenu)||m_MenuDefault.IsMenu(pMenu)) {
            m_Menu.MeasureItem(lpMeasureItemStruct);
            bSetFlag=TRUE;
         }
      }
   }
   if (!bSetFlag) CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
   /*
	// TODO: Add your message handler code here and/or call default
	
	return CMDIFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
   */

   LRESULT lresult;
   if (m_Menu.IsMenu(pMenu)||m_MenuDefault.IsMenu(pMenu))
      lresult=BCMenu::FindKeyboardShortcut(nChar,nFlags,pMenu);
   else
      lresult=CMDIFrameWnd::OnMenuChar(nChar,nFlags,pMenu);
   return (lresult);
}

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// TODO: Add your message handler code here

   if (!bSysMenu) {
      if (m_Menu.IsMenu(pPopupMenu)||m_MenuDefault.IsMenu(pPopupMenu))
         BCMenu::UpdateMenu(pPopupMenu);
   }	
}

