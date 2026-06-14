// SmallFontAttrDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "SmallFontAttrDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmallFontAttrDialog dialog


CSmallFontAttrDialog::CSmallFontAttrDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSmallFontAttrDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmallFontAttrDialog)
	m_sAlignment = _T("");
	m_nAngle = 0;
	m_nHeight = 10;
	m_nWidth = 5;
	//}}AFX_DATA_INIT
   m_nY=m_nX=0;
}


void CSmallFontAttrDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmallFontAttrDialog)
	DDX_CBString(pDX, ID_FONTD_ALIGNMENT, m_sAlignment);
	DDV_MaxChars(pDX, m_sAlignment, 2);
	DDX_Text(pDX, ID_FONTD_ANGLE, m_nAngle);
	DDV_MinMaxUInt(pDX, m_nAngle, 0, 360);
	DDX_Text(pDX, ID_FONTD_HEIGHT, m_nHeight);
	DDV_MinMaxUInt(pDX, m_nHeight, 1, 64);
	DDX_Text(pDX, ID_FONTD_WIDTH, m_nWidth);
	DDV_MinMaxUInt(pDX, m_nWidth, 1, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSmallFontAttrDialog, CDialog)
	//{{AFX_MSG_MAP(CSmallFontAttrDialog)
	ON_BN_CLICKED(IDD_GR_SMALL_FONT_SELECTION, OnFontdDefault)
	ON_NOTIFY(UDN_DELTAPOS, ID_FONTD_HEIGHT_SPIN, OnDeltaposFontdHeightSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmallFontAttrDialog message handlers

BOOL CSmallFontAttrDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   CFont *pFont=CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
   CWnd *pWnd=GetWindow(GW_CHILD);
   while (pWnd) {
      pWnd->SetFont(pFont); 
      pWnd=pWnd->GetNextWindow();
   }

   if (m_nX>0 && m_nY) {
      CRect Rect;
      GetWindowRect(&Rect);
      int nWidth=Rect.Width();
      int nHeight=Rect.Height();
      Rect.SetRect(m_nX,m_nY,m_nX+nWidth-1,m_nY+nHeight-1);
      //MoveWindow(&Rect);      
      if (Rect.bottom > GetSystemMetrics(SM_CYSCREEN)) {
         Rect.top=m_nY-(Rect.bottom-Rect.top);
      }
      if (Rect.right>GetSystemMetrics(SM_CXSCREEN)) {
         Rect.left=GetSystemMetrics(SM_CXSCREEN)-(Rect.right-Rect.left);
      }
      SetWindowPos(NULL,Rect.left,Rect.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
   }

   if (m_sAlignment.IsEmpty()) { //2001.0409
      CComboBox *pBox=(CComboBox*)GetDlgItem(ID_FONTD_ALIGNMENT);
      pBox->SetCurSel(0);
      pBox->GetLBText(0,m_sAlignment);
   }

   m_ColorBtn.SubclassDlgItem(ID_FONTD_COLOR,this);
   //CSmallFontAttrDialog::OnFontdDefault();

	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSmallFontAttrDialog::OnFontdDefault() 
{
	// TODO: Add your control notification handler code here
	m_nWidth=5;
   m_nHeight=10;
   m_sAlignment="LB";
   m_nAngle=0;
   m_ColorBtn.nCurrentColor=RGB(0,0,0);
   UpdateData(FALSE);
}

void CSmallFontAttrDialog::SetWindowGravityPos(CPoint Point)
{
   m_nX=Point.x;
   m_nY=Point.y;
}

void CSmallFontAttrDialog::SetWindowGravityPos(int xPos, int yPos)
{
   m_nX=xPos;
   m_nY=yPos;
}

void CSmallFontAttrDialog::OnDeltaposFontdHeightSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

   switch (pNMUpDown->iDelta) {
   case -1 : m_nHeight++;break;
   case +1 : m_nHeight--;break;
   }
   if (m_nHeight<1) m_nHeight=1;
   if (m_nHeight>64) m_nHeight=64;
   UpdateData(FALSE);
	
   //
	*pResult = 0;
}

