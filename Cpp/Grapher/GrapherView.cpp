// GrapherView.cpp : implementation of the CGrapherView class
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "afxpriv.h"    // For WM_SETMESSAGESTRING

#include "Grapher.h"
#include "GrapherDoc.h"
#include "GrapherView.h"
#include "GrLogDialog.h"
#include "GrPropertySheet.h"
#include "GrDefaultSymbolDialog.h"
#include "GrPathEnvironmentDialog.h"
#include "GrPlotWizard.h"
#include "Token.h"
#include "FileDialogEx.h"

#include "plot.h"
#include "plotse.h"
#include "myGR.h"
#include "tools.h"

extern CGrapherApp theApp;

int mySetFrameWindowText( const char *string )
{
   CWnd *pWnd=((CWinApp*)AfxGetApp())->m_pMainWnd;
   pWnd->SendMessage(WM_SETMESSAGESTRING,0,(LPARAM)(LPCSTR)string);
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGrapherView

IMPLEMENT_DYNCREATE(CGrapherView, CZoomView)

BEGIN_MESSAGE_MAP(CGrapherView, CZoomView)
	//{{AFX_MSG_MAP(CGrapherView)   
	ON_COMMAND(ID_FILE_OPEN_, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS_, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_, OnUpdateFileSaveAs)
	ON_COMMAND(IDM_VIEW_LEFT, OnViewLeft)
	ON_COMMAND(IDM_VIEW_DOWN, OnViewDown)
	ON_COMMAND(IDM_VIEW_RIGHT, OnViewRight)
	ON_COMMAND(IDM_VIEW_UP, OnViewUp)
	ON_COMMAND(IDM_VIEW_TRANSLATE, OnViewTranslate)
   ON_COMMAND(IDM_VIEW_REDRAW, OnRedraw)
	ON_COMMAND(IDM_FIT_TO_OBJECT, OnFitToObject)
	ON_COMMAND(IDM_FIT_TO_CANVAS, OnFitToCanvas)
	ON_UPDATE_COMMAND_UI(IDM_FIT_TO_OBJECT, OnUpdateFitToObject)
	ON_UPDATE_COMMAND_UI(IDM_FIT_TO_CANVAS, OnUpdateFitToCanvas)
	ON_COMMAND(IDM_VIEW_CANVAS_A4H, OnViewCanvasA4h)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_CANVAS_A4H, OnUpdateViewCanvasA4h)
	ON_COMMAND(IDM_VIEW_CANVAS_A4V, OnViewCanvasA4v)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_CANVAS_A4V, OnUpdateViewCanvasA4v)
	ON_COMMAND(IDM_WINDOWSFONT, OnWindowsFont)
	ON_COMMAND(IDM_VIEW_ZOOM_IN, OnViewZoomIn)
	ON_COMMAND(IDM_VIEW_ZOOM_OUT, OnViewZoomOut)
	ON_COMMAND(IDM_VIEW_FULL, OnViewFull)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_ZOOM_IN, OnUpdateViewZoomIn)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_ZOOM_OUT, OnUpdateViewZoomOut)
	ON_COMMAND(IDM_VIEW_HAND, OnViewHand)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_HAND, OnUpdateViewHand)
	ON_COMMAND(IDM_VIEW_MAG_25, OnViewMag25)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MAG_25, OnUpdateViewMag25)
	ON_COMMAND(IDM_VIEW_MAG_50, OnViewMag50)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MAG_50, OnUpdateViewMag50)
	ON_COMMAND(IDM_VIEW_MAG_100, OnViewMag100)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MAG_100, OnUpdateViewMag100)
	ON_COMMAND(IDM_VIEW_MAG_200, OnViewMag200)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MAG_200, OnUpdateViewMag200)
	ON_COMMAND(IDM_VIEW_MAG_400, OnViewMag400)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MAG_400, OnUpdateViewMag400)
	ON_COMMAND(IDM_VIEW_MAG_75, OnViewMag75)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MAG_75, OnUpdateViewMag75)
	ON_COMMAND(IDM_VIEW_MAG_125, OnViewMag125)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MAG_125, OnUpdateViewMag125)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_COMMAND(IDM_FILE_SAVEAS_EMF, OnFileSaveasEmf)
	ON_COMMAND(IDM_FILE_SAVEAS_HPGLF, OnFileSaveasHpglf)
	ON_COMMAND(IDM_FILE_SAVEAS_PSF, OnFileSaveasPsf)
	ON_COMMAND(IDM_FILE_SAVEAS_WMF, OnFileSaveasWmf)
	ON_UPDATE_COMMAND_UI(IDM_FILE_SAVEAS_EMF, OnUpdateFileSaveasEmf)
	ON_UPDATE_COMMAND_UI(IDM_FILE_SAVEAS_HPGLF, OnUpdateFileSaveasHpglf)
	ON_UPDATE_COMMAND_UI(IDM_FILE_SAVEAS_PSF, OnUpdateFileSaveasPsf)
	ON_UPDATE_COMMAND_UI(IDM_FILE_SAVEAS_WMF, OnUpdateFileSaveasWmf)
	ON_COMMAND(IDM_VIEW_LOG, OnViewLog)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(IDM_GR_PLOT_DEFAULTSYMBOL, OnGrPlotDefaultsymbol)
	ON_COMMAND(IDM_VIEW_SCRIPT, OnViewScript)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_FILE_SAVE_, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_, OnUpdateFileSave)
	ON_COMMAND(IDM_HOMEMADEFONT, OnHomemadeFont)
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_COMMAND(IDM_VIEW_ZOOM_OFF, OnViewZoomOff)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_ZOOM_OFF, OnUpdateViewZoomOff)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(IDM_EXEC_GR, OnExecGr)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
   ON_COMMAND_RANGE(IDM_GR_PLOT_PAGE,IDM_GR_GLOB_PAGE,OnGrPropertyPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrapherView construction/destruction

CGrapherView::CGrapherView() :
m_bLandscape(FALSE),
m_bGrScriptModified(FALSE)
{
	// TODO: add construction code here

   m_sGrFile.Empty();
   m_sGrScript.Empty();
   m_sGrLog.Empty();
   m_pGrBlobList=NULL;

   m_nGrPlotStatus=GR_EMPTY;
   m_nWinScaleType='f';
   m_nEvent='r';
   m_nEventX=m_nEventY=m_nEventWidth=m_nEventHeight=0;
   m_dEventFactor=1.0;
   m_LogDialogModeless=0; // modeless dialog

   myGROpen();
   myGRSetEchoFunction(mySetFrameWindowText);

   memset(&m_FileStatus,0,sizeof(CFileStatus));
   //LockFile();
   //UnlockFile();
   m_FileStatusOfGargamelFiles.RemoveAll();
   m_FileStatusOfTemporaryFiles.RemoveAll();

   CWinApp* pApp=AfxGetApp();
   m_bLandscape=pApp->GetProfileInt(RegKeySettings,RegKeyPageLandscape,1);

   m_pFont=NULL;
   m_pGrForPrint=NULL;
}

CGrapherView::~CGrapherView()
{
   myGRFreeBlob(m_pGrBlobList);
   myGRClose();

   CGrapherView::DeleteTemporaryFilesOnDisk();

   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileInt(
      RegKeySettings,RegKeyPageLandscape,m_bLandscape?TRUE:FALSE);
   if (!m_sGrFile.IsEmpty())
   pApp->WriteProfileString(RegKeyRecentFileList,RegKeyRecentFile1,m_sGrFile);

   if (m_pFont) delete m_pFont; //20030529
}

/////////////////////////////////////////////////////////////////////////////
// CGrapherView drawing

void CGrapherView::OnInitialUpdate() 
{   
	CZoomView::OnInitialUpdate(); //shik96
   switch (m_bLandscape) {
   case TRUE: SetZoomSizes(ZP_A4H);break;
   case FALSE: SetZoomSizes(ZP_A4);break;
   }
   theApp.SetPageOrientation(m_bLandscape);
   DoZoomFull();

   int height = 18;
	m_pFont = new CFont();
   m_pFont->CreateFont(height,0,0,0,
         FW_NORMAL,FALSE,FALSE,
         FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
         DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, "Arial");

   CDocument *pDoc=GetDocument();
   m_sGrFile=pDoc->GetPathName();

   LoadGrFile(m_sGrFile);
}

void CGrapherView::OnDraw(CDC* pDC)
{
	CGrapherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here  

   HWND hWnd;

   // Draw Border
   CSize Size;
   GetPageSizeOfLogicalCoordinate(Size);
   CRect Rect(1,1,Size.cx-1,Size.cy-1);
   if (!pDC->IsPrinting()) {
      pDC->Rectangle(&Rect);
      Rect.InflateRect(-1,-1,1,1);
      pDC->DrawEdge(&Rect,BDR_RAISEDOUTER,BF_BOTTOMRIGHT);
      hWnd=m_hWnd;
   } else {
      hWnd=0;
   }

   hWnd=0; // What does this mean? 20030217

   GERECT geRect;
   geRect.x=1;
   geRect.y=1;
   geRect.width=Rect.Width();
   geRect.height=Rect.Height();
   geRect.borderWidth=0;
   switch (m_nGrPlotStatus) {
   case GR_EMPTY :
      if (m_sGrScript.IsEmpty()) break;
      //SetCurrentDirectory(GetGrFolder());//20030529 for safety
      AddFileStatusOfGargamelFiles();
      myGRExecuteSilently(m_sGrFile,m_sGrScript,&m_pGrBlobList);
      m_sGrLog=myGRLogPointer(); //20030902
      if (!m_pGrBlobList) {
         // m_sGrScript.Empty(); 20030220
         CString sMsg=myGRErrorLogPointer();
         MessageBox(sMsg,"Grapher error message ...",MB_ICONWARNING);
         m_nGrPlotStatus=GR_FAILED;
         break;
      }
      myGRRefresh(
         m_pGrBlobList,(char*)hWnd,(char*)pDC->m_hDC,&geRect,
         GetZoomPageDpiFactor(),
         m_nWinScaleType,m_nEventX,m_nEventY,m_dEventFactor,
         TRUE,NULL);
      m_nGrPlotStatus=GR_ENROLLED;
      AddFileStatusOfTemporaryFiles(myGRTemporaryFilesPointer());
      if (m_LogDialogModeless) m_LogDialogModeless->SetStream(m_sGrLog);
      break;
   case GR_FAILED : // 20030308
      break;
   case GR_ENROLLED :
      myGRRefresh(
         m_pGrBlobList,(char*)hWnd,(char*)pDC->m_hDC,&geRect,
         GetZoomPageDpiFactor(),
         m_nWinScaleType,m_nEventX,m_nEventY,m_dEventFactor,
         !pDC->IsPrinting(),&m_pGrForPrint);
      break;
   }
}

/////////////////////////////////////////////////////////////////////////////
// CGrapherView printing

BOOL CGrapherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGrapherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing

   //Y.Kim,20030217
   m_pGrForPrint=NULL;
}

void CGrapherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing

   //Y.Kim,20030217
   myGRGEClose(m_pGrForPrint);
   m_pGrForPrint=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CGrapherView diagnostics

#ifdef _DEBUG
void CGrapherView::AssertValid() const
{
	//CScrollView::AssertValid();
   CZoomView::AssertValid(); //shik96
}

void CGrapherView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGrapherDoc* CGrapherView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrapherDoc)));
	return (CGrapherDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGrapherView message handlers

void CGrapherView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here

   /*
	CMenu Menu;
   Menu.LoadMenu(IDR_GRSCRIPTER);
   CMenu *pContext=Menu.GetSubMenu(0);
   pContext->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
      point.x,point.y,AfxGetMainWnd());
   */

  m_PopUpMenu.LoadMenu(IDR_GRSCRIPTER);
  m_PopUpMenu.LoadToolbar(IDR_MAINFRAME);

  m_PopUpMenu.ModifyODMenu(NULL,IDM_VIEW_LOG,IDB_GR_LOG);
  m_PopUpMenu.ModifyODMenu(NULL,IDM_GR_PLOT_PAGE,IDB_GR_PROPERTYSHEET);
  m_PopUpMenu.ModifyODMenu(NULL,IDM_GR_MIXER,IDB_GR_MIXER);
  m_PopUpMenu.ModifyODMenu(NULL,IDM_GR_RENOVATOR,IDB_GR_RENOVATOR);
  
  //ClientToScreen(&point);
  BCMenu *pSub = (BCMenu *)m_PopUpMenu.GetSubMenu(0);
  //pSub->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
  pSub->TrackPopupMenu(
     TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
     point.x,point.y,AfxGetMainWnd());
  m_PopUpMenu.DestroyMenu();
}

