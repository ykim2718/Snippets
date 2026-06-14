//------------------------------------------------------------------------------
// www.codeguru.com
// zoomview.cpp : Implements Zooming functions in a CScrollView window
// Written by Brad Pirtle, CS:72450,1156, Internet:pirtle@qlogic.com
// Copyright 1994, QuickLogic Corp., all rights reserved.
// Version 1.0
//------------------------------------------------------------------------------
// modified by shik96@unitel.co.kr, 2000.01.17 - 2.16
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "resource.h"
#include "zoomview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CZoomView, CScrollView)
	//{{AFX_MSG_MAP(CZoomView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_RBUTTONDOWN()
	ON_WM_CANCELMODE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define PICKMARGIN  10        // Screen pixels apart for region zoom

/////////////////////////////////////////////////////////////////////////////
// CZoomView
IMPLEMENT_DYNCREATE(CZoomView, CScrollView)

/*---------------------------------------------------------------------------
   FUNCTION: CZoomView
   PURPOSE : Constructor for the CZoomView class 
---------------------------------------------------------------------------*/
CZoomView::CZoomView()
: CScrollView()
{
	// Init zoom mode to nothing
   m_zoomPage    = ZP_A4H;
   m_zoomPageDPI = 300;
   m_zoomPageDpiFactor=1.0;
	m_zoomMode    = ZM_OFF;
	m_bCaptured   = FALSE;
	m_zoomScale   = 1.0;
	m_ptDragRect.SetRectEmpty();

   // Load the zoom cursor   
   //m_hZoomCursor=::LoadCursor(NULL,IDC_CROSS); //shik
	m_hZoomInCursor=::LoadCursor(AfxGetInstanceHandle(),
      MAKEINTRESOURCE(IDC_ZOOM_IN_CURSOR));
   m_hZoomOutCursor=::LoadCursor(AfxGetInstanceHandle(),
      MAKEINTRESOURCE(IDC_ZOOM_OUT_CURSOR));
   m_hHandSpreadedCursor=::LoadCursor(AfxGetInstanceHandle(),
      MAKEINTRESOURCE(IDC_HAND_SPREADED_CURSOR));
   m_hHandGrapsedCursor=::LoadCursor(AfxGetInstanceHandle(),
      MAKEINTRESOURCE(IDC_HAND_GRAPSED_CURSOR));

	// Default to centering on full fit
	m_bCenter = TRUE;

   m_origHandScrollPoint.x=m_origHandScrollPoint.y=0;

} // CZoomView

/*---------------------------------------------------------------------------
   FUNCTION: ~CZoomView
   PURPOSE : Destructor for the CZoomView class 
---------------------------------------------------------------------------*/
CZoomView::~CZoomView()
{
	// Clean up the cursors if they were loaded properly
	if (m_hZoomInCursor) DestroyCursor(m_hZoomInCursor);
   if (m_hZoomOutCursor) DestroyCursor(m_hZoomOutCursor);
   if (m_hHandSpreadedCursor) DestroyCursor(m_hHandSpreadedCursor);
   if (m_hHandGrapsedCursor) DestroyCursor(m_hHandGrapsedCursor);
} // ~CZoomView

//------------------------------------------------------------------------------
// shik96,2000.1.19+2.10
//------------------------------------------------------------------------------
void CZoomView::OnInitialUpdate()
{
   //shik(
   DWORD nBr=GetClassLong(this->m_hWnd,GCL_HBRBACKGROUND); //COLOR_BTNSHADOW
   static CBrush hBr(GetSysColor(COLOR_BTNSHADOW)); //COLOR_GRAYTEXT
   // static -> 3/18/2002
   SetClassLong(this->m_hWnd,GCL_HBRBACKGROUND,(LONG)(HBRUSH)hBr);
   //shik)

  	CView::OnInitialUpdate();
   SetZoomSizes(m_zoomPage);

   //20030408
   m_iPageMargin=10;
}

/////////////////////////////////////////////////////////////////////////////
// CZoomView overridden default CScrollView members
/////////////////////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------
   FUNCTION: SetZoomSizes
   PURPOSE : Set up the CZoomView class with the logical page size, and 
   			 scrolling page/line units.  
   			 This replaces CScrollView::SetScrollSizes.
