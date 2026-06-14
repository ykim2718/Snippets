// GrSlctPage.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrSlctPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include <float.h>
#include "tools.h" //20030222
#include "plot.h" //20030222
#include "number.h" //20030803
#include "GrPropertySheet.h"
#include "SmallFontAttrDialog.h"

static char *qLineStyleStrings[]={
   "solid",
   "longdashed __ __ __",
   "shortdashed _ _ _ _",
   "dashdotted _ . _ . _",
   "dotted . . . . . . ."
};

static struct _qBatchJobList {
   int nID;
   char *qString;
} qBatchJobList[] = {
   ID_GRSLCT_SYMBOL_TYPE,"Symbol type",
   ID_GRSLCT_SYMBOL_COLOR,"Symbol color",
   ID_GRSLCT_SYMBOL_SOLID,"Symbol solid",
   ID_GRSLCT_SYMBOL_SIZE,"Symbol size",
   ID_GRSLCT_LINECONNECTION_CB,"Line on&off",
   ID_GRSLCT_SYMBOL_LINE_COLOR,"Line color",
   ID_GRSLCT_SYMBOL_LINE_STYLE,"Line style",
   ID_GRSLCT_SYMBOL_LINE_WIDTH,"Line width",
   ID_GRSLCT_LEGEND_CB,"Legend on&off",
   ID_GRSLCT_LEGEND_TEXT,"Legend text",
   ID_GRSLCT_LEGEND_SIZE,"Legend size",
   ID_GRSLCT_ETC_MOMENT_RANGE,"Moment range",
   ID_GRSLCT_ETC_MAP_COLOR_MIN,"Map color min",
   ID_GRSLCT_ETC_MAP_COLOR_MAX,"Map color max",
   ID_GRSLCT_ETC_MAP_COLOR_TOTAL,"Map color total",
   ID_GRSLCT_ETC_MAP_NO_FORMAT,"Map no. format"
};

/////////////////////////////////////////////////////////////////////////////
// CGrSlctPage property page

IMPLEMENT_DYNCREATE(CGrSlctPage, CPropertyPage)

CGrSlctPage::CGrSlctPage() : CPropertyPage(CGrSlctPage::IDD)
{
	//{{AFX_DATA_INIT(CGrSlctPage)
	m_bSymbSolid = TRUE;
	m_sLegendText = _T("");
	m_nSymbPenNo = 0;
	m_bLegend = FALSE;
	m_bLineConnection = TRUE;
	m_bSymbol = TRUE;
	m_nEtcMapColorTotal = 5;
	m_nEtcMomentRange = 100;
	m_nLegendSize = 5;
	m_nSymbSize = 5;
	m_sEtcMapNoFormat = _T("");
	m_nSymbRepetition = 0;
	m_nLineWidth = 1;
	m_bLegendXLocAuto = TRUE;
	m_bLegendYLocAuto = TRUE;
	m_sXVariable = _T("");
	m_sYVariable = _T("");
	m_sZVariable = _T("");
	m_sLegendX = _T("");
	m_sLegendY = _T("");
	//}}AFX_DATA_INIT
   
   m_nPrecedingSliderPosition=-1; // also OnSetActive();

   m_SymbColorBtn.nCurrentColor=RGB(0,0,0);
   m_SymbLineColorBtn.nCurrentColor=RGB(64,64,64); // Dark gray
   m_EtcMapColorMinBtn.nCurrentColor=RGB(255,255,0);
   m_EtcMapColorMaxBtn.nCurrentColor=RGB(255,0,0);
}

CGrSlctPage::~CGrSlctPage()
{
}

void CGrSlctPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrSlctPage)
	DDX_Control(pDX, ID_GRSLCT_LEGEND_SLIDER_TEXT, m_LegendSliderLabel);
	DDX_Control(pDX, ID_GRSLCT_LEGEND_SLIDER, m_LegendSlider);
	DDX_Check(pDX, ID_GRSLCT_SYMBOL_SOLID, m_bSymbSolid);
	DDX_Text(pDX, ID_GRSLCT_LEGEND_TEXT, m_sLegendText);
	DDV_MaxChars(pDX, m_sLegendText, 64);
	DDX_Text(pDX, ID_GRSLCT_SYMBOL_PEN, m_nSymbPenNo);
	DDV_MinMaxUInt(pDX, m_nSymbPenNo, 0, 16);
	DDX_Check(pDX, ID_GRSLCT_LEGEND_CB, m_bLegend);
	DDX_Check(pDX, ID_GRSLCT_LINECONNECTION_CB, m_bLineConnection);
	DDX_Check(pDX, ID_GRSLCT_SYMBOL_CB, m_bSymbol);
	DDX_Text(pDX, ID_GRSLCT_ETC_MAP_COLOR_TOTAL, m_nEtcMapColorTotal);
	DDV_MinMaxUInt(pDX, m_nEtcMapColorTotal, 2, 19);
	DDX_Text(pDX, ID_GRSLCT_ETC_MOMENT_RANGE, m_nEtcMomentRange);
	DDV_MinMaxUInt(pDX, m_nEtcMomentRange, 50, 100);
	DDX_Text(pDX, ID_GRSLCT_LEGEND_SIZE, m_nLegendSize);
	DDV_MinMaxUInt(pDX, m_nLegendSize, 1, 36);
	DDX_Text(pDX, ID_GRSLCT_SYMBOL_SIZE, m_nSymbSize);
	DDV_MinMaxUInt(pDX, m_nSymbSize, 1, 36);
	DDX_CBString(pDX, ID_GRSLCT_ETC_MAP_NO_FORMAT, m_sEtcMapNoFormat);
	DDX_Text(pDX, ID_GRSLCT_SYMBOL_NCOPY, m_nSymbRepetition);
	DDV_MinMaxUInt(pDX, m_nSymbRepetition, 0, 1024);
	DDX_Text(pDX, ID_GRSLCT_SYMBOL_LINE_WIDTH, m_nLineWidth);
	DDV_MinMaxUInt(pDX, m_nLineWidth, 1, 36);
	DDX_Check(pDX, ID_GRSLCT_LEGEND_X_AUTO, m_bLegendXLocAuto);
	DDX_Check(pDX, ID_GRSLCT_LEGEND_Y_AUTO, m_bLegendYLocAuto);
	DDX_Text(pDX, ID_GRSLCT_XCOLS, m_sXVariable);
	DDX_Text(pDX, ID_GRSLCT_YCOLS, m_sYVariable);
	DDX_Text(pDX, ID_GRSLCT_ZCOLS, m_sZVariable);
	DDX_Text(pDX, ID_GRSLCT_LEGEND_X, m_sLegendX);
	DDX_Text(pDX, ID_GRSLCT_LEGEND_Y, m_sLegendY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrSlctPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrSlctPage)
	ON_BN_CLICKED(ID_GRSLCT_SYMBOL_SOLID, OnGrslctSymbolSolid)
	ON_BN_CLICKED(ID_GRSLCT_ADD, OnGrslctAdd)
	ON_BN_CLICKED(ID_GRSLCT_ADDALL, OnGrslctAddall)
	ON_BN_CLICKED(ID_GRSLCT_DEL, OnGrslctDelete)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(ID_GRSLCT_SYMBOL_CB, OnGrslctSymbolCb)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRSLCT_ETC_MOMENT_RANGE_SPIN, OnDeltaposOfAllSpins)
	ON_BN_CLICKED(ID_GRSLCT_LEGEND_TEXT_FONTATTR, OnGrslctLegendTextFontattr)
	ON_BN_CLICKED(ID_GRSLCT_PREV, OnGrslctPrev)
	ON_BN_CLICKED(ID_GRSLCT_NEXT, OnGrslctNext)
	ON_BN_CLICKED(ID_GRSLCT_LEGEND_X_AUTO, OnGrslctLegendXLocAuto)
	ON_BN_CLICKED(ID_GRSLCT_LEGEND_Y_AUTO, OnGrslctLegendYLocAuto)
	ON_LBN_SELCHANGE(ID_GRSLCT_BATCHJOB, OnSelchangeGrslctBatchjob)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRSLCT_SYMBOL_SIZE_SPIN, OnDeltaposOfAllSpins)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRSLCT_ETC_MAP_COLOR_TOTAL_SPIN, OnDeltaposOfAllSpins)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRSLCT_LEGEND_SIZE_SPIN, OnDeltaposOfAllSpins)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRSLCT_SYMBOL_LINE_WIDTH_SPIN, OnDeltaposOfAllSpins)
	//}}AFX_MSG_MAP
   ON_MESSAGE(WM_COLORBTNMESSAGE,OnMyMessage)
   ON_MESSAGE(WM_PLOTSYMBOLBTNMESSAGE,OnMyMessage)
   ON_CONTROL_RANGE(BN_CLICKED,ID_GRSYMB_DISPLAY_ON,ID_GRSYMB_DISPLAY_OFF,OnGrsymbOnoffTool)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrSlctPage message handlers

BOOL CGrSlctPage::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
   if (pMsg->message==WM_KEYDOWN) {
      CWnd *pFocused=GetFocus();
      if (pFocused->m_hWnd!=m_LegendSlider.m_hWnd) {
         switch (pMsg->wParam) {
         case VK_PRIOR : m_LegendSlider.SendMessage(WM_KEYDOWN,VK_LEFT,0);break;
         case VK_NEXT : m_LegendSlider.SendMessage(WM_KEYDOWN,VK_RIGHT,0);break;
         }
      }
   }

	if (m_ToolTipForPrev.m_hWnd) m_ToolTipForPrev.RelayEvent(pMsg);
   if (m_ToolTipForNext.m_hWnd) m_ToolTipForNext.RelayEvent(pMsg);
   if (m_ToolTipForBatch.m_hWnd) m_ToolTipForBatch.RelayEvent(pMsg);

	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CGrSlctPage::InitToolTipsOnInitDialog()
{
   if (m_ToolTipForPrev.m_hWnd==NULL) {
      m_ToolTipForPrev.Create(this);
		m_ToolTipForPrev.Activate(TRUE);
      CWnd *pWnd=GetDlgItem(ID_GRSLCT_PREV);
      CRect Rect;pWnd->GetClientRect(Rect);
      m_ToolTipForPrev.AddTool(pWnd,"You can use Page-Up key instead.",Rect,1);
      m_ToolTipForPrev.SetDelayTime(TTDT_INITIAL,0);
   }
   if (m_ToolTipForNext.m_hWnd==NULL) {
      m_ToolTipForNext.Create(this);
		m_ToolTipForNext.Activate(TRUE);
      CWnd *pWnd=GetDlgItem(ID_GRSLCT_NEXT);
      CRect Rect;pWnd->GetClientRect(Rect);
      m_ToolTipForNext.AddTool(pWnd,"Can use Page-Down key to navigate.",Rect,1);
      m_ToolTipForNext.SetDelayTime(TTDT_INITIAL,0);
   }
   if (m_ToolTipForBatch.m_hWnd==NULL) {
      m_ToolTipForBatch.Create(this);
		m_ToolTipForBatch.Activate(TRUE);
      CWnd *pWnd=GetDlgItem(ID_GRSLCT_BATCHJOB);
      CRect Rect;pWnd->GetClientRect(Rect);
      m_ToolTipForBatch.AddTool(pWnd,"No selection for batch process.",Rect,1);
      m_ToolTipForBatch.SetDelayTime(TTDT_INITIAL,0);
   }
}