void CGrapherView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

   BOOL bSetFlag=FALSE;
   if(lpMeasureItemStruct->CtlType==ODT_MENU){
      if(IsMenu((HMENU)lpMeasureItemStruct->itemID) &&
         BCMenu::IsMenu((HMENU)lpMeasureItemStruct->itemID)){
         m_PopUpMenu.MeasureItem(lpMeasureItemStruct);
         bSetFlag=TRUE;
      }
   }
	if(!bSetFlag)CZoomView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
	
	//CZoomView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

LRESULT CGrapherView::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	// TODO: Add your message handler code here and/or call default

  LRESULT lResult;
  if (BCMenu::IsMenu(pMenu))
     lResult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
  else
     lResult=CView::OnMenuChar(nChar, nFlags, pMenu);
  return(lResult);
  
	//return CZoomView::OnMenuChar(nChar, nFlags, pMenu);
}

void CGrapherView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

   POINT Pt;
   Pt.x=point.x;
   Pt.y=point.y;
   CZoomView::ViewDPtoLP(&Pt);
   CString message;
   message.Format("x=%d y=%d",Pt.x,Pt.y);
   CWnd *pWnd=((CWinApp*)AfxGetApp())->m_pMainWnd;
   pWnd->SendMessage(WM_SETMESSAGESTRING,0,(LPARAM)(LPCSTR)message);

	CZoomView::OnMouseMove(nFlags, point);
}

void CGrapherView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
   CWnd *pWnd=((CWinApp*)AfxGetApp())->m_pMainWnd;
   CString message;
   message.Format("OnLButtonDblClk... x=%d y=%d",point.x,point.y);
   pWnd->SendMessage(WM_SETMESSAGESTRING,0,(LPARAM)(LPCSTR)message);

	CZoomView::OnLButtonDblClk(nFlags, point);
}

void CGrapherView::OnFileOpen() 
{
	// TODO: Add your command handler code here

   CWinApp* pApp=AfxGetApp();
   CDocument *pDoc=GetDocument();
   CString sDirectory;
   sDirectory.Empty();
   if (pDoc) sDirectory=pDoc->GetPathName();
   if (sDirectory.IsEmpty()) {
      sDirectory=pApp->GetProfileString(RegKeyRecentFileList,RegKeyRecentFile1);
   }
   if (!sDirectory.IsEmpty()) {
      int nPos=sDirectory.ReverseFind('\\');
      if (nPos!=-1) {
         sDirectory.Delete(nPos,sDirectory.GetLength()-nPos);
      }
   }

   char qFilter[]="Grapher Script Files (*.gr)|*.gr|"
                  "Data Files (*.dat;*.txt)|*.dat;*.txt|"
                  "All Files (*.*)|*.*||";
   CFileDialogEx Dialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      qFilter,NULL);
   Dialog.m_ofn.lpstrInitialDir=sDirectory;
   Dialog.DoModal();
   CString sFile=Dialog.GetPathName();

   if (sFile.IsEmpty()) return;
   pApp->OpenDocumentFile((LPCTSTR)sFile);
}

void CGrapherView::OnFileSave()
{
	// TODO: Add your command handler code here

   if (!m_bGrScriptModified) return;
   if (m_sGrFile.IsEmpty()) return;
   if (m_sGrScript.IsEmpty()) return;

   //2001.0406
   const int nTempPath=1024;
   char qTempPath[nTempPath];
   GetTempPath(nTempPath,qTempPath);
   int nCount=SEGetPlotCount(m_sGrScript);
   int nPos,nNameLength,nValueLength;
   CString sFile;
   for (int nIndex=1;nIndex<=nCount;nIndex++) {
      nPos=SEGetOptionPosition(
         m_sGrScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_PLOT,nIndex,
         PLOTSCRIPT_DATA,1,
         PLOTSCRIPT_TYPE,1,
         "xyfile=",1,0);
      if (nPos>0) {
         nNameLength=SEGetOptionNameLength(m_sGrScript,nPos);
         nValueLength=SEGetOptionValueLength(m_sGrScript,nPos);
         sFile=m_sGrScript.Mid(nPos+nNameLength+1,nValueLength);
         if (sFile[0]=='\"') {
            sFile.Delete(0);
            sFile.Delete(sFile.GetLength()-1);
         }
         sFile.TrimLeft();
         if (!strncmp(sFile,qTempPath,strlen(qTempPath))) {
            CopyFile(sFile,m_sGrFile+"xy",FALSE);
            m_sGrScript.Replace(sFile,m_sGrFile+"xy");
         }
      }
   }
   
   CFile File;
   int nResult=File.Open(m_sGrFile,CFile::modeCreate|CFile::modeWrite);
   if (!nResult) {
      CString sMessage;
      sMessage.Format(
         "Warning, file open error took place. : \n %s",
         m_sGrFile);
      MessageBox(sMessage,NULL,MB_ICONWARNING);
      return;
   }
   File.WriteHuge(m_sGrScript,m_sGrScript.GetLength());
   File.GetStatus(m_FileStatus);
   File.Close();

   m_bGrScriptModified=FALSE;

   CString sPath=GetGrFolder();
   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileString(RegKeySettings,RegKeyFileDirectory,sPath);
}