---------------------------------------------------------------------------*/
void CZoomView::SetZoomSizes (
	SIZE sizeTotal,
	const SIZE& sizePage, // in logical units
	const SIZE& sizeLine) // in logical units
{
	// Set up the defaults
	ASSERT(sizeTotal.cx >= 0 && sizeTotal.cy >= 0);
	m_nMapMode    = MM_ANISOTROPIC; // Need for arbitrary scaling
   m_totalLog    = sizeTotal;
	// Setup default Viewport extent to be conversion of Window extent
	// into device units.
	//BLOCK for DC
	{
		CWindowDC dc(NULL);
		dc.SetMapMode(m_nMapMode);

		// total size
		m_totalDev = m_totalLog;
		dc.LPtoDP((LPPOINT)&m_totalDev);
	} // Release DC here

	// Save the origional Viewport Extent
	m_origTotalDev = m_totalDev;
	// Save the origional scrollbar info - for CalculateBars
	m_origPageDev = sizePage;
	m_origLineDev = sizeLine;
	// Fugure out scroll bar info
	CalculateBars();
	// Notify the class that the zoom scale was set
	NotifyZoom();
} // SetZoomSizes

//------------------------------------------------------------------------------
// shik96,2000.1.19+2.10
//------------------------------------------------------------------------------
void CZoomView::SetZoomSizes (
	ZoomPage_ zoomPage,
	const SIZE& sizePage, // in logical units
	const SIZE& sizeLine) // in logical units
{
   CSize sheet;
S: switch (zoomPage) { // [mm]
   case ZP_A3  : sheet.cx=297; sheet.cy=420;break;
   case ZP_A3H : sheet.cx=420; sheet.cy=297;break;
   case ZP_A4  : sheet.cx=210; sheet.cy=297;break;
   case ZP_A4H : sheet.cx=297; sheet.cy=210;break;
   case ZP_LT  : sheet.cx=216; sheet.cy=279;break; //Letter
   case ZP_LTH : sheet.cx=279; sheet.cy=216;break; //Letter
   default     : zoomPage=m_zoomPage;goto S;
   }
   //m_zoomPageDpiFactor=zoomPageResolution ? abs(zoomPageResolution):1;
   //sheet.cx*=m_zoomPageDpiFactor;
   //sheet.cy*=m_zoomPageDpiFactor;
   m_zoomPage=zoomPage;
   CDC *dc=GetDC();
   int wMM=dc->GetDeviceCaps(HORZSIZE);
   int hMM=dc->GetDeviceCaps(VERTSIZE);
   int wPX=dc->GetDeviceCaps(HORZRES);
   int hPX=dc->GetDeviceCaps(VERTRES);
   float DPI=min((float)(wPX/wMM*25.4),(float)(hPX/hMM*25.4));
   if (DPI<m_zoomPageDPI) m_zoomPageDpiFactor=m_zoomPageDPI/DPI;
   sheet.cx=abs((int)(sheet.cx*wPX/wMM*m_zoomPageDpiFactor));
   sheet.cy=abs((int)(sheet.cy*hPX/hMM*m_zoomPageDpiFactor));
   SetZoomSizes(sheet);
}

/*---------------------------------------------------------------------------
   FUNCTION: OnPrepareDC
   PURPOSE : Override of CScrollView for MM_ANISOTROPIC zoom mode
---------------------------------------------------------------------------*/
void CZoomView::OnPrepareDC (
	CDC* pDC, 
	CPrintInfo* pInfo)
{
#ifdef _DEBUG
	if (m_nMapMode != MM_ANISOTROPIC) {
		TRACE0("Error: must call SetZoomSizes() before painting zoom view\n");
		ASSERT(FALSE);
		return;
	}
#endif //_DEBUG

	ASSERT_VALID(pDC);
	ASSERT(m_totalLog.cx >= 0 && m_totalLog.cy >= 0);
	ASSERT(m_totalDev.cx >= 0 && m_totalDev.cx >= 0);
	// Set the Mapping mode, and the window and viewport extents
	pDC->SetMapMode(m_nMapMode);
	pDC->SetWindowExt(m_totalLog);   // in logical coordinates
	CPoint ptVpOrg;

	if (!pDC->IsPrinting()) {
		pDC->SetViewportExt(m_totalDev); // in device  coordinates

		// by default shift viewport origin in negative direction of scroll
		ASSERT(pDC->GetWindowOrg() == CPoint(0,0));
		ptVpOrg = -GetDeviceScrollPosition();

		// Center full fit
		if (m_bCenter) {
			CRect rect;
			GetClientRect(&rect);
			// if client area is larger than total device size,
			// override scroll positions to place origin such that
			// output is centered in the window
			if (m_totalDev.cx < rect.Width())
				ptVpOrg.x = (rect.Width() - m_totalDev.cx) / 2;
			if (m_totalDev.cy < rect.Height())
				ptVpOrg.y = (rect.Height() - m_totalDev.cy) / 2;
		}
	} else {
		// Special case for printing
		CSize  printSize;
      printSize.cx = pDC->GetDeviceCaps(HORZRES);
      printSize.cy = pDC->GetDeviceCaps(VERTRES);
		// Maintain the origional ratio, setup origin shift
		PersistRatio(m_totalLog, printSize, ptVpOrg);
		// Zoom completely out
		pDC->SetViewportExt(printSize);
	}
	// Set the new origin
	pDC->SetViewportOrg(ptVpOrg);
	// For default Printing behavior
	CView::OnPrepareDC(pDC, pInfo);
} // OnPrepareDC

