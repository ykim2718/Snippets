// GargamelSplitDialog.cpp : implementation file
//

#include "stdafx.h"
#include "gargamelsplit.h"
#include "GargamelSplitDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include <io.h> // for _access()
#include "../DialogAggregate/DialogAggregate.h"
#include "Token.h"

static char qThisClassName[]="CGargamelSplitDialog";
static char qFileFilter[]=
   "All Files (*.*)|*.*|Text Files (*.txt)|*.txt|Data Files (*.dat)|*.dat||";

#define ALIAS_MESSAGE_DEFAULT "Alias here"

static
int Compare( const void *arg1, const void *arg2 )
{
   /* Compare all of both strings: */
   return _stricmp( * ( char** ) arg1, * ( char** ) arg2 );
}

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitDialog dialog


CGargamelSplitDialog::CGargamelSplitDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGargamelSplitDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGargamelSplitDialog)
	m_nTailCountForAlias = 0;
	//}}AFX_DATA_INIT

   m_sLastDirectory.Empty();
   m_sLastScriptDirectory.Empty();
   m_sLastScriptOnDestory.Empty();
   m_bCheckFileExistance=TRUE;

   //:)
   HRESULT hResult=NO_ERROR;
   hResult=::CoCreateInstance(
      IID_ANYFINDCLASS,NULL,CLSCTX_INPROC_SERVER,
      IID_IANYFIND,(void**)&m_pAnyfind);
   if (FAILED(hResult)) {
      switch (hResult) {
      case REGDB_E_CLASSNOTREG :
         AfxMessageBox(
            "shik96@samsung.co.kr \n\n"
            "Watch out ! (hResult=REGDB_E_CLASSNOTREG) \n\n"
            "A specified class is not registered in the registration \n"
            "database. Also can indicate that the type of server you \n"
            "requested in the CLSCTX enumeration is not registered or \n"
            "the values for the server types in the registry are corrupt.",
            MB_ICONSTOP
            );
         break;
      case CLASS_E_NOAGGREGATION :
         AfxMessageBox(
            "shik96@samsung.co.kr \n\n"
            "Watch out ! (hResult=CLASS_E_NOAGGREGATION) \n\n"
            "This class cannot be created as part of an aggregate. ",
            MB_ICONSTOP
            );
         break;
      }
      m_pAnyfind=NULL;
   }
   //:)

   CWinApp* pApp=AfxGetApp();
   m_sLastDirectory=pApp->GetProfileString(RegKeySettings,RegKeyLastDirectoryAtSplit);
   m_sLastScriptDirectory=pApp->GetProfileString(RegKeySettings,RegKeyLastScriptDirectoryAtSplit);
   int nCount=pApp->GetProfileInt(RegKeySettings,RegKeyExecCount,0);
   pApp->WriteProfileInt(RegKeySettings,RegKeyExecCount,++nCount);
}

CGargamelSplitDialog::~CGargamelSplitDialog() //shik96
{
   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileString(
      RegKeySettings,RegKeyLastDirectoryAtSplit,m_sLastDirectory);
   pApp->WriteProfileString(
      RegKeySettings,RegKeyLastScriptDirectoryAtSplit,m_sLastScriptDirectory);
}

void CGargamelSplitDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGargamelSplitDialog)
	DDX_Control(pDX, ID_SPLIT_CLEAR, m_MenuButtonClear);
	DDX_Control(pDX, ID_SPLIT_LISTBOX, m_ListBox);
	DDX_Text(pDX, ID_SPLIT_ALIAS_INSERT_TAILCOUNT, m_nTailCountForAlias);
	DDV_MinMaxUInt(pDX, m_nTailCountForAlias, 0, 32);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGargamelSplitDialog, CDialog)
	//{{AFX_MSG_MAP(CGargamelSplitDialog)
	ON_BN_CLICKED(ID_SPLIT_ADD, OnSplitAdd)
	ON_BN_CLICKED(ID_SPLIT_INSERT, OnSplitInsert)
	ON_BN_CLICKED(ID_SPLIT_DELETE, OnSplitDelete)
	ON_BN_CLICKED(ID_SPLIT_CLEAR, OnSplitClear)
	ON_BN_CLICKED(ID_SPLIT_CUTPASTE, OnSplitCutpaste)
	ON_BN_CLICKED(ID_SPLIT_MOVE_UP, OnSplitMoveUp)
	ON_BN_CLICKED(ID_SPLIT_MOVE_DOWN, OnSplitMoveDown)
	ON_BN_CLICKED(ID_SPLIT_SORT, OnSplitSort)
	ON_BN_CLICKED(ID_SPLIT_ALIAS_INSERT, OnSplitAliasInsert)
	ON_NOTIFY(UDN_DELTAPOS, ID_SPLIT_ALIAS_INSERT_TAILCOUNT_SPIN, OnDeltaposSplitAliasInsertTailcountSpin)
	ON_BN_CLICKED(ID_SPLIT_CHANGE_DIRECTORY, OnSplitChangeDirectory)
	ON_BN_CLICKED(ID_SPLIT_READ_FILELIST, OnSplitReadFilelist)
	ON_BN_CLICKED(ID_SPLIT_WRITE_FILELIST, OnSplitWriteFilelist)
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_SPLIT_VIEW_EDITOR, OnSplitViewEditor)
	ON_BN_CLICKED(ID_SPLIT_VIEW, OnSplitView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitDialog message handlers

BOOL CGargamelSplitDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   SetEnableDisableButtons();
   m_ListBox.SetFrameControlOption(0,0); // Nothing for default
   m_ListBox.SetFrameControlOption(DFC_MENU,DFCS_MENUARROWRIGHT|DFCS_FLAT); // 1
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGargamelSplitDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

   m_bCheckFileExistance=FALSE; //2001.0511
   m_sLastScriptOnDestory=GetScriptFromDialog();
}

void CGargamelSplitDialog::SetEnableDisableButtons()
{
   int bEnable=m_ListBox.GetCount();
   GetDlgItem(ID_SPLIT_INSERT)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_DELETE)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_CLEAR)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_CUTPASTE)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_MOVE_UP)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_MOVE_DOWN)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_SORT)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_ALIAS_INSERT)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_ALIAS_INSERT_TAILCOUNT)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_ALIAS_INSERT_TAILCOUNT_SPIN)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_VIEW)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_VIEW_EDITOR)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_CHANGE_DIRECTORY)->EnableWindow(bEnable);
   GetDlgItem(ID_SPLIT_WRITE_FILELIST)->EnableWindow(bEnable);
}

int CGargamelSplitDialog::ListChkAddedBefore(int nIDList, const char *pString)
{
   //LB_FINDSTRINGEXACT
   int nTotal,nIndex,nLength;
   char *pStream;

   CWnd *pList=GetDlgItem(nIDList);
   nTotal=pList->SendMessage(LB_GETCOUNT,0,0);
   if (!nTotal) goto F;
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      nLength=pList->SendMessage(LB_GETTEXTLEN,nIndex,0);
      pStream=new char[(nLength+1)*sizeof(TCHAR)];
      pList->SendMessage(LB_GETTEXT,nIndex,(LPARAM)pStream);
      if (!strcmp(pStream,pString)) {
         delete pStream;
         CString strAddedBefore(pString);
         strAddedBefore+="\n\n"
                         "Already defined in the list.\n"
                         "Do you want add it disregarding this message ?";
         switch (AfxMessageBox((LPCTSTR)strAddedBefore,MB_YESNO|MB_ICONQUESTION)) {
         case IDYES : return IDYES;
         case IDNO  : return IDNO;
         }
      }
      delete pStream;
   }
F: return IDYES;
}

void CGargamelSplitDialog::ListDelete(int nIDList)
{
   int nIndex;
   CWnd *pList=GetDlgItem(nIDList);
   nIndex=pList->SendMessage(LB_GETCURSEL,0,0);
   if (nIndex<0) {
      MessageBox(
         "Choose a position you want to delete. ",
         qThisClassName,
         MB_OK|MB_ICONWARNING);
      return;
   }
   pList->SendMessage(LB_DELETESTRING,nIndex,0);
   CWnd::SendDlgItemMessage(nIDList,LB_SETCURSEL,nIndex,0);
}

