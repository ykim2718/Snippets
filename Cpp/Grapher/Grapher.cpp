// Grapher.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Grapher.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "GrapherDoc.h"
#include "GrapherView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include <tlhelp32.h>
#include <process.h>

#include <afxadv.h> // CRecentFileList .... shik96

#include "FileDialogEx.h"
#include "winspool.h"  // for ::OpenPrinter(),::DocumentProperties()
#include "GrPathEnvironmentDialog.h"
#include "GrPlotMixerDialog.h"
#include "GrHistoryDialog.h"
#include "GrapherPalleteDialog.h" // ACTIVE_X
#include "GrapherRenovatorDialog.h" // ACTIVE_X

#include "plotse.h"

/////////////////////////////////////////////////////////////////////////////
// CGrapherApp

BEGIN_MESSAGE_MAP(CGrapherApp, CWinApp)
	//{{AFX_MSG_MAP(CGrapherApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDM_PALLETE, OnPallete)
	ON_COMMAND(IDM_PREFERENCE, OnPreference)
	ON_COMMAND(IDM_GARGAMEL, OnGargamel)
	ON_COMMAND(IDM_BRAINY, OnBrainy)
	ON_COMMAND(IDM_SMURFETTE, OnSmurfette)
	ON_COMMAND(IDM_GRPLOT_WIZARD_THRUGARGAMEL, OnGrplotWizardThruGargamel)
	ON_COMMAND(IDM_GR_MIXER, OnGrMixder)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(IDM_HISTORY, OnHistory)
	ON_COMMAND(IDM_GR_RENOVATOR, OnGrRenovator)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
   // shik96
   ON_COMMAND_RANGE(IDM_SAMPLE0,IDM_SAMPLE7,OnSample)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrapherApp construction

CGrapherApp::CGrapherApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

   m_PlotWizardDialogModeless=0; // modeless dialog
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGrapherApp object

CGrapherApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGrapherApp initialization