BOOL CGrSlctPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   InitToolTipsOnInitDialog();

   LOGFONT LogFont;
   GetFont()->GetLogFont(&LogFont);
   LogFont.lfUnderline=TRUE;
   m_MyFont.CreateFontIndirect(&LogFont);
   GetDlgItem(ID_GRSLCT_SYMBOL_CB)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRSLCT_LINECONNECTION_CB)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRSLCT_LEGEND_CB)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRSLCT_MOMENT)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRSLCT_MAP)->SetFont(&m_MyFont);

   m_SymbColorBtn.SubclassDlgItem(ID_GRSLCT_SYMBOL_COLOR,this);
   m_SymbLineColorBtn.SubclassDlgItem(ID_GRSLCT_SYMBOL_LINE_COLOR,this);
   m_SymbTypeBtn.SubclassDlgItem(ID_GRSLCT_SYMBOL_TYPE,this);

   SetComboBoxStringsOfLineStyle(ID_GRSLCT_SYMBOL_LINE_STYLE);

   m_EtcMapColorMinBtn.SubclassDlgItem(ID_GRSLCT_ETC_MAP_COLOR_MIN,this);
   m_EtcMapColorMaxBtn.SubclassDlgItem(ID_GRSLCT_ETC_MAP_COLOR_MAX,this);

   ((CComboBox*)GetDlgItem(ID_GRSLCT_ETC_MAP_NO_FORMAT))->SetCurSel(0);

   SetListBoxStringsOfBatchJob();

   OnGrslctLegendXLocAuto();
   OnGrslctLegendYLocAuto();

 	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrSlctPage::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

   switch (wParam) {
   case WM_COLORBTNMESSAGE :
      switch (lParam) {
      case ID_GRSLCT_SYMBOL_COLOR :
         m_SymbTypeBtn.m_nSymbFillColor=m_SymbColorBtn.nCurrentColor;
         break;
      case ID_GRSLCT_SYMBOL_LINE_COLOR :
         m_SymbTypeBtn.m_nSymbStrokeColor=m_SymbLineColorBtn.nCurrentColor;
         break;
      }
      m_SymbTypeBtn.Invalidate();
      break;
   case WM_PLOTSYMBOLBTNMESSAGE :
      // Nothing to do. 20010319
      break;
   }
}

void CGrSlctPage::OnGrslctSymbolSolid() 
{
	// TODO: Add your control notification handler code here
   UpdateData(TRUE);
	m_SymbTypeBtn.m_bFillSymbol=m_bSymbSolid;
   m_SymbTypeBtn.m_bStrokeSymbol=TRUE;
   m_SymbTypeBtn.Invalidate();
}

void CGrSlctPage::OnGrslctLegendXLocAuto() 
{
	// TODO: Add your control notification handler code here
	int bCheck=((CButton*)GetDlgItem(ID_GRSLCT_LEGEND_X_AUTO))->GetCheck();
	GetDlgItem(ID_GRSLCT_LEGEND_X)->EnableWindow(bCheck==FALSE);
}

void CGrSlctPage::OnGrslctLegendYLocAuto() 
{
	// TODO: Add your control notification handler code here
	int bCheck=((CButton*)GetDlgItem(ID_GRSLCT_LEGEND_Y_AUTO))->GetCheck();
   GetDlgItem(ID_GRSLCT_LEGEND_Y)->EnableWindow(bCheck==FALSE);
}

void CGrSlctPage::OnGrslctAdd()  //Y.Kim,20030216
{
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &sScript=pSheet->m_sGrScript;
   if (sScript.IsEmpty()) return;

   int nIndex=m_LegendSlider.GetRangeMax()+1;
   CGrSlctPage::SetSymbolScriptFromDialog(nIndex);
   m_LegendSlider.SetRangeMax(nIndex); //Y.Kim,20030217
   m_LegendSlider.SetPos(nIndex);
   m_nPrecedingSliderPosition=nIndex; //Y.Kim,20030217-L-
   CGrSlctPage::OnSetActive();
}