void CGargamelSplitDialog::OnSplitAdd() 
{
	// TODO: Add your control notification handler code here

   CFileDialogEx Dialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT,
      qFileFilter);
   Dialog.m_ofn.lpstrInitialDir=(LPCTSTR)m_sLastDirectory;
   CString sTitle;
   sTitle.Format(" Add ... (%s)",(LPCTSTR)m_sLastDirectory);
   Dialog.m_ofn.lpstrTitle=sTitle;
   int nResult=Dialog.DoModal();
   if (nResult==IDCANCEL) return;

   if (!m_ListBox.GetCount()) {
      m_ListBox.AddString(ALIAS_MESSAGE_DEFAULT);
      m_ListBox.SetItemData(0,1);
   }

   POSITION Position;
   int nCount,nIndex;
   char **pTable;
   CString sFile;

   for (Position=Dialog.GetStartPosition(),nCount=0;
        Position;
        Dialog.GetNextPathName(Position),nCount++);
   pTable=new char * [nCount];
   for (Position=Dialog.GetStartPosition(),nIndex=0;
        Position;
        nIndex++) {
      sFile=Dialog.GetNextPathName(Position);
      nResult=ListChkAddedBefore(ID_SPLIT_LISTBOX,(LPCTSTR)sFile);
      if (nResult==IDNO) {
         nCount--;
         continue;
      }
      pTable[nIndex]=new char[sFile.GetLength()+1];
      strcpy(pTable[nIndex],sFile);
   }
   if (!nCount) return;
   qsort((void*)pTable,nCount,sizeof(char*),Compare);
   for (nIndex=0;nIndex<nCount;nIndex++) {
      m_ListBox.AddString(pTable[nIndex]);
      delete pTable[nIndex];
   }
   delete pTable;
   if ((nIndex=sFile.ReverseFind('\\'))!=-1) {
      sFile.Delete(nIndex,sFile.GetLength()-nIndex);
      m_sLastDirectory=sFile;
   }

   SetEnableDisableButtons();
}

void CGargamelSplitDialog::OnSplitInsert() 
{
	// TODO: Add your control notification handler code here

   int nIndex;
   CWnd *pList=GetDlgItem(ID_SPLIT_LISTBOX);
   nIndex=pList->SendMessage(LB_GETCURSEL,0,0);
   if (nIndex<0) {
      MessageBox(
         "Choose a position you want to insert. ",
         qThisClassName,
         MB_OK|MB_ICONWARNING);
      return;
   }
   CFileDialogEx Dialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT,
      qFileFilter);
   if (!m_sLastDirectory.IsEmpty()) {
      Dialog.m_ofn.lpstrInitialDir=(LPCTSTR)m_sLastDirectory;
   }
   if (Dialog.DoModal()==IDCANCEL) return;
   POSITION p=Dialog.GetStartPosition();
   CString sFile;
   while (p) {
      sFile=Dialog.GetNextPathName(p);
      if (sFile.IsEmpty()) return;
      pList->SendMessage(LB_INSERTSTRING,nIndex,(long)(LPCTSTR)sFile);
   }

   if (!sFile.IsEmpty()) {
      int nPos=sFile.ReverseFind('\\');
      if (nPos!=-1) {
         sFile.Delete(nPos,sFile.GetLength()-nPos);
         m_sLastDirectory=sFile;
      }
   }
}

void CGargamelSplitDialog::OnSplitDelete() 
{
	// TODO: Add your control notification handler code here

   CGargamelSplitDialog::ListDelete(ID_SPLIT_LISTBOX);
   SetEnableDisableButtons();
}

void CGargamelSplitDialog::OnSplitClear() 
{
	// TODO: Add your control notification handler code here
	
   CRect Rect;
   GetDlgItem(ID_SPLIT_CLEAR)->GetWindowRect(&Rect);

   CMenu Menu;
   int pMenuID = 0;
   DWORD nSelectionMade;
   VERIFY(Menu.LoadMenu(IDR_CLEAR_LIST_MENU));
   CMenu* pPopup=Menu.GetSubMenu(pMenuID);
   ASSERT(pPopup!=NULL);
   nSelectionMade=pPopup->TrackPopupMenu(
      TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD,
      Rect.right,Rect.top,this);
   pPopup->DestroyMenu();

   switch (nSelectionMade) {
   case IDM_CLEAR_LIST_ALL :
      m_ListBox.ResetContent();
      SetEnableDisableButtons();
      break;
   case IDM_CLEAR_LIST_ALIASES : //Y.Kim,20030204
      int nCount=m_ListBox.GetCount();
      if (!nCount) return;
      for (int bData,nIndex=nCount-1;nIndex>-1;nIndex--) {
         bData=m_ListBox.GetItemData(nIndex);
         if (bData) {
            m_ListBox.DeleteString(nIndex);
         }
      }
      break;
   }
}

