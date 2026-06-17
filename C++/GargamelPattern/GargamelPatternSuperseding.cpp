// GargamelPatternSuperseding.cpp : implementation file
//

#include "stdafx.h"
#include "GargamelPatternSuperseding.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternSuperseding dialog


CGargamelPatternSuperseding::CGargamelPatternSuperseding(
   CWnd* pParent /*=NULL*/,
   const char *pFindWhat /*=NULL*/,
   const char *pReplaceWith /*=NULL*/
   )
	: CDialog(CGargamelPatternSuperseding::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGargamelPatternSuperseding)
	m_sFindWhat = _T("");
	m_sReplaceWith = _T("");
	m_bFindWhatInAlias = FALSE;
	m_bFindWhatInEquation = FALSE;
	m_bFindWhatInPattern = FALSE; // 2001.0801
	m_bFindWhatInFormat = FALSE;
	m_bFindWhatIn1stNo = FALSE;
	m_bFindWhatInLastNo = FALSE;
	m_bFindWhatInLC = FALSE;
	m_bFindWhatInUC = FALSE;
	//}}AFX_DATA_INIT

   m_sFindWhat=pFindWhat;
	m_sReplaceWith=pReplaceWith;
}


void CGargamelPatternSuperseding::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGargamelPatternSuperseding)
	DDX_Text(pDX, ID_FINDWHAT, m_sFindWhat);
	DDV_MaxChars(pDX, m_sFindWhat, 32);
	DDX_Text(pDX, ID_REPLACEWITH, m_sReplaceWith);
	DDV_MaxChars(pDX, m_sReplaceWith, 32);
	DDX_Check(pDX, ID_FINDWHAT_IN_ALIAS, m_bFindWhatInAlias);
	DDX_Check(pDX, ID_FINDWHAT_IN_EQUATION, m_bFindWhatInEquation);
	DDX_Check(pDX, ID_FINDWHAT_IN_PATTERN, m_bFindWhatInPattern);
	DDX_Check(pDX, ID_FINDWHAT_IN_FORMAT, m_bFindWhatInFormat);
	DDX_Check(pDX, ID_FINDWHAT_IN_1STNO, m_bFindWhatIn1stNo);
	DDX_Check(pDX, ID_FINDWHAT_IN_LASTNO, m_bFindWhatInLastNo);
	DDX_Check(pDX, ID_FINDWHAT_IN_LC, m_bFindWhatInLC);
	DDX_Check(pDX, ID_FINDWHAT_IN_UC, m_bFindWhatInUC);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGargamelPatternSuperseding, CDialog)
	//{{AFX_MSG_MAP(CGargamelPatternSuperseding)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternSuperseding message handlers


BOOL CGargamelPatternSuperseding::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
   CFont *pFont=(this->GetParent())->GetFont();
   this->SetFont(pFont); // Frustrated! Not Work. 2K.0524
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
