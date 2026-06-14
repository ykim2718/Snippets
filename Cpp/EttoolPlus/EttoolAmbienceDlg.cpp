// EttoolAmbienceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EttoolPlus.h"
#include "EttoolAmbienceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEttoolAmbienceDlg dialog


CEttoolAmbienceDlg::CEttoolAmbienceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEttoolAmbienceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEttoolAmbienceDlg)
	m_sPathOfEttool = _T("");
	m_sPathOfM4 = _T("");
	m_sPathOfEditor = _T("");
	//}}AFX_DATA_INIT

   HRESULT hResult=::CoCreateInstance(
      CLSID_FileFolderTreeSelectionDialog,NULL,CLSCTX_INPROC_SERVER,
      IID_IFileFolderTreeSelectionDialog,(void**)&m_pFileFolderTreeSelectionDialog);
   if (FAILED(hResult)) {
      MessageBox("Error, ::CoCreateInstance().",NULL,MB_ICONWARNING);
      m_pFileFolderTreeSelectionDialog=NULL;
   }

   CWinApp* pApp=AfxGetApp();
   m_sPathOfEttool=pApp->GetProfileString(RegKeySettings,RegKeyEttoolFile);
   m_sPathOfM4=pApp->GetProfileString(RegKeySettings,RegKeyM4File);
   m_sPathOfEditor=pApp->GetProfileString(RegKeySettings,RegKeyEditorFile);
}

void CEttoolAmbienceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEttoolAmbienceDlg)
	DDX_Text(pDX, ID_ETTOOL_PATH, m_sPathOfEttool);
	DDX_Text(pDX, ID_M4_PATH, m_sPathOfM4);
	DDX_Text(pDX, ID_EDITOR_PATH, m_sPathOfEditor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEttoolAmbienceDlg, CDialog)
	//{{AFX_MSG_MAP(CEttoolAmbienceDlg)
	ON_BN_CLICKED(ID_APPLY, OnApply)
	ON_BN_CLICKED(ID_ETTOOL_PATH_BROWSER, OnEttoolPathBrowser)
	ON_BN_CLICKED(ID_M4_PATH_BROWSER, OnM4PathBrowser)
	ON_BN_CLICKED(ID_EDITOR_PATH_BROWSER, OnEditorPathBrowser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEttoolAmbienceDlg message handlers

void CEttoolAmbienceDlg::OnApply() 
{
	// TODO: Add your control notification handler code here

   UpdateData(TRUE);

   int nPos;
   nPos=m_sPathOfEttool.ReverseFind('\\');
   if (strnicmp(m_sPathOfEttool,m_sPathOfM4,nPos)) {
      MessageBox(
         "Warning, Both ettool.exe and m4.exe must lie on the same folder !",
         NULL,MB_ICONWARNING);
      return;
   }

   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileString(RegKeySettings,RegKeyEttoolFile,m_sPathOfEttool);
   pApp->WriteProfileString(RegKeySettings,RegKeyM4File,m_sPathOfM4);
   pApp->WriteProfileString(RegKeySettings,RegKeyEditorFile,m_sPathOfEditor);

   CDialog::OnOK();
}

void CEttoolAmbienceDlg::OnEttoolPathBrowser() 
{
	// TODO: Add your control notification handler code here

   UpdateData(TRUE);
   if (!m_pFileFolderTreeSelectionDialog) return;
   m_pFileFolderTreeSelectionDialog->SetFolderSelectionMode(FALSE);
   m_pFileFolderTreeSelectionDialog->DoDialog();
   char *pPath;
   m_pFileFolderTreeSelectionDialog->GetFilePath((unsigned short**)&pPath);
   if (pPath) {
      m_sPathOfEttool=pPath;
      ::SysFreeString((unsigned short*)pPath);
   }
	UpdateData(FALSE);
}

void CEttoolAmbienceDlg::OnM4PathBrowser() 
{
	// TODO: Add your control notification handler code here
	
   UpdateData(TRUE);
   if (!m_pFileFolderTreeSelectionDialog) return;
   m_pFileFolderTreeSelectionDialog->SetFolderSelectionMode(FALSE);
   m_pFileFolderTreeSelectionDialog->DoDialog();
   char *pPath;
   m_pFileFolderTreeSelectionDialog->GetFilePath((unsigned short**)&pPath);
   if (pPath) {
      m_sPathOfM4=pPath;
      ::SysFreeString((unsigned short*)pPath);
   }
	UpdateData(FALSE);
}

void CEttoolAmbienceDlg::OnEditorPathBrowser() 
{
	// TODO: Add your control notification handler code here
	
   UpdateData(TRUE);
   if (!m_pFileFolderTreeSelectionDialog) return;
   m_pFileFolderTreeSelectionDialog->SetFolderSelectionMode(FALSE);
   m_pFileFolderTreeSelectionDialog->DoDialog();
   char *pPath;
   m_pFileFolderTreeSelectionDialog->GetFilePath((unsigned short**)&pPath);
   if (pPath) {
      m_sPathOfEditor=pPath;
      ::SysFreeString((unsigned short*)pPath);
   }
	UpdateData(FALSE);
}