/*---------------------------------------------------------------------------
   FUNCTION: CalculateBars
   PURPOSE : Update the scrollbars - uses logical units
				 Call when the Viewport changes size.
---------------------------------------------------------------------------*/
void CZoomView::CalculateBars (void)
{
	{	// BLOCK for DC
		CWindowDC dc(NULL);
		dc.SetMapMode(m_nMapMode);

		// Calculate new device units for scrollbar
		// Start with origional logical units from SetScrollPos
		m_pageDev = m_origPageDev;
		dc.LPtoDP((LPPOINT)&m_pageDev);
		m_lineDev = m_origLineDev;
		dc.LPtoDP((LPPOINT)&m_lineDev);
	} // Free DC

	// Make sure of the range
	if (m_pageDev.cy < 0)  m_pageDev.cy = -m_pageDev.cy;
	if (m_lineDev.cy < 0)  m_lineDev.cy = -m_lineDev.cy;

	// If none specified - use one tenth
	ASSERT(m_totalDev.cx >= 0 && m_totalDev.cy >= 0);
	if (m_pageDev.cx == 0) m_pageDev.cx = m_totalDev.cx / 10;
	if (m_pageDev.cy == 0) m_pageDev.cy = m_totalDev.cy / 10;
	if (m_lineDev.cx == 0) m_lineDev.cx = m_pageDev.cx  / 10;
	if (m_lineDev.cy == 0) m_lineDev.cy = m_pageDev.cy  / 10;

	// Now update the scrollbars
	if (m_hWnd != NULL) {
		UpdateBars();
		Invalidate(TRUE); // Zoom scale changed, redraw all
	}
} // CalculateBars

/*---------------------------------------------------------------------------
   FUNCTION: AssertValid
   PURPOSE : Make sure valid class
---------------------------------------------------------------------------*/
#ifdef _DEBUG
void CZoomView::AssertValid() const
{
	// Bypass CScrollView because of MM_ANISOTROPIC map mode
   // Ok ... shik96,2000.1.19
	CView::AssertValid();
} // AssertValid
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZoomView custom members to implement zooming functionality
/////////////////////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------
   FUNCTION: DoZoomIn
   PURPOSE : Zoom the view in on a rect
---------------------------------------------------------------------------*/
int  CZoomView::DoZoomIn (
	CRect &rect)   // rect in logical coordinates
{
	ASSERT(m_nMapMode == MM_ANISOTROPIC);
	// Make sure that the rect is normalized
	CRect zoomRect = rect;
	NormalizeRect(zoomRect);

	// Get the center of rect
	CPoint ptCenter(rect.CenterPoint()); //shik96,2000.1.19

	// See if the rect is small enough for a point zoom (Device coordinates)
	CRect rectDP = zoomRect;
	ViewLPtoDP((LPPOINT)&rectDP, 2);
   BOOL bPointZoom = (max(rectDP.Width(), rectDP.Height()) < PICKMARGIN);
	if (bPointZoom) {
		// Just do normal point zoom
		return DoZoomIn(&ptCenter);
	}

	CRect clientRect;
	GetClientRect(&clientRect);

	// Calculate the new zoom scale.
	float scaleH = (float) (clientRect.right  + 1) / (float) zoomRect.Width();
	float scaleV = (float) (clientRect.bottom + 1) / (float) zoomRect.Height();
	// Keep the scale Isotropic
	m_zoomScale = min(scaleH, scaleV);

	// Modify the Viewport extent
   CSize viewportExtent; //shik96,2000.1.19
	viewportExtent.cx = (int) ((float) m_origTotalDev.cx * m_zoomScale);
	viewportExtent.cy = (int) ((float) m_origTotalDev.cy * m_zoomScale);
   if (viewportExtent.cx>32767||viewportExtent.cy>32767)
      return FALSE;
   m_totalDev=viewportExtent;
	CalculateBars();

	// Set the current center point.
	CenterOnLogicalPoint(ptCenter);
	// Notify the class that a new zoom scale was done
	NotifyZoom();
	return TRUE;
} // DoZoomIn (Rect)

/*---------------------------------------------------------------------------
   FUNCTION: DoZoomIn
   PURPOSE : Zoom the view in on a point by the specified scale factor
---------------------------------------------------------------------------*/
int  CZoomView::DoZoomIn (
	CPoint *point,   // point in logical coordinates
	float  delta)    // scale factor
{
	CPoint ptCenter;

	ASSERT(m_nMapMode == MM_ANISOTROPIC);
	// Save the current center point.
	if (!point) {
   	ptCenter = GetLogicalCenterPoint();
	} else {
   	ptCenter = *point;
	}

	// Increase the zoom scale.
	m_zoomScale *= delta;

	// Modify the Viewport extent
	m_totalDev.cx = (int) ((float) m_origTotalDev.cx * m_zoomScale);
	m_totalDev.cy = (int) ((float) m_origTotalDev.cy * m_zoomScale);
	CalculateBars();
	// Set the current center point.
	CenterOnLogicalPoint(ptCenter);
	// Notify the class that a new zoom scale was done
	NotifyZoom();
	return TRUE;
} // DoZoomIn (Pt)

/*---------------------------------------------------------------------------
   FUNCTION: DoZoomOut
   PURPOSE : Zoom the view out on a point by one scale factor
---------------------------------------------------------------------------*/
int  CZoomView::DoZoomOut (
	CPoint *point,   // point in logical coordinates
	float  delta)    // scale factor
{
	CPoint ptCenter;

	ASSERT(m_nMapMode == MM_ANISOTROPIC);
	// Save the current center point.
	if (!point) {
   	ptCenter = GetLogicalCenterPoint();
	} else {
   	ptCenter = *point;
	}

	// Decrease the zoom scale.
	m_zoomScale /= delta;

	// Modify the Viewport extent
	m_totalDev.cx = (int) ((float) m_origTotalDev.cx * m_zoomScale);
	m_totalDev.cy = (int) ((float) m_origTotalDev.cy * m_zoomScale);
	CalculateBars();
	// Set the current center point (logical coordinates.
	CenterOnLogicalPoint(ptCenter);
	// Notify the class that a new zoom scale was done
	NotifyZoom();
	return TRUE;
} // DoZoomOut

/*---------------------------------------------------------------------------
   FUNCTION: DoZoomFull
   PURPOSE : Zoom the view to full state
---------------------------------------------------------------------------*/
int  CZoomView::DoZoomFull (void)
{
	ASSERT(m_nMapMode == MM_ANISOTROPIC);
	CRect  rc;
	CPoint pt;
	CSize  sizeSb;
	// Just set Viewport Extent to Client size for full fit
	GetTrueClientSize(m_totalDev, sizeSb);
	// Maintain origional ratio
	PersistRatio(m_totalLog, m_totalDev, pt);
   m_totalDev.cx-=m_iPageMargin; //shik96,00.2.10 I am to add more later
   m_totalDev.cy-=m_iPageMargin; //shik96,00.2.10 I am to add more later
   if (m_totalDev.cx<=0) m_totalDev.cx=0;
   if (m_totalDev.cy<=0) m_totalDev.cy=0;
	// Set the new zoom scale (could use cx or cy)
	m_zoomScale = (float) m_totalDev.cx / m_origTotalDev.cx ;
	// Remove the scrollbars
	UpdateBars();
	// Complete redraw
	Invalidate(TRUE);
	// Notify the class that a new zoom scale was done
	NotifyZoom();
   // Reset zoom mode (shik96)
   CZoomView::OnChar(27,1,0); //shik96,2000.3.20
	return TRUE;
} // DoZoomInFull

