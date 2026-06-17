// GargamelSplitFrameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GargamelSplitFrameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitFrameDialog dialog

CGargamelSplitFrameDialog::CGargamelSplitFrameDialog( CWnd* pParent /*=NULL*/ )
	: CDialog(CGargamelSplitFrameDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGargamelSplitFrameDialog)
	//}}AFX_DATA_INIT
   
   m_sStream.Empty();
   m_sDirectory.Empty();
}


void CGargamelSplitFrameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGargamelSplitFrameDialog)
	DDX_Control(pDX, ID_GARGAMELSPLITCTRL, m_GargamelSplitCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGargamelSplitFrameDialog, CDialog)
	//{{AFX_MSG_MAP(CGargamelSplitFrameDialog)
	ON_BN_CLICKED(ID_ANOTHEROK, OnAnotherok)
	ON_BN_CLICKED(ID_ANOTHERCANCEL, OnAnothercancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitFrameDialog message handlers

BOOL CGargamelSplitFrameDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   if (!m_sStream.IsEmpty()) m_GargamelSplitCtrl.SetSplitScript(m_sStream);
   if (!m_sDirectory.IsEmpty()) m_GargamelSplitCtrl.SetDirectory(m_sDirectory);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGargamelSplitFrameDialog::OnOK()
{
   m_GargamelSplitCtrl.NotifyFlagrantDialogOk();
}

void CGargamelSplitFrameDialog::OnCancel()
{
   m_GargamelSplitCtrl.NotifyFlagrantDialogCancel();
}

void CGargamelSplitFrameDialog::OnAnotherok() 
{
	// TODO: Add your control notification handler code here

   m_sStream=m_GargamelSplitCtrl.GetSplitScript();
   CGargamelSplitFrameDialog::OnOK();
   EndDialog(IDOK);
}

void CGargamelSplitFrameDialog::OnAnothercancel() 
{
	// TODO: Add your control notification handler code here

   m_sStream.Empty();
	EndDialog(IDCANCEL);
}
