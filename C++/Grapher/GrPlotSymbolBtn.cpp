// PlotSymbolBtn.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrPlotSymbolBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "plotsymb.h"

/////////////////////////////////////////////////////////////////////////////

static
void DrawSymbolButtonBorder( LPDRAWITEMSTRUCT lpd )
{
   CDC DC;
   DC.Attach(lpd->hDC);
   int top    = lpd->rcItem.top;
   int left   = lpd->rcItem.left;
   int bottom = lpd->rcItem.bottom;
   int right  = lpd->rcItem.right;
   
   CPen PenBlack,PenWhite,PenDarkGray;
   PenBlack.CreateStockObject(BLACK_PEN);
   PenWhite.CreateStockObject(WHITE_PEN);
   PenDarkGray.CreatePen(PS_SOLID,1,RGB(128,128,128));

   // Clear the background using the 3DFACE color.
   DC.Rectangle(&lpd->rcItem);

   // Draw the border
   if (!(lpd->itemState & ODS_SELECTED)) { // Button is up
      DC.SelectObject(&PenBlack);
      DC.MoveTo(left,bottom-1);
      DC.LineTo(right-1,bottom-1);
      DC.LineTo(right-1,top);
      DC.SelectObject(&PenDarkGray);
      DC.MoveTo(left+1,bottom-2);
      DC.LineTo(right-2,bottom-2);
      DC.LineTo(right-2,top+1);
      DC.SelectObject(&PenWhite);
      DC.LineTo(left+1,top+1);
      DC.LineTo(left+1,bottom-2);
   } else { // Button is down
      DC.SelectObject(&PenDarkGray);
      DC.MoveTo(left,bottom-1);
      DC.LineTo(left,top);
      DC.LineTo(right-1,top);
      DC.SelectObject(&PenWhite);
      DC.MoveTo(right-1,top-1);
      DC.LineTo(right-1,bottom-1);
      DC.LineTo(left+1,bottom-1);
      DC.SelectObject(&PenBlack);
      DC.MoveTo(left+1,bottom-2);
      DC.LineTo(left+1,top+1);
      DC.LineTo(right-2,top+1);
      // by moving this, we get the things inside the button
      // to draw themselves one pixel down and one to the right.
      // This completes the "pushed" effect
      left++;
      right++;
      bottom++;
      top++;
   }
}

static
void DrawSymbolButton(int nIDCtl,LPDRAWITEMSTRUCT lpDrawItemStruct,
                      BOOL bFillPath,COLORREF nSymbFillColor,
                      BOOL bStrokePath,COLORREF nSymbStrokeColor)
{
	// TODO: Add your message handler nCode here and/or call default

   //DrawSymbolButtonBorder(lpDrawItemStruct); 2001.0226
	
   CDC DC;
   CPen PenSymbol;
   CBrush BrushB,BrushF;
   CPen *pOldPen;
   CBrush *pOldBrush;

   DC.Attach(lpDrawItemStruct->hDC);
   //DC.SetMapMode(MM_LOMETRIC);

   PenSymbol.CreatePen(PS_SOLID,1,nSymbStrokeColor);
   BrushB.CreateSolidBrush(RGB(255,255,255));
   BrushF.CreateSolidBrush(nSymbFillColor);
   pOldPen=DC.SelectObject(&PenSymbol);
   pOldBrush=DC.SelectObject(&BrushF);

   CRect Viewport(lpDrawItemStruct->rcItem);
   Viewport.DeflateRect(1,1);
   DC.DPtoLP(&Viewport);
   DC.FillRect(&Viewport,&BrushB);

   if (nIDCtl==ID_GR_PLOT_SYMBOL_BUTTON_71) {
      CFont *pOldFont;
      CFont Font;
      Font.CreateFont(
         15,0,0,0,
         FW_BOLD,FALSE,FALSE,
         FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
         DEFAULT_QUALITY,VARIABLE_PITCH|FF_DONTCARE,"Arial");
      pOldFont=DC.SelectObject(&Font);
      DC.SetBkMode(TRANSPARENT);
      DC.SetTextColor(nSymbStrokeColor);
      DC.TextOut(2,2,"Box",3);
      DC.SelectObject(pOldFont);
      DC.SelectObject(pOldPen);
      DC.SelectObject(pOldBrush);
      DC.Detach();
      return;
   }

   int nTotal=32;
   int *xPoints=new int[nTotal]; 
   int *yPoints=new int[nTotal];  
   int nCode=nIDCtl-ID_GR_PLOT_SYMBOL_BUTTON_01+1;
   int nCount=GetStrokeSymbolPoints(nCode,xPoints,yPoints,nTotal);
   if (!nCount) {
      delete xPoints;
      delete yPoints;
      DC.SelectObject(pOldPen);
      DC.SelectObject(pOldBrush);
      DC.Detach();
      return;
   }
   int nIndex,nWindowMax=0;
   for (nIndex=0;nIndex<nCount;nIndex++) {
      nWindowMax=max(nWindowMax,xPoints[nIndex]);
      nWindowMax=max(nWindowMax,yPoints[nIndex]);
   }
   Viewport.DeflateRect(2,2);
   float x0,y0,scale;
   if (Viewport.Width()>=Viewport.Height()) {
      x0=(float)(Viewport.Width()-Viewport.Height())/2+Viewport.left;
      y0=(float)Viewport.top;
      scale=(float)Viewport.Height()/nWindowMax;
   } else {
      x0=(float)Viewport.left;
      y0=(float)(Viewport.Height()-Viewport.Width())/2+Viewport.top;
      scale=(float)Viewport.Width()/nWindowMax;
   }
   for (nIndex=0;nIndex<nCount;nIndex++) {
      xPoints[nIndex]=(int)(xPoints[nIndex]*scale+x0);
      yPoints[nIndex]=(int)(yPoints[nIndex]*scale+y0);
   }
   DC.BeginPath();
   DC.MoveTo(xPoints[0],yPoints[0]);
   for (nIndex=1;nIndex<nCount;nIndex++) DC.LineTo(xPoints[nIndex],yPoints[nIndex]);
   DC.EndPath();
   if (bFillPath)
      DC.FillPath();
   if (bStrokePath) {
      if (bFillPath) {
         DC.BeginPath();
         DC.MoveTo(xPoints[0],yPoints[0]);
         for (nIndex=1;nIndex<nCount;nIndex++) DC.LineTo(xPoints[nIndex],yPoints[nIndex]);
         DC.EndPath();
      }
      DC.StrokePath();
   }
   delete xPoints;
   delete yPoints;

   DC.SelectObject(pOldPen);
   DC.SelectObject(pOldBrush);
   DC.Detach();
}