//------------------------------------------------------------------------------
// shik96,2000.1.18+2.10
//------------------------------------------------------------------------------
int CZoomView::DoZoomPercent (int percent)
{
   ASSERT(m_nMapMode == MM_ANISOTROPIC);
   if (percent<10||percent>1000) return FALSE;
   CPoint ptCenter=GetLogicalCenterPoint();
	m_zoomScale=(float)(percent/100.0);
	m_totalDev.cx=(int)((float)m_origTotalDev.cx*m_zoomScale/m_zoomPageDpiFactor);
	m_totalDev.cy=(int)((float)m_origTotalDev.cy*m_zoomScale/m_zoomPageDpiFactor);
	CalculateBars();
	CenterOnLogicalPoint(ptCenter);
	NotifyZoom();
	return TRUE;
} // DoZoomPercent

/*---------------------------------------------------------------------------
   FUNCTION: SetZoomMode
   PURPOSE : Put the view into the specified zoom mode
---------------------------------------------------------------------------*/
void CZoomView::SetZoomMode (
	ZoomMode_ zoomMode)
{
	ASSERT(m_nMapMode == MM_ANISOTROPIC);
	if (zoomMode!=m_zoomMode) {
		m_zoomMode=zoomMode;
		// Force cursor change now
		OnSetCursor(NULL,HTCLIENT,0);
	}
} // SetZoomMode

/*---------------------------------------------------------------------------
   FUNCTION: CenterOnLogicalPoint
   PURPOSE : Same as CScrollView::CenterOnPoint, but for logical coordinates
---------------------------------------------------------------------------*/
void CZoomView::CenterOnLogicalPoint(CPoint pt)
{
	// Convert the point to device coordinates
	ViewLPtoDP(&pt);
	// Account for scroll bar position
	ClientToDevice(pt);
	// Use CScrollView's function for device coordinates
	CScrollView::CenterOnPoint(pt);
} // CenterOnLogicalPoint

/*---------------------------------------------------------------------------
   FUNCTION: GetLogicalCenterPoint
   PURPOSE : Get the center of screen in logical coordinates
---------------------------------------------------------------------------*/
CPoint CZoomView::GetLogicalCenterPoint (void)  // Point in logical units
{
	CPoint pt;
	CRect rect;
	// Get the center of screen
	GetClientRect(&rect);
	pt.x = (rect.Width()  / 2);
	pt.y = (rect.Height() / 2);

	// Convert the point to logical coordinates
	ViewDPtoLP(&pt);
	return pt;
} // GetLogicalCenterPoint

/*---------------------------------------------------------------------------
   FUNCTION: DrawBox
   PURPOSE : Draw a box - XOR if want to erase
---------------------------------------------------------------------------*/
void CZoomView::DrawBox (
	CDC   &dc,
	CRect &rect,
	BOOL  xor)
{
	CPen pen;
	// Save the device context
	dc.SaveDC();
	if (xor) {
		dc.SetROP2(R2_NOTXORPEN);
		pen.CreatePen(PS_DOT,  0,RGB(255,0,0)); // 0 width = 1 device unit
	} else {
		pen.CreatePen(PS_SOLID,0,RGB(255,0,0)); // 0 width = 1 device unit
	}
	dc.SelectObject(&pen);
	// Draw the rect with lines (eliminate rect middle fill)
	dc.MoveTo(rect.left,  rect.top);
	dc.LineTo(rect.right, rect.top);
	dc.LineTo(rect.right, rect.bottom);
	dc.LineTo(rect.left,  rect.bottom);
	dc.LineTo(rect.left,  rect.top);
	// Clean up
	dc.RestoreDC(-1);
} // DrawBox

/*---------------------------------------------------------------------------
   FUNCTION: DrawLine
   PURPOSE : Draw a line - XOR to erase
---------------------------------------------------------------------------*/
void CZoomView::DrawLine (
	CDC &dc,
	const int &x1, // Logical units
	const int &y1,
	const int &x2,
	const int &y2,
	BOOL      xor)
{	
	CPen pen;
	// Save the device context
	dc.SaveDC();
	if (xor) {
		dc.SetROP2(R2_NOTXORPEN);
		pen.CreatePen(PS_DASH,  0, RGB(0, 0, 0)); // 0 width = 1 device unit
	} else {
		pen.CreatePen(PS_SOLID, 0, RGB(0, 0, 0)); // 0 width = 1 device unit
	}
	dc.SelectObject(&pen);

	// Draw the line
	dc.MoveTo(x1, y1);
	dc.LineTo(x2, y2);
	// Clean up
	dc.RestoreDC(-1);
} // DrawLine