void CGargamelSplitDialog::OnSplitCutpaste() 
{
	// TODO: Add your control notification handler code here

   char buttonText[][6]={"Cut","Paste"};
   static int iCut=-1,nTotal;
   int nIndex,i;
   char *pStream;

	CWnd *pList=GetDlgItem(ID_SPLIT_LISTBOX);
   nIndex=pList->SendMessage(LB_GETCURSEL,0,0);
   if (nIndex<0) {
      MessageBox("Choose a position.",qThisClassName,MB_OK|MB_ICONSTOP);
      return;
   }
   if (iCut<0) {
      iCut=nIndex;
R:    nTotal=pList->SendMessage(LB_GETCOUNT,0,0);
      pList->SendMessage(LB_ADDSTRING,nTotal++,(long)"<End>");
      SetDlgItemText(ID_SPLIT_CUTPASTE,buttonText[1]);
      return;
   } else {
      i=pList->SendMessage(LB_GETCOUNT,0,0);
      if (nTotal!=i) {
         nTotal=i;
         MessageBox("Something changed.",qThisClassName,MB_OK|MB_ICONSTOP);
         goto R;
      }
      pList->SendMessage(LB_DELETESTRING,nTotal-1,0);
      i=pList->SendMessage(LB_GETTEXTLEN,iCut,0);
      pStream=new char[(i+1)*sizeof(TCHAR)];
      pList->SendMessage(LB_GETTEXT,iCut,(LPARAM)pStream);
      if (nIndex>iCut) nIndex--;
      pList->SendMessage(LB_DELETESTRING,iCut,0);
      pList->SendMessage(LB_INSERTSTRING,nIndex,(long)(LPCTSTR)pStream);
      SetDlgItemText(ID_SPLIT_CUTPASTE,buttonText[0]);
      iCut=-1;
      delete pStream;
   }
}

void CGargamelSplitDialog::OnSplitMoveUp() 
{
	// TODO: Add your control notification handler code here

   int nItem=m_ListBox.GetCurSel();
   if (nItem==LB_ERR) return;
	m_ListBox.MoveItemUp(nItem);
}

void CGargamelSplitDialog::OnSplitMoveDown() 
{
	// TODO: Add your control notification handler code here
	
   int nItem=m_ListBox.GetCurSel();
   if (nItem==LB_ERR) return;
	m_ListBox.MoveItemDown(nItem);
}

void CGargamelSplitDialog::OnSplitSort() 
{
	// TODO: Add your control notification handler code here

   int nCount=m_ListBox.GetCount();
   if (!nCount) return;
   char **pTable;
   pTable=new char * [nCount];
   CString sReturn;
   int nIndex,nLength,bAlias;
   for (nIndex=0;nIndex<nCount;nIndex++) {
      m_ListBox.GetText(nIndex,sReturn);
      bAlias=m_ListBox.GetItemData(nIndex);
      if (bAlias) sReturn.Insert(0,AF_SPLIT_INDICATOR);
      nLength=sReturn.GetLength();
      pTable[nIndex]=new char[nLength+1];
      strcpy(pTable[nIndex],(LPCTSTR)sReturn);
   }
   qsort((void*)pTable,nCount,sizeof(char*),Compare);
   m_ListBox.ResetContent();
   for (nIndex=0;nIndex<nCount;nIndex++) {
      bAlias=pTable[nIndex][0]==AF_SPLIT_INDICATOR;
      if (bAlias) strcpy(pTable[nIndex],pTable[nIndex]+1);
      m_ListBox.AddString(pTable[nIndex]);
      if (bAlias) m_ListBox.SetItemData(nIndex,1);
      delete pTable[nIndex];
   }
   delete pTable;
}

