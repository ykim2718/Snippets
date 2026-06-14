// zoomview.h : Implements Zooming functions in a CScrollView window
// Written by Brad Pirtle, CS:72450,1156, Internet:pirtle@qlogic.com
// Copyright 1994, QuickLogic Corp., all rights reserved.
// Version 1.0
//
// modified by shik96@unitel.co.kr , 00.01.17-
//

#ifndef ZOOMVIEW_H
#define ZOOMVIEW_H

/////////////////////////////////////////////////////////////////////////////
// CZoomView view
class CZoomView : public CScrollView
{
	DECLARE_DYNCREATE(CZoomView)

// Operations
public:
   typedef enum {ZP_A3,ZP_A3H,ZP_A4,ZP_A4H,ZP_LT,ZP_LTH} ZoomPage_; //shik96
   int       GetZoomPage() {return m_zoomPage;};
   float     GetZoomPageDpiFactor() {return m_zoomPageDpiFactor;};
   void      SetZoomSizes(ZoomPage_ zp,
      const SIZE& sizePage = sizeDefault,const SIZE& sizeLine = sizeDefault);
	void      SetZoomSizes(SIZE sizeTotal,
      const SIZE& sizePage = sizeDefault,const SIZE& sizeLine = sizeDefault);
	void      CenterOnLogicalPoint(CPoint ptCenter);
	CPoint    GetLogicalCenterPoint(void);

	typedef enum {ZM_OFF,ZM_IN,ZM_OUT,ZM_HAND} ZoomMode_;
	void      SetZoomMode   (ZoomMode_ zoomMode);
	ZoomMode_ GetZoomMode() {return m_zoomMode;};
   float     GetZoomScale() {return m_zoomScale;};
	int       DoZoomIn      (CRect &rect);
	int       DoZoomIn      (CPoint *point = NULL, float delta = 1.25);
	int       DoZoomOut     (CPoint *point = NULL, float delta = 1.25);
	int       DoZoomFull    ();
   int       DoZoomPercent (int percent = 100); //shik96

   void      NotifyZoom(void) {};

	void      ViewDPtoLP (LPPOINT lpPoints, int nCount = 1);
	void      ViewLPtoDP (LPPOINT lpPoints, int nCount = 1);
	void      ClientToDevice(CPoint &point);
	void      NormalizeRect(CRect &rect);
	void 		 DrawBox(CDC &dc, CRect &rect, BOOL xor = TRUE);
	void 		 DrawLine(CDC &dc, const int &x1, const int &y1, 
							 const int &x2, const int &y2, BOOL xor = TRUE);

// Implementation
protected:
	CZoomView(); // protected constructor used by dynamic creation
	virtual ~CZoomView();
   virtual void OnInitialUpdate(); //shik96
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif //_DEBUG

private:
	// Internally called functions
	void 		 PersistRatio(const CSize &orig, CSize &dest, CPoint &remainder);
	void      CalculateBars(void);

	// Private member variables
   int       m_iPageMargin; //YKim,20030408
   ZoomPage_ m_zoomPage;   //shik96
   int       m_zoomPageDPI; //shik96,2000.2.10
   float     m_zoomPageDpiFactor; //shik96,2000.2.10
	ZoomMode_ m_zoomMode;
	BOOL      m_bCaptured;
	CRect     m_ptDragRect;
	CSize     m_origTotalDev;  //Origional total size in device units
	CSize     m_origPageDev;   //Origional per page scroll size in device units
	CSize     m_origLineDev;   //Origional per line scroll size in device units
	float     m_zoomScale;
	HCURSOR   m_hZoomInCursor,m_hZoomOutCursor,
             m_hHandSpreadedCursor,m_hHandGrapsedCursor;
   CPoint    m_origHandScrollPoint; //shik96: for handCursor-Action

public:
	void GetPageSizeOfDeviceCoordinate(CSize &Size);
	void GetPageSizeOfLogicalCoordinate(CSize &Size);
	virtual void OnDraw(CDC* pDC) {CZoomView::OnDraw(pDC);}; // Pure Virtual
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	void ViewDPtoLP(CRect &Rect);
	void ViewLPtoDP(CRect& Rect);
	// Generated message map functions
	//{{AFX_MSG(CZoomView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

   afx_msg void OnRButtonDown_(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif
