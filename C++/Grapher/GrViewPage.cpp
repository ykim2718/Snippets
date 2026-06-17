// GrViewPage.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrViewPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include <math.h>
#include <Float.h>
#include "GrPropertySheet.h"

/////////////////////////////////////////////////////////////////////////////
// CGrViewPage property page

IMPLEMENT_DYNCREATE(CGrViewPage, CPropertyPage)

CGrViewPage::CGrViewPage() : CPropertyPage(CGrViewPage::IDD)
{
	//{{AFX_DATA_INIT(CGrViewPage)
	m_dX1 = 0.2;
	m_dX2 = 0.8;
	m_dY1 = 0.2;
	m_dY2 = 0.8;
	m_dStep = 0.010;
	m_nRow = 2;
	m_nCol = 2;
	m_nRCIndex = 1;
	//}}AFX_DATA_INIT
}

CGrViewPage::~CGrViewPage()
{
}

void CGrViewPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrViewPage)
	DDX_Control(pDX, ID_GRVIEW_Y2_SPIN, m_SpinY2);
	DDX_Control(pDX, ID_GRVIEW_X2_SPIN, m_SpinX2);
	DDX_Control(pDX, ID_GRVIEW_Y1_SPIN, m_SpinY1);
	DDX_Control(pDX, ID_GRVIEW_X1_SPIN, m_SpinX1);
	DDX_Text(pDX, ID_GRVIEW_X1, m_dX1);
	DDV_MinMaxDouble(pDX, m_dX1, -0.5, 1.5);
	DDX_Text(pDX, ID_GRVIEW_X2, m_dX2);
	DDV_MinMaxDouble(pDX, m_dX2, -0.5, 1.5);
	DDX_Text(pDX, ID_GRVIEW_Y1, m_dY1);
	DDV_MinMaxDouble(pDX, m_dY1, -0.5, 1.5);
	DDX_Text(pDX, ID_GRVIEW_Y2, m_dY2);
	DDV_MinMaxDouble(pDX, m_dY2, -0.5, 1.5);
	DDX_Text(pDX, ID_GRVIEW_STEP, m_dStep);
	DDV_MinMaxDouble(pDX, m_dStep, 1.e-003, 5.e-002);
	DDX_Text(pDX, ID_GRVIEW_ROW, m_nRow);
	DDV_MinMaxUInt(pDX, m_nRow, 1, 16);
	DDX_Text(pDX, ID_GRVIEW_COL, m_nCol);
	DDV_MinMaxUInt(pDX, m_nCol, 1, 16);
	DDX_Text(pDX, ID_GRVIEW_RCINDEX, m_nRCIndex);
	DDV_MinMaxUInt(pDX, m_nRCIndex, 1, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrViewPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrViewPage)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRVIEW_X1_SPIN, OnDeltaposGrviewSpinAll)
	ON_BN_CLICKED(ID_GRVIEW_RCLAPPLY, OnGrviewRclapply)
   ON_NOTIFY(UDN_DELTAPOS, ID_GRVIEW_X2_SPIN, OnDeltaposGrviewSpinAll)
   ON_NOTIFY(UDN_DELTAPOS, ID_GRVIEW_Y1_SPIN, OnDeltaposGrviewSpinAll)
   ON_NOTIFY(UDN_DELTAPOS, ID_GRVIEW_Y2_SPIN, OnDeltaposGrviewSpinAll)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
   ON_CONTROL_RANGE(BN_CLICKED,ID_GRVIEW_PRESET_11,ID_GRVIEW_PRESET_188,OnGrviewPresetSize)
   ON_CONTROL_RANGE(BN_CLICKED,ID_GRVIEW_INFLATE,ID_GRVIEW_DEFLATE_Y,OnGrviewResize)
   ON_CONTROL_RANGE(BN_CLICKED,ID_GRVIEW_MOVE_LEFT,ID_GRVIEW_MOVE_DOWN,OnGrviewMove)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrViewPage message handlers