void CGrSlctPage::OnGrslctAddall()  //Y.Kim,20030211
{
	CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &sScript=pSheet->m_sGrScript;
   if (sScript.IsEmpty()) return;

	CWinApp *pApp=AfxGetApp();
   CString sDefaultSymbol,sIndex,sReturn,sReturnTuned;
   int nCount,nIndex;

   nIndex=SEGetOptionPosition(sScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,"type=",1,0);
   nCount=nIndex<0 ? 0:SEGetOptionFrequencyInaRange(sScript,nIndex,"type=");
   nCount=GetXYZVariableColumnCount('y')-nCount;
   if (nCount<=0) return;

   nIndex=0;
   while (nCount--) {
      sIndex.Format(RegKeyDefaultSymbolFormat,nIndex);
      sReturn=pApp->GetProfileString(RegKeyGrAttributes,sIndex);
      if (sReturn.IsEmpty()) {
         sIndex.Format(RegKeyDefaultSymbolFormat,nIndex=0);
         sReturn=pApp->GetProfileString(RegKeyGrAttributes,sIndex);
      }
      sIndex.Format("#%02d",nIndex+1);
      sReturnTuned.Format(sReturn,0,sIndex); // nCopy=0
      nIndex++;
      sDefaultSymbol+=sReturnTuned+"\n";
   }

   //
   int nPos=SEGetSafeOptionPosition(
         (LPCTSTR)sScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
         PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,
         PLOTSCRIPT_TYPE,INT_MAX, //Y.Kim,20030217
         0);
   sDefaultSymbol.Insert(0," ");
   sScript.Insert(nPos,(LPCTSTR)sDefaultSymbol);
   nPos=m_LegendSlider.GetRangeMax()+1; //Y.Kim,20030216+17
   m_LegendSlider.SetRangeMax(nPos); //Y.Kim,20030216+17
   m_LegendSlider.SetPos(nPos); //Y.Kim,20030216+17
   m_nPrecedingSliderPosition=nPos; //Y.Kim,20030217-L-
   CGrSlctPage::OnSetActive();

   m_LegendSlider.ClearSel(true);//-_-
}

void CGrSlctPage::OnGrslctDelete() 
{
	CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &sScript=pSheet->m_sGrScript;
   if (sScript.IsEmpty()) return;

   int nSliderPos=m_LegendSlider.GetPos();
   if (nSliderPos<=0) return;
   int nSliderMin=m_LegendSlider.GetRangeMin();
   int nIndex=SEGetOptionPosition(
      sScript,
      PLOTSCRIPT_BEGINNING,1,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,
      PLOTSCRIPT_TYPE,nSliderPos,
      0);
   int nLength=SEGetOptionBlockLength(sScript,nIndex);
   sScript.Delete(nIndex,nLength);
   CGrSlctPage::OnSetActive();

   m_LegendSlider.ClearSel(true);//-_-
}

void CGrSlctPage::OnHScrollForSlider()
{
   int nMin,nMax;
   m_LegendSlider.GetRange(nMin,nMax);
   if (1<=nMin && m_nPrecedingSliderPosition<=nMax) {
      if (m_nPrecedingSliderPosition<=0) m_nPrecedingSliderPosition=1;
      CGrSlctPage::SetSymbolScriptFromDialog(m_nPrecedingSliderPosition);
   }

   int nCurrentPos=m_LegendSlider.GetPos();
   CString sText;
   sText.Format("%02d/%02d",nCurrentPos,nMax);
   m_LegendSliderLabel.SetWindowText(sText);
   CGrSlctPage::SetSymbolScriptToDialog(nCurrentPos);

   m_nPrecedingSliderPosition=nCurrentPos;
}

void CGrSlctPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

   CGrSlctPage::OnHScrollForSlider();

   //
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGrSlctPage::OnGrslctSymbolCb() 
{
	// TODO: Add your control notification handler code here
   //20030225
   //m_bSymbol=((CButton*)GetDlgItem(ID_GRSLCT_SYMBOL_CB))->GetCheck();
}

void CGrSlctPage::SetComboBoxStringsOfLineStyle(int nID)
{
   CComboBox *pCB=(CComboBox*)GetDlgItem(nID);
   int nIndex,nCount=sizeof(qLineStyleStrings)/sizeof(qLineStyleStrings[0]);   
   for (nIndex=0;nIndex<nCount;nIndex++) {
      pCB->AddString(qLineStyleStrings[nIndex]);
   }
   pCB->SetCurSel(0);
}

void CGrSlctPage::SetListBoxStringsOfBatchJob()
{
   CListBox *pLB=(CListBox*)GetDlgItem(ID_GRSLCT_BATCHJOB);
   int nIndex,nCount=sizeof(qBatchJobList)/sizeof(qBatchJobList[0]);   
   for (nIndex=0;nIndex<nCount;nIndex++) {
      pLB->AddString(qBatchJobList[nIndex].qString);
   }
}

void CGrSlctPage::OnDeltaposOfAllSpins(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

   CWnd *pWnd;
   CString sReturn;
   int nResult;
   switch (pNMHDR->idFrom) {
   case ID_GRSLCT_SYMBOL_SIZE_SPIN :
      pWnd=GetDlgItem(ID_GRSLCT_SYMBOL_SIZE);
      pWnd->GetWindowText(sReturn);
      nResult=atoi(sReturn)+pNMUpDown->iDelta*-1;
      break;
   case ID_GRSLCT_SYMBOL_LINE_WIDTH_SPIN :
      pWnd=GetDlgItem(ID_GRSLCT_SYMBOL_LINE_WIDTH);
      pWnd->GetWindowText(sReturn);
      nResult=atoi(sReturn)+pNMUpDown->iDelta*-1;
      break;
   case ID_GRSLCT_LEGEND_SIZE_SPIN :
      pWnd=GetDlgItem(ID_GRSLCT_LEGEND_SIZE);
      pWnd->GetWindowText(sReturn);
      nResult=atoi(sReturn)+pNMUpDown->iDelta*-1;
      break;
   case ID_GRSLCT_ETC_MOMENT_RANGE_SPIN :
      pWnd=GetDlgItem(ID_GRSLCT_ETC_MOMENT_RANGE);
      pWnd->GetWindowText(sReturn);
      nResult=atoi(sReturn)+pNMUpDown->iDelta*-2;
      break;
   case ID_GRSLCT_ETC_MAP_COLOR_TOTAL_SPIN :
      pWnd=GetDlgItem(ID_GRSLCT_ETC_MAP_COLOR_TOTAL);
      pWnd->GetWindowText(sReturn);
      nResult=atoi(sReturn)+pNMUpDown->iDelta*-1;
      break;
   }
   sReturn.Format("%d",nResult);
   pWnd->SetWindowText(sReturn);
	
	*pResult = 0;
}

void CGrSlctPage::OnGrslctLegendTextFontattr() 
{
	// TODO: Add your control notification handler code here

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   int nSymbIndex=m_LegendSlider.GetPos();
   if (nSymbIndex<=0) return;
	
   CWnd *pWnd=GetFocus();
   CRect Rect;
   pWnd->GetWindowRect(&Rect);
	CSmallFontAttrDialog Dialog;
   Dialog.SetWindowGravityPos(Rect.CenterPoint());

   int nResult;
   char *pAddr;

   nResult=SEGetOptionValueInteger (
      10,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nSymbIndex,
      "legend.height=",1,0);
   Dialog.m_nHeight=nResult;

   nResult=SEGetOptionValueInteger(
      (int)(Dialog.m_nHeight/2),Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nSymbIndex,
      "legend.width=",1,0);
   Dialog.m_nWidth=nResult;

   Dialog.m_sAlignment=pAddr=SEGetOptionValueString(
      "LB",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nSymbIndex,
      "legend.align=",1,0);
   myFree(pAddr);
   if (isdigit(Dialog.m_sAlignment[0])) {
      nResult=(int)atof(Dialog.m_sAlignment);
      switch (nResult) {
      default :
      case 11 : Dialog.m_sAlignment="LB";break;
      case 12 : Dialog.m_sAlignment="LC";break;
      case 13 : Dialog.m_sAlignment="LT";break;
      case 21 : Dialog.m_sAlignment="CB";break;
      case 22 : Dialog.m_sAlignment="CC";break;
      case 23 : Dialog.m_sAlignment="CT";break;
      case 31 : Dialog.m_sAlignment="RB";break;
      case 32 : Dialog.m_sAlignment="RC";break;
      case 33 : Dialog.m_sAlignment="RT";break;
      }
   }

   nResult=SEGetOptionValueInteger(
      0,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nSymbIndex,
      "legend.angle=",1,0);
   Dialog.m_nAngle=nResult;

   nResult=SEGetOptionPosition(
      Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nSymbIndex,
      "legend.color=",1,0);
   if (nResult>=0) {
      int nNameLength=SEGetOptionNameLength(Script,nResult);
      int nValueLength=SEGetOptionValueLength(Script,nResult);
      nResult+=nNameLength+1;
      if (isdigit(Script[nResult])) {
         nResult=(int)atof((char*)(LPCTSTR)Script+nResult);
         Dialog.m_ColorBtn.nCurrentColor=nResult;
      } else {
         Dialog.m_ColorBtn.nCurrentColor=
            GEColorByName(NULL,Script.Mid(nResult,nValueLength));
      }
   }

	int nResponse=Dialog.DoModal();
	if (nResponse==IDCANCEL) return;

   char *pScript;
   int nScript;
   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   CString sSymbType,sPara;
   sSymbType.Format("%s=%d",PLOTSCRIPT_TYPE,m_SymbTypeBtn.m_nSymbolIndex);

   sPara.Format("legend.height=%d",Dialog.m_nHeight);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,sSymbType,nSymbIndex,
      sPara,1,0);

   sPara.Format("legend.width=%d",Dialog.m_nWidth);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,sSymbType,nSymbIndex,
      sPara,1,0);

   sPara.Format("legend.align=%s",Dialog.m_sAlignment);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,sSymbType,nSymbIndex,
      sPara,1,0);

   sPara.Format("legend.angle=%d",Dialog.m_nAngle);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,sSymbType,nSymbIndex,
      sPara,1,0);

   sPara.Format("legend.color=%d",Dialog.m_ColorBtn.nCurrentColor);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,sSymbType,nSymbIndex,
      sPara,1,0);

   Script=pScript;
   delete pScript;
   return;
}

