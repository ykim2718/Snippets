// ListCtrlEx1.cpp : implementation file
//

#include "stdafx.h"
#include "gargamelpattern.h"
#include "ListCtrlEx1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx1Edit

CListCtrlEx1Edit::CListCtrlEx1Edit()
:m_x(0),m_y(0),m_width(0),m_height(0)
{
}

CListCtrlEx1Edit::~CListCtrlEx1Edit()
{
}

BEGIN_MESSAGE_MAP(CListCtrlEx1Edit, CEdit)
	//{{AFX_MSG_MAP(CListCtrlEx1Edit)
	ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx1Edit message handlers

void CListCtrlEx1Edit::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	lpwndpos->x=m_x;
   lpwndpos->y=m_y;
   lpwndpos->cx=m_width;
   lpwndpos->cy=m_height; //shik96,2001.0508
   CEdit::OnWindowPosChanging(lpwndpos);
}

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx1

CListCtrlEx1::CListCtrlEx1()
{
   m_nColumn=0;
   m_sRowStringDivider="\n";
   m_bLCEEdit=-1;
}

CListCtrlEx1::~CListCtrlEx1()
{
}

BEGIN_MESSAGE_MAP(CListCtrlEx1, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx1)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx1 message handlers

void CListCtrlEx1::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here

   *pResult=1;
   CPoint posMouse;
   GetCursorPos(&posMouse);
   ScreenToClient(&posMouse);
   LV_COLUMN lvc;
   lvc.mask=LVCF_WIDTH;
   CRect rcItem;
   this->GetItemRect(pDispInfo->item.iItem,rcItem,LVIR_LABEL);
   if (rcItem.PtInRect(posMouse)) m_bLCEEdit=0;
   int nCol=1;
   while (m_bLCEEdit==-1 && this->GetColumn(nCol,&lvc)) {
      rcItem.left=rcItem.right;
      rcItem.right+=lvc.cx;
      if (rcItem.PtInRect(posMouse)) m_bLCEEdit=nCol;
      nCol++;
   }
   if (m_bLCEEdit==-1) return;
   // HWND hWnd=(HWND)SendMessage(LVM_GETEDITCONTROL); // <- original
   HWND hWnd=GetEditControl()->m_hWnd;              // <- shik96,2001.0508
   ASSERT(hWnd!=NULL);
   VERIFY(m_LCEEdit.SubclassWindow(hWnd));
   m_LCEEdit.m_x=rcItem.left;
   m_LCEEdit.m_y=rcItem.top-2; //shik96,2001.0508
   m_LCEEdit.m_width=(rcItem.right-rcItem.left+1);
   m_LCEEdit.m_height=rcItem.Height()+3; //shik96,2001.0508
   m_LCEEdit.SetWindowText(this->GetItemText(pDispInfo->item.iItem,m_bLCEEdit));
	
	*pResult = 0;
}

void CListCtrlEx1::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here

   CString sEdit=pDispInfo->item.pszText;
	if (!sEdit.IsEmpty()) {
		this->SetItemText(pDispInfo->item.iItem,m_bLCEEdit,sEdit);
	}
	m_bLCEEdit=-1;
	VERIFY(m_LCEEdit.UnsubclassWindow()!=NULL);
	this->SetItemState(pDispInfo->item.iItem,0,LVNI_FOCUSED|LVNI_SELECTED);
	
	*pResult = 0;
}

void CListCtrlEx1::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);

   switch (nChar) {
   case VK_DELETE : case 'D' : case 'd' : CListCtrlEx1::DeleteRows();break;
   default : ;
   }
}

// Copying/Moving Rows in CListCtrl www.codeguru.com
// This article was contributed by James Spibey. 
// This article is very strightfoward but I thought it was a feature that most
// people could use in their own custom CListCtrls or CLIstViews.
// I had the need in one of my projects nTo allow the user nTo rearrange the order
// of the ListCtrl but I didn't want nTo allow them nTo drag and drop. Therefore I
// came up with this. 
BOOL CListCtrlEx1::MoveRow( int nFrom, int nTo )
{
	if(nFrom==nTo || nFrom<0 || nTo<0) return FALSE;
   BOOL bResult;
   if (nFrom<nTo) nTo++;                      //down//2000.0508
	if (CopyRow(nFrom,nTo)) {
		if (nFrom > nTo)
			DeleteItem(nFrom + 1);
		else
			DeleteItem(nFrom);
		bResult=TRUE;
   } else
      bResult=FALSE;
   if (nFrom<nTo) nTo--;                      //down//2000.0508
   SetItemState(nTo,LVIS_SELECTED,LVIS_SELECTED); //2000.0508
   return bResult;                               //2000.0508
}