void CGargamelSplitDialog::OnSplitAliasInsert() 
{
	// TODO: Add your control notification handler code here

   int nCount=m_ListBox.GetCount();
   if (!nCount) return;
   CString sReturn,sAlias;
   int i;

   UpdateData(TRUE);
   if (m_nTailCountForAlias) {
      sReturn.Format(
         "Now, I will insert an automatic alias pString into the front of each row.\n"
         "Alias pString will be the right part of each row with a size of %d.\n"
         "\n"
         "Can I proceed on this way ?",
         m_nTailCountForAlias);
      switch (MessageBox((LPCTSTR)sReturn,qThisClassName,MB_YESNO|MB_ICONQUESTION)) {
      case IDYES : break;
      default : return;
      }
      CString lfString=_T("");
      for (i=0;i<nCount;i++) {
         m_ListBox.GetText(i,sReturn);
         sReturn.TrimLeft();
         if (sReturn[0]==AF_SPLIT_INDICATOR) continue;
         lfString+="\n"+sReturn;
      }
      m_ListBox.ResetContent();
      i=0;
      CToken Token(lfString,"\n");
      while (Token.IsNext()) {
         sReturn=Token.GetNextToken();
         sAlias=sReturn.Right(m_nTailCountForAlias);
         sAlias.Insert(0," ");
         sAlias.Insert(0,AF_SPLIT_INDICATOR);
         m_ListBox.InsertString(i++,(LPCTSTR)sAlias);
         m_ListBox.InsertString(i++,(LPCTSTR)sReturn);
      }
      return;
   }

   int nIndex=m_ListBox.GetCurSel();
   if (nIndex<0) nIndex=0;

   if ((i=(nIndex-1))>=0) {
      m_ListBox.GetText(i,sReturn);
      sReturn.TrimLeft();
      if (sReturn[0]==AF_SPLIT_INDICATOR) return;
   }
   if ((i=nIndex)<nCount) {
      m_ListBox.GetText(i,sReturn);
      sReturn.TrimLeft();
      if (sReturn[0]==AF_SPLIT_INDICATOR) return;
   }
   sReturn.Format(ALIAS_MESSAGE_DEFAULT);

   m_ListBox.InsertString(nIndex,(LPCTSTR)sReturn);
   m_ListBox.SetItemData(nIndex,1);
}

void CGargamelSplitDialog::OnDeltaposSplitAliasInsertTailcountSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
   switch (pNMUpDown->iDelta) {
   case -1 : m_nTailCountForAlias++;break;
   case +1 : m_nTailCountForAlias--;break;
   }
   if (m_nTailCountForAlias<0) m_nTailCountForAlias=0;
   if (m_nTailCountForAlias>32) m_nTailCountForAlias=0;
   UpdateData(FALSE);

	*pResult = 0;
}

void CGargamelSplitDialog::OnSplitViewEditor() 
{
	// TODO: Add your control notification handler code here
	
   CFileDialogEx Dialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "Exec Files (*.exe;*.com)|*.exe;*.com|All Files (*.*)|*.*||",
      NULL);
   Dialog.m_ofn.lpstrTitle=_T("외부 Editor 실행파일을 선택하세요.");
   Dialog.DoModal();
   CString sExecute=Dialog.GetPathName();
   if (sExecute.IsEmpty()) return;
   AfxGetApp()->WriteProfileString(RegKeySettings,RegKeyTextViewer,(LPCTSTR)sExecute);
}

void CGargamelSplitDialog::OnSplitChangeDirectory() 
{
	// TODO: Add your control notification handler code here

   int nTotal=m_ListBox.GetCount();
   if (!nTotal) return;

   IFileFolderTreeSelectionDialog* pFileFolderTreeSelectionDialog;
   HRESULT hResult=::CoCreateInstance(
      CLSID_FileFolderTreeSelectionDialog,NULL,CLSCTX_INPROC_SERVER,
      IID_IFileFolderTreeSelectionDialog,(void**)&pFileFolderTreeSelectionDialog);
   if (FAILED(hResult)) {
      MessageBox(
         "Error, ::CoCreateInstance() for CLSID_FileFolderTreeSelectionDialog:IID_IFileFolderTreeSelectionDialog",
         qThisClassName,MB_ICONWARNING);
      return;
   }

   int nIndex,nPos;
   CString sReturn(""),sRight;

   for (nIndex=0,nPos=-1;nIndex<nTotal && nPos<0;nIndex++) {
      m_ListBox.GetText(nIndex,sReturn);
      nPos=sReturn.ReverseFind('\\');
      if (nPos<0) sReturn.Empty();
      else        sReturn.Delete(nPos,sReturn.GetLength()-nPos);
   }
   BSTR pInitialDirectory=sReturn.AllocSysString();
   pFileFolderTreeSelectionDialog->SetInitialDirectory(pInitialDirectory);
   ::SysFreeString((unsigned short*)pInitialDirectory);
   pFileFolderTreeSelectionDialog->SetFolderSelectionMode(TRUE);
   int nResult=pFileFolderTreeSelectionDialog->DoDialog();
   if (nResult==IDCANCEL) return;

   char *pPath;
   pFileFolderTreeSelectionDialog->GetFolderPath((unsigned short**)&pPath);
   if (!pPath) return;
   CString sNewPath=pPath;
   ::SysFreeString((unsigned short*)pPath);

   for (nIndex=0;nIndex<nTotal;nIndex++) {
      m_ListBox.GetText(nIndex,sReturn);
      nPos=sReturn.ReverseFind('\\');
      if (nPos<0) continue;
      sRight=sReturn.Right(sReturn.GetLength()-nPos);
      sRight.Insert(0,(LPCTSTR)sNewPath);
      m_ListBox.DeleteString(nIndex);
      m_ListBox.InsertString(nIndex,(LPCTSTR)sRight);
   }
}

