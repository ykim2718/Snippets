// GargamelTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "gargamel.h"
#include "GargamelTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Y.Kim,20030206

#include "Execute.h"
#include "GargamelPatternFrameDialog.h"
#include "GargamelPatternForMatrixFrameDialog.h"
#include "GargamelSplitFrameDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CGargamelTabCtrl

CGargamelTabCtrl::CGargamelTabCtrl()
{
}

CGargamelTabCtrl::~CGargamelTabCtrl()
{
   int nCount,nIndex;
   while (nCount=m_aTabDialogs.GetSize()) {
      nIndex=nCount-1;
      delete ((CDialog*)m_aTabDialogs[nIndex]);
      m_aTabDialogs.RemoveAt(nIndex); //Y.Kim,20030215 TLT
   }
}

BEGIN_MESSAGE_MAP(CGargamelTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CGargamelTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGargamelTabCtrl message handlers

void CGargamelTabCtrl::AddToTapArray(CString sText,CDialog *pDialog,int nDialogID,int bShow)
{
   if (bShow) InsertItem(GetItemCount(),sText);
   pDialog->Create(nDialogID,this);
   m_aTabTexts.Add(sText);
   m_aTabDialogs.Add((CObject*)pDialog);
   m_aTabDialogIDs.Add(nDialogID);
}

int CGargamelTabCtrl::GetTabArrayCount()
{
   return m_aTabTexts.GetSize();
}

void CGargamelTabCtrl::Commence()
{
   AddToTapArray(_T("Execute"),new CExecute,IDD_GARGAMEL_EXECUTE,true);
   AddToTapArray(_T("Pattern"),new CGargamelPatternFrameDialog,IDD_GARGAMEL_PATTERN,true);
   AddToTapArray(_T("Pattern for matrix"),new CGargamelPatternForMatrixFrameDialog,IDD_GARGAMEL_PATTERNFORMATRIX,false);
   AddToTapArray(_T("Split"),new CGargamelSplitFrameDialog,IDD_GARGAMEL_SPLIT,true);

   SetWindowCustomizedFirst();
}

void CGargamelTabCtrl::SetWindowCustomizedFirst()
{
   int nMarginOfTabCtrlToWnd=10;
   int nMarginOfPageToTabCtrl=5;
   CRect rPage,rTab,rItem,rWnd,rect;

   rPage.SetRectEmpty();
   for (int nIndex=0;nIndex<GetTabArrayCount();nIndex++) {
      ((CDialog *)m_aTabDialogs[nIndex])->GetWindowRect(&rect);
      ScreenToClient(&rect);
      rPage|=rect;
   }
   GetClientRect(&rTab);
   GetItemRect(0,&rItem);

   int x1=0;
   int y1=0;
   int x2=x1+rPage.Width()+nMarginOfPageToTabCtrl*2;
   int y2=y1+rItem.Height()+rPage.Height()+nMarginOfPageToTabCtrl*2;
   rWnd.SetRect(x1,y1,x2,y2);
   rWnd.InflateRect(nMarginOfTabCtrlToWnd,nMarginOfTabCtrlToWnd);
   rWnd.bottom+=20; // Don't know :( 2K.0809
   GetParent()->MoveWindow(&rWnd);
   GetParent()->CenterWindow();

   rTab.CopyRect(rWnd);
   rTab-=rTab.TopLeft();
   rTab.DeflateRect(nMarginOfTabCtrlToWnd,nMarginOfTabCtrlToWnd);
   rTab.bottom-=rItem.Height();
   MoveWindow(&rTab);

   x1=nMarginOfPageToTabCtrl; // Because each "page" window is children of
   y1=rItem.Height()+nMarginOfPageToTabCtrl;    // CGargamelTabCtrl window.
   x2=rPage.Width();
   y2=rPage.Height();
   ((CDialog *)m_aTabDialogs[0])->SetWindowPos(&wndTop,x1,y1,x2,y2,SWP_SHOWWINDOW);
   for (nIndex=1;nIndex<GetTabArrayCount();nIndex++) {
      ((CDialog *)m_aTabDialogs[nIndex])->SetWindowPos(&wndTop,x1,y1,x2,y2,SWP_HIDEWINDOW);
   }
   SetCurSel(m_nTabArrayIndex=0);
}

void CGargamelTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
   *pResult = 0;
	// TODO: Add your control notification handler code here

   int nCurrentSelection=GetCurSel();
   int nTabArrayIndexNew=GetTabArrayIndexFromTabIndex(nCurrentSelection);
   if (nTabArrayIndexNew==m_nTabArrayIndex) return;

   CDialog *pDialog=(CDialog*)m_aTabDialogs[m_nTabArrayIndex];
   pDialog->SendMessage(GargamelUpdateDataMessage,true,0);
   pDialog->ShowWindow(SW_HIDE);

   m_nTabArrayIndex=nTabArrayIndexNew;
   pDialog=(CDialog*)m_aTabDialogs[m_nTabArrayIndex];
   pDialog->SendMessage(GargamelUpdateDataMessage,false,0);
   pDialog->ShowWindow(SW_SHOW);
   pDialog->SetFocus();

   // TODO: Before this.
	*pResult = 0;
}

