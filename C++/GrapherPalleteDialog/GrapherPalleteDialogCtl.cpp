// GrapherPalleteDialogCtl.cpp : Implementation of the CGrapherPalleteDialogCtrl ActiveX Control class.

#include "stdafx.h"
#include "GrapherPalleteDialog.h"
#include "GrapherPalleteDialogCtl.h"
#include "GrapherPalleteDialogPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGrapherPalleteDialogCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGrapherPalleteDialogCtrl, COleControl)
	//{{AFX_MSG_MAP(CGrapherPalleteDialogCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CGrapherPalleteDialogCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CGrapherPalleteDialogCtrl)
	DISP_FUNCTION(CGrapherPalleteDialogCtrl, "DoModal", DoModal, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CGrapherPalleteDialogCtrl, COleControl)
	//{{AFX_EVENT_MAP(CGrapherPalleteDialogCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGrapherPalleteDialogCtrl, 1)
	PROPPAGEID(CGrapherPalleteDialogPropPage::guid)
END_PROPPAGEIDS(CGrapherPalleteDialogCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGrapherPalleteDialogCtrl, "GRAPHERPALLETEDIALOG.GrapherPalleteDialogCtrl.1",
	0xf24c34c, 0x4552, 0x11d5, 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CGrapherPalleteDialogCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGrapherPalleteDialog =
		{ 0xf24c34a, 0x4552, 0x11d5, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };
const IID BASED_CODE IID_DGrapherPalleteDialogEvents =
		{ 0xf24c34b, 0x4552, 0x11d5, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGrapherPalleteDialogOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGrapherPalleteDialogCtrl, IDS_GRAPHERPALLETEDIALOG, _dwGrapherPalleteDialogOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogCtrl::CGrapherPalleteDialogCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGrapherPalleteDialogCtrl

BOOL CGrapherPalleteDialogCtrl::CGrapherPalleteDialogCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GRAPHERPALLETEDIALOG,
			IDB_GRAPHERPALLETEDIALOG,
			afxRegApartmentThreading,
			_dwGrapherPalleteDialogOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogCtrl::CGrapherPalleteDialogCtrl - Constructor

CGrapherPalleteDialogCtrl::CGrapherPalleteDialogCtrl()
{
	InitializeIIDs(&IID_DGrapherPalleteDialog, &IID_DGrapherPalleteDialogEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogCtrl::~CGrapherPalleteDialogCtrl - Destructor

CGrapherPalleteDialogCtrl::~CGrapherPalleteDialogCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogCtrl::OnDraw - Drawing function

void CGrapherPalleteDialogCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogCtrl::DoPropExchange - Persistence support

void CGrapherPalleteDialogCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
// For information on using these flags, please see MFC technical note
// #nnn, "Optimizing an ActiveX Control".
DWORD CGrapherPalleteDialogCtrl::GetControlFlags()
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
// CGrapherPalleteDialogCtrl::OnResetState - Reset control to default state

void CGrapherPalleteDialogCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogCtrl message handlers

#include "GrPalleteDialog.h"

void CGrapherPalleteDialogCtrl::DoModal() 
{
	// TODO: Add your dispatch handler code here

   CGrPalleteDialog Dialog(AfxGetMainWnd());
   Dialog.DoModal();
}