void CGargamelSplitDialog::OnSplitReadFilelist() 
{
	// TODO: Add your control notification handler code here
	
   if (!m_pAnyfind) return;
	
	CFileDialogEx Dialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "Gargamel Input Files (*.in)|*.in|All Files (*.*)|*.*||");
   Dialog.m_ofn.lpstrInitialDir=(LPCTSTR)m_sLastScriptDirectory;
   if (Dialog.DoModal()==IDCANCEL) return;

   CString sFile=Dialog.GetPathName();
   if (sFile.IsEmpty()) return;
   CFile hFile(sFile,CFile::modeRead);
   int nLength=hFile.GetLength();
   char *pStream=new char[nLength*sizeof(TCHAR)];
   hFile.ReadHuge(pStream,nLength);
   hFile.Close();

   char *sDumpFileName,*lfsPattern,*lfsSplit;
   int nSearchType,nColumnarMatrixType,bNumericAlias,nPostProcessType;
   int nResult=m_pAnyfind->_AFGetParametersFromScript(
      pStream,
      &sDumpFileName,
      &nSearchType,&nColumnarMatrixType,&bNumericAlias,
      &nPostProcessType,
      &lfsPattern,&lfsSplit);
   delete pStream;
   if (!nResult) {
      MessageBox("Error, script file is invalid.",qThisClassName,MB_OK|MB_ICONSTOP);
      return;
   }

   SetScriptToDialog(lfsSplit);
   
   m_pAnyfind->_AFReleaseString(sDumpFileName);
   m_pAnyfind->_AFReleaseString(lfsPattern);
   m_pAnyfind->_AFReleaseString(lfsSplit);

   if (!sFile.IsEmpty()) {
      int nPos=sFile.ReverseFind('\\');
      if (nPos!=-1) {
         sFile.Delete(nPos,sFile.GetLength()-nPos);
         m_sLastScriptDirectory=sFile;
      }
   }

   SetEnableDisableButtons();
}

BOOL CGargamelSplitDialog::WriteCurrentListToAFile(const char *qFile)
{
   if (!qFile || !strlen(qFile)) return FALSE;

   char *sDumpFileName,*lfsPattern,*lfsSplit;
   int nSearchType,nColumnarMatrixType,bNumericAlias,nPostProcessType;
   int nResult,nCount;
   CString sReturn,sScript;
   char *pInScript,*pOutScript;
   CFile hFile;
   
   if (!hFile.Open(qFile,CFile::modeRead)) return FALSE;
   nCount=hFile.GetLength();
   pInScript=new char[nCount*sizeof(TCHAR)];
   hFile.ReadHuge(pInScript,nCount);
   hFile.Close();
   nResult=m_pAnyfind->_AFGetParametersFromScript(
      pInScript,
      &sDumpFileName,
      &nSearchType,&nColumnarMatrixType,&bNumericAlias,
      &nPostProcessType,
      &lfsPattern,&lfsSplit);
   delete pInScript;
   if (!nResult) {
      MessageBox("Error, script file is invalid.",qThisClassName,MB_OK|MB_ICONSTOP);
      return FALSE;
   }

   m_pAnyfind->_AFPutParametersIntoScript(
      &pOutScript,
      "made by CGargamelSplitDialog",sDumpFileName,
      nSearchType,nColumnarMatrixType,bNumericAlias,nPostProcessType,
      lfsPattern,(LPCTSTR)GetScriptFromDialog());      
   m_pAnyfind->_AFReleaseString(sDumpFileName);
   m_pAnyfind->_AFReleaseString(lfsPattern);
   m_pAnyfind->_AFReleaseString(lfsSplit);
   sScript=pOutScript;
   m_pAnyfind->_AFReleaseString(pOutScript);
   if (!hFile.Open(qFile,CFile::modeWrite)) return FALSE;
   hFile.WriteHuge(sScript,sScript.GetLength());
   hFile.Close();

   return TRUE;
}

