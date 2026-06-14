// GrPalleteDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GrPalleteDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "geWindow.h"
#define NOOFCOLORTABLE 10

/////////////////////////////////////////////////////////////////////////////
// CGrPalleteDialog dialog


CGrPalleteDialog::CGrPalleteDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGrPalleteDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrPalleteDialog)
	m_nB4 = 0;
	m_nB1 = 0;
	m_nB2 = 0;
	m_nB3 = 0;
	m_nB5 = 0;
	m_nB6 = 0;
	m_nB7 = 0;
	m_nB8 = 0;
	m_nB9 = 0;
	m_nG1 = 0;
	m_nG2 = 0;
	m_nG3 = 0;
	m_nG4 = 0;
	m_nG5 = 0;
	m_nG6 = 0;
	m_nG7 = 0;
	m_nG8 = 0;
	m_nG9 = 0;
	m_sN1 = _T("");
	m_sN2 = _T("");
	m_sN3 = _T("");
	m_sN4 = _T("");
	m_sN5 = _T("");
	m_sN6 = _T("");
	m_sN7 = _T("");
	m_sN8 = _T("");
	m_sN9 = _T("");
	m_nV1 = 0;
	m_nV2 = 0;
	m_nB0 = 0;
	m_nG0 = 0;
	m_sN0 = _T("");
	m_nR0 = 0;
	m_nR2 = 0;
	m_nR3 = 0;
	m_nR4 = 0;
	m_nR5 = 0;
	m_nR6 = 0;
	m_nR7 = 0;
	m_nR8 = 0;
	m_nR9 = 0;
	m_nV0 = 0;
	m_nV3 = 0;
	m_nV4 = 0;
	m_nV5 = 0;
	m_nV6 = 0;
	m_nV7 = 0;
	m_nV8 = 0;
	m_nV9 = 0;
	m_nR1 = 0;
	//}}AFX_DATA_INIT
}


void CGrPalleteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrPalleteDialog)
	DDX_Control(pDX, ID_GRCOLORTABLE_P0, m_P0);
	DDX_Control(pDX, ID_GRCOLORTABLE_P9, m_P9);
	DDX_Control(pDX, ID_GRCOLORTABLE_P8, m_P8);
	DDX_Control(pDX, ID_GRCOLORTABLE_P7, m_P7);
	DDX_Control(pDX, ID_GRCOLORTABLE_P6, m_P6);
	DDX_Control(pDX, ID_GRCOLORTABLE_P5, m_P5);
	DDX_Control(pDX, ID_GRCOLORTABLE_P4, m_P4);
	DDX_Control(pDX, ID_GRCOLORTABLE_P3, m_P3);
	DDX_Control(pDX, ID_GRCOLORTABLE_P2, m_P2);
	DDX_Control(pDX, ID_GRCOLORTABLE_P1, m_P1);
	DDX_Control(pDX, ID_GRCOLORTABLE_SLIDER, m_SliderCtrl);
	DDX_Text(pDX, ID_GRCOLORTABLE_B4, m_nB4);
	DDV_MinMaxUInt(pDX, m_nB4, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_B1, m_nB1);
	DDV_MinMaxUInt(pDX, m_nB1, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_B2, m_nB2);
	DDV_MinMaxUInt(pDX, m_nB2, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_B3, m_nB3);
	DDV_MinMaxUInt(pDX, m_nB3, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_B5, m_nB5);
	DDV_MinMaxUInt(pDX, m_nB5, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_B6, m_nB6);
	DDV_MinMaxUInt(pDX, m_nB6, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_B7, m_nB7);
	DDV_MinMaxUInt(pDX, m_nB7, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_B8, m_nB8);
	DDV_MinMaxUInt(pDX, m_nB8, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_B9, m_nB9);
	DDV_MinMaxUInt(pDX, m_nB9, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G1, m_nG1);
	DDV_MinMaxUInt(pDX, m_nG1, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G2, m_nG2);
	DDV_MinMaxUInt(pDX, m_nG2, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G3, m_nG3);
	DDV_MinMaxUInt(pDX, m_nG3, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G4, m_nG4);
	DDV_MinMaxUInt(pDX, m_nG4, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G5, m_nG5);
	DDV_MinMaxUInt(pDX, m_nG5, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G6, m_nG6);
	DDV_MinMaxUInt(pDX, m_nG6, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G7, m_nG7);
	DDV_MinMaxUInt(pDX, m_nG7, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G8, m_nG8);
	DDV_MinMaxUInt(pDX, m_nG8, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G9, m_nG9);
	DDV_MinMaxUInt(pDX, m_nG9, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_N1, m_sN1);
	DDX_Text(pDX, ID_GRCOLORTABLE_N2, m_sN2);
	DDX_Text(pDX, ID_GRCOLORTABLE_N3, m_sN3);
	DDX_Text(pDX, ID_GRCOLORTABLE_N4, m_sN4);
	DDX_Text(pDX, ID_GRCOLORTABLE_N5, m_sN5);
	DDX_Text(pDX, ID_GRCOLORTABLE_N6, m_sN6);
	DDX_Text(pDX, ID_GRCOLORTABLE_N7, m_sN7);
	DDX_Text(pDX, ID_GRCOLORTABLE_N8, m_sN8);
	DDX_Text(pDX, ID_GRCOLORTABLE_N9, m_sN9);
	DDX_Text(pDX, ID_GRCOLORTABLE_V1, m_nV1);
	DDX_Text(pDX, ID_GRCOLORTABLE_V2, m_nV2);
	DDX_Text(pDX, ID_GRCOLORTABLE_B0, m_nB0);
	DDV_MinMaxUInt(pDX, m_nB0, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_G0, m_nG0);
	DDV_MinMaxUInt(pDX, m_nG0, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_N0, m_sN0);
	DDX_Text(pDX, ID_GRCOLORTABLE_R0, m_nR0);
	DDV_MinMaxUInt(pDX, m_nR0, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_R2, m_nR2);
	DDV_MinMaxUInt(pDX, m_nR2, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_R3, m_nR3);
	DDV_MinMaxUInt(pDX, m_nR3, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_R4, m_nR4);
	DDV_MinMaxUInt(pDX, m_nR4, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_R5, m_nR5);
	DDV_MinMaxUInt(pDX, m_nR5, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_R6, m_nR6);
	DDV_MinMaxUInt(pDX, m_nR6, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_R7, m_nR7);
	DDV_MinMaxUInt(pDX, m_nR7, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_R8, m_nR8);
	DDV_MinMaxUInt(pDX, m_nR8, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_R9, m_nR9);
	DDV_MinMaxUInt(pDX, m_nR9, 0, 255);
	DDX_Text(pDX, ID_GRCOLORTABLE_V0, m_nV0);
	DDX_Text(pDX, ID_GRCOLORTABLE_V3, m_nV3);
	DDX_Text(pDX, ID_GRCOLORTABLE_V4, m_nV4);
	DDX_Text(pDX, ID_GRCOLORTABLE_V5, m_nV5);
	DDX_Text(pDX, ID_GRCOLORTABLE_V6, m_nV6);
	DDX_Text(pDX, ID_GRCOLORTABLE_V7, m_nV7);
	DDX_Text(pDX, ID_GRCOLORTABLE_V8, m_nV8);
	DDX_Text(pDX, ID_GRCOLORTABLE_V9, m_nV9);
	DDX_Text(pDX, ID_GRCOLORTABLE_R1, m_nR1);
	DDV_MinMaxUInt(pDX, m_nR1, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrPalleteDialog, CDialog)
	//{{AFX_MSG_MAP(CGrPalleteDialog)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrPalleteDialog message handlers

BOOL CGrPalleteDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   m_nColorIndex=0;
   m_nColorTotal=GEColorTotal(NULL);

   m_SliderCtrl.SetRange(0,m_nColorTotal-NOOFCOLORTABLE);
   m_SliderCtrl.SetPos(m_nColorIndex);
   m_SliderCtrl.SetPageSize(10);
   RefreshControls(m_nColorIndex);

   // 20020914
   // By using an idea of Mak (2002/09/06),written on www.codeguru.com
   CFont *pFont=CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
   CWnd *pWnd=GetWindow(GW_CHILD);
   while (pWnd) {
      pWnd->SetFont(pFont); 
      pWnd=pWnd->GetNextWindow();
   }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrPalleteDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nIndex=m_SliderCtrl.GetPos();
   if (m_nColorIndex==nIndex) return;
   m_nColorIndex=nIndex;
   RefreshControls(nIndex);
}