/*---------------------------------------------------------------------------
   FUNCTION: OnLButtonDown
   PURPOSE : Handle the left mouse click
---------------------------------------------------------------------------*/
void CZoomView::OnLButtonDown(
	UINT nFlags, 
	CPoint point)
{
	// Pass the message along
	CScrollView::OnLButtonDown(nFlags, point);

	switch (m_zoomMode) {
   case ZM_IN:
      // Capture the mouse for zooming in
      m_bCaptured = TRUE;
      SetCapture();
      // Save the mouse down point for XOR rect
      ViewDPtoLP(&point);
      m_ptDragRect.SetRect(point.x, point.y, point.x, point.y);
      ::SetCursor(m_hZoomInCursor);  //shik96
      break;
   case ZM_OUT:
      ::SetCursor(m_hZoomOutCursor);
      break;
   case ZM_HAND:
      m_bCaptured = TRUE;
      m_origHandScrollPoint=point;
      ::SetCursor(m_hHandGrapsedCursor);
   default:
      // Do nothing.
      break;
   }
} // OnLButtonDown

/*---------------------------------------------------------------------------
   FUNCTION: OnMouseMove
   PURPOSE : Handle the mouse movement
---------------------------------------------------------------------------*/
#include "afxpriv.h"    // For WM_SETMESSAGESTRING (shik96)
void CZoomView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Pass the message along
	CScrollView::OnMouseMove(nFlags, point);

   /* 2000.3.23
   CWnd *pWnd=((CWinApp*)AfxGetApp())->m_pMainWnd;
   CString message;
   message.Format("x=%d y=%d",point.x,point.y);
   pWnd->SendMessage(WM_SETMESSAGESTRING,0,(LPARAM)(LPCSTR)message);
   */

   CSize sizeScroll; //shik96) ZM_HAND

	if (m_bCaptured) {
		// Get the Device Context
		CClientDC dc(this);
		OnPrepareDC(&dc);
	
		switch (m_zoomMode) {
      case ZM_IN:
         // Draw the drag-rect to erase last rect
         DrawBox(dc, m_ptDragRect);
         // Draw new rect
         dc.DPtoLP(&point);
         m_ptDragRect.BottomRight() = point;
         DrawBox(dc, m_ptDragRect);
         break;
      case ZM_HAND: //shik96, 2000.2.16
         sizeScroll.cx=m_origHandScrollPoint.x-point.x;
         sizeScroll.cy=m_origHandScrollPoint.y-point.y;
         if (abs(sizeScroll.cx)>5 || abs(sizeScroll.cy)>5 ) {
            OnScrollBy(sizeScroll);
            m_origHandScrollPoint=point;
         }
         break;
      default:
         // Do nothing.
         break;
		}
   }

} // OnMouseMove

/*---------------------------------------------------------------------------
   FUNCTION: OnLButtonUp
   PURPOSE : Handle the left mouse release
---------------------------------------------------------------------------*/
void CZoomView::OnLButtonUp (
	UINT nFlags, 
	CPoint point)
{
	// Pass the message along
	CScrollView::OnLButtonUp(nFlags, point);
	
	switch (m_zoomMode) {
   case ZM_IN:
      // Uncapture the mouse?
      if (m_bCaptured) {
         m_bCaptured = FALSE;
         ReleaseCapture();
         // Set back the cross cursor to the Z
         //shik96)	::SetCursor(m_hZoomCursor);
         // Get the Device Context
         CClientDC dc(this);
         OnPrepareDC(&dc);
         // Erase the bounding box
         DrawBox(dc, m_ptDragRect);
         // Now Zoom in on logical rectangle
         DoZoomIn(m_ptDragRect);
      }
      //m_zoomMode=ZM_OFF; //shik96,2000.1.18
      break;
   case ZM_OUT:
      ViewDPtoLP(&point);
      DoZoomOut(&point);
      //m_zoomMode=ZM_OFF; //shik96,2000.1.18
      break;
   case ZM_HAND:
      m_bCaptured = FALSE;
      ::SetCursor(m_hHandSpreadedCursor);
      break;
   default:
      // Do nothing.
      break;
   }
} // OnLButtonUp

/*---------------------------------------------------------------------------
   FUNCTION: OnRButtonDown
   PURPOSE : Handle the right mouse click - CANCELS CURRENT ZOOM MODE OR DRAG
---------------------------------------------------------------------------*/
void CZoomView::OnRButtonDown_(UINT nFlags, CPoint point)
{
	CScrollView::OnRButtonDown(nFlags, point);

   CZoomView::OnChar(27,1,0); //shik96,2000.3.20

} // OnRButtonDown