BOOL CGrapherView::OnFileSaveOnDestroy()
{
   if (m_bGrScriptModified) {
      int nResult=MessageBox(
         "The script is modified. Save changes into the file ?",
         m_sGrFile,MB_ICONQUESTION|MB_YESNOCANCEL);
      switch (nResult) {
      case IDYES : OnFileSave(); return TRUE;
      case IDNO : return TRUE;
      case IDCANCEL : return FALSE;
      }
   }
   return TRUE;
}

void CGrapherView::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable(m_bGrScriptModified);
}

void CGrapherView::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
   if (m_sGrScript.IsEmpty()) return;

   CGrapherDoc *pDoc=GetDocument();
   CString sFile=pDoc->GetPathName();
   if (sFile.IsEmpty()) return;

   CWinApp* pApp=AfxGetApp();
   CString sPath=pApp->GetProfileString(RegKeySettings,RegKeyFileDirectory);

   CFileDialogEx Dialog(
      FALSE,"gr",sFile, //Y.Kim,20030217
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,
      "Grapher Script Files (*.gr)|*.gr||",NULL);
   Dialog.m_ofn.lpstrInitialDir=(LPCTSTR)sPath;
   Dialog.DoModal();
   CString sNewFile=Dialog.GetPathName();
   if (sNewFile.IsEmpty()) return;

   pDoc->SetPathName(sNewFile);
   m_sGrFile=sNewFile;

   //2001.0406
   m_bGrScriptModified=TRUE;
   CGrapherView::OnFileSave();
   m_bGrScriptModified=FALSE;
}

void CGrapherView::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

   //pCmdUI->Enable(m_bGrScriptModified);
   pCmdUI->Enable(m_nGrPlotStatus==GR_ENROLLED);
}

void CGrapherView::OnFileSaveasWmf() 
{
	// TODO: Add your command handler code here
	
}

void CGrapherView::OnFileSaveasEmf() 
{
	// TODO: Add your command handler code here

   char sFilter[]=
      "Enhanced Meta Files (*.emf)|*.emf|""All Files (*.*)|*.*||";
   CFileDialog Dialog(FALSE,"emf","Grapher.emf",
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,
      sFilter,NULL);
   int nResponse=Dialog.DoModal();
	if (nResponse!=IDOK) return;
   CString sFile=Dialog.GetPathName();
   /* CFile File;
   if (File.Open((LPCTSTR)sFile,CFile::modeRead)) {
      File.Close();
      remove(sFile);
   }
   */
   remove(sFile);

   CMetaFileDC mfDC;
   CString sDescription;
   sDescription.Format("%s:%s",myGRVersionPointer(),sFile);
   int nLength=sDescription.GetLength();
   char *pAddr = new char [nLength+2];
   memset(pAddr,0,nLength+2);
   strcpy(pAddr,(LPCTSTR)sDescription);

   if (!mfDC.CreateEnhanced(GetDC(),sFile,NULL,pAddr)) {
      CString sMessage;
      sMessage.Format(
         "Warning, \n"
         "A target file seems to be locked by some other program. \n"
         "Could not create enhanced meta file :"
         "%s\n",
         sFile);
      MessageBox(sMessage,NULL,MB_ICONWARNING);
      delete pAddr;
      return;
   }
   delete pAddr;

   CSize Size;
   GetPageSizeOfLogicalCoordinate(Size);
   GERECT geRect;
   geRect.x=0;
   geRect.y=0;
   geRect.width=Size.cx;
   geRect.height=Size.cy;
   geRect.borderWidth=0;

   char *pReturn;
   myGRRefresh(
      m_pGrBlobList,
      NULL,(char*)mfDC.m_hDC,&geRect,
      GetZoomPageDpiFactor(),
      m_nWinScaleType,m_nEventX,m_nEventY,m_dEventFactor,
      FALSE,&pReturn);
   if (nResponse=GetLastError()) { //20020913Y.Kim
      LPVOID lpMsgBuf;
      FormatMessage( 
         FORMAT_MESSAGE_ALLOCATE_BUFFER | 
         FORMAT_MESSAGE_FROM_SYSTEM | 
         FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL,
         GetLastError(),
         MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),// Default language
         (LPTSTR)&lpMsgBuf,
         0,
         NULL);
      CString sMessage;
      sMessage.Format(
         "Warning, \n"
         "Unknown error while creating Enhanced Meta File object. \n"
         "Error message: %s"
         "Sorry, Could not create Enhanced Meta File named:\n"
         "%s\n",
         lpMsgBuf,sFile);
      MessageBox(sMessage,NULL,MB_ICONSTOP);
      LocalFree(lpMsgBuf);
      return;
   }

   HENHMETAFILE hEmf=mfDC.CloseEnhanced();
   ::DeleteEnhMetaFile(hEmf);

   myGRGEClose(pReturn);
}