BOOL CGrViewPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   CWnd *pWnd;
   pWnd=GetDlgItem(ID_GRVIEW_X1);
   m_SpinX1.SetBuddy(pWnd);
   pWnd=GetDlgItem(ID_GRVIEW_Y1);
   m_SpinY1.SetBuddy(pWnd);
   pWnd=GetDlgItem(ID_GRVIEW_X2);
   m_SpinX2.SetBuddy(pWnd);
   pWnd=GetDlgItem(ID_GRVIEW_Y2);
   m_SpinY2.SetBuddy(pWnd);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CGrViewPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bResult=CPropertyPage::OnKillActive();

   UpdateData(TRUE);
   if (m_dX1>=m_dX2 || m_dX1>=m_dX2) {
      CString sTemp;
      sTemp.Format(
         "Warning, invalid viewport coordination !\n"
         "Ridiculous relation each other : x1=%.3f x2=%.3f y1=%.3f y2=%.3f",
         m_dX1,m_dX2,m_dY1,m_dY2);
      MessageBox(sTemp,NULL,MB_ICONWARNING);
      return FALSE;
   } else if ((m_dX2-m_dX1)<0.1 || (m_dY2-m_dY1)<0.1) {
      CString sTemp;
      sTemp.Format(
         "Warning, much smaller rectangle to draw than the smallest 0.1x0.1 !\n"
         "Coordination : x1=%.3f x2=%.3f y1=%.3f y2=%.3f",
         m_dX1,m_dX2,m_dY1,m_dY2);
      MessageBox(sTemp,NULL,MB_ICONWARNING);
      return FALSE;
   }

   CGrapherApp *pApp=(CGrapherApp*)AfxGetApp();
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return bResult;

   const char *qView=PLOTSCRIPT_VIEW,
              *qX1="x1=",*qX2="x2=",*qY1="y1=",*qY2="y2=";
   int nPos,nLength;
   CString sTemp;

   nPos=SEGetOptionPosition(
      Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,1,0);
   if (nPos==-1) {
      nPos=SEGetSafeOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,1,0);
      Script.Insert(nPos,qView);
      Script.Insert(nPos+strlen(qView)," ");
   }

   nPos=SEGetOptionPosition(
      Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,1,qX1,1,0);
   sTemp.Format("%s%.3f ",qX1,m_dX1);
   if (nPos==-1) {
      nPos=SEGetSafeOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,qX1,1,0);
      Script.Insert(nPos,sTemp);
   } else if (nPos>=0) {
      nLength=SEGetOptionLength(Script,nPos);
      Script.Delete(nPos,nLength);
      Script.Insert(nPos,sTemp);
   }

   nPos=SEGetOptionPosition(
      Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,1,qX2,1,0);
   sTemp.Format("%s%.3f ",qX2,m_dX2);
   if (nPos==-1) {
      nPos=SEGetSafeOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,qX2,1,0);
      Script.Insert(nPos,sTemp);
   } else if (nPos>=0) {
      nLength=SEGetOptionLength(Script,nPos);
      Script.Delete(nPos,nLength);
      Script.Insert(nPos,sTemp);
   }

   nPos=SEGetOptionPosition(
      Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,1,qY1,1,0);
   sTemp.Format("%s%.3f ",qY1,m_dY1);
   if (nPos==-1) {
      nPos=SEGetSafeOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,qY1,1,0);
      Script.Insert(nPos,sTemp);
   } else if (nPos>=0) {
      nLength=SEGetOptionLength(Script,nPos);
      Script.Delete(nPos,nLength);
      Script.Insert(nPos,sTemp);
   }

   nPos=SEGetOptionPosition(
      Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,1,qY2,1,0);
   sTemp.Format("%s%.3f ",qY2,m_dY2);
   if (nPos==-1) {
      nPos=SEGetSafeOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,qView,qY2,1,0);
      Script.Insert(nPos,sTemp);
   } else if (nPos>=0) {
      nLength=SEGetOptionLength(Script,nPos);
      Script.Delete(nPos,nLength);
      Script.Insert(nPos,sTemp);
   }

   return bResult;
}

BOOL CGrViewPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return CPropertyPage::OnSetActive();

   m_dX1=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_VIEW,1,"x1=",1,0);
   m_dX2=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_VIEW,1,"x2=",1,0);
   m_dY1=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_VIEW,1,"y1=",1,0);
   m_dY2=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_VIEW,1,"y2=",1,0);

   if (m_dX1==DBL_MIN || m_dX2==DBL_MIN ||
      m_dY1==DBL_MIN || m_dY2==DBL_MIN) {
      m_dX1=0.2;m_dX2=0.8;
      m_dY1=0.2;m_dY2=0.8;
   }

   /* 2001.0224
   HENHMETAFILE hEMF=pSheet->m_PlotPage.m_EmfCanvas.GetEnhMetaFile();
   if (hEMF) {
      ((CStatic*)GetDlgItem(ID_EMF_CANVAS_AT_VIEW))->SetEnhMetaFile(hEMF);
   }
   */

   if (m_bFirstSetActive) UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}