void CZoomView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)  //shik96, 2000.3.20
{
   CScrollView::OnChar(nChar, nRepCnt, nFlags);

   if (nChar!=27) return;

   // See if currently captured
	if (m_bCaptured) {
		// Maintain current mode, just stop current drag
		m_bCaptured = FALSE;
		ReleaseCapture();
		// Get the Device Context
		CClientDC dc(this);
		OnPrepareDC(&dc);

		switch (m_zoomMode) {
      case ZM_IN:
         // Erase last rect
         DrawBox(dc, m_ptDragRect);
         break;
      default:
         // Do nothing.
         break;
		}
	} else {
		// Cancel current mode
		m_zoomMode = ZM_OFF;
	}
}

/*---------------------------------------------------------------------------
   FUNCTION: OnSetCursor
   PURPOSE : Set the cursor depending on the zoom mode
---------------------------------------------------------------------------*/
BOOL CZoomView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (nHitTest != HTCLIENT)
		return CScrollView::OnSetCursor(pWnd, nHitTest, message);

	switch (m_zoomMode) {
   case ZM_OFF:  ::SetCursor(::LoadCursor(NULL,IDC_ARROW));break;
   case ZM_IN:   ::SetCursor(m_hZoomInCursor);             break;
   case ZM_OUT:  ::SetCursor(m_hZoomOutCursor);            break;
   case ZM_HAND: m_bCaptured ? ::SetCursor(m_hHandGrapsedCursor):
                        ::SetCursor(m_hHandSpreadedCursor);break;
	}

	return TRUE;
}

/*---------------------------------------------------------------------------
   FUNCTION: ViewDPtoLP
   PURPOSE : Same as DPtoLP, but gets the Client DC for the view
---------------------------------------------------------------------------*/
void CZoomView::ViewDPtoLP (
	LPPOINT lpPoints,
	int     nCount)
{
	// Convert to logical units
	// Called from View when no DC is available
	ASSERT(m_nMapMode > 0); // must be set
	CWindowDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(lpPoints, nCount);
} // ViewDPtoLP

/*---------------------------------------------------------------------------
   FUNCTION: ViewLPtoDP
   PURPOSE : Same as LPtoDP, but gets the Client DC for the view
---------------------------------------------------------------------------*/
void CZoomView::ViewLPtoDP (
	LPPOINT lpPoints,
	int     nCount)
{
	// Convert to logical units
	// Called from View when no DC is available
	ASSERT(m_nMapMode > 0); // must be set
	CWindowDC dc(this);
	OnPrepareDC(&dc);
	dc.LPtoDP(lpPoints, nCount);
} // ViewLPtoDP

/*---------------------------------------------------------------------------
   FUNCTION: ClientToDevice
   PURPOSE : Convert from Client coordinates to relative Device coordinates
---------------------------------------------------------------------------*/
void CZoomView::ClientToDevice (
	CPoint &point)
{
	// Need to account for scrollbar position
	CPoint scrollPt = GetDeviceScrollPosition();
	point.x += scrollPt.x;
	point.y += scrollPt.y;
} // ClientToDevice

/*---------------------------------------------------------------------------
   FUNCTION: NormalizeRect
   PURPOSE : Normalize the rectangle
---------------------------------------------------------------------------*/
void CZoomView::NormalizeRect (
	CRect &rect)
{
   if (rect.left > rect.right) {
      int r = rect.right;
      rect.right = rect.left;
      rect.left = r;
   }
   if (rect.top > rect.bottom) {
      int b = rect.bottom;
      rect.bottom = rect.top;
      rect.top = b;
   }
} // NormalizeRect

/*---------------------------------------------------------------------------
   FUNCTION: PersistRatio
   PURPOSE : Make a CSize maintain the given ratio (by shrinking if nescessary)
---------------------------------------------------------------------------*/
void CZoomView::PersistRatio (
	const CSize &orig,
	CSize       &dest,
	CPoint      &remainder)
{
	float ratio1 = (float) orig.cx / orig.cy;
	float ratio2 = (float) dest.cx / dest.cy;
	int   newSize;

	// Do nothing if they are the same
	if (ratio1 > ratio2) {
		// Shrink hieght
		newSize = (int)(dest.cx / ratio1);
		remainder.x = 0;
		remainder.y = dest.cy - newSize;
		dest.cy = newSize;
	} else if (ratio2 > ratio1) {
		// Shrink width
		newSize = (int)(dest.cy * ratio1);
		remainder.x = dest.cx - newSize;
		remainder.y = 0;
		dest.cx = newSize;
	}
} // PersistRatio

