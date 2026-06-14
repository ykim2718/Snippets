// GrPathEnvironemntDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "GrPathEnvironmentDialog.h"
#include "../DialogAggregate/DialogAggregate.h"
#include "GetFolder.h"

/////////////////////////////////////////////////////////////////////////////
// CGrPathEnvironmentDialog dialog


CGrPathEnvironmentDialog::CGrPathEnvironmentDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGrPathEnvironmentDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrPathEnvironmentDialog)
	m_sPathOfEditor = _T("");
	m_sPathOfGargamel = _T("");
	m_sPathOfSample = _T("");
	m_sPathOfSmurfette = _T("");
	m_sHomeDirectory = _T("");
	//}}AFX_DATA_INIT
   CWinApp *pApp=AfxGetApp();
   m_sHomeDirectory=
      pApp->GetProfileString(RegKeySettings,RegKeyHomeDirectory);
   m_sPathOfSample=
      pApp->GetProfileString(RegKeySettings,RegKeyExampleFolder);
   m_sPathOfEditor=
      pApp->GetProfileString(RegKeySettings,RegKeyTextViewer);
   m_sPathOfGargamel=
      pApp->GetProfileString(RegKeySettings,RegKeyGargamelFile);
   m_sPathOfSmurfette=
      pApp->GetProfileString(RegKeySettings,RegKeySmurfetteFile);
}

CGrPathEnvironmentDialog::~CGrPathEnvironmentDialog()
{
	CWinApp *pApp=AfxGetApp();
   pApp->WriteProfileString(
      RegKeySettings,RegKeyHomeDirectory,(LPCTSTR)m_sHomeDirectory);
   pApp->WriteProfileString(
      RegKeySettings,RegKeyExampleFolder,(LPCTSTR)m_sPathOfSample);
   pApp->WriteProfileString(
      RegKeySettings,RegKeyTextViewer,(LPCTSTR)m_sPathOfEditor);
   pApp->WriteProfileString(
      RegKeySettings,RegKeyGargamelFile,(LPCTSTR)m_sPathOfGargamel);
   pApp->WriteProfileString(
      RegKeySettings,RegKeySmurfetteFile,(LPCTSTR)m_sPathOfSmurfette);
}

void CGrPathEnvironmentDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrPathEnvironmentDialog)
	DDX_Text(pDX, ID_PATHENV_EDITOR, m_sPathOfEditor);
	DDX_Text(pDX, ID_PATHENV_GARGAMEL, m_sPathOfGargamel);
	DDX_Text(pDX, ID_PATHENV_SAMPLE, m_sPathOfSample);
	DDX_Text(pDX, ID_PATHENV_SMURFETTE, m_sPathOfSmurfette);
	DDX_Text(pDX, ID_PATHENV_HOME, m_sHomeDirectory);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGrPathEnvironmentDialog, CDialog)
	//{{AFX_MSG_MAP(CGrPathEnvironmentDialog)
	ON_BN_CLICKED(ID_PATHENV_EDITOR_BROWSER, OnPathenvEditorBrowser)
	ON_BN_CLICKED(ID_PATHENV_GARGAMEL_BROWSER, OnPathenvGargamelBrowser)
	ON_BN_CLICKED(ID_PATHENV_SAMPLE_BROWSER, OnPathenvSampleBrowser)
	ON_BN_CLICKED(ID_PATHENV_SMURFETTE_BROWSER, OnPathenvSmurfetteBrowser)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_PATHENV_HOME_DIRECTORY, OnPathenvHomeDirectory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrPathEnvironmentDialog message handlers