void CGrPalleteDialog::RefreshControls(int nColorIndex)
{
   char *pName;
   unsigned long nColor;
   unsigned short red,green,blue;
   CRect Rect;
   for (int nIndex=0;nIndex<NOOFCOLORTABLE;nIndex++) {
      pName=(char*)GEColorNameByIndex(NULL,nIndex+nColorIndex);
      nColor=GEColorByName(NULL,pName);
      GEColor2RGB(NULL,nColor,&red,&green,&blue,0);
      switch (nIndex) {
      case 0 : m_nR0=red;m_nG0=green;m_nB0=blue;m_nV0=nColor;m_sN0=pName;break;
      case 1 : m_nR1=red;m_nG1=green;m_nB1=blue;m_nV1=nColor;m_sN1=pName;break;
      case 2 : m_nR2=red;m_nG2=green;m_nB2=blue;m_nV2=nColor;m_sN2=pName;break;
      case 3 : m_nR3=red;m_nG3=green;m_nB3=blue;m_nV3=nColor;m_sN3=pName;break;
      case 4 : m_nR4=red;m_nG4=green;m_nB4=blue;m_nV4=nColor;m_sN4=pName;break;
      case 5 : m_nR5=red;m_nG5=green;m_nB5=blue;m_nV5=nColor;m_sN5=pName;break;
      case 6 : m_nR6=red;m_nG6=green;m_nB6=blue;m_nV6=nColor;m_sN6=pName;break;
      case 7 : m_nR7=red;m_nG7=green;m_nB7=blue;m_nV7=nColor;m_sN7=pName;break;
      case 8 : m_nR8=red;m_nG8=green;m_nB8=blue;m_nV8=nColor;m_sN8=pName;break;
      case 9 : m_nR9=red;m_nG9=green;m_nB9=blue;m_nV9=nColor;m_sN9=pName;break;
      }
      GetColorRectAndValue(nIndex,Rect,nColor);
      ScreenToClient(&Rect);
      RedrawWindow(&Rect);
   }
   UpdateData(FALSE);
}


void CGrPalleteDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
   CDC *pDC=&dc;
   int nIndex;
   unsigned long nColor;
   CRect Rect;
   CBrush Brush;
   CBrush *pBrush=&Brush;
   for (nIndex=0;nIndex<NOOFCOLORTABLE;nIndex++) {
      GetColorRectAndValue(nIndex,Rect,nColor);
      ScreenToClient(&Rect);
      pBrush->CreateSolidBrush(nColor);
      pDC->FillRect(&Rect,pBrush);
      pBrush->DeleteObject();
   }

	// Do not call CDialog::OnPaint() for painting messages
}

void CGrPalleteDialog::GetColorRectAndValue(
   int nColorIndex, CRect &Rect, unsigned long &nColorValue)
{
   switch (nColorIndex) {
   case 0 : m_P0.GetWindowRect(&Rect);nColorValue=m_nV0;break;
   case 1 : m_P1.GetWindowRect(&Rect);nColorValue=m_nV1;break;
   case 2 : m_P2.GetWindowRect(&Rect);nColorValue=m_nV2;break;
   case 3 : m_P3.GetWindowRect(&Rect);nColorValue=m_nV3;break;
   case 4 : m_P4.GetWindowRect(&Rect);nColorValue=m_nV4;break;
   case 5 : m_P5.GetWindowRect(&Rect);nColorValue=m_nV5;break;
   case 6 : m_P6.GetWindowRect(&Rect);nColorValue=m_nV6;break;
   case 7 : m_P7.GetWindowRect(&Rect);nColorValue=m_nV7;break;
   case 8 : m_P8.GetWindowRect(&Rect);nColorValue=m_nV8;break;
   case 9 : m_P9.GetWindowRect(&Rect);nColorValue=m_nV9;break;
   default: Rect.SetRectEmpty();nColorValue=0;
   }
}

BOOL CGrPalleteDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

   if (pMsg->message==WM_KEYDOWN) {
      CWnd *pFocused=GetFocus();
      if (pFocused->m_hWnd!=m_SliderCtrl.m_hWnd) {
         switch (pMsg->wParam) {
         case VK_UP : m_SliderCtrl.SendMessage(WM_KEYDOWN,VK_UP,0);break;
         case VK_DOWN : m_SliderCtrl.SendMessage(WM_KEYDOWN,VK_DOWN,0);break;
         case VK_PRIOR : m_SliderCtrl.SendMessage(WM_KEYDOWN,VK_PRIOR,0);break;
         case VK_NEXT : m_SliderCtrl.SendMessage(WM_KEYDOWN,VK_NEXT,0);break;
         }
      }
   }
	
	return CDialog::PreTranslateMessage(pMsg);
}