BOOL CGrSlctPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL bResult=CPropertyPage::OnKillActive();
   if (!bResult) return bResult;
   
   CGrSlctPage::SetSymbolScriptFromDialog(m_LegendSlider.GetPos());

   return bResult;
}

BOOL CGrSlctPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) {
      m_LegendSlider.SetRange(0,0);
      m_LegendSlider.SetPos(0);
      return CPropertyPage::OnSetActive();
   }

   m_sXVariable=SEGetOptionValueString("?",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      PLOTSCRIPT_4UNDERSCORES,1,"xno=",1,0);
   m_sYVariable=SEGetOptionValueString("?",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      PLOTSCRIPT_4UNDERSCORES,1,"yno=",1,0);
   m_sZVariable=SEGetOptionValueString("?",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      PLOTSCRIPT_4UNDERSCORES,1,"zno=",1,0);

   UpdateData(FALSE);
   
   int nResult,nCount,nSymbolIndex;
   nResult=SEGetOptionPosition(Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,"type=",1,0);
   nCount=SEGetOptionFrequencyInaRange(Script,nResult,"type=");
   if (nCount>=1) {
      nSymbolIndex=m_LegendSlider.GetPos();//Y.Kim,20030217
      m_LegendSlider.SetRange(1,nCount);
      if (nSymbolIndex<1) nSymbolIndex=1;//Y.Kim,20030217
      if (nSymbolIndex>nCount) nSymbolIndex=nCount;//Y.Kim,20030217
      //nSymbolIndex=1; Y.Kim,20030217
      CString sPara;
      sPara.Format("%02d/%02d",nSymbolIndex,nCount);// 20030217 Y.Kim
      m_LegendSliderLabel.SetWindowText(sPara);
   } else {
      m_LegendSlider.SetRange(0,0);
      nSymbolIndex=0;
      m_LegendSliderLabel.SetWindowText("00/00");
   }
   m_LegendSlider.SetPos(nSymbolIndex);

   CGrSlctPage::SetSymbolScriptToDialog(nSymbolIndex);

   // Warning
   /* 2001.0319
   if (!m_bXLBAuto||!m_bXUBAuto) {
      nResult=SEGetOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         "xlog",1,0);
      if (nResult>0)
         MessageBox(
         "Warning, Recommend automatic x boundary in logarithmic x scale.",
         NULL,MB_ICONEXCLAMATION);
   }
   if (!m_bYLBAuto||!m_bYUBAuto) {
      nResult=SEGetOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         "ylog",1,0);
      if (nResult>0)
         MessageBox(
         "Warning, Recommend automatic y boundary in logarithmic y scale",
         NULL,MB_ICONEXCLAMATION);
   }
   if (!m_bZLBAuto||!m_bZUBAuto) {
      nResult=SEGetOptionPosition(
         Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         "zlog",1,0);
      if (nResult>0)
         MessageBox(
         "Warning, Recommend automatic z boundary in logarithmic z scale",
         NULL,MB_ICONEXCLAMATION);
   }
   */

   if (m_bFirstSetActive) UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

