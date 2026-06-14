// GrapherRenovatorDialogPpg.cpp : Implementation of the CGrapherRenovatorDialogPropPage property page class.

#include "stdafx.h"
#include "GrapherRenovatorDialog.h"
#include "GrapherRenovatorDialogPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGrapherRenovatorDialogPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGrapherRenovatorDialogPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CGrapherRenovatorDialogPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGrapherRenovatorDialogPropPage, "GRAPHERRENOVATORDIALOG.GrapherRenovatorDialogPropPage.1",
	0x9ff3ac5c, 0x4612, 0x11d5, 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a)


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogPropPage::CGrapherRenovatorDialogPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGrapherRenovatorDialogPropPage

BOOL CGrapherRenovatorDialogPropPage::CGrapherRenovatorDialogPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GRAPHERRENOVATORDIALOG_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogPropPage::CGrapherRenovatorDialogPropPage - Constructor

CGrapherRenovatorDialogPropPage::CGrapherRenovatorDialogPropPage() :
	COlePropertyPage(IDD, IDS_GRAPHERRENOVATORDIALOG_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CGrapherRenovatorDialogPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogPropPage::DoDataExchange - Moves data between page and properties

void CGrapherRenovatorDialogPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGrapherRenovatorDialogPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherRenovatorDialogPropPage message handlers
