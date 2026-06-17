// GargamelPatternForMatrixCtl.cpp : Implementation of the CGargamelPatternForMatrixCtrl ActiveX Control class.

#include "stdafx.h"
#include "GargamelPatternForMatrix.h"
#include "GargamelPatternForMatrixCtl.h"
#include "GargamelPatternForMatrixPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGargamelPatternForMatrixCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGargamelPatternForMatrixCtrl, COleControl)
	//{{AFX_MSG_MAP(CGargamelPatternForMatrixCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CGargamelPatternForMatrixCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CGargamelPatternForMatrixCtrl)
	DISP_PROPERTY_EX(CGargamelPatternForMatrixCtrl, "PatternForMatrixScript", GetPatternForMatrixScript, SetPatternForMatrixScript, VT_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CGargamelPatternForMatrixCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CGargamelPatternForMatrixCtrl, COleControl)
	//{{AFX_EVENT_MAP(CGargamelPatternForMatrixCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGargamelPatternForMatrixCtrl, 1)
	PROPPAGEID(CGargamelPatternForMatrixPropPage::guid)
END_PROPPAGEIDS(CGargamelPatternForMatrixCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGargamelPatternForMatrixCtrl, "GARGAMELPATTERNFORMATRIX.GargamelPatternForMatrixCtrl.1",
	0x941c461f, 0x8ba3, 0x406a, 0xb0, 0x9b, 0x98, 0xd4, 0xc3, 0x9f, 0xc5, 0x24)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CGargamelPatternForMatrixCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGargamelPatternForMatrix =
		{ 0x2025cfcd, 0x58a, 0x4b3e, { 0xab, 0x84, 0xaf, 0x1d, 0x84, 0x53, 0xeb, 0xa6 } };
const IID BASED_CODE IID_DGargamelPatternForMatrixEvents =
		{ 0x90158d30, 0xc775, 0x404f, { 0x99, 0x2e, 0x40, 0x2f, 0xf, 0x92, 0x56, 0x83 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGargamelPatternForMatrixOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGargamelPatternForMatrixCtrl, IDS_GARGAMELPATTERNFORMATRIX, _dwGargamelPatternForMatrixOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixCtrl::CGargamelPatternForMatrixCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGargamelPatternForMatrixCtrl

BOOL CGargamelPatternForMatrixCtrl::CGargamelPatternForMatrixCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_GARGAMELPATTERNFORMATRIX,
			IDB_GARGAMELPATTERNFORMATRIX,
			afxRegApartmentThreading,
			_dwGargamelPatternForMatrixOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixCtrl::CGargamelPatternForMatrixCtrl - Constructor

CGargamelPatternForMatrixCtrl::CGargamelPatternForMatrixCtrl()
{
	InitializeIIDs(&IID_DGargamelPatternForMatrix, &IID_DGargamelPatternForMatrixEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixCtrl::~CGargamelPatternForMatrixCtrl - Destructor

CGargamelPatternForMatrixCtrl::~CGargamelPatternForMatrixCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixCtrl::OnDraw - Drawing function

void CGargamelPatternForMatrixCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	
   //Y.Kim,20030207
   if (m_Dialog.GetSafeHwnd()) { // for running
	   m_Dialog.MoveWindow(rcBounds,true);
   } else { // for coding
      pdc->FillRect(rcBounds,CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
      pdc->Ellipse(rcBounds);
      CRect Rect(rcBounds);
      Rect.DeflateRect(10,10);
      pdc->DrawText("Y.Kim/43360207",&Rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixCtrl::DoPropExchange - Persistence support

void CGargamelPatternForMatrixCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixCtrl::OnResetState - Reset control to default state

void CGargamelPatternForMatrixCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixCtrl::AboutBox - Display an "About" box to the user

void CGargamelPatternForMatrixCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_GARGAMELPATTERNFORMATRIX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixCtrl message handlers

int CGargamelPatternForMatrixCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

   //Y.Kim,20030207
   m_Dialog.Create(IDD_GARGAMEL_PATTERNFORMATRIX,this);

	return 0;
}

BSTR CGargamelPatternForMatrixCtrl::GetPatternForMatrixScript() 
{
	CString strResult;
	// TODO: Add your property handler here

   int bVisible=::IsWindow(m_Dialog.m_hWnd)&&m_Dialog.IsWindowVisible();
   strResult=bVisible ? m_Dialog.GetScriptFromDialog():m_Dialog.m_sLastScriptOnDestory;

   //
	return strResult.AllocSysString();
}

void CGargamelPatternForMatrixCtrl::SetPatternForMatrixScript(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

   m_Dialog.SetScriptToDialog(lpszNewValue);

   //
	SetModifiedFlag();
}