void CGrViewPage::OnDeltaposGrviewSpinAll(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

   UpdateData(TRUE); // 200302224
   double nDelta=pNMUpDown->iDelta*-0.01;
   switch (pNMHDR->idFrom) {
   case ID_GRVIEW_X1_SPIN : m_dX1+=nDelta; break;
   case ID_GRVIEW_X2_SPIN : m_dX2+=nDelta; break;
   case ID_GRVIEW_Y1_SPIN : m_dY1+=nDelta; break;
   case ID_GRVIEW_Y2_SPIN : m_dY2+=nDelta; break;
   }
   RoundCoordinateAtTwoDecimalPoint();
   UpdateData(FALSE);
	
	*pResult = 0;
}

void CGrViewPage::OnGrviewPresetSize( UINT nID ) 
{
	// TODO: Add your control notification handler code here

	if (!UpdateData(TRUE)) return;
   switch (nID) {
   case ID_GRVIEW_PRESET_11  : m_dX1=0.20;m_dX2=0.80;m_dY1=0.20;m_dY2=0.80;break;
   case ID_GRVIEW_PRESET_121 : m_dX1=0.25;m_dX2=0.75;m_dY1=0.55;m_dY2=0.95;break;
   case ID_GRVIEW_PRESET_122 : m_dX1=0.25;m_dX2=0.75;m_dY1=0.05;m_dY2=0.45;break;
   case ID_GRVIEW_PRESET_131 : m_dX1=0.30;m_dX2=0.70;m_dY1=0.75;m_dY2=1.05;break;
   case ID_GRVIEW_PRESET_132 : m_dX1=0.30;m_dX2=0.70;m_dY1=0.35;m_dY2=0.65;break;
   case ID_GRVIEW_PRESET_133 : m_dX1=0.30;m_dX2=0.70;m_dY1=-.05;m_dY2=0.25;break;
   case ID_GRVIEW_PRESET_141 : m_dX1=0.15;m_dX2=0.46;m_dY1=0.55;m_dY2=0.85;break;
   case ID_GRVIEW_PRESET_142 : m_dX1=0.54;m_dX2=0.85;m_dY1=0.55;m_dY2=0.85;break;
   case ID_GRVIEW_PRESET_143 : m_dX1=0.15;m_dX2=0.46;m_dY1=0.15;m_dY2=0.45;break;
   case ID_GRVIEW_PRESET_144 : m_dX1=0.54;m_dX2=0.85;m_dY1=0.15;m_dY2=0.45;break;
   case ID_GRVIEW_PRESET_161 : m_dX1=0.20;m_dX2=0.45;m_dY1=0.67;m_dY2=0.90;break;
   case ID_GRVIEW_PRESET_162 : m_dX1=0.55;m_dX2=0.80;m_dY1=0.67;m_dY2=0.90;break;
   case ID_GRVIEW_PRESET_163 : m_dX1=0.20;m_dX2=0.45;m_dY1=0.37;m_dY2=0.60;break;
   case ID_GRVIEW_PRESET_164 : m_dX1=0.55;m_dX2=0.80;m_dY1=0.37;m_dY2=0.60;break;
   case ID_GRVIEW_PRESET_165 : m_dX1=0.20;m_dX2=0.45;m_dY1=0.07;m_dY2=0.30;break;
   case ID_GRVIEW_PRESET_166 : m_dX1=0.55;m_dX2=0.80;m_dY1=0.07;m_dY2=0.30;break;
   case ID_GRVIEW_PRESET_181 : m_dX1=0.15;m_dX2=0.48;m_dY1=0.84;m_dY2=1.09;break;
   case ID_GRVIEW_PRESET_182 : m_dX1=0.58;m_dX2=0.92;m_dY1=0.84;m_dY2=1.09;break;
   case ID_GRVIEW_PRESET_183 : m_dX1=0.15;m_dX2=0.48;m_dY1=0.53;m_dY2=0.78;break;
   case ID_GRVIEW_PRESET_184 : m_dX1=0.58;m_dX2=0.92;m_dY1=0.53;m_dY2=0.78;break;
   case ID_GRVIEW_PRESET_185 : m_dX1=0.15;m_dX2=0.48;m_dY1=0.22;m_dY2=0.47;break;
   case ID_GRVIEW_PRESET_186 : m_dX1=0.58;m_dX2=0.92;m_dY1=0.22;m_dY2=0.47;break;
   case ID_GRVIEW_PRESET_187 : m_dX1=0.15;m_dX2=0.48;m_dY1=-.09;m_dY2=0.16;break;
   case ID_GRVIEW_PRESET_188 : m_dX1=0.58;m_dX2=0.92;m_dY1=-.09;m_dY2=0.16;break;
   }
   UpdateData(FALSE);
}