int CGargamelTabCtrl::GetTabArrayIndexFromDialogID(int nDialogID)
{
   for (int nIndex=0;nIndex<GetTabArrayCount();nIndex++) {
      if (m_aTabDialogIDs[nIndex]==(UINT)nDialogID) {
         return nIndex;
      }
   }
   return -1;
}

int CGargamelTabCtrl::GetTabArrayIndexFromTabIndex(int nTabIndex)
{
   if (nTabIndex>GetItemCount()) return -1;
   CString sTabText;
   TCITEM TabCtrlItem;
   TabCtrlItem.mask=TCIF_TEXT;
   TabCtrlItem.cchTextMax=255;
   TabCtrlItem.pszText=sTabText.GetBuffer(TabCtrlItem.cchTextMax);
   GetItem(nTabIndex,&TabCtrlItem);
   for (int nIndex=0;nIndex<GetTabArrayCount();nIndex++) {
      if (!sTabText.Compare(m_aTabTexts[nIndex])) {
         return nIndex;
      }
   }
   return -1;
}

int CGargamelTabCtrl::IsActivatedDialogInTabControl(int nDialogID)
{
   int nTabArrayIndex=GetTabArrayIndexFromDialogID(nDialogID);
   CString sTabArrayText(m_aTabTexts[nTabArrayIndex]);
   CString sTabText;
   TCITEM TabCtrlItem;
   TabCtrlItem.mask=TCIF_TEXT;
   TabCtrlItem.cchTextMax=255;
   TabCtrlItem.pszText=sTabText.GetBuffer(TabCtrlItem.cchTextMax);
   for (int nArrayIndex=0;nArrayIndex<GetItemCount();nArrayIndex++) {
       GetItem(nArrayIndex,&TabCtrlItem);
      if (!sTabArrayText.Compare(sTabText)) {
         return true;
      }
   }
   return false;
}

CDialog * CGargamelTabCtrl::GetDialogClassPtr(int nDialogID)
{
   int nIndex=GetTabArrayIndexFromDialogID(nDialogID);
   return nIndex>=0 ? (CDialog*)m_aTabDialogs[nIndex]:(CDialog*)0;
}

int CGargamelTabCtrl::SetTabArrayItemProperty(int nDialogID,int nTabIndex,int bShow)
{
   if (!GetTabArrayCount()) return false; //20030209
   if (bShow) {
      if (IsActivatedDialogInTabControl(nDialogID)) return false;
      int nTabArrayIndex=GetTabArrayIndexFromDialogID(nDialogID);
      InsertItem(nTabIndex,m_aTabTexts[nTabArrayIndex]);
   } else {
      if (GetTabArrayIndexFromDialogID(nDialogID)!=
          GetTabArrayIndexFromTabIndex(nTabIndex)) return false;
      DeleteItem(nTabIndex);
      Invalidate(); //2003.2.7
   }
   return true;
}