BOOL CGrapherApp::InitInstance()
{
   //shik96
   SetRegistryKey("Y.Kim");
   if (IsAnotherExecutingAlready()) {
      AfxMessageBox(
         "Warning, another process is already executing. \n"
         "This program is designed to allow only one copy at a time. \n\n"
         "Could not work ! \n\n"
         "^o^",
         MB_ICONWARNING);
      return TRUE;
   }

   AfxEnableControlContainer();

   int nCount=GetProfileInt(RegKeySettings,RegKeyExecCount,0);
   WriteProfileInt(RegKeySettings,RegKeyExecCount,++nCount);
   WriteProfileString(RegKeySettings,RegKeyVersion,"1999.9-20030423");

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	//SetRegKey(_T("Local AppWizard-Generated Applications")); shik96

	LoadStdProfileSettings(9);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_CHILDFRAME,
		RUNTIME_CLASS(CGrapherDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CGrapherView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

   // BCMenu
   // This code replaces the MFC created menus with the Ownerdrawn versions 
   pDocTemplate->m_hMenuShared=pMainFrame->NewMenu();
   pMainFrame->m_hMenuDefault=pMainFrame->NewMenuDefault();
   // This simulates a window being opened if you don't have
   // a default window displayed at startup
   pMainFrame->OnUpdateFrameMenu(pMainFrame->m_hMenuDefault);

   // Change the initial directory  2001.0420-0421
   CString sFolder=*(m_pRecentFileList[0].m_arrNames);
   if (!sFolder.IsEmpty()) {
      int nPos=sFolder.ReverseFind('\\');
      sFolder.Delete(nPos,sFolder.GetLength()-nPos);
      SetCurrentDirectory(sFolder);
   }

   // 2001.0803
   EnableShellOpen();
   RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGrapherApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   CString sVersion=AfxGetApp()->GetProfileString(RegKeySettings,RegKeyVersion);
   if (sVersion.IsEmpty()) return TRUE;
   GetDlgItem(ID_GRAPHER_VERSION)->SetWindowText(sVersion);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CGrapherApp message handlers


void CGrapherApp::SetPageOrientation(BOOL isLandscape)
{
   // Get default printer settings.
   PRINTDLG   pd;

   pd.lStructSize = (DWORD) sizeof(PRINTDLG);
   if (GetPrinterDeviceDefaults(&pd)) {
      // Lock memory handle.
      DEVMODE FAR* pDevMode =(DEVMODE FAR*)::GlobalLock(m_hDevMode);
      LPDEVNAMES lpDevNames;
      LPTSTR lpszDriverName, lpszDeviceName, lpszPortName;
      HANDLE hPrinter;

      if (pDevMode) {
         // Change printer settings in here.
         pDevMode->dmOrientation = isLandscape ? DMORIENT_LANDSCAPE:DMORIENT_PORTRAIT;
         // Unlock memory handle.
         lpDevNames = (LPDEVNAMES)GlobalLock(pd.hDevNames);
         lpszDriverName = (LPTSTR )lpDevNames + lpDevNames->wDriverOffset;
         lpszDeviceName = (LPTSTR )lpDevNames + lpDevNames->wDeviceOffset;
         lpszPortName   = (LPTSTR )lpDevNames + lpDevNames->wOutputOffset;

         ::OpenPrinter(lpszDeviceName, &hPrinter, NULL);
         ::DocumentProperties(NULL,hPrinter,lpszDeviceName,pDevMode,
            pDevMode, DM_IN_BUFFER|DM_OUT_BUFFER);

         // Sync the pDevMode.
         // See SDK help for DocumentProperties for more info.
         ::ClosePrinter(hPrinter);
         ::GlobalUnlock(m_hDevNames);
         ::GlobalUnlock(m_hDevMode);
      }
   }
}

BOOL CGrapherApp::IsAnotherExecutingAlready()
{
   CWinApp *pApp=AfxGetApp();
   unsigned int nPID=pApp->GetProfileInt(RegKeySettings,RegKeyProcessID,0);
   unsigned int nCurrentPID=GetCurrentProcessId();
   if (nPID && nPID!=nCurrentPID) {
      HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
      PROCESSENTRY32 pe32={0};
      pe32.dwSize=sizeof(PROCESSENTRY32);
      if (Process32First(hSnapShot,&pe32)) {
         do {
            if (pe32.th32ProcessID==nPID) {
               CString sAppName(AfxGetAppName());
               CString sExec(pe32.szExeFile);
               int nPos=sExec.ReverseFind('\\');
               if (nPos) sExec.Delete(0,nPos+1);
               sAppName.MakeLower();
               sExec.MakeLower();
               if (sExec.Find(sAppName)==0) {
                  CloseHandle(hSnapShot);
                  return TRUE;
               }
            }
         } while (Process32Next(hSnapShot,&pe32)); 
      }
      CloseHandle(hSnapShot);
   }
   pApp->WriteProfileInt(RegKeySettings,RegKeyProcessID,nCurrentPID);
   return FALSE;
}

CString CGrapherApp::GetPathOfSmurfette()
{
   CWinApp *pApp=AfxGetApp();
   CString sPath=pApp->GetProfileString(RegKeySettings,RegKeySmurfetteFile);
   if (sPath.IsEmpty()) {
      AfxMessageBox(_T("Smurfette 실행파일을 먼저 선택하세요."),MB_ICONEXCLAMATION);
      CGrPathEnvironmentDialog Dialog;
      Dialog.DoModal();
      sPath=pApp->GetProfileString(RegKeySettings,RegKeySmurfetteFile);
   }
   return sPath;
}

CString CGrapherApp::GetPathOfGargamel()
{
   CWinApp *pApp=AfxGetApp();
   CString sPath=pApp->GetProfileString(RegKeySettings,RegKeyGargamelFile);
   if (sPath.IsEmpty()) {
      AfxMessageBox(_T("Gargamel 실행파일을 먼저 선택하세요."),MB_ICONEXCLAMATION);
      CGrPathEnvironmentDialog Dialog;
      Dialog.DoModal();
      sPath=pApp->GetProfileString(RegKeySettings,RegKeyGargamelFile);
   }
   return sPath;
}

CString CGrapherApp::GetPathOfHome()
{
   CString sPath=
      this->GetProfileString(RegKeySettings,RegKeyHomeDirectory);
   return sPath;
}

void CGrapherApp::OnGargamel() 
{
	// TODO: Add your command handler code here
	CString sPath=this->GetPathOfGargamel();
   if (sPath.IsEmpty()) return;
   WinExec((LPCTSTR)sPath,SW_SHOWDEFAULT);	
}

void CGrapherApp::OnSmurfette() 
{
	// TODO: Add your command handler code here
	CString sPath=this->GetPathOfSmurfette();
   if (sPath.IsEmpty()) return;
   WinExec((LPCTSTR)sPath,SW_SHOWDEFAULT);
}

void CGrapherApp::OnBrainy() 
{
	// TODO: Add your command handler code here
	
}

void CGrapherApp::OnSample(UINT nID)
{
   CString sPath=GetProfileString(RegKeySettings,RegKeyExampleFolder);
   if (sPath.IsEmpty()) {
      AfxMessageBox(
         "Warning, Enroll the folder where samples (demo[0123456].gr) are before using it !",
         MB_ICONEXCLAMATION);
      CGrPathEnvironmentDialog Dialog;
      Dialog.DoModal();
      sPath=GetProfileString(RegKeySettings,RegKeyExampleFolder);
      if (sPath.IsEmpty()) return;
   }
   CString sFile;
   switch (nID) {
   case IDM_SAMPLE0 : sFile="demo0.gr";break;
   case IDM_SAMPLE1 : sFile="demo1.gr";break;
   case IDM_SAMPLE2 : sFile="demo2.gr";break;
   case IDM_SAMPLE3 : sFile="demo3.gr";break;
   case IDM_SAMPLE4 : sFile="demo4.gr";break;
   case IDM_SAMPLE5 : sFile="demo5.gr";break;
   case IDM_SAMPLE6 : sFile="demo6.gr";break;
   case IDM_SAMPLE7 : sFile="demo7.gr";break;
   }
   sFile.Insert(0,"\\");
   sFile.Insert(0,(LPCTSTR)sPath);
   CFile File;
   int bResult=File.Open((LPCTSTR)sFile,CFile::modeRead);
   if (!bResult) {
      WriteProfileString(RegKeySettings,RegKeyExampleFolder,0);
      return;
   }
   File.Close();

   OpenDocumentFile((LPCTSTR)sFile);
}

void CGrapherApp::OnPallete() 
{
	// TODO: Add your command handler code here

   CGrapherPalleteDialog Dialog;
   int nResult=Dialog.Create(NULL,NULL,CRect(0,0,0,0),AfxGetMainWnd(),1);
   if (nResult) Dialog.DoModal();
}

void CGrapherApp::OnPreference() 
{
   // TODO: Add your command handler code here
   //CDialog Dialog(IDD_GR_PATH_ENVIRONMENT);
   CGrPathEnvironmentDialog Dialog;
   Dialog.DoModal();
}

void CGrapherApp::OnGrplotWizardThruGargamel() 
{
   // TODO: Add your command handler code here
   //CGrPlotWizard dlg(this);
   //dlg.DoModal();
   if (m_PlotWizardDialogModeless == NULL) {
		m_PlotWizardDialogModeless = new CGrPlotWizard();
      m_PlotWizardDialogModeless->Create();
   } else
		m_PlotWizardDialogModeless->SetActiveWindow();
   m_PlotWizardDialogModeless->ShowWindow(SW_SHOW);
}

void CGrapherApp::OnGrMixder() 
{
	// TODO: Add your command handler code here

   CGrPlotMixerDialog Dialog;
   Dialog.DoModal();
}

void CGrapherApp::OnGrRenovator() 
{
	// TODO: Add your command handler code here
	
   CGrapherRenovatorDialog Dialog;
   Dialog.Create(NULL,NULL,CRect(0,0,0,0),AfxGetMainWnd(),1);
   int nResult=Dialog.DoModal();
}

void CGrapherApp::OnFileOpen() 
{
	// TODO: Add your command handler code here

   CMDIFrameWnd *pFrame;
   CMDIChildWnd *pChild;
   CGrapherView *pView;
   pFrame=(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
   if (pFrame) {
      pChild=(CMDIChildWnd*)pFrame->GetActiveFrame();
      if (pChild) {
         pView=(CGrapherView*)pChild->GetActiveView();
         if (pView) {
            pView->OnFileOpenByAlien();
            return;
         }
      }
   }

   CString sDirectory;
   sDirectory=GetProfileString(RegKeyRecentFileList,RegKeyRecentFile1);
   if (!sDirectory.IsEmpty()) {
      int nPos=sDirectory.ReverseFind('\\');
      if (nPos!=-1) {
         sDirectory.Delete(nPos,sDirectory.GetLength()-nPos);
      }
   }
   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "Grapher Script Files (*.gr)|*.gr|All Files (*.*)|*.*||",NULL);
   fDialog.m_ofn.lpstrInitialDir=sDirectory;
   fDialog.DoModal();
   CString sFile=fDialog.GetPathName();
   if (sFile.IsEmpty()) return;
   OpenDocumentFile((LPCTSTR)sFile);
}

void CGrapherApp::OnHistory() 
{
	// TODO: Add your command handler code here
	CGrHistoryDialog Dialog;
   Dialog.DoModal();
}