void CGrapherView::OnFileSaveasPsf() 
{
	// TODO: Add your command handler code here

   char sFilter[]=
      "Postscript Files (*.ps)|*.ps|""All Files (*.*)|*.*||";
   CFileDialog Dialog(FALSE,"ps","Grapher.ps",
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,
      sFilter,NULL);
   int nResponse=Dialog.DoModal();
	if (nResponse!=IDOK) return;
   CString sFile=Dialog.GetPathName();

   if (m_nGrPlotStatus==GR_EMPTY) {
      MessageBox("(INTERNAL) Error, No BLOB",NULL,MB_ICONEXCLAMATION&MB_ICONWARNING);
      return;
   }
   GERECT geRect;
   geRect.x=1;
   geRect.y=1;
   geRect.width=m_totalLog.cx;
   geRect.height=m_totalLog.cx;
   geRect.borderWidth=0;
   myGRPrint(
      m_pGrBlobList,NULL,NULL,
      &geRect,GetZoomPageDpiFactor(),GE_EventNull,0,0,1.0,
      sFile,m_bLandscape);
}

void CGrapherView::OnFileSaveasHpglf() 
{
	// TODO: Add your command handler code here
	
}

void CGrapherView::OnUpdateFileSaveasWmf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}

void CGrapherView::OnUpdateFileSaveasEmf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nGrPlotStatus!=GR_EMPTY);
}

void CGrapherView::OnUpdateFileSaveasPsf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nGrPlotStatus!=GR_EMPTY);
}

void CGrapherView::OnUpdateFileSaveasHpglf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}

void CGrapherView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nGrPlotStatus!=GR_EMPTY);
}

void CGrapherView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nGrPlotStatus!=GR_EMPTY);
}

void CGrapherView::OnEditCopy() 
{
	// TODO: Add your command handler code here

   CMetaFileDC mfDC;
   CString sDescription;
   sDescription.Format("%s:%s",myGRVersionPointer(),"CGrapherView::OnEditCopy()");
   int nLength=sDescription.GetLength();
   char *pAddr = new char [nLength+2];
   memset(pAddr,0,nLength+2);
   strcpy(pAddr,(LPCTSTR)sDescription);
   mfDC.CreateEnhanced(GetDC(),NULL,NULL,pAddr);
   delete pAddr;
   CSize Size;
   GetPageSizeOfLogicalCoordinate(Size);
   double ArbitraryFactor=1.0;
   GERECT geRect;
   geRect.x=0;
   geRect.y=0;
   geRect.width=(int)(Size.cx*ArbitraryFactor);
   geRect.height=(int)(Size.cy*ArbitraryFactor);
   geRect.borderWidth=0;
   char *pDC;
   myGRRefresh(
      m_pGrBlobList,
      NULL,(char*)mfDC.m_hDC,&geRect,
      (float)(GetZoomPageDpiFactor()*ArbitraryFactor),
      m_nWinScaleType,m_nEventX,m_nEventY,m_dEventFactor,
      FALSE,&pDC); //Y.Kim,20030217
   HENHMETAFILE hEMF=mfDC.CloseEnhanced();
   myGRGEClose(pDC); //Y.Kim,20030217

   OpenClipboard();
   EmptyClipboard();
   ::SetClipboardData(CF_ENHMETAFILE,hEMF);
   CloseClipboard();

   //::DeleteEhnMetaFile(hemf);   zzz
}

void CGrapherView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nGrPlotStatus!=GR_EMPTY);
}

void CGrapherView::OnViewZoomOff() 
{
	// TODO: Add your command handler code here
	SetZoomMode(ZM_OFF);
}

void CGrapherView::OnUpdateViewZoomOff(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetZoomMode()==ZM_OFF);
}

void CGrapherView::OnViewHand() 
{
	// TODO: Add your command handler code here
   if (GetZoomMode() == ZM_HAND) {
		SetZoomMode(ZM_OFF);
	} else {
		SetZoomMode(ZM_HAND);
	}
}

void CGrapherView::OnUpdateViewHand(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetZoomMode()==ZM_HAND);
}

void CGrapherView::OnViewZoomIn() 
{
	// TODO: Add your command handler code here
	CWnd *pWin = ((CWinApp *) AfxGetApp())->m_pMainWnd;
	if (GetZoomMode() == ZM_IN) {
		SetZoomMode(ZM_OFF);
		pWin->SendMessage(WM_SETMESSAGESTRING, 0, 
			(LPARAM)(LPCSTR)"");
	} else {
		SetZoomMode(ZM_IN);
		pWin->SendMessage(WM_SETMESSAGESTRING, 0, 
			(LPARAM)(LPCSTR)"Click to zoom in on point or drag a zoom box.");
	}
}

void CGrapherView::OnUpdateViewZoomIn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetZoomMode()==ZM_IN);
}

void CGrapherView::OnViewZoomOut() 
{
	// TODO: Add your command handler code here
   CWnd *pWin = ((CWinApp *) AfxGetApp())->m_pMainWnd;
	if (GetZoomMode() == ZM_OUT) {
		SetZoomMode(ZM_OFF);
		pWin->SendMessage(WM_SETMESSAGESTRING, 0, 
			(LPARAM)(LPCSTR)"");
	} else {
		SetZoomMode(ZM_OUT);
		pWin->SendMessage(WM_SETMESSAGESTRING, 0, 
			(LPARAM)(LPCSTR)"Click to zoom out on point.");
	}
}

void CGrapherView::OnUpdateViewZoomOut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetZoomMode()==ZM_OUT);
}

void CGrapherView::OnViewFull() 
{
	// TODO: Add your command handler code here
	DoZoomFull();
}

void CGrapherView::OnRedraw() 
{
	// TODO: Add your command handler code here
   //CWnd::Invalidate();
   CWnd::RedrawWindow();
}