/////////////////////////////////////////////////////////////////////////////
// CGrPlotSymbolBtn

CGrPlotSymbolBtn::CGrPlotSymbolBtn()
{
   m_nSymbolIndex=1;
   m_SubDialog.m_pParent=this;
   m_bFillSymbol=TRUE;
   m_bStrokeSymbol=TRUE;
   m_nSymbStrokeColor=RGB(0,0,0);
   m_nSymbFillColor=RGB(64,64,64);
}

CGrPlotSymbolBtn::~CGrPlotSymbolBtn()
{
}

BEGIN_MESSAGE_MAP(CGrPlotSymbolBtn, CButton)
	//{{AFX_MSG_MAP(CGrPlotSymbolBtn)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrPlotSymbolBtn message handlers

void CGrPlotSymbolBtn::OnClicked() 
{
	// TODO: Add your control notification handler nCode here
	if (m_SubDialog.DoModal()==IDOK) {
      InvalidateRect(NULL);
      CWnd *pParent=GetParent();
      pParent->SendMessage(
         WM_PLOTSYMBOLBTNMESSAGE,WM_PLOTSYMBOLBTNMESSAGE,(LPARAM)GetDlgCtrlID());
   }
}

void CGrPlotSymbolBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   DrawSymbolButton(
      m_nSymbolIndex+ID_GR_PLOT_SYMBOL_BUTTON_01-1,
      lpDrawItemStruct,      
      m_bFillSymbol,m_nSymbFillColor,
      m_bStrokeSymbol,m_nSymbStrokeColor);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGrPlotSymbolBtnDlg dialog


CGrPlotSymbolBtnDlg::CGrPlotSymbolBtnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGrPlotSymbolBtnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrPlotSymbolBtnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGrPlotSymbolBtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrPlotSymbolBtnDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrPlotSymbolBtnDlg, CDialog)
	//{{AFX_MSG_MAP(CGrPlotSymbolBtnDlg)
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP

   ON_COMMAND_RANGE(ID_GR_PLOT_SYMBOL_BUTTON_01,ID_GR_PLOT_SYMBOL_BUTTON_71,OnSymbolButton)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrPlotSymbolBtnDlg message handlers

BOOL CGrPlotSymbolBtnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   RECT rBtn,rDlg;
	m_pParent->GetWindowRect(&rBtn);
   SetWindowPos(NULL,rBtn.left,rBtn.bottom,0,0,SWP_NOSIZE|SWP_NOZORDER);
   GetWindowRect(&rDlg);
   if (rDlg.bottom > GetSystemMetrics(SM_CYSCREEN)) {
      rDlg.top = rBtn.top-(rDlg.bottom-rDlg.top);
   }
   if (rDlg.right > GetSystemMetrics(SM_CXSCREEN)) {
      rDlg.left = GetSystemMetrics(SM_CXSCREEN) - (rDlg.right-rDlg.left);
   }
   SetWindowPos(NULL,rDlg.left,rDlg.top,0,0,SWP_NOSIZE|SWP_NOZORDER);
   SetCapture();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrPlotSymbolBtnDlg::EndDialog( int nResult )
{
   ReleaseCapture();
   CDialog::EndDialog(nResult);
}

void CGrPlotSymbolBtnDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler nCode here and/or call default
   CGrPlotSymbolBtn *btn=(CGrPlotSymbolBtn*)m_pParent;
   DrawSymbolButton(nIDCtl,lpDrawItemStruct,
      btn->m_bFillSymbol,btn->m_nSymbFillColor,
      btn->m_bStrokeSymbol,btn->m_nSymbStrokeColor);
	CDialog::OnDrawItem(nIDCtl,lpDrawItemStruct);
}

void CGrPlotSymbolBtnDlg::OnSymbolButton( UINT nID )
{
   CGrPlotSymbolBtn *pButton=(CGrPlotSymbolBtn*)m_pParent;
   pButton->m_nSymbolIndex=nID-ID_GR_PLOT_SYMBOL_BUTTON_01+1;
   EndDialog(IDOK);
}

void CGrPlotSymbolBtnDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler nCode here and/or call default

   RECT Rect;
   POINT Point;
   Point.x=point.x;
   Point.y=point.y;
   ClientToScreen(&Point);
   GetWindowRect(&Rect);
   if (!PtInRect(&Rect,Point)) {
      EndDialog(IDCANCEL);
   } else {      
      CWnd *pChild=ChildWindowFromPoint(point);
      if (pChild && pChild!=this)
         pChild->SendMessage(WM_LBUTTONDOWN);
   }   
	
	CDialog::OnLButtonDown(nFlags, point);
}
