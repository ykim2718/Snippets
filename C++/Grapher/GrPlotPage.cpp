// GrPlotPage.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrPlotPage.h"
#include "GrPlotWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "GrapherDoc.h"
#include "GrapherView.h"
#include "GrPropertySheet.h"

#include "myGR.h"

/////////////////////////////////////////////////////////////////////////////
// CGrPlotPage property page

IMPLEMENT_DYNCREATE(CGrPlotPage, CPropertyPage)

CGrPlotPage::CGrPlotPage() : CPropertyPage(CGrPlotPage::IDD)
{
	//{{AFX_DATA_INIT(CGrPlotPage)
	//}}AFX_DATA_INIT
   m_aEMF.RemoveAll();
}

CGrPlotPage::~CGrPlotPage()
{
   while (m_aEMF.GetSize()) {
      if (m_aEMF[0]) ::DeleteEnhMetaFile((HENHMETAFILE)(m_aEMF[0]));
      m_aEMF.RemoveAt(0);
   }
}

void CGrPlotPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrPlotPage)
	DDX_Control(pDX, ID_GRPLOT_TREECTRL, m_TreeCtrl);
	DDX_Control(pDX, ID_GRPLOT_EMF_CANVAS, m_EmfCanvas);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrPlotPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrPlotPage)
	ON_BN_CLICKED(ID_GRPLOT_ADD, OnGrplotAdd)
	ON_BN_CLICKED(ID_GRPLOT_DELETE, OnGrplotDelete)
	ON_BN_CLICKED(ID_GRPLOT_TOEMF, OnGrplotToemf)
	ON_NOTIFY(TVN_SELCHANGED, ID_GRPLOT_TREECTRL, OnSelchangedGrplotTreectrl)
	ON_BN_CLICKED(ID_GRPLOT_COPY, OnGrplotCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrPlotPage message handlers

BOOL CGrPlotPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   CGrapherApp *pApp=(CGrapherApp*)AfxGetApp();
   m_pSheet=GetParentOwner();

   CGrPropertySheet *pSheet=(CGrPropertySheet*)m_pSheet;
   CString &Script=pSheet->m_sGrScript;
   CString sReturn;
   for (int nIndex=1;nIndex<=pSheet->m_nPlotTotal;nIndex++) {
      m_aEMF.SetAtGrow(nIndex,NULL);
      m_aEMFIndex.SetAtGrow(nIndex,nIndex);
      sReturn=GetScriptPlotString(Script,nIndex);
      m_TreeCtrl.InsertItem(sReturn);
   }

   /*
   CDC *pDC=m_EmfCanvas.GetDC();
   pDC->SetBkMode(OPAQUE);
   pDC->SetBkColor(0x00ff0000);
   m_EmfCanvas.RedrawWindow();
   //m_EmfCanvas.ReleaseDC(pDC);
   */
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrPlotPage::OnGrplotAdd() 
{
#ifdef _DEBUG
	CGrapherApp *pApp=(CGrapherApp*)AfxGetApp();
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) Script="%geBeginning .glob gtxt gout %grEnd";
   pSheet->m_nPlotTotal++;
   pSheet->m_nPlotIndex=pSheet->m_nPlotTotal;

   const char *qPlot=".plot attr data xyzb slct ____ ufun axis text view";
   /*
   int nPos=SEGetOptionPosition(
      Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,0);
   if (nPos==-1) {
      nPos=SEGetSafeOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,0);
   }
   */
   int nPos=SEGetSafeOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,0);
   Script.Insert(nPos,qPlot);
   Script.Insert(nPos+strlen(qPlot)," ");

   CGrPlotPage::OnSetActive();
#endif
}

void CGrPlotPage::OnGrplotCopy() 
{
	// TODO: Add your control notification handler code here

   if (!m_TreeCtrl.GetSelectedItem()) return;
	
}

void CGrPlotPage::OnGrplotDelete() 
{
	// TODO: Add your control notification handler code here

   if (!m_TreeCtrl.GetSelectedItem()) return;

   CGrPropertySheet *pSheet=(CGrPropertySheet*)m_pSheet;
   CString &Script=pSheet->m_sGrScript;

   if (pSheet->m_nPlotTotal==1) return;
   pSheet->m_nPlotTotal--;

   char *pScript=new char[Script.GetLength()+1];
   strcpy(pScript,Script);
   SEDeleteIndexedPlotBlock(pScript,pSheet->m_nPlotIndex);
   Script=pScript;
   delete pScript;

   ::DeleteEnhMetaFile((HENHMETAFILE)(m_aEMF[pSheet->m_nPlotIndex]));
   m_aEMF.RemoveAt(pSheet->m_nPlotIndex);
   m_aEMFIndex.RemoveAt(pSheet->m_nPlotIndex);

   DelTreeCtrlSelection(pSheet->m_nPlotIndex);
}

CString CGrPlotPage::GetScriptPlotString(CString &Script,int nPlotIndex)
{
   char *pName=SEGetPlotName(Script,nPlotIndex);
   CString sReturn(pName);
   myFree(pName);
   return sReturn;
}

