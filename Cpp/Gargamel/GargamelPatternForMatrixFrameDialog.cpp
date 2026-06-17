// GargamelPatternForMatrixFrameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "gargamel.h"
#include "GargamelPatternForMatrixFrameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Y.Kim,20020206

#include "GargamelTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixFrameDialog dialog


CGargamelPatternForMatrixFrameDialog::CGargamelPatternForMatrixFrameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGargamelPatternForMatrixFrameDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGargamelPatternForMatrixFrameDialog)
	//}}AFX_DATA_INIT
}


void CGargamelPatternForMatrixFrameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGargamelPatternForMatrixFrameDialog)
	DDX_Control(pDX, ID_GARGAMEL_PATTERNFORMATRIX_OCX, m_GargamelPatternForMatrixOcx);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGargamelPatternForMatrixFrameDialog, CDialog)
	//{{AFX_MSG_MAP(CGargamelPatternForMatrixFrameDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP

   //Y.Kim,20030206
   ON_REGISTERED_MESSAGE(GargamelUpdateDataMessage,OnGargamelUpdateData)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixFrameDialog message handlers

void CGargamelPatternForMatrixFrameDialog::OnGargamelUpdateData(WPARAM wParam, LPARAM lParam)
{
   switch (wParam) {
   case true:  GetScript(m_sStream);break; // MyUpdateDataTrue
   case false: SetScript(m_sStream);break; // MyUpdateDataFalse
   }
}

void CGargamelPatternForMatrixFrameDialog::SetScript(const CString &sForwarding)
{
   m_GargamelPatternForMatrixOcx.SetPatternForMatrixScript(sForwarding);
}

void CGargamelPatternForMatrixFrameDialog::GetScript(CString &sReturn)
{
   sReturn=m_GargamelPatternForMatrixOcx.GetPatternForMatrixScript();
}