// Copying/Moving Rows in CListCtrl www.codeguru.com
// This article was contributed by James Spibey. 
// This article is very strightfoward but I thought it was a feature that most
// people could use in their own custom CListCtrls or CLIstViews.
// I had the need in one of my projects nTo allow the user nTo rearrange the order
// of the ListCtrl but I didn't want nTo allow them nTo drag and drop. Therefore I
// came up with this. 
BOOL CListCtrlEx1::CopyRow( int nFrom, int nTo )
{
	//Can't move nTo the same place, or nFrom or nTo a negative index
	if (nFrom == nTo || nFrom < 0 || nTo < 0)
		return FALSE;

	//Copy the row nTo the new index
	InsertItem(nTo, GetItemText(nFrom, 0));
	//If row has been inserted before original
	//increment the original
	if (nFrom > nTo)
		nFrom++;
	//Loop through subitems
	for (int i = 1; i < GetColumnCount(); i++) {
		SetItemText(nTo, i, GetItemText(nFrom, i));
	}

	return TRUE;
}

void CListCtrlEx1::AddRow( const char *qString )
{
   CListCtrlEx1::InsertRow(qString,GetItemCount());
}

void CListCtrlEx1::InsertRow( const char *qString,int nPos )
{
   CString row=qString;
   row.TrimLeft();
   row.TrimRight();
   row+=m_sRowStringDivider;
   CUIntArray iArray;
   iArray.SetSize(m_nColumn);
   int i,j;
   for (i=j=0;i<iArray.GetSize();i++) {
      j=row.Find(m_sRowStringDivider,j);
      if (j<0) return;
      iArray.SetAt(i,j);
      j++;
   }

   if (nPos<0) {
      POSITION position=this->GetFirstSelectedItemPosition();
      nPos= (!position) ? GetItemCount():(int)position-1;
      SetItemState(nPos,0,LVIS_SELECTED);
   }

   LV_ITEM lvi;
   ZeroMemory(&lvi,sizeof(LV_ITEM));
   lvi.mask=LVIF_TEXT;
   lvi.iItem=nPos;
   lvi.iSubItem=j=0;
   i=0;
   j=iArray.GetAt(0);
   CString mid=row.Mid(i,j);
   (LPCTSTR&)lvi.pszText=mid;
   lvi.cchTextMax=strlen(lvi.pszText);
   this->InsertItem(&lvi);
   for (int nIndex=1;nIndex<m_nColumn;nIndex++) {
      lvi.iSubItem=nIndex;
      i=iArray.GetAt(nIndex-1);
      j=iArray.GetAt(nIndex);
      mid=row.Mid(i+1,j-i-1);
      (LPCTSTR&)lvi.pszText=mid;
      lvi.cchTextMax=strlen(lvi.pszText);
      this->SetItem(&lvi);
   }
}
                                 
void CListCtrlEx1::DeleteRows()
{   
   POSITION nPos=this->GetFirstSelectedItemPosition();
   if (nPos==NULL) return;
   int nItem;
   CUIntArray Array;
   while (nPos) {
      nItem=this->GetNextSelectedItem(nPos);
      Array.Add(nItem);
   }
   int nLast;
   while (Array.GetSize()) {
      nLast=Array.GetSize()-1;
      nItem=Array[nLast];
      DeleteItem(nItem);
      SetItemState(nItem,LVIS_SELECTED,LVIS_SELECTED);
      Array.RemoveAt(nLast);
   }
}

void CListCtrlEx1::Clear()
{
   DeleteAllItems();
}

CString CListCtrlEx1::GetRow( int nRow )
{
   CString sReturn,sRow;
   for (int nIndex=0;nIndex<m_nColumn;nIndex++) {
      sRow=GetItemText(nRow,nIndex);
      sRow.TrimLeft();
      sRow.TrimRight();
      sReturn+=sRow;
      sReturn+=m_sRowStringDivider;
   }
   sReturn.TrimRight();
   return sReturn;
}

int CListCtrlEx1::GetRowCount()
{
   return GetItemCount();
}

int CListCtrlEx1::GetColumnCount()
{
   return m_nColumn;
}

void CListCtrlEx1::SetColumnHeaders(int nColumn,LCEX_COLUMHEADER *pColumns)
{
   m_nColumn=nColumn;
   // insert columns
   LV_COLUMN lvc;
   lvc.mask=LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
   for (int nIndex=0;nIndex<m_nColumn;nIndex++) {
      lvc.fmt=LVCFMT_LEFT;
      lvc.cx=pColumns[nIndex].nWidth;
      lvc.pszText=pColumns[nIndex].pLabel;
      lvc.iSubItem=nIndex;
      this->InsertColumn(nIndex,&lvc);
   }
}

