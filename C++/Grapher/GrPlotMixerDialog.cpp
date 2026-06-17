// GrPlotMixerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrPlotMixerDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "MainFrm.h"
#include "GrapherDoc.h"
#include "GrapherView.h"

#include "plotse.h"

/////////////////////////////////////////////////////////////////////////////
// CGrPlotMixerDialog dialog


CGrPlotMixerDialog::CGrPlotMixerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGrPlotMixerDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrPlotMixerDialog)
	m_bRelayout = TRUE;
	//}}AFX_DATA_INIT
}


void CGrPlotMixerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrPlotMixerDialog)
	DDX_Control(pDX, ID_GR_PLOT_MIXER_TREECTRL, m_OptionsTreeCtrl);
	DDX_Check(pDX, ID_RELAYOUT, m_bRelayout);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrPlotMixerDialog, CDialog)
	//{{AFX_MSG_MAP(CGrPlotMixerDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrPlotMixerDialog message handlers

void SetTreeCtrlNewStyle(HWND hWnd,long lStyleMask,BOOL bSetBits)
{
   long lStyleOld;
   
   lStyleOld=GetWindowLong(hWnd,GWL_STYLE);
   lStyleOld&=~lStyleMask;
   if (bSetBits)
      lStyleOld|=lStyleMask;
   
   SetWindowLong(hWnd,GWL_STYLE,lStyleOld);
   SetWindowPos(hWnd,NULL,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
}

BOOL CGrPlotMixerDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   //SetFont(((CMDIFrameWnd*)AfxGetApp()->m_pMainWnd)->GetFont());

   CMDIFrameWnd *pFrame=(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
   CMDIChildWnd *pChildFrame=(CMDIChildWnd*)pFrame->GetActiveFrame();
   CDocument *pDoc=pChildFrame->GetActiveDocument();
   CDocTemplate* pDocTemplate=pDoc->GetDocTemplate();
   POSITION xPosition=pDocTemplate->GetFirstDocPosition();
   int nViewIndex=1;
   while (xPosition &&(pDoc=pDocTemplate->GetNextDoc(xPosition))) {
      POSITION xPos=pDoc->GetFirstViewPosition();
      CGrapherView* pView=(CGrapherView*)pDoc->GetNextView(xPos);
      if (pView->m_sGrScript.IsEmpty()) continue;

      m_Options.SetOptionItem(pDoc->GetTitle(),IDB_OPTIONTREECTRL_ITEMS,IDB_OPTIONTREECTRL_ITEMS);
      int nCount=SEGetPlotCount(pView->m_sGrScript);
      CString sPlotIndex,sPlotName;
      char *pName;
      for (int nIndex=1;nIndex<=nCount;nIndex++) {
         sPlotIndex.Format("%d-%d",nViewIndex,nIndex);
         pName=SEGetPlotName(pView->m_sGrScript,nIndex);
         sPlotName.Format("\t%s",pName);
         myFree(pName);
         m_Options.SetOption(sPlotIndex,COptions::CheckTrue);
         m_Options.SetOptionItem(sPlotIndex,sPlotName,COptions::CheckTrue,IDB_OPTIONTREECTRL_CHECKON,IDB_OPTIONTREECTRL_CHECKOFF);
      }
      nViewIndex++;
   }

   /*
   m_Options.SetOption("RadioOption1",0);
	m_Options.SetOption("RadioOption2",1);
	m_Options.SetOptionItem("Radio Options",IDB_OPTIONTREECTRL_ITEMS, IDB_OPTIONTREECTRL_ITEMS);
	m_Options.SetOptionItem("RadioOption1","\tSelection 0",0,IDB_OPTIONTREECTRL_RADIOON,IDB_OPTIONTREECTRL_RADIOOFF);
	m_Options.SetOptionItem("RadioOption1","\tSelection 1",1,IDB_OPTIONTREECTRL_RADIOON,IDB_OPTIONTREECTRL_RADIOOFF);
	m_Options.SetOptionItem("RadioOption1","\tSelection 2",2,IDB_OPTIONTREECTRL_RADIOON,IDB_OPTIONTREECTRL_RADIOOFF);
   m_Options.SetOptionItem("RadioOption2","\t\tSelection 0",0,IDB_OPTIONTREECTRL_RADIOON,IDB_OPTIONTREECTRL_RADIOOFF);
   m_Options.SetOptionItem("RadioOption2","\t\tSelection 1",1,IDB_OPTIONTREECTRL_RADIOON,IDB_OPTIONTREECTRL_RADIOOFF);
	m_Options.SetOptionItem("RadioOption1","\tSelection 3",3,IDB_OPTIONTREECTRL_RADIOON,IDB_OPTIONTREECTRL_RADIOOFF);
   m_Options.SetOptionItem("Check Options",IDB_OPTIONTREECTRL_ITEMS,IDB_OPTIONTREECTRL_ITEMS);
	m_Options.SetOption("CheckOption1",COptions::CheckFalse);
	m_Options.SetOptionItem("CheckOption1","\tCheck 1",COptions::CheckTrue,IDB_OPTIONTREECTRL_CHECKON,IDB_OPTIONTREECTRL_CHECKOFF);
   m_Options.SetOption("RadioOption3",1);
   m_Options.SetOptionItem("RadioOption3","\t\tSelection 0",0,IDB_OPTIONTREECTRL_RADIOON,IDB_OPTIONTREECTRL_RADIOOFF);
   m_Options.SetOptionItem("RadioOption3","\t\tSelection 1",1,IDB_OPTIONTREECTRL_RADIOON,IDB_OPTIONTREECTRL_RADIOOFF);
   m_Options.SetOption("CheckOption2",COptions::CheckTrue);
   m_Options.SetOptionItem("CheckOption2","\tCheck 2",COptions::CheckTrue,IDB_OPTIONTREECTRL_CHECKON,IDB_OPTIONTREECTRL_CHECKOFF);
   */

	m_OptionsTreeCtrl.m_pOptions=&m_Options;
	m_Options.BeginTrans();

   SetTreeCtrlNewStyle(m_OptionsTreeCtrl.m_hWnd,TVS_HASLINES,TRUE);
   m_OptionsTreeCtrl.Initialize(NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

const char * CGrPlotMixerDialog::GetScriptBelongsToAView(const CString &sName)
{
   CMDIFrameWnd *pFrame=(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
   CMDIChildWnd *pChildFrame=(CMDIChildWnd*)pFrame->GetActiveFrame();
   CDocument *pDoc=pChildFrame->GetActiveDocument();
   CDocTemplate* pDocTemplate=pDoc->GetDocTemplate();
   POSITION xPosition=pDocTemplate->GetFirstDocPosition();
   while (xPosition &&(pDoc=pDocTemplate->GetNextDoc(xPosition))) {
      POSITION xPos=pDoc->GetFirstViewPosition();
      CGrapherView* pView=(CGrapherView*)pDoc->GetNextView(xPos);
      if (!sName.Compare(pDoc->GetTitle())) {
         return pView->m_sGrScript;
      }
   }
   return (const char*)0;
}

void CGrPlotMixerDialog::OnOK() 
{
	// TODO: Add extra validation here

   UpdateData(TRUE);

   CString sAll;
   char *pScript;
   int nPlotIndex,nIndex;
   CUIntArray UIntArray;

   sAll.Empty();

   HTREEITEM hRoot=m_OptionsTreeCtrl.GetRootItem();
   HTREEITEM hItem=hRoot;
   OPTIONITEM* pData;
   while (hRoot) {
      pData=(OPTIONITEM*)m_OptionsTreeCtrl.GetItemData(hRoot);
      SEGetSimpleScript(GetScriptBelongsToAView(pData->szText),&pScript);
      hItem=hRoot;
      if (m_OptionsTreeCtrl.ItemHasChildren(hItem)) {
         nPlotIndex=1;
         UIntArray.RemoveAll();
         hItem=m_OptionsTreeCtrl.GetChildItem(hItem);
         while (hItem) {
            pData=(OPTIONITEM*)m_OptionsTreeCtrl.GetItemData(hItem);
            if (!m_Options[pData->szName]) {
               UIntArray.Add(nPlotIndex);
            }
            nPlotIndex++;
            hItem=m_OptionsTreeCtrl.GetNextSiblingItem(hItem);
         }
         nIndex=UIntArray.GetSize();
         while (nIndex--) {
            nPlotIndex=UIntArray[nIndex];
            SEDeleteIndexedPlotBlock(pScript,nPlotIndex);
         }
         sAll+=pScript;
         sAll+=PLOTSCRIPT_LINEEND;
      }
      hRoot=m_OptionsTreeCtrl.GetNextSiblingItem(hRoot);
      myFree(pScript);
   }

   if (sAll.IsEmpty()) return;
   if (!SEMixUpScripts(sAll,&pScript,m_bRelayout)) return;
   sAll=pScript;
   myFree(pScript);

   CGrPlotWizard pWizard;
   CString sFile=pWizard.GetGrTemporaryFileName();
   CFile File;
   File.Open(sFile,CFile::modeCreate|CFile::modeWrite);
   File.WriteHuge(sAll,sAll.GetLength());
   File.Close();
   AfxGetApp()->OpenDocumentFile(sFile);

	CDialog::OnOK();
}