void CGargamelSplitDialog::OnSplitWriteFilelist() 
{
	// TODO: Add your control notification handler code here

   CRect Rect;
   GetDlgItem(ID_SPLIT_WRITE_FILELIST)->GetWindowRect(&Rect);

   //http://codeguru.earthweb.com/menu/track_popup.shtml
   //Using CMenu::TrackPopupMenu as an Immediate Function 
   //This article was contributed by Randy More. 
   CMenu menu;
   int pMenuID = 0;
   DWORD SelectionMade;
   VERIFY(menu.LoadMenu(IDR_WRITE_LIST_MENU));

   CMenu* pPopup = menu.GetSubMenu(pMenuID);
   ASSERT(pPopup != NULL);

   POINT pp;
   //GetCursorPos(&pp);
   pp.x=Rect.right;
   pp.y=Rect.top;
   SelectionMade = pPopup->TrackPopupMenu(
      TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD,
      pp.x,pp.y,this);
   
   pPopup->DestroyMenu();

   if (SelectionMade==IDM_WRITE_LIST_TO_A_FILE ||
       SelectionMade==IDM_WRITE_LIST_TO_FILES) {
      CString sListBox=GetScriptFromDialog();
      if (sListBox.IsEmpty()) {
         MessageBox("Warning, Enrolled file list is empty !",qThisClassName,MB_ICONWARNING);
         return;
      }
      if (SelectionMade==IDM_WRITE_LIST_TO_A_FILE) {
         CFileDialogEx Dialog(TRUE,NULL,NULL,
            OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
            "Gargamel Script Files (*.in)|*.in|All files (*.*)|*.*||");
         Dialog.m_ofn.lpstrInitialDir=(LPCTSTR)m_sLastScriptDirectory;
         CString sTitle;
         sTitle.Format(" Write ... (%s)",(LPCTSTR)m_sLastScriptDirectory);
         Dialog.m_ofn.lpstrTitle=sTitle;
         if (Dialog.DoModal()==IDCANCEL) return;
         WriteCurrentListToAFile(Dialog.GetPathName());
      } else if (SelectionMade==IDM_WRITE_LIST_TO_FILES) {
         CWriteFileListToSynchronize Dialog(this);
         Dialog.DoModal();
      }
   }
}

void CGargamelSplitDialog::SetScriptToDialog(const CString &Stream)
{
   UpdateData(FALSE);
   m_ListBox.ResetContent();
   if (Stream.IsEmpty()) { /*
      GetDlgItem(ID_SPLIT_INS)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_DEL)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_CLEAR)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_MOVEUP)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_MOVEDOWN)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_SORT)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_READ_FILELIST)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_WRITE_FILELIST)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_CHANGEDIRECTORY)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_ALIASINSERT_TAILCOUNT)->EnableWindow(FALSE);
      GetDlgItem(ID_SPLIT_ALIASINSERT)->EnableWindow(FALSE); */
      return;
   } else { /*
      GetDlgItem(ID_SPLIT_INS)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_DEL)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_CLEAR)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_MOVEUP)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_MOVEDOWN)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_SORT)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_READ_FILELIST)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_WRITE_FILELIST)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_CHANGEDIRECTORY)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_ALIASINSERT_TAILCOUNT)->EnableWindow(TRUE);
      GetDlgItem(ID_SPLIT_ALIASINSERT)->EnableWindow(TRUE); */
   }

   //Y.Kim,20030204
   CToken Token(Stream,"\n");
   CString sItem;
   BOOL bAlias;
   m_ListBox.ResetContent();
   while (Token.IsNext()) {
      sItem=Token.GetNextToken();
      sItem.TrimLeft();
      sItem.TrimRight();
      bAlias=false;
      if (sItem[0]==AF_SPLIT_INDICATOR) {
         sItem.Delete(0);
         sItem.TrimLeft();
         bAlias=true;
      }
      m_ListBox.AddString((LPCTSTR)sItem);
      if (bAlias) m_ListBox.SetItemData(m_ListBox.GetCount()-1,1);
   }
   //m_ListBox.SetCurSel( 0 );

   SetEnableDisableButtons(); //2001.0409
   m_bCheckFileExistance=TRUE; //2001.0511
}