void CGrapherView::OnViewMag25() 
{
	// TODO: Add your command handler code here
	DoZoomPercent(25);
}

void CGrapherView::OnUpdateViewMag25(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int scale=(int)(GetZoomScale()*100);
   pCmdUI->SetRadio(scale==25);
}

void CGrapherView::OnViewMag50() 
{
	// TODO: Add your command handler code here
	DoZoomPercent(50);
}

void CGrapherView::OnUpdateViewMag50(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int scale=(int)(GetZoomScale()*100);
   pCmdUI->SetRadio(scale==50);
}

void CGrapherView::OnViewMag75() 
{
	// TODO: Add your command handler code here
	DoZoomPercent(75);
}

void CGrapherView::OnUpdateViewMag75(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int scale=(int)(GetZoomScale()*100);
   pCmdUI->SetRadio(scale==75);
}

void CGrapherView::OnViewMag100() 
{
	// TODO: Add your command handler code here
	DoZoomPercent(100);
}

void CGrapherView::OnUpdateViewMag100(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int scale=(int)(GetZoomScale()*100);
   pCmdUI->SetRadio(scale==100);
}

void CGrapherView::OnViewMag125() 
{
	// TODO: Add your command handler code here
	DoZoomPercent(125);
}

void CGrapherView::OnUpdateViewMag125(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   int scale=(int)(GetZoomScale()*100);
   pCmdUI->SetRadio(scale==125);
	
}

void CGrapherView::OnViewMag200() 
{
	// TODO: Add your command handler code here
	DoZoomPercent(200);
}

void CGrapherView::OnUpdateViewMag200(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   int scale=(int)(GetZoomScale()*100);
   pCmdUI->SetRadio(scale==200);	
}

void CGrapherView::OnViewMag400() 
{
	// TODO: Add your command handler code here
	DoZoomPercent(400);
}

void CGrapherView::OnUpdateViewMag400(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	int scale=(int)(GetZoomScale()*100);
   pCmdUI->SetRadio(scale==400);
}

void CGrapherView::OnViewCanvasA4h() 
{
	// TODO: Add your command handler code here
	SetZoomSizes(ZP_A4H);
   DoZoomFull();
   //
   theApp.SetPageOrientation(m_bLandscape=TRUE);
}

void CGrapherView::OnUpdateViewCanvasA4h(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(GetZoomPage()==ZP_A4H);
}

void CGrapherView::OnViewCanvasA4v() 
{
	// TODO: Add your command handler code here
	SetZoomSizes(ZP_A4);
   DoZoomFull();
   //
   theApp.SetPageOrientation(m_bLandscape=FALSE);
}

void CGrapherView::OnUpdateViewCanvasA4v(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   pCmdUI->SetRadio(GetZoomPage()==ZP_A4);
}

void CGrapherView::OnViewLeft()
{
	// TODO: Add your command handler code here
   OnHScroll(SB_LINELEFT,0,0);
}

void CGrapherView::OnViewDown() 
{
	// TODO: Add your command handler code here
   OnVScroll(SB_LINEDOWN,0,0);
}

void CGrapherView::OnViewUp() 
{
	// TODO: Add your command handler code here
   OnVScroll(SB_LINEUP,0,0);
}

void CGrapherView::OnViewRight() 
{
	// TODO: Add your command handler code here
   OnHScroll(SB_LINERIGHT,0,0);
}

void CGrapherView::OnViewTranslate() 
{
	// TODO: Add your command handler code here
   /*
   POINT point;

   GetCursorPos(&point);
   CWnd::ScreenToClient(&point);
   event='t';
   eventX=point.x;
   eventY=point.y;
   eventFactor=1.0; //not used
   CWnd::Invalidate();
   */
}

void CGrapherView::OnFitToObject() 
{
	// TODO: Add your command handler code here
   m_nWinScaleType='f';
   CWnd::RedrawWindow();
}

void CGrapherView::OnUpdateFitToObject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_nWinScaleType=='f');
}

void CGrapherView::OnFitToCanvas() 
{
	// TODO: Add your command handler code here
   m_nWinScaleType='F';
   CWnd::RedrawWindow();
}

void CGrapherView::OnUpdateFitToCanvas(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   pCmdUI->SetRadio(m_nWinScaleType=='F');
}

BOOL CGrapherView::LoadGrFile(const char *qFile)
{
   if (!qFile||!*qFile) return FALSE;

   CFile File;
   if (!File.Open(qFile,CFile::modeRead)) return FALSE;
   CFileStatus FileStatus;
   File.GetStatus(FileStatus);
   if (m_FileStatus.m_size) {
      int nResult=memcmp(&FileStatus,&m_FileStatus,sizeof(CFileStatus));
      if (nResult) {
         CString sMessage;
         sMessage.Format(
            "Warning,\n"
            "Grapher script file is modified by unknown reason.\n"
            "Its name is:  %s \n"
            "Are you willing to go on to read again and plot it ?",
            FileStatus.m_szFullName);
         nResult=MessageBox(
            sMessage,"Grapher Alert",MB_ICONWARNING|MB_YESNO);
         if (nResult==IDNO) {
            File.Close();
            return FALSE;
         }
      }
   }

   const int nMarginFactor=2; // for tail trimming and SESetOptionParameter().
   int nBuffer=File.GetLength()*sizeof(char)*nMarginFactor;
   char *pScript=new char[nBuffer];
   int nScript=File.ReadHuge(pScript,nBuffer);
   File.GetStatus(m_FileStatus);
   File.Close();
   memset(pScript+nScript,0,nBuffer-nScript);

   int nResult;

   CString sHomePath,sOption;
   sHomePath=((CGrapherApp*)AfxGetApp())->GetPathOfHome();
   sOption="home="+sHomePath;
   nResult=SESetOptionParameter(
      pScript,nBuffer,
      PLOTSCRIPT_BEGINNING,1,PLOTSCRIPT_GLOB,1,PLOTSCRIPT_EXEC,1,
      sOption,1,0);
   ASSERT(nResult);
   
   m_sGrScript=pScript;

   SEGetOptionPosition(
      pScript,
      PLOTSCRIPT_BEGINNING,1,PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GOUT,1,
      "landscape",1,0)
      >0 ? OnViewCanvasA4h() : OnViewCanvasA4v();

   delete pScript;

   //20030306
   m_sGrFile=qFile;
   //CString sFolder=GetGrFolder();//20030226
   char qBuffer[1024];
   //sprintf(qBuffer,"%s",sFolder);
   //if (GetFullPathName(GetGrFileName(),1023,qBuffer,NULL))
   sprintf(qBuffer,"%s",m_sGrFile); //20030307
   if (GetLongPathName(qBuffer,qBuffer,sizeof(qBuffer))) //20030307
      m_sGrFile=qBuffer;
   SetCurrentDirectory(GetGrFolder()); //20030306//20030307
   GetDocument()->SetPathName(m_sGrFile); //20030307
   
   //20030311
   m_bGrScriptModified=FALSE;

   return TRUE;
}

