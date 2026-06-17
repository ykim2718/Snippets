// GargamelSplitCtl.cpp : Implementation of the CGargamelSplitCtrl ActiveX Control class.

#include "stdafx.h"
#include "GargamelSplit.h"
#include "GargamelSplitCtl.h"
#include "GargamelSplitPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGargamelSplitCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGargamelSplitCtrl, COleControl)
	//{{AFX_MSG_MAP(CGargamelSplitCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CGargamelSplitCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CGargamelSplitCtrl)
	DISP_PROPERTY_EX(CGargamelSplitCtrl, "SplitScript", GetSplitScript, SetSplitScript, VT_BSTR)
	DISP_FUNCTION(CGargamelSplitCtrl, "NotifyFlagrantDialogOk", NotifyFlagrantDialogOk, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGargamelSplitCtrl, "NotifyFlagrantDialogCancel", NotifyFlagrantDialogCancel, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGargamelSplitCtrl, "SetDirectory", SetDirectory, VT_EMPTY, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CGargamelSplitCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CGargamelSplitCtrl, COleControl)
	//{{AFX_EVENT_MAP(CGargamelSplitCtrl)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGargamelSplitCtrl, 1)
	PROPPAGEID(CGargamelSplitPropPage::guid)
END_PROPPAGEIDS(CGargamelSplitCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGargamelSplitCtrl, "GARGAMELSPLIT.GargamelSplitCtrl.1",
	0x3731efa6, 0xf83d, 0x11d4, 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CGargamelSplitCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGargamelSplit =
		{ 0x3731efa4, 0xf83d, 0x11d4, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };
const IID BASED_CODE IID_DGargamelSplitEvents =
		{ 0x3731efa5, 0xf83d, 0x11d4, { 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGargamelSplitOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGargamelSplitCtrl, IDS_GARGAMELSPLIT, _dwGargamelSplitOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitCtrl::CGargamelSplitCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGargamelSplitCtrl

BOOL CGargamelSplitCtrl::CGargamelSplitCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GARGAMELSPLIT,
			IDB_GARGAMELSPLIT,
			afxRegApartmentThreading,
			_dwGargamelSplitOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitCtrl::CGargamelSplitCtrl - Constructor

CGargamelSplitCtrl::CGargamelSplitCtrl()
{
	InitializeIIDs(&IID_DGargamelSplit, &IID_DGargamelSplitEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitCtrl::~CGargamelSplitCtrl - Destructor

CGargamelSplitCtrl::~CGargamelSplitCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitCtrl::OnDraw - Drawing function

void CGargamelSplitCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);

   if (m_Dialog.GetSafeHwnd()) { // runtime 
	  m_Dialog.MoveWindow(rcBounds,TRUE);
   } else { // design time (do not use m_Dialog)
      pdc->FillRect(rcBounds,CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
      pdc->Ellipse(rcBounds);
      CRect Rect(rcBounds);
      Rect.DeflateRect(10,10);
      pdc->DrawText("shik96@samsung.co.kr/2001-2",&Rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
   }
}

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitCtrl::DoPropExchange - Persistence support

void CGargamelSplitCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitCtrl::OnResetState - Reset control to default state

void CGargamelSplitCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitCtrl::AboutBox - Display an "About" box to the user

void CGargamelSplitCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_GARGAMELSPLIT);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitCtrl message handlers

int CGargamelSplitCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
   m_Dialog.Create(IDD_GARGAMEL_SPLIT,this); //shik96

	return 0;
}

BSTR CGargamelSplitCtrl::GetSplitScript() 
{
	CString strResult;
	// TODO: Add your property handler here

   int bVisible=::IsWindow(m_Dialog.m_hWnd)&&m_Dialog.IsWindowVisible();
   strResult=bVisible ? m_Dialog.GetScriptFromDialog():m_Dialog.m_sLastScriptOnDestory;

   // TODO: Add before this. shik96
	return strResult.AllocSysString();
}

void CGargamelSplitCtrl::SetSplitScript(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

   m_Dialog.SetScriptToDialog(lpszNewValue);

	SetModifiedFlag();
}

void CGargamelSplitCtrl::NotifyFlagrantDialogOk() 
{
	// TODO: Add your dispatch handler code here

   if (!m_Dialog.m_ListBox.m_pEdit) return;
   if (!m_Dialog.m_ListBox.m_pEdit->IsWindowVisible()) return;
   m_Dialog.m_ListBox.EndEditing(FALSE);

}

void CGargamelSplitCtrl::NotifyFlagrantDialogCancel() 
{
	// TODO: Add your dispatch handler code here

   if (!m_Dialog.m_ListBox.m_pEdit) return;
   if (!m_Dialog.m_ListBox.m_pEdit->IsWindowVisible()) return;
   m_Dialog.m_ListBox.EndEditing(TRUE);

}

void CGargamelSplitCtrl::SetDirectory(LPCTSTR qPath) 
{
	// TODO: Add your dispatch handler code here

   m_Dialog.m_sLastDirectory=qPath;
}