void CGrPathEnvironmentDialog::OnPathenvHomeDirectory() 
{
	// TODO: Add your control notification handler code here

   int nResult=MessageBox(
      _T("내부 Grapher script에서 Gargamel script (*.in) 파일 (pattern 또는\n"
         "split 파일)을 기술하는 상위 폴더(home directory)를 저장합니다.\n\n"
         "이 상위폴더가 저장되어 있으면, 내부의 Gargamel pattern 파일 또는\n"
         "split 파일의 위치를 내부적으로 기술할 때, 각 path의 상위부분이 선택한\n"
         "상위폴더와 동일할 경우 상위 path를 ~/로 바꾸어서 저장합니다.\n"
         "실행시 ~는 저장한 상위폴더로 대치되어 실행하기 때문에 Gargamel의 \n"
         "pattern또는 split 파일의 위치가 변경되었을 때 상위폴더의 수정만으로\n"
         "Gargamel script의 폴더 수정이 가능하여 손쉽게 동작이 용이합니다\n\n"
         "    그러나, pattern또는 split파일의 path가 자동으로 치환되기\n"
         "때문에 일관성있게 pattern파일과 split 파일에서 치환되지 않습니다. 즉\n"
         "상황에 따라서 pattern파일이나 split 파일 또는 모두에서 치환될 수도\n"
         "있으니 사용에 주의를 요합니다. -_-"),
      NULL,
      MB_ICONEXCLAMATION|MB_OKCANCEL);
   if (nResult==IDCANCEL) return;

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
      m_sHomeDirectory=pPath;
      ::SysFreeString((unsigned short*)pPath);
   }

   UpdateData(FALSE);
}

void CGrPathEnvironmentDialog::OnPathenvSampleBrowser() 
{
	// TODO: Add your control notification handler code here
   CFileDialog fDialog(
      TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "Grapher Files (*.gr)|*.gr|All Files (*.*)|*.*||",
      NULL);
   CString sReturn;
   int bOk=GetFolder( //20030210
      &sReturn,
      _T("Choose the sample folder of Grapher."),
      this->m_hWnd,
      NULL,
      NULL
      );
   if (bOk&&!sReturn.IsEmpty()) m_sPathOfSample=sReturn;
   UpdateData(FALSE);	
}

void CGrPathEnvironmentDialog::OnPathenvEditorBrowser() 
{
   // TODO: Add your control notification handler code here
   CWinApp *pApp=AfxGetApp();
   CFileDialog fDialog(
      TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "Exec Files (*.exe;*.com)|*.exe;*.com|All Files (*.*)|*.*||",
      NULL);
   fDialog.m_ofn.lpstrTitle=_T("외부 Editor 실행파일을 선택하세요.");
   fDialog.DoModal();
   m_sPathOfEditor=fDialog.GetPathName();
   if (m_sPathOfEditor.IsEmpty()) return;
   UpdateData(FALSE);
}

void CGrPathEnvironmentDialog::OnPathenvGargamelBrowser() 
{
	// TODO: Add your control notification handler code here
   CFileDialog fDialog(
      TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "Exec Files (*.exe;*.com)|*.exe;*.com|All Files (*.*)|*.*||",
      NULL);
   fDialog.m_ofn.lpstrTitle=
      _T("Gargamel 실행파일을 선택하세요.");
   fDialog.DoModal();
   m_sPathOfGargamel=fDialog.GetPathName();
   if (m_sPathOfGargamel.IsEmpty()) return;
   UpdateData(FALSE);
}

void CGrPathEnvironmentDialog::OnPathenvSmurfetteBrowser() 
{
	// TODO: Add your control notification handler code here
   CFileDialog fDialog(
      TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "Exec Files (*.exe;*.com)|*.exe;*.com|All Files (*.*)|*.*||",
      NULL);
   fDialog.m_ofn.lpstrTitle=
      _T("Smurfette 실행파일을 선택하세요.");
   fDialog.DoModal();
   m_sPathOfSmurfette=fDialog.GetPathName();
   if (m_sPathOfSmurfette.IsEmpty()) return;
   UpdateData(FALSE);
}

void CGrPathEnvironmentDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	UpdateData(TRUE);
	CDialog::OnClose();
}
