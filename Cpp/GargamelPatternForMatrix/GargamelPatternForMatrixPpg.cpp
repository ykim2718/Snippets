// GargamelPatternForMatrixPpg.cpp : Implementation of the CGargamelPatternForMatrixPropPage property page class.

#include "stdafx.h"
#include "GargamelPatternForMatrix.h"
#include "GargamelPatternForMatrixPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGargamelPatternForMatrixPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGargamelPatternForMatrixPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CGargamelPatternForMatrixPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGargamelPatternForMatrixPropPage, "GARGAMELPATTERNFORMATRIX.GargamelPatternForMatrixPropPage.1",
	0xc42835b7, 0x22d7, 0x42a4, 0x90, 0x1b, 0x27, 0xe4, 0x92, 0x85, 0x8f, 0xe0)


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixPropPage::CGargamelPatternForMatrixPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGargamelPatternForMatrixPropPage

BOOL CGargamelPatternForMatrixPropPage::CGargamelPatternForMatrixPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GARGAMELPATTERNFORMATRIX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixPropPage::CGargamelPatternForMatrixPropPage - Constructor

CGargamelPatternForMatrixPropPage::CGargamelPatternForMatrixPropPage() :
	COlePropertyPage(IDD, IDS_GARGAMELPATTERNFORMATRIX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CGargamelPatternForMatrixPropPage)
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixPropPage::DoDataExchange - Moves data between page and properties

void CGargamelPatternForMatrixPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGargamelPatternForMatrixPropPage)
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixPropPage message handlers