void CGrSlctPage::SetSymbolScriptToDialog(int nIndex)
{
   if (nIndex<=0) return;

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   char *pAddr;

   // Symbol
   pAddr=SEGetOptionValueString(
      "on",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "symbol=",1,
      0);
   m_bSymbol=tolower(pAddr[1])=='n' ? TRUE:FALSE;
   myFree(pAddr);
   m_SymbTypeBtn.m_nSymbolIndex=SEGetOptionValueInteger(
      1,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      0);
   if (m_SymbTypeBtn.m_nSymbolIndex==-6) m_SymbTypeBtn.m_nSymbolIndex=71;

   pAddr=SEGetOptionValueString(
      "black",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "symbol.color=",1,
      0);
   m_SymbTypeBtn.m_nSymbFillColor=isdigit(pAddr[0]) ?
      atoi((LPCTSTR)pAddr):
      GEColorByName(NULL,(LPCTSTR)pAddr);
   myFree(pAddr);

   m_SymbTypeBtn.m_nSymbStrokeColor=m_SymbTypeBtn.m_nSymbFillColor;
   m_SymbColorBtn.nCurrentColor=m_SymbTypeBtn.m_nSymbFillColor;

   m_bSymbSolid=SEGetOptionPosition(
      Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "solid",1,
      0) >=0 ? TRUE:FALSE;
   m_SymbTypeBtn.m_bFillSymbol=m_bSymbSolid;

   m_SymbTypeBtn.Invalidate();
   m_SymbColorBtn.Invalidate();

   m_nSymbRepetition=SEGetOptionValueInteger(
      0,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "nCopy=",1,
      0);

   m_nSymbSize=SEGetOptionValueInteger(
      7,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "symbol.size=",1,
      0);

   // Line

   pAddr=SEGetOptionValueString(
      "on",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "line=",1,
      0);
   m_bLineConnection=tolower(pAddr[1])=='n' ? TRUE:FALSE;
   myFree(pAddr);

   pAddr=SEGetOptionValueString(
      "black",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "line.color=",1,
      0);
   m_SymbLineColorBtn.nCurrentColor=isdigit(pAddr[0]) ?
      atoi((LPCTSTR)pAddr):
      GEColorByName(NULL,(LPCTSTR)pAddr);
   myFree(pAddr);
   m_SymbLineColorBtn.Invalidate();

   CComboBox *pBox;
   pBox=(CComboBox*)GetDlgItem(ID_GRSLCT_SYMBOL_LINE_STYLE);
   pAddr=SEGetOptionValueString(
      "solid",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "line.dash_list=",1,
      0);
   if (pAddr[0]=='(') {
      pBox->AddString(pAddr);
      pBox->SetCurSel(pBox->GetCount()-1);
   } else {
      if (!strcmp(pAddr,"solid")) pBox->SetCurSel(0);
      else if (!strcmp(pAddr,"longdashed")) pBox->SetCurSel(1);
      else if (!strcmp(pAddr,"shortdashed")) pBox->SetCurSel(2);
      else if (!strcmp(pAddr,"dashdotted")) pBox->SetCurSel(3);
      else if (!strcmp(pAddr,"dotted")) pBox->SetCurSel(4);
      else pBox->SetCurSel(0);
   }
   myFree(pAddr);

   m_nLineWidth=SEGetOptionValueInteger(
      1,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "line.width=",1,
      0);

   // Legend
   pAddr=SEGetOptionValueString(
      "on",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "legend=",1,
      0);
   m_bLegend=tolower(pAddr[1])=='n' ? TRUE:FALSE;
   myFree(pAddr);

   m_sLegendText=pAddr=SEGetOptionValueString(
      "null",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "legend.txt=",1,
      0);
   myFree(pAddr);
   if (m_sLegendText[0]=='\"' &&
      m_sLegendText[m_sLegendText.GetLength()-1]=='\"') {
      m_sLegendText.Delete(0);
      m_sLegendText.Delete(m_sLegendText.GetLength()-1);
   }

   m_nLegendSize=SEGetOptionValueInteger(
      5,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "legend.symbolsize=",1,
      0);

   m_sLegendX=SEGetOptionValueString(
      "?",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "x=",1,
      0);
   m_bLegendXLocAuto=isnumstr(m_sLegendX) ? FALSE:TRUE; //20030803
   if (!m_bLegendXLocAuto) m_sLegendX=dtos(stod(m_sLegendX),"%z"); //20030803
   GetDlgItem(ID_GRSLCT_LEGEND_X)->EnableWindow(!m_bLegendXLocAuto);
   m_sLegendY=SEGetOptionValueString(
      "?",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_TYPE,nIndex,
      "y=",1,
      0);
   m_bLegendYLocAuto=isnumstr(m_sLegendY) ? FALSE:TRUE; //20030803
   if (!m_bLegendYLocAuto) m_sLegendY=dtos(stod(m_sLegendY),"%z"); //20030803
   GetDlgItem(ID_GRSLCT_LEGEND_Y)->EnableWindow(!m_bLegendYLocAuto);

   // nEtc==PLT2D_GENETIC
   m_nEtcMomentRange=SEGetOptionValueInteger(
      100,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,
      "etc.Range=",1,
      0);

   // nEtc==PLT2D_FLAT3D
   pAddr=SEGetOptionValueString(
      "yellow",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,
      "etc.ColorMin=",1,
      0);
   m_EtcMapColorMinBtn.nCurrentColor=isdigit(pAddr[0]) ?
      atoi((LPCTSTR)pAddr):
      GEColorByName(NULL,(LPCTSTR)pAddr);
   myFree(pAddr);
   m_EtcMapColorMinBtn.Invalidate();

   pAddr=SEGetOptionValueString(
      "red",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,
      "etc.ColorMax=",1,
      0);
   m_EtcMapColorMaxBtn.nCurrentColor=isdigit(pAddr[0]) ?
      atoi((LPCTSTR)pAddr):
      GEColorByName(NULL,(LPCTSTR)pAddr);
   myFree(pAddr);
   m_EtcMapColorMaxBtn.Invalidate();

   m_nEtcMapColorTotal=SEGetOptionValueInteger(
      5,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,
      "etc.ColorTotal=",1,
      0);

   m_sEtcMapNoFormat=pAddr=SEGetOptionValueString(
      "%d",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,
      "etc.Format=",1,
      0);
   myFree(pAddr);
   m_sEtcMapNoFormat.TrimLeft('\"');
   m_sEtcMapNoFormat.TrimRight('\"');

   UpdateData(FALSE);
}

