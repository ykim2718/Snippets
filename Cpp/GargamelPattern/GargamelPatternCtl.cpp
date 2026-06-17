// GargamelPatternCtl.cpp : Implementation of the CGargamelPatternCtrl ActiveX Control class.

#include "stdafx.h"
#include "GargamelPattern.h"
#include "GargamelPatternCtl.h"
#include "GargamelPatternPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGargamelPatternCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGargamelPatternCtrl, COleControl)
	//{{AFX_MSG_MAP(CGargamelPatternCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CGargamelPatternCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CGargamelPatternCtrl)
	DISP_PROPERTY_EX(CGargamelPatternCtrl, "PatternScript", GetPatternScript, SetPatternScript, VT_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CGargamelPatternCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CGargamelPatternCtrl, COleControl)
	//{{AFX_EVENT_MAP(CGargamelPatternCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGargamelPatternCtrl, 1)
	PROPPAGEID(CGargamelPatternPropPage::guid)
END_PROPPAGEIDS(CGargamelPatternCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGargamelPatternCtrl, "GARGAMELPATTERN.GargamelPatternCtrl.1",
	0x33406922, 0xf75f, 0x11d4, 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CGargamelPatternCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGargamelPattern =
		{ 0x33406939, 0xf75f, 0x11d4, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };
const IID BASED_CODE IID_DGargamelPatternEvents =
		{ 0x3340693a, 0xf75f, 0x11d4, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGargamelPatternOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGargamelPatternCtrl, IDS_GARGAMELPATTERN, _dwGargamelPatternOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternCtrl::CGargamelPatternCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGargamelPatternCtrl

BOOL CGargamelPatternCtrl::CGargamelPatternCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GARGAMELPATTERN,
			IDB_GARGAMELPATTERN,
			afxRegApartmentThreading,
			_dwGargamelPatternOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternCtrl::CGargamelPatternCtrl - Constructor

CGargamelPatternCtrl::CGargamelPatternCtrl()
{
	InitializeIIDs(&IID_DGargamelPattern, &IID_DGargamelPatternEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternCtrl::~CGargamelPatternCtrl - Destructor

CGargamelPatternCtrl::~CGargamelPatternCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternCtrl::OnDraw - Drawing function

void CGargamelPatternCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternCtrl::DoPropExchange - Persistence support

void CGargamelPatternCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternCtrl::OnResetState - Reset control to default state

void CGargamelPatternCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternCtrl::AboutBox - Display an "About" box to the user

void CGargamelPatternCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_GARGAMELPATTERN);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternCtrl message handlers

CGargamelPatternPropPage* g_pGargamelPattern=NULL;

BSTR CGargamelPatternCtrl::GetPatternScript() 
{
	CString strResult;
	// TODO: Add your property handler here

   ASSERT(g_pGargamelPattern);
   strResult=g_pGargamelPattern->GetScriptFromDialog();

   // TODO: Add before this. shik96
	return strResult.AllocSysString();
}

void CGargamelPatternCtrl::SetPatternScript(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

   //Error Fatal Crucial Trying Provoking Annoying ...
   //CGargamelPatternPropPage *pOLEPage=(CGargamelPatternPropPage*)GetParent();
   //pOLEPage->m_sStream.Empty();
   //pOLEPage->m_sStream=lpszNewValue;

   ASSERT(g_pGargamelPattern);
   g_pGargamelPattern->SetScriptToDialog(lpszNewValue,FALSE);

   // TODO: Add before this. shik96
	SetModifiedFlag();
}


