// GrapherRenovatorDialogCtl.cpp : Implementation of the CGrapherRenovatorDialogCtrl ActiveX Control class.

#include "stdafx.h"
#include "GrapherRenovatorDialog.h"
#include "GrapherRenovatorDialogCtl.h"
#include "GrapherRenovatorDialogPpg.h"

#include "GrRenovatorDialog.h" //shik96


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGrapherRenovatorDialogCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGrapherRenovatorDialogCtrl, COleControl)
	//{{AFX_MSG_MAP(CGrapherRenovatorDialogCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CGrapherRenovatorDialogCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CGrapherRenovatorDialogCtrl)
	DISP_FUNCTION(CGrapherRenovatorDialogCtrl, "DoModal", DoModal, VT_I4, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CGrapherRenovatorDialogCtrl, COleControl)
	//{{AFX_EVENT_MAP(CGrapherRenovatorDialogCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGrapherRenovatorDialogCtrl, 1)
	PROPPAGEID(CGrapherRenovatorDialogPropPage::guid)
END_PROPPAGEIDS(CGrapherRenovatorDialogCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGrapherRenovatorDialogCtrl, "GRAPHERRENOVATORDIALOG.GrapherRenovatorDialogCtrl.1",
	0x9ff3ac45, 0x4612, 0x11d5, 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CGrapherRenovatorDialogCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGrapherRenovatorDialog =
		{ 0x9ff3ac5a, 0x4612, 0x11d5, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };
const IID BASED_CODE IID_DGrapherRenovatorDialogEvents =
		{ 0x9ff3ac5b, 0x4612, 0x11d5, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGrapherRenovatorDialogOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGrapherRenovatorDialogCtrl, IDS_GRAPHERRENOVATORDIALOG, _dwGrapherRenovatorDialogOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogCtrl::CGrapherRenovatorDialogCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGrapherRenovatorDialogCtrl

BOOL CGrapherRenovatorDialogCtrl::CGrapherRenovatorDialogCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GRAPHERRENOVATORDIALOG,
			IDB_GRAPHERRENOVATORDIALOG,
			afxRegApartmentThreading,
			_dwGrapherRenovatorDialogOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogCtrl::CGrapherRenovatorDialogCtrl - Constructor

CGrapherRenovatorDialogCtrl::CGrapherRenovatorDialogCtrl()
{
	InitializeIIDs(&IID_DGrapherRenovatorDialog, &IID_DGrapherRenovatorDialogEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogCtrl::~CGrapherRenovatorDialogCtrl - Destructor

CGrapherRenovatorDialogCtrl::~CGrapherRenovatorDialogCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogCtrl::OnDraw - Drawing function

void CGrapherRenovatorDialogCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogCtrl::DoPropExchange - Persistence support

void CGrapherRenovatorDialogCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
// For information on using these flags, please see MFC technical note
// #nnn, "Optimizing an ActiveX Control".
DWORD CGrapherRenovatorDialogCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// The control can activate without creating a window.
	// TODO: when writing the control's message handlers, avoid using
	//		the m_hWnd member variable without first checking that its
	//		value is non-NULL.
	dwFlags |= windowlessActivate;
	return dwFlags;
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogCtrl::OnResetState - Reset control to default state

void CGrapherRenovatorDialogCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogCtrl message handlers

long CGrapherRenovatorDialogCtrl::DoModal() 
{
	// TODO: Add your dispatch handler code here

   CGrRenovatorDialog Dialog(AfxGetMainWnd());
   return (long)Dialog.DoModal();
}
