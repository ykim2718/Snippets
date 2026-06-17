// GargamelPattern.cpp : Implementation of CGargamelPatternApp and DLL registration.

#include "stdafx.h"
#include "GargamelPattern.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CGargamelPatternApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x33406938, 0xf75f, 0x11d4, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CGargamelPatternApp::InitInstance - DLL initialization

BOOL CGargamelPatternApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.

      //shik96@samsung.co.kr
	   m_pszAppName=_tcsdup(_T("GargamelPattern")); //2002.0913â¬èŒÇµÇ¢
      SetRegistryKey(_T("Y.Kim"));
      CoInitialize(NULL);
      //:)
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CGargamelPatternApp::ExitInstance - DLL termination

int CGargamelPatternApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

   //shik96@samsung.co.kr
   CoUninitialize();
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