void CGrViewPage::OnGrviewResize( UINT nID ) 
{
	// TODO: Add your control notification handler code here

   if (!UpdateData(TRUE)) return;
   switch (nID) {
   case ID_GRVIEW_INFLATE :
      m_dX1-=m_dStep;m_dX2+=m_dStep;
      m_dY1-=m_dStep;m_dY2+=m_dStep;break;
   case ID_GRVIEW_DEFLATE :
      m_dX1+=m_dStep;m_dX2-=m_dStep;
      m_dY1+=m_dStep;m_dY2-=m_dStep;break;
   case ID_GRVIEW_INFLATE_X :
      m_dX1-=m_dStep;m_dX2+=m_dStep;break;
   case ID_GRVIEW_INFLATE_Y :
      m_dY1-=m_dStep;m_dY2+=m_dStep;break;
   case ID_GRVIEW_DEFLATE_X :
      m_dX1+=m_dStep;m_dX2-=m_dStep;break;
   case ID_GRVIEW_DEFLATE_Y :
      m_dY1+=m_dStep;m_dY2-=m_dStep;break;
   }
   RoundCoordinateAtTwoDecimalPoint();
   UpdateData(FALSE);
}

//Y.Kim,20030216
void CGrViewPage::OnGrviewRclapply() 
{
	// TODO: Add your control notification handler code here

	if (!UpdateData(true)) return;

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   int bLandscape=SEGetOptionPosition(Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GOUT,1,"landscape",1,0);
   bLandscape=bLandscape>0 ? 1:0;

   double dWidth,dHeight;
   double iSpace=0.03,oSpace=0.05;
   double eMargin=0.28; // 0.28x2=0.56 : outside margin with an orientation.
   double xOrigin,yOrigin;

   xOrigin=(bLandscape ? -1*eMargin:0)+oSpace;
   yOrigin=(bLandscape ? 0:-1*eMargin)+oSpace;

   dWidth=((bLandscape ? 1+eMargin*2:1)-oSpace*2)/m_nCol;
   dHeight=((bLandscape ? 1:1+eMargin*2)-oSpace*2)/m_nRow;

   int nRow=(int)((m_nRCIndex-1)/m_nCol)%m_nRow;
   int nCol=(m_nRCIndex-1)%m_nCol;
   nRow=m_nRow-nRow-1; // top-down

   m_dX1=dWidth*nCol; m_dX2=m_dX1+dWidth;
   m_dY1=dHeight*nRow;m_dY2=m_dY1+dHeight;

   m_dX1=m_dX1+iSpace+xOrigin;
   m_dX2=m_dX2-iSpace+xOrigin;
   m_dY1=m_dY1+iSpace+yOrigin;
   m_dY2=m_dY2-iSpace+yOrigin;

   RoundCoordinateAtTwoDecimalPoint();

   UpdateData(false);
}

void CGrViewPage::OnGrviewMove( UINT nID ) 
{
	// TODO: Add your control notification handler code here

   if (!UpdateData(TRUE)) return;
   switch (nID) {
   case ID_GRVIEW_MOVE_LEFT : m_dX1-=m_dStep;m_dX2-=m_dStep;break;
   case ID_GRVIEW_MOVE_RIGHT: m_dX1+=m_dStep;m_dX2+=m_dStep;break;
   case ID_GRVIEW_MOVE_UP   : m_dY1+=m_dStep;m_dY2+=m_dStep;break;
   case ID_GRVIEW_MOVE_DOWN : m_dY1-=m_dStep;m_dY2-=m_dStep;break;
   }
   UpdateData(FALSE);
}

void CGrViewPage::RoundCoordinateAtTwoDecimalPoint()
{
   m_dX1=floor(m_dX1*100+0.5)/100.0;
   m_dX2=floor(m_dX2*100+0.5)/100.0;
   m_dY1=floor(m_dY1*100+0.5)/100.0;
   m_dY2=floor(m_dY2*100+0.5)/100.0;
}
