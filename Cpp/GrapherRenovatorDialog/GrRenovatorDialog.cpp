// GrRenovatorDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "GrRenovatorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "FileDialogEx.h"
#include "str++.h"
#include "plotse.h"

#include "..\DialogAggregate\DialogAggregate.h" // Automatic use of precompiled headers : stdafx.h
#include "..\DialogAggregate\DialogAggregate_i.c" //shik96,2001.0511 since above.

/////////////////////////////////////////////////////////////////////////////
// CGrRenovatorDialog dialog


CGrRenovatorDialog::CGrRenovatorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGrRenovatorDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrRenovatorDialog)
	m_sOutFolder = _T("");
	//}}AFX_DATA_INIT
   m_sDirectory.Empty();
}


void CGrRenovatorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrRenovatorDialog)
	DDX_Control(pDX, ID_RENOVATOR_LISTCTRL, m_ListCtrlEx2);
	DDX_Text(pDX, ID_RENOVATOR_OUTFOLDER, m_sOutFolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrRenovatorDialog, CDialog)
	//{{AFX_MSG_MAP(CGrRenovatorDialog)
	ON_BN_CLICKED(ID_RENOVATOR_ADD, OnRenovatorAdd)
	ON_BN_CLICKED(ID_RENOVATOR_DELETE, OnRenovatorDelete)
	ON_BN_CLICKED(ID_RENOVATOR_OUTFOLDER_BROWSER, OnRenovatorOutfolderBrowser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrRenovatorDialog message handlers

BOOL CGrRenovatorDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   for (int nIndex=0;nIndex<N_BUTTONS;nIndex++)
		VERIFY(Buttons[nIndex].AutoLoad(ID_BUTTON_MIN+nIndex,this));
   
   LCEX_COLUMHEADER Columns[]={{"Before",300},{"After",300}};
   int nColumn=sizeof(Columns)/sizeof(Columns[0]);
   m_ListCtrlEx2.SetColumnHeaders(nColumn,Columns);
   m_ListCtrlEx2.SetExtendedStyle(
      LVS_EX_FULLROWSELECT | 
      LVS_EX_ONECLICKACTIVATE | 
      LVS_EX_UNDERLINEHOT );
      //LVS_EX_GRIDLINES);

	m_SmallImageList.Create(IDB_SMALLICONS, 16, 1, RGB(255, 255, 255));
	m_SmallImageList.SetOverlayImage(2, 1);
   m_ListCtrlEx2.SetImageList(&m_SmallImageList,LVSIL_SMALL);

   GetDlgItem(ID_RENOVATOR_PROGRESS)->ShowWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrRenovatorDialog::OnRenovatorAdd() 
{
	// TODO: Add your control notification handler code here

   char qGrapherFilter[]="Grapher Script Files (*.gr)|*.gr||";
   char qGargamelFilter[]="Gargamel Script Files (*.in)|*.in||";
   char *pFilter;
   CString sReturn;

   int nSelection=m_ListCtrlEx2.GetFirstSelectedRowIndex();
   if (nSelection>=0) {
      sReturn=m_ListCtrlEx2.GetRow(nSelection);
      sReturn.MakeReverse();
      sReturn.TrimLeft();
      if (tolower(sReturn[1])=='g') {
         MessageBox(
            "Warning, .. \n\nCould not replace Grapher file that is already fixed up by Renovator !",
            "CGrRenovatorDialog",
            MB_ICONEXCLAMATION);
         return;
      }
      pFilter=qGargamelFilter;
   } else {
      sReturn.Empty();
      pFilter=qGrapherFilter;
   }

	CFileDialogEx Dialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      pFilter,AfxGetMainWnd());
   Dialog.m_ofn.lpstrInitialDir=(LPCTSTR)m_sDirectory;
   int nResponse=Dialog.DoModal();
	if (nResponse!=IDOK) return;
   CString sFile=Dialog.GetPathName();

   if (nSelection>=0) {
      ASSERT(pFilter==qGargamelFilter);
      m_ListCtrlEx2.SetItemText(nSelection,1,sFile);
   } else {
      int nRow=m_ListCtrlEx2.GetItemCount();
      LV_ITEM lvi_Grapher;
      lvi_Grapher.mask=LVIF_TEXT|LVIF_IMAGE;//|LVIF_STATE;
      lvi_Grapher.iItem=nRow;
      lvi_Grapher.iSubItem=0;
      lvi_Grapher.pszText=(char*)(LPCTSTR)sFile;
      lvi_Grapher.iImage=1;
      //lvi_Grapher.stateMask=LVIS_STATEIMAGEMASK;
      //lvi_Grapher.state=INDEXTOSTATEIMAGEMASK(1);
      m_ListCtrlEx2.InsertItem(&lvi_Grapher);

      CString sFileShort(sFile);
      int nPos=sFileShort.ReverseFind('\\');
      sFileShort.Delete(0,nPos);
      m_ListCtrlEx2.SetItemText(nRow,1,sFileShort);
      
      CFile File;
      File.Open(sFile,CFile::modeRead);
      int nScript=File.GetLength();
      char *pScript=new char[nScript];
      File.ReadHuge(pScript,nScript);
      File.Close();
      
      LV_ITEM lvi_Gargamel;
      lvi_Gargamel.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_INDENT;
      lvi_Gargamel.iItem=FALSE;
      lvi_Gargamel.iSubItem=0;
      lvi_Gargamel.pszText=(char*)FALSE;
      lvi_Gargamel.iImage=2;
      lvi_Gargamel.iIndent=1;
      char *pAddr;
      CToken Token(NULL,"|");
      CString sReturn;
      for (int nIndex=1;;nIndex++) {
         pAddr=(char*)SEGetOptionValueString(
            NULL,pScript,
            PLOTSCRIPT_BEGINNING,1,
            PLOTSCRIPT_GLOB,1,
            PLOTSCRIPT_EXEC,1,"file=",nIndex,
            0);
         if (!pAddr) {
            delete pScript;
            if (nIndex==1) m_ListCtrlEx2.DeleteItem(nRow);
            return;
         }
         Token=pAddr;
         myFree(pAddr);
         sReturn=Token.GetTokenByIndex(1);
         sReturn.TrimLeft();
         sReturn.TrimRight();
         lvi_Gargamel.iItem=nRow+nIndex;
         lvi_Gargamel.pszText=(char*)(LPCTSTR)sReturn;
         m_ListCtrlEx2.InsertItem(&lvi_Gargamel);
      }
   }
}

void CGrRenovatorDialog::OnRenovatorDelete() 
{
	// TODO: Add your control notification handler code here
	
}


void CGrRenovatorDialog::OnRenovatorOutfolderBrowser() 
{
	// TODO: Add your control notification handler code here

   CoInitialize(NULL);
   IFileFolderTreeSelectionDialog* pDialog;
   HRESULT hResult=::CoCreateInstance(
      CLSID_FileFolderTreeSelectionDialog,NULL,CLSCTX_INPROC_SERVER,
      IID_IFileFolderTreeSelectionDialog,(void**)&pDialog);
   if (FAILED(hResult)) {
      MessageBox(
         "Error, ::CoCreateInstance() for IFileFolderTreeSelectionDialog:IID_IFileFolderTreeSelectionDialog",
         NULL,MB_ICONWARNING);
      CoUninitialize();
      return;
   }
   pDialog->SetFolderSelectionMode(TRUE);
   pDialog->DoDialog();
   char *pPath;
   pDialog->GetFolderPath((unsigned short**)&pPath);
   CoUninitialize();

   if (pPath) {
      m_sOutFolder=pPath;
      ::SysFreeString((unsigned short*)pPath);
      UpdateData(FALSE);
   }
}