CString CGargamelSplitDialog::GetScriptFromDialog()
{
   int nCount=m_ListBox.GetCount();
   if (!nCount) return _T("");

   CString sReturn=_T(""),sLine,sTemp;
   int bAlias; //Y.Kim,20030204
   int nResult; //Y.Kim,20030215

   for (int nIndex=0;nIndex<nCount;nIndex++) {
      m_ListBox.GetText(nIndex,sLine);
      bAlias=m_ListBox.GetItemData(nIndex);
      sLine.TrimLeft();
      sLine.TrimRight();
      if (sLine.IsEmpty()) continue;
      if (m_bCheckFileExistance && !bAlias && _access(sLine,0)==-1) {
         sTemp="Warning, the named file does not exist or is not accessible :\n";
         sTemp+=sLine;
         sTemp+="\n\nDo you want to check the other files ?";
         nResult=MessageBox(sTemp,qThisClassName,MB_ICONWARNING|MB_YESNO);
         m_bCheckFileExistance=nResult==IDYES;
      }
      if (bAlias) sLine.Insert(0,AF_SPLIT_INDICATOR);
      sReturn+="\n"+sLine;
   }

   int bFirst=1;
   int bAliasFound=0;
   CToken Token(sReturn,"\n");
   sReturn=_T("");
   while (Token.IsNext()) {
      sLine=Token.GetNextToken();
      sLine.TrimLeft();
      sLine.TrimRight();
      if (sLine.IsEmpty()) continue;
      if (bFirst) {
         bFirst=0;
         if (sLine[0]!=AF_SPLIT_INDICATOR) {
            /* 2001.0207
            MessageBox(
               "Warning, first row must be a \"alias\" string !",
               qThisClassName,MB_ICONWARNING);
            */
            const char *qInsertAliasHere="< Alias first";
            m_ListBox.InsertString(0,qInsertAliasHere);
            sReturn.Insert(0,"\n");
            sReturn.Insert(0,qInsertAliasHere);
            // return; 2K.1025
         }
      } else {
         int nNext=Token.GetNextTokenCount();
         if (nNext==0
            && sLine[0]==AF_SPLIT_INDICATOR) {
            MessageBox(
               "Warning, The last row must not be a \"alias\" string !\n"
               "It will be removed automatically.",
               qThisClassName,MB_ICONWARNING);
            continue;
         }
      }
      if (sLine[0]==AF_SPLIT_INDICATOR) {
         if (bAliasFound) {
            MessageBox(
               "Warning, Subsequent row could not be \"alias\" simultaneously ! \n"
               "Followings after the first will be ignored.",
               qThisClassName,MB_ICONWARNING); //|MB_YESNO);
            continue;
         }
         sTemp=sLine.Mid(1,sLine.GetLength()-1);
         if (sTemp.IsEmpty()) {
            MessageBox(
               "Warning, There is a vacant \"alias\" !\n"
               "\"null\" string will be added after '<'",
               qThisClassName,MB_ICONWARNING);
            sLine+=" null";
         }
      }
      switch (sLine[0]) {
      case AF_SPLIT_INDICATOR : bAliasFound=1;break;
      default  : bAliasFound=0;break;
      }
      sReturn+=sLine;
      sReturn+="\r\n";
   }

   sReturn.TrimRight();
   return sReturn;
}

void CGargamelSplitDialog::OnSplitView() 
{
	// TODO: Add your control notification handler code here
	
   int nResult=m_ListBox.GetCurSel();
   if (nResult==LB_ERR) return;
   CString sReturn;
   m_ListBox.GetText(nResult,sReturn);

   CFile File;
   if (!File.Open(sReturn,CFile::modeRead)) {
      MessageBox(
         "Warning, file open error have happened.",
         qThisClassName,MB_ICONEXCLAMATION);
      return;
   }
   File.Close();

   CWinApp *pApp=AfxGetApp();
   CString sExecute=pApp->GetProfileString(RegKeySettings,RegKeyTextViewer);
   if (sExecute.IsEmpty()) {
      MessageBox(
         "Warning, you should enroll the viewer before.",
         qThisClassName,MB_ICONEXCLAMATION);
      CGargamelSplitDialog::OnSplitViewEditor();
   }
   sExecute+=" "+sReturn;
   WinExec((LPCTSTR)sExecute,SW_SHOWDEFAULT);
}
