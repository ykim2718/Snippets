// GrapherDoc.cpp : implementation of the CGrapherDoc class
//

#include "stdafx.h"
#include "Grapher.h"

#include "GrapherDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrapherDoc

IMPLEMENT_DYNCREATE(CGrapherDoc, CDocument)

BEGIN_MESSAGE_MAP(CGrapherDoc, CDocument)
	//{{AFX_MSG_MAP(CGrapherDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrapherDoc construction/destruction

CGrapherDoc::CGrapherDoc()
{
	// TODO: add one-time construction code here
}

CGrapherDoc::~CGrapherDoc()
{
}

BOOL CGrapherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGrapherDoc serialization

void CGrapherDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGrapherDoc diagnostics

#ifdef _DEBUG
void CGrapherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrapherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGrapherDoc commands

