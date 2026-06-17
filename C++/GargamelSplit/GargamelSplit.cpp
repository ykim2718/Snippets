// GargamelSplit.cpp : Implementation of CGargamelSplitApp and DLL registration.

#include "stdafx.h"
#include "GargamelSplit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CGargamelSplitApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x3731efa3, 0xf83d, 0x11d4, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CGargamelSplitApp::InitInstance - DLL initialization

BOOL CGargamelSplitApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.

      //shik96@samsung.co.kr
	  m_pszAppName=_tcsdup(_T("GargamelSplit")); //2002.0913â¬èŒÇµÇ¢
      SetRegistryKey("Y.Kim");
      CoInitialize(NULL);
      //:)
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CGargamelSplitApp::ExitInstance - DLL termination

int CGargamelSplitApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

   //shik96@samsung.co.kr
   CoInitialize(NULL);
   //:)

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
