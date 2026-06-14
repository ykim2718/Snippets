// Gargamel.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Gargamel.h"
#include "GargamelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "Afxcom_.h"
#include "Execute.h"

/////////////////////////////////////////////////////////////////////////////
// CGargamelApp

BEGIN_MESSAGE_MAP(CGargamelApp, CWinApp)
	//{{AFX_MSG_MAP(CGargamelApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGargamelApp construction

CGargamelApp::CGargamelApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGargamelApp object

CGargamelApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGargamelApp initialization

BOOL CGargamelApp::InitInstance()
{
   //shik96@samsung.co.kr
   AfxEnableControlContainer();

   SetRegistryKey("Y.Kim");
   CoInitialize(NULL);

   HRESULT hResult=::CoCreateInstance(
      IID_ANYFINDCLASS,NULL,CLSCTX_INPROC_SERVER,
      IID_IANYFIND,(void**)&m_pAnyfind);
   if (FAILED(hResult)) {
      switch (hResult) {
      case REGDB_E_CLASSNOTREG :
         AfxMessageBox(
            "yongshik.kim@samsung.com \n\n"
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
            "yongshik.kim@samsung.com \n\n"
            "Watch out ! (hResult=CLASS_E_NOAGGREGATION) \n\n"
            "This class cannot be created as part of an aggregate. ",
            MB_ICONSTOP
            );
         break;
      }
      return FALSE;
   }
   //:)

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CGargamelDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////

int CGargamelApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	//shik96@samsung.co.kr
   CoUninitialize();
   //:)

	return CWinApp::ExitInstance();
}