void CGrapherView::OnExecGr()
{
	// TODO: Add your command handler code here

   if (m_sGrFile.IsEmpty()) return;
   if (!LoadGrFile(m_sGrFile)) return;
   m_sGrLog.Empty();
   m_nGrPlotStatus=GR_EMPTY;
   myGRFreeBlob(m_pGrBlobList);
   m_pGrBlobList=NULL;
   OnRedraw();
}

void CGrapherView::OnGrPlotDefaultsymbol() 
{
	// TODO: Add your command handler code here
	CGrDefaultSymbolDialog Dialog;
   Dialog.DoModal();
}

void CGrapherView::OnWindowsFont() 
{
	// TODO: Add your command handler code here

   LOGFONT lf;
   strcpy(lf.lfFaceName,"ARIAL NARROW"); //20030223
	CFontDialog Dialog(&lf);
	int nResponse=Dialog.DoModal();
	if (nResponse!=IDOK) return;
   Dialog.GetCurrentFont(&lf);
   if (!*lf.lfFaceName) return;
   myGRBlobChangeFont(m_pGrBlobList,lf.lfFaceName);
   CWnd::RedrawWindow();
}

void CGrapherView::OnHomemadeFont() 
{
	// TODO: Add your command handler code here

   myGRBlobChangeFont(m_pGrBlobList,"");
   //I consider following to be a stupid way,but it works. 3/18/2002
   CWnd::RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW);
   CWnd::RedrawWindow();
}

void CGrapherView::OnViewScript() 
{
	// TODO: Add your command handler code here

   if (m_sGrFile.IsEmpty()) return;
   CWinApp *pApp=AfxGetApp();
   CString sExe=
      pApp->GetProfileString(RegKeySettings,RegKeyTextViewer);
   if (sExe.IsEmpty()) {
      AfxMessageBox(
         _T("외부 Script editor 실행파일을 먼저 선택하세요."),
         MB_ICONEXCLAMATION);
R:    CGrPathEnvironmentDialog Dialog;
      Dialog.DoModal();
      sExe=pApp->GetProfileString(RegKeySettings,RegKeyTextViewer);
   } else {
      CFile File;
      if (!File.Open(sExe,CFile::modeRead)) {
         sExe.Insert(0,"\"");
         sExe+="\" 파일의 오류입니다.\n";
         sExe+="외부 Script editor 실행파일을 full path로 다시 선택하세요.";
         AfxMessageBox(_T(sExe),
         MB_ICONEXCLAMATION);
         goto R;
      }
      File.Close();
   }
   UpdateData(TRUE);
   sExe+=" \""+m_sGrFile+"\"";
   WinExec((LPCTSTR)sExe,SW_SHOWDEFAULT);
}

void CGrapherView::OnViewLog() 
{
	// TODO: Add your command handler code here

   if (m_sGrLog.IsEmpty()) return;
   if (m_LogDialogModeless == NULL) {
		m_LogDialogModeless = new CGrLogDialog();
      m_LogDialogModeless->Create();
   } else
		m_LogDialogModeless->SetActiveWindow();

   char *pShortPath=yGetShortPath(m_sGrFile,36); //20030525
   CString sText;
   sText="Gr Log on ";
   sText+=pShortPath;
   freeEx(pShortPath);
   m_LogDialogModeless->SetWindowText(sText);
   m_LogDialogModeless->SetStream(m_sGrLog);
   m_LogDialogModeless->ShowWindow(SW_SHOW);
}

void CGrapherView::OnGrPropertyPage(int nID)
{
   int nIndex=0;
   switch (nID) {
   case IDM_GR_PLOT_PAGE : nIndex=0;break;
	case IDM_GR_ATTR_PAGE : nIndex=1;break;
	case IDM_GR_DATA_PAGE : nIndex=2;break;
   case IDM_GR_XYZB_PAGE : nIndex=3;break;
	case IDM_GR_SYMB_PAGE : nIndex=4;break;
	case IDM_GR_AXIS_PAGE : nIndex=5;break;
	case IDM_GR_TEXT_PAGE : nIndex=6;break;
	case IDM_GR_UFUN_PAGE : nIndex=7;break;
	case IDM_GR_VIEW_PAGE : nIndex=8;break;
	case IDM_GR_GLOB_PAGE : nIndex=9;break;
   }
   char *pShortPath=m_sGrFile.IsEmpty() ? 0:yGetShortPath(m_sGrFile,36); //20030308,0529
   CGrPropertySheet Sheet(
      m_sGrFile.IsEmpty() ? "Nothing..":pShortPath, //20030308
      this,nIndex);
   freeEx(pShortPath);
   Sheet.m_sGrFile=m_sGrFile;
   Sheet.m_sGrScript=m_sGrScript;
   Sheet.m_sGrLog=m_sGrLog;
   int nResult=Sheet.DoModal();
   switch(nResult) {
   case IDOK :
      m_nGrPlotStatus=GR_EMPTY;
      m_bGrScriptModified=TRUE;
      m_sGrScript=Sheet.m_sGrScript;
      RedrawWindow();
      break;
   default   :
      m_nGrPlotStatus=GR_ENROLLED;
      //m_bGrScriptModified=FALSE; 2001.0312
      break;
   }
}