void CGrPlotPage::OnGrplotToemf() 
{
	// TODO: Add your control notification handler code here

   
   HENHMETAFILE hEMF=m_EmfCanvas.GetEnhMetaFile();
   if (!hEMF) {
      MessageBox("Warning, You have no plot made.",NULL,MB_ICONWARNING);
      return;
   }

   CFileDialog fDialog(FALSE,"emf","Grapher.emf",
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,
      "Enhanced Meta Files (*.emf)|*.emf||",NULL);
   int nResponse=fDialog.DoModal();
	if (nResponse!=IDOK) return;
   CString sFile=fDialog.GetPathName();
   if ((_access(sFile,0))!=-1 && remove(sFile)==-1) {
      CString sTemp;
      sTemp.Format(
         "Warning, \n"
         "A target file seems to be locked by some other program. \n"
         "Could not create enhanced meta file : %s \n",
         sFile);
      MessageBox(sTemp,NULL,MB_ICONWARNING);
      return;
   }

   HDC hDC=::GetDC(NULL);
   UINT nBuffer=GetWinMetaFileBits(hEMF,0,NULL,MM_ANISOTROPIC,hDC);   
   ::ReleaseDC(NULL,hDC);
   LPBYTE pBuffer=new BYTE[nBuffer];
	GetEnhMetaFileBits(hEMF,nBuffer,pBuffer);
	HANDLE hFile=CreateFile(sFile,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
   DWORD nNumberOfBytesWritten;
	WriteFile(hFile,pBuffer,nBuffer,&nNumberOfBytesWritten,NULL);
	delete pBuffer;
	CloseHandle(hFile);
}

HENHMETAFILE CGrPlotPage::GetEnhMetaFileOfGr(int nPlotIndex)
{
   CMDIFrameWnd *pFrame=(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
   CMDIChildWnd *pChild=pFrame->MDIGetActive();
   CGrapherView *pView=(CGrapherView*)pChild->GetActiveView();

   if (!pView->m_pGrBlobList) return (HENHMETAFILE)0; //20030427

   CMetaFileDC mfDC;
   CString sDescription;
   sDescription.Format("%s-%s",
      myGRVersionPointer(),"CGrPlotPage::OnSelchangeGrplotListbox()");
   int nLength=sDescription.GetLength();
   char *pAddr = new char [nLength+2];
   memset(pAddr,0,nLength+2);
   strcpy(pAddr,(LPCTSTR)sDescription);
   mfDC.CreateEnhanced(GetDC(),NULL,NULL,pAddr);
   delete pAddr;
   //mfDC.m_bPrinting=1; 2001.0316
   //pView->OnPrepareDC(&mfDC); 2001.0316
   CSize Size;
   pView->GetPageSizeOfLogicalCoordinate(Size);
   GERECT geRect;
   geRect.x=0;
   geRect.y=0;
   geRect.width=Size.cx;
   geRect.height=Size.cy;
   geRect.borderWidth=0;
   char *pGEClose;
   myGRRefreshPlotByOne(
     pView->m_pGrBlobList,
     NULL,(char*)mfDC.m_hDC,&geRect,pView->GetZoomPageDpiFactor(),
     'f',0,0,(float)1.0,
     nPlotIndex,
     FALSE,&pGEClose
     );
   HENHMETAFILE hEMF=mfDC.CloseEnhanced();
   myGRGEClose(pGEClose); //20020914

   return hEMF;
}

void CGrPlotPage::SetTreeCtrlSelection(int nIndex)
{
   int nItem=0;
   HTREEITEM hItem=m_TreeCtrl.GetRootItem( );
   while (hItem) {
      nItem++;
      if (nItem==nIndex) {
         m_TreeCtrl.SelectItem(hItem);
         break;
      }
      hItem=m_TreeCtrl.GetNextItem(hItem,TVGN_NEXT);
   }
   OnSelchangedGrplotTreectrl(NULL,NULL);
}

int CGrPlotPage::GetTreeCtrlCurrentSelection()
{
   HTREEITEM hSelectedItem=m_TreeCtrl.GetSelectedItem();
   if (!hSelectedItem) return 0;
   int nIndex=0;
   HTREEITEM hItem=m_TreeCtrl.GetRootItem( );
   while (hItem) {
      nIndex++;
      if (hItem==hSelectedItem) return nIndex;
      hItem=m_TreeCtrl.GetNextItem(hItem,TVGN_NEXT);
   }
   return 0;
}

void CGrPlotPage::DelTreeCtrlSelection(int nIndex)
{
   HTREEITEM hItem=m_TreeCtrl.GetRootItem( );
   while (hItem && --nIndex) hItem=m_TreeCtrl.GetNextItem(hItem,TVGN_NEXT);
   if (hItem && !nIndex) m_TreeCtrl.DeleteItem(hItem);
}

void CGrPlotPage::OnSelchangedGrplotTreectrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
   if (pResult) *pResult = 0;
	// TODO: Add your control notification handler code here

   if (m_TreeCtrl.GetCount()==-1) return;
   CGrPropertySheet *pSheet=(CGrPropertySheet*)m_pSheet;
   GetDlgItem(ID_GRPLOT_DELETE)->EnableWindow(pSheet->m_nPlotTotal>1);
   pSheet->m_nPlotIndex=GetTreeCtrlCurrentSelection();
   if (!pSheet->m_nPlotIndex) return;

   pSheet->RefreshWindowTitleText();

   HENHMETAFILE hEMF;
   if (m_aEMF[pSheet->m_nPlotIndex]) {
      hEMF=(HENHMETAFILE)m_aEMF[pSheet->m_nPlotIndex];
   } else {
      int nPlotIndex=m_aEMFIndex[pSheet->m_nPlotIndex];
      hEMF=GetEnhMetaFileOfGr(nPlotIndex);
      m_aEMF[pSheet->m_nPlotIndex]=hEMF;
   }
   m_EmfCanvas.SetEnhMetaFile(hEMF);
}

BOOL CGrPlotPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

   CGrPropertySheet *pSheet=(CGrPropertySheet*)m_pSheet;
   SetTreeCtrlSelection(pSheet->m_nPlotIndex);
	
	return CPropertyPage::OnSetActive();
}

