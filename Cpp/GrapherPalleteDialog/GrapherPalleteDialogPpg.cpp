// GrapherPalleteDialogPpg.cpp : Implementation of the CGrapherPalleteDialogPropPage property page class.

#include "stdafx.h"
#include "GrapherPalleteDialog.h"
#include "GrapherPalleteDialogPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGrapherPalleteDialogPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGrapherPalleteDialogPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CGrapherPalleteDialogPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGrapherPalleteDialogPropPage, "GRAPHERPALLETEDIALOG.GrapherPalleteDialogPropPage.1",
	0xf24c34d, 0x4552, 0x11d5, 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a)


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogPropPage::CGrapherPalleteDialogPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGrapherPalleteDialogPropPage

BOOL CGrapherPalleteDialogPropPage::CGrapherPalleteDialogPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GRAPHERPALLETEDIALOG_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogPropPage::CGrapherPalleteDialogPropPage - Constructor

CGrapherPalleteDialogPropPage::CGrapherPalleteDialogPropPage() :
	COlePropertyPage(IDD, IDS_GRAPHERPALLETEDIALOG_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CGrapherPalleteDialogPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogPropPage::DoDataExchange - Moves data between page and properties

void CGrapherPalleteDialogPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGrapherPalleteDialogPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CGrapherPalleteDialogPropPage message handlers