void CGrapherView::AddFileStatusOfTemporaryFiles(CString sTemporaryFiles)
{
   while (m_FileStatusOfTemporaryFiles.GetSize()) {
      delete m_FileStatusOfTemporaryFiles[0];
      m_FileStatusOfTemporaryFiles.RemoveAt(0);
   }

   CToken Token(sTemporaryFiles,"\n");
   CString sReturn;
   CFile File;
   CFileStatus FileStatus,*pFileStatus;
   while (Token.IsNext()) {
      sReturn=Token.GetNextToken();
      if (!File.Open(sReturn,CFile::modeRead)) continue;
      File.GetStatus(FileStatus);
      pFileStatus=new CFileStatus[1];
      memcpy(pFileStatus,&FileStatus,sizeof(CFileStatus));
      m_FileStatusOfTemporaryFiles.Add(pFileStatus);
      File.Close();
   }
}

void CGrapherView::DeleteTemporaryFilesOnDisk()
{
   CFileStatus *pFileStatus;
   for (int nIndex=0;nIndex<=m_FileStatusOfTemporaryFiles.GetUpperBound();nIndex++) {
      pFileStatus=(CFileStatus*)m_FileStatusOfTemporaryFiles[nIndex];
      remove(pFileStatus->m_szFullName);
      delete pFileStatus;
   }
   m_FileStatusOfTemporaryFiles.RemoveAll();
}

void CGrapherView::AddFileStatusOfGargamelFiles()
{
   const char *qTarget="file";
   char *pScript;
   SEGetSimpleScript(m_sGrScript,&pScript);
   int nResult=SEGetOptionPosition(
      pScript,
      PLOTSCRIPT_BEGINNING,1,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_EXEC,1,qTarget,1,0);
   if (nResult<0) {
      while (m_FileStatusOfGargamelFiles.GetSize()) {
         delete m_FileStatusOfGargamelFiles[0];
         m_FileStatusOfGargamelFiles.RemoveAt(0);
      }
      myFree(pScript);
      return;
   }

   CStringArray FileNameArray;
   int nCount=SEGetOptionFrequencyInaRange(pScript,nResult,qTarget);
   CString sResult,sPattern,sSplit;
   CToken Token(NULL,"|\"");
   for (int nIndex=0;nIndex<nCount;nIndex++) {
      sResult=SEGetOptionValueString(
         NULL,pScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_GLOB,1,PLOTSCRIPT_EXEC,1,qTarget,nIndex+1,0);
      if (sResult.IsEmpty()) continue;
      Token=sResult;
      sPattern=Token.GetTokenByIndex(0);
      sPattern.TrimLeft();
      sPattern.TrimRight();
      sSplit=Token.GetTokenByIndex(1);
      sSplit.TrimLeft();
      sSplit.TrimRight();
      FileNameArray.Add(sPattern);
      FileNameArray.Add(sSplit);
   }
   myFree(pScript);

   CPtrArray FileStatusOfGargamelFiles;
   CFile File;
   CFileStatus FileStatus,*pFileStatus;
   while (FileNameArray.GetSize()) {
      if (!File.Open(FileNameArray[0],CFile::modeRead)) {
         FileNameArray.RemoveAt(0);
         continue;
      }
      File.GetStatus(FileStatus);
      File.Close();
      pFileStatus=new CFileStatus[1];
      memcpy(pFileStatus,&FileStatus,sizeof(CFileStatus));
      FileStatusOfGargamelFiles.Add(pFileStatus);
      FileNameArray.RemoveAt(0);
   }

   if (FileStatusOfGargamelFiles.GetSize()!=
      m_FileStatusOfGargamelFiles.GetSize()) {
R:    while (m_FileStatusOfGargamelFiles.GetSize()) {
         delete m_FileStatusOfGargamelFiles[0];
         m_FileStatusOfGargamelFiles.RemoveAt(0);
      }
      m_FileStatusOfGargamelFiles.Copy(FileStatusOfGargamelFiles);
      DeleteTemporaryFilesOnDisk();
      return;
   }

   nCount=FileStatusOfGargamelFiles.GetSize();
   while (nCount--) {
      nResult=memcmp(
         (CFileStatus*)FileStatusOfGargamelFiles[nCount],
         (CFileStatus*)m_FileStatusOfGargamelFiles[nCount],
         sizeof(CFileStatus));
      if (nResult) goto R;
   }
}

//Y.Kim,20030216
CString CGrapherView::GetGrFolder()
{ 
   CString sFolder(m_sGrFile);
   sFolder.MakeReverse();
   int nPos=sFolder.FindOneOf(":\\");
   if (nPos==-1) return (char*)0;
   sFolder.Delete(0,nPos);
   sFolder.MakeReverse();
   return sFolder;
}

CString CGrapherView::GetGrFileName()
{
   CString sFolder=GetGrFolder();
	CString sFile=m_sGrFile;
	sFile.Replace(sFolder,"");
	return sFile;
}
