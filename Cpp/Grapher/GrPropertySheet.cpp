// GrPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

extern "C" void myFree(void*);

#define ID_BUTTON_PLOT_PREV 900000
#define ID_BUTTON_PLOT_NEXT 900001

/////////////////////////////////////////////////////////////////////////////
// CGrPropertySheet

IMPLEMENT_DYNAMIC(CGrPropertySheet, CPropertySheet)

CGrPropertySheet::CGrPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
   m_sGrScript.Empty();
   m_sGrScriptHead.Empty();
   m_sGrScriptTail.Empty();
   m_sGrLog.Empty();
   m_sGrFile.Empty();

   AddControlPages();
}

CGrPropertySheet::CGrPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage),
   m_bOk(FALSE)
{
   AddControlPages();
}

CGrPropertySheet::~CGrPropertySheet()
{
}

BEGIN_MESSAGE_MAP(CGrPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CGrPropertySheet)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(ID_BUTTON_PLOT_PREV,OnButtonPlotPrevious)
   ON_BN_CLICKED(ID_BUTTON_PLOT_NEXT,OnButtonPlotNext)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrPropertySheet message handlers

void CGrPropertySheet::AddControlPages()
{
    AddPage(&m_PlotPage);
    AddPage(&m_AttrPage);
	 AddPage(&m_DataPage);
	 AddPage(&m_XyzbPage);
	 AddPage(&m_SlctPage);
    AddPage(&m_AxisPage);
	 AddPage(&m_TextPage);
	 AddPage(&m_UfunPage);
    AddPage(&m_ViewPage);
	 AddPage(&m_GlobPage);
}

BOOL CGrPropertySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here

   CWnd *pApply,*pCancel,*pOk;
   pApply=GetDlgItem(ID_APPLY_NOW);
   pCancel=GetDlgItem(IDCANCEL);
   pOk=GetDlgItem(IDOK);
   CRect RectApply,RectCancel;
   pApply->GetWindowRect(&RectApply);
   pCancel->GetWindowRect(&RectCancel);
   ScreenToClient(&RectApply);
   ScreenToClient(&RectCancel);
   pApply->ShowWindow(SW_HIDE);
   pCancel->MoveWindow(&RectApply);
   pOk->MoveWindow(&RectCancel);

// www.codeguru.com
// Adding a Button to CPropertySheet 
// Jeremy Davis.
   CRect RectTab;
   GetTabControl()->GetWindowRect(RectTab);
   ScreenToClient(RectTab);
   CRect Rect(&RectApply);
   Rect.left=RectTab.left;
   Rect.right=RectTab.left+RectApply.Width()-10;
   m_ButtonPlotPrev.Create(
      "Previous",
      BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,Rect,this,
      ID_BUTTON_PLOT_PREV);
   m_ButtonPlotPrev.SetFont(GetFont());
   Rect.left=Rect.right+5;
   Rect.right=Rect.left+RectApply.Width()-20;
   m_ButtonPlotNext.Create(
      "Next",
      BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP,Rect,this,
      ID_BUTTON_PLOT_NEXT);
   m_ButtonPlotNext.SetFont(GetFont());
   if (!m_sGrScript.IsEmpty()) {
      char *pScript;
      SEGetSimpleScript(m_sGrScript,&pScript);
      m_sGrScript=pScript;
      myFree(pScript);
   }

	return bResult;
}

BOOL CGrPropertySheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
   if (wParam==IDOK) {
      m_bOk=TRUE;
   }
	return CPropertySheet::OnCommand(wParam, lParam);
}

int CGrPropertySheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

   if (m_sGrScript.IsEmpty()) {
      m_nPlotTotal=0;
      m_nPlotIndex=0;
   } else {
      char *pScript;
      SEGetSimpleScript(m_sGrScript,&pScript);
      m_nPlotTotal=SEGetOptionFrequencyInaRange(pScript,0,PLOTSCRIPT_PLOT);
      m_nPlotIndex=1;
      m_sGrScriptHead=m_sGrScript.Left(m_sGrScript.Find(PLOTSCRIPT_BEGINNING));
      m_sGrScriptTail=m_sGrScript.Right(m_sGrScript.GetLength()
         -m_sGrScript.Find(PLOTSCRIPT_END)-strlen(PLOTSCRIPT_END));
      m_sGrScript=pScript;
      myFree(pScript);
   }
	
	return 0;
}

void CGrPropertySheet::OnDestroy() 
{
	CPropertySheet::OnDestroy();
	
	// TODO: Add your message handler code here

	if (m_bOk!=TRUE) return;
   if (m_sGrScript.IsEmpty()) return;

   char *pScript;
   SEGetSimpleScript(m_sGrScript,&pScript);
   m_sGrScript=m_sGrScriptHead+pScript+m_sGrScriptTail; //Y.Kim,20030211
   myFree(pScript);
}

void CGrPropertySheet::OnButtonPlotPrevious()
{
   if (m_nPlotIndex<=1) return;
   CPropertyPage* pPage=GetActivePage();
   pPage->OnKillActive();
   m_nPlotIndex--;
   RefreshWindowTitleText();
   if (GetActiveIndex()) {
      pPage->OnSetActive();
   } else {
      CGrPlotPage *pPlotPage=(CGrPlotPage*)pPage;
      pPlotPage->SetTreeCtrlSelection(m_nPlotIndex);
   }
}

void CGrPropertySheet::OnButtonPlotNext()
{
   if (m_nPlotIndex>=m_nPlotTotal) return;
   CPropertyPage* pPage=GetActivePage();
   pPage->OnKillActive();
   m_nPlotIndex++;
   RefreshWindowTitleText();
   if (GetActiveIndex()) {
      pPage->OnSetActive();
   } else {
      CGrPlotPage *pPlotPage=(CGrPlotPage*)pPage;
      pPlotPage->SetTreeCtrlSelection(m_nPlotIndex);
   }
}

void CGrPropertySheet::RefreshWindowTitleText()
{
   CString sReturn;
   GetWindowText(sReturn);
   int nPos=sReturn.Find(" -> [");
   if (nPos>0) sReturn.Delete(nPos,sReturn.GetLength()-nPos);
   CString sTail;
   sTail.Format(" -> [%d/%d]",m_nPlotIndex,m_nPlotTotal);
   sReturn+=sTail;
   SetWindowText(sReturn);
}

CString CGrPropertySheet::GetFolderFromFilePath(const char *qFilePath)
{
   CString sFolder(qFilePath);
   sFolder.MakeReverse();
   int nPos=sFolder.FindOneOf(":\\");
   if (nPos==-1) return (char*)0;
   sFolder.Delete(0,nPos);
   sFolder.MakeReverse();
   return sFolder;
}
