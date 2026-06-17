// GargamelSplitPpg.cpp : Implementation of the CGargamelSplitPropPage property page class.

#include "stdafx.h"
#include "GargamelSplit.h"
#include "GargamelSplitPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGargamelSplitPropPage, COlePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGargamelSplitPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CGargamelSplitPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGargamelSplitPropPage, "GARGAMELSPLIT.GargamelSplitPropPage.1",
	0x3731efa7, 0xf83d, 0x11d4, 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a)


/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitPropPage::CGargamelSplitPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGargamelSplitPropPage

BOOL CGargamelSplitPropPage::CGargamelSplitPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GARGAMELSPLIT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitPropPage::CGargamelSplitPropPage - Constructor

CGargamelSplitPropPage::CGargamelSplitPropPage() :
	COlePropertyPage(IDD, IDS_GARGAMELSPLIT_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CGargamelSplitPropPage)
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitPropPage::DoDataExchange - Moves data between page and properties

void CGargamelSplitPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGargamelSplitPropPage)
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitPropPage message handlers