//------------------------------------------------------------------------------
// shik96,2000.1.17-1.19+2.9,2K0907
//------------------------------------------------------------------------------
extern "C" {
typedef struct {
   int x,y;
   unsigned int width,height,borderWidth;
} GERECT;
typedef struct _GERECTNODE {
   struct _GERECTNODE *next;
   GERECT rect;
} GERECTNODE;
typedef struct _GERECTLIST {
   GERECTNODE *head,*tail;
   int total;
} GERECTLIST;
int GECreateXRectList (
   GERECTLIST **ppList,
   const GERECT *pRect1, const GERECT *pRect2
   );
int GEDestroyXRectList (
   GERECTLIST *pList
   );
}
BOOL CZoomView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

   /*
   GERECT ClientRect,ClipRect;
   CRect Rect;
   GetClientRect(&Rect);
   ClientRect.x=Rect.left;
   ClientRect.y=Rect.top;
   ClientRect.width=Rect.Width();
   ClientRect.height=Rect.Height();
   pDC->GetClipBox(&Rect);
   if (Rect.IsRectEmpty()) return false;
   ClipRect.x=Rect.left;
   ClipRect.y=Rect.top;
   ClipRect.width=Rect.Width();
   ClipRect.height=Rect.Height();
   GERECTLIST *pList;
   GECreateXRectList(&pList,&ClientRect,&ClipRect);
   GERECTNODE *pNode=pList->head;
   Rect.SetRect(
      pNode->rect.x,pNode->rect.y,
      pNode->rect.x+pNode->rect.width-1,
      pNode->rect.y+pNode->rect.height-1
      );
   CZoomView::ViewDPtoLP(Rect);
   pDC->DrawEdge((LPRECT)Rect,BDR_SUNKENOUTER,BF_BOTTOMRIGHT);
   pDC->SaveDC();
   pDC->SelectStockObject(LTGRAY_BRUSH);
   for (pNode=pNode->next;pNode;pNode=pNode->next) {
      Rect.SetRect(
         pNode->rect.x,pNode->rect.y,
         pNode->rect.x+pNode->rect.width-1,
         pNode->rect.y+pNode->rect.height-1
      );
      CZoomView::ViewDPtoLP(Rect);
      //CScrollView::OnEraseBkgnd(pDC);
      pDC->Rectangle(&Rect);
   }
   pDC->RestoreDC(-1);
   GEDestroyXRectList(pList);

   return true;
   */
   /*
   CBrush br(GetSysColor(COLOR_WINDOW)); 
   FillOutsideRect(pDC,&br);
   return TRUE;  
   */
   /*
   FillOutsideRect(pDC,(CBrush*)pDC->SelectStockObject(LTGRAY_BRUSH));
   return true;
   */
   return CScrollView::OnEraseBkgnd(pDC);
}

void CZoomView::ViewLPtoDP(CRect &Rect)
{
   CPoint PtTopLeft,PtBottomRight;
   PtTopLeft=Rect.TopLeft();
   PtBottomRight=Rect.BottomRight();
   ViewLPtoDP(&PtTopLeft);
   ViewLPtoDP(&PtBottomRight);
   Rect.SetRect(PtTopLeft,PtBottomRight);
}

void CZoomView::ViewDPtoLP(CRect &Rect)
{
   CPoint PtTopLeft,PtBottomRight;
   PtTopLeft=Rect.TopLeft();
   PtBottomRight=Rect.BottomRight();
   ViewDPtoLP(&PtTopLeft);
   ViewDPtoLP(&PtBottomRight);
   Rect.SetRect(PtTopLeft,PtBottomRight);
}

void CZoomView::GetPageSizeOfLogicalCoordinate(CSize &Size)
{
   Size=m_totalLog;
}

void CZoomView::GetPageSizeOfDeviceCoordinate(CSize &Size)
{
   Size=m_totalDev;
}

//20030408
void CZoomView::OnSize(UINT nType, int cx, int cy) 
{
	//CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

   //20030408
   if (!IsWindowVisible()) return;
   if (cx<=m_iPageMargin||cy<=m_iPageMargin) return;
   if (m_zoomMode!=ZM_OFF) return;
   DoZoomFull();

   CScrollView::OnSize(nType, cx, cy); //20030428
}