void CGrSlctPage::SetSymbolScriptFromDialog(int nIndex)
{
   UpdateData(TRUE);

   if (nIndex<=0) return;

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   char *pScript;
   int nScript;
   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   CString sSymbType,sPara;

   // Symbol

   int nSymbolIndex=m_SymbTypeBtn.m_nSymbolIndex;
   if (nSymbolIndex==71) nSymbolIndex=-6;
   sSymbType.Format("%s=%d",PLOTSCRIPT_TYPE,nSymbolIndex);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,0);

   sPara=m_bSymbol ? "symbol=on":"symbol=off";
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   sPara.Format("symbol.color=%d",m_SymbTypeBtn.m_nSymbFillColor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   SEDelOptionParameter(
      pScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,"solid",1,0);
   SEDelOptionParameter(
      pScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,"hollow",1,0);
   sPara=m_bSymbSolid ? "solid":"hollow";
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   sPara.Format("nCopy=%d",m_nSymbRepetition);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   sPara.Format("symbol.size=%d",m_nSymbSize);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   // Line

   sPara=m_bLineConnection ? "line=on":"line=off";
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   sPara.Format("line.color=%d",m_SymbLineColorBtn.nCurrentColor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   CComboBox *pBox;
   pBox=(CComboBox*)GetDlgItem(ID_GRSLCT_SYMBOL_LINE_STYLE);
   pBox->GetLBText(pBox->GetCurSel(),sPara);
   sPara.TrimRight(" ._-");
   sPara.Insert(0,"line.dash_list=");
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   sPara.Format("line.width=%d",m_nLineWidth);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   // Legend

   sPara=m_bLegend ? "legend=on":"legend=off";
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   sPara.Format("legend.txt=\"%s\"",m_sLegendText);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   sPara.Format("legend.symbolsize=%d",m_nLegendSize);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   m_sLegendX.Format("%g",stod(m_sLegendX)); //20030803
   sPara="x=" + (m_bLegendXLocAuto ? "*":m_sLegendX); //20030803
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);
   m_sLegendY.Format("%g",stod(m_sLegendY)); //20030803
   sPara="y=" + (m_bLegendYLocAuto ? "*":m_sLegendY); //20030803
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,nIndex,sPara,1,0);

   sSymbType=PLOTSCRIPT_4UNDERSCORES;

   // nEtc==PLT2D_GENETIC

   sPara.Format("etc.Range=%d",m_nEtcMomentRange);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,1,sPara,1,0);

   // nEtc==PLT2D_FLAT3D

   sPara.Format("etc.ColorMin=%d",m_EtcMapColorMinBtn.nCurrentColor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,1,sPara,1,0);

   sPara.Format("etc.ColorMax=%d",m_EtcMapColorMaxBtn.nCurrentColor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,1,sPara,1,0);

   sPara.Format("etc.ColorTotal=%d",m_nEtcMapColorTotal);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,1,sPara,1,0);

   sPara.Format("etc.Format=%s",m_sEtcMapNoFormat);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,
      sSymbType,1,sPara,1,0);

   Script=pScript;
   delete pScript;
}

void CGrSlctPage::OnGrslctPrev() 
{
	// TODO: Add your control notification handler code here

   m_LegendSlider.SendMessage(WM_KEYDOWN,VK_LEFT,0);
}

void CGrSlctPage::OnGrslctNext() 
{
	// TODO: Add your control notification handler code here

   ::SendMessage(m_LegendSlider.m_hWnd,WM_KEYDOWN,VK_RIGHT,0);
}

double CGrSlctPage::GetValueFromGrLog(const char *qPara,double dDefault)
{
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrLog;
   if (Script.IsEmpty()) return dDefault;
   double dReturn=SEGetOptionValueFloating(dDefault,Script,qPara,pSheet->m_nPlotIndex,0);
   return dReturn;
}

void CGrSlctPage::OnSelchangeGrslctBatchjob() 
{
	// TODO: Add your control notification handler code here

   CWnd *pWnd=GetDlgItem(ID_GRSLCT_BATCHJOB);
   int nCount=((CListBox*)pWnd)->GetSelCount();
   CString sTipText;
   sTipText.Format("You've selected \"%d\" item(s) for batch.",nCount);
   /*
   m_ToolTipForBatch.UpdateTipText(sTipText,pWnd);
   m_ToolTipForBatch.Update();
   */
   m_ToolTipForBatch.DelTool(pWnd);
   m_ToolTipForBatch.AddTool(pWnd,sTipText);
   m_ToolTipForBatch.Activate(true);
}

int CGrSlctPage::GetXYZVariableColumnCount(int nType)
{ 
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return 0;

   char *pAddr;
   switch (nType) {
   case 1 : case 'x' : pAddr="xno=";break;
   case 2 : case 'y' : pAddr="yno=";break;
   default:
   case 3 : case 'z' : pAddr="zno=";break;
   }
   CString sVariable=SEGetOptionValueString(
      "?",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,pAddr,1,0);
   if (!ispunct(sVariable[0])) GRGetColNumberCount(sVariable);//20030222
   sVariable=SEGetOptionValueString(
      "",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_DATA,1,"type=",1,0);
   if (sVariable.CompareNoCase("file")) return 0;
   sVariable=SEGetOptionValueString(
      "",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_DATA,1,"type=",1,"file=",1,0);
   if (sVariable.IsEmpty()) return 0;
   int nRow=0,nCol=0;
   GetMtrxRowColFrFile(sVariable,&nRow,&nCol);
   return nCol-1; // -1 for x-column.
}

void CGrSlctPage::OnGrsymbOnoffTool( int nID ) 
{
	// TODO: Add your control notification handler code here
	
   int bCheck=nID==ID_GRSYMB_DISPLAY_ON ? 1:0;

	((CButton*)GetDlgItem(ID_GRSLCT_SYMBOL_CB))->SetCheck(bCheck);
   ((CButton*)GetDlgItem(ID_GRSLCT_LINECONNECTION_CB))->SetCheck(bCheck);
   ((CButton*)GetDlgItem(ID_GRSLCT_LEGEND_CB))->SetCheck(bCheck);
}
