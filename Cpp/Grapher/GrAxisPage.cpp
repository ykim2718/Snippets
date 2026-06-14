// GrAxisPage.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrAxisPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "plot.h"
#include "SmallFontAttrDialog.h"
#include "GrPropertySheet.h"

static char *qLineStyleStrings[]={
   "solid",
   "longdashed __ __ __",
   "shortdashed _ _ _ _",
   "dashdotted _ . _ . _",
   "dotted . . . . . . ."
};

static char *qLabelFormat[]={
   "%.1g","%.1f","%.1e","%d","%s","%.0z"
};

/////////////////////////////////////////////////////////////////////////////
// CGrAxisPage property page

IMPLEMENT_DYNCREATE(CGrAxisPage, CPropertyPage)

CGrAxisPage::CGrAxisPage() : CPropertyPage(CGrAxisPage::IDD)
{
	//{{AFX_DATA_INIT(CGrAxisPage)
	m_bAxisDisplay = TRUE;
	m_bLabelDisplay = TRUE;
	m_bTitleDisplay = TRUE;
	m_dTitleSpaceFactor = 1.0f;
	m_sLabelEquation = _T("");
	m_sTitle = _T("");
	m_dLocAnyFrom = 0.0;
	m_dLocAnyTo = 0.0;
	m_dLocAnyAt = 0.0;
	m_bMajorTickDisplay = FALSE;
	m_bMajorTickInside = FALSE;
	m_bMajorTickOutside = FALSE;
	m_bMajorTickStepAuto = FALSE;
	m_bMinorTickDisplay = FALSE;
	m_bMinorTickInside = FALSE;
	m_bMinorTickOutside = FALSE;
	m_bMinorTickStepAuto = FALSE;
	m_bMajorGridDisplay = FALSE;
	m_bMinorGridDisplay = FALSE;
	m_sLabelFormat = _T("");
	m_nAxleThickness = 1;
	m_sMajorTickStep = _T("");
	m_sMinorTickStep = _T("");
	//}}AFX_DATA_INIT

   m_nPrecedingComboBoxSelection=-1;

   m_nAxisType=TYPE_X;
   m_nAxisLocationType=LOC_LOW;
}

CGrAxisPage::~CGrAxisPage()
{
}

void CGrAxisPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrAxisPage)
	DDX_Control(pDX, ID_GRAXIS_ID, m_ID);
	DDX_Check(pDX, ID_GRAXIS_AXIS_DISPLAY, m_bAxisDisplay);
	DDX_Check(pDX, ID_GRAXIS_LABEL_DISPLAY, m_bLabelDisplay);
	DDX_Check(pDX, ID_GRAXIS_TITLE_DISPLAY, m_bTitleDisplay);
	DDX_Text(pDX, ID_GRAXIS_TITLE_SPACEFACTOR, m_dTitleSpaceFactor);
	DDV_MinMaxDouble(pDX, m_dTitleSpaceFactor, -20., 20.);
	DDX_Text(pDX, ID_GRAXIS_LABEL_EQUATION, m_sLabelEquation);
	DDX_Text(pDX, ID_GRAXIS_TITLE_STRING, m_sTitle);
	DDV_MaxChars(pDX, m_sTitle, 256);
	DDX_Text(pDX, ID_GRAXIS_LOC_ANY_FROM, m_dLocAnyFrom);
	DDX_Text(pDX, ID_GRAXIS_LOC_ANY_TO, m_dLocAnyTo);
	DDX_Text(pDX, ID_GRAXIS_LOC_ANY_AT, m_dLocAnyAt);
	DDX_Check(pDX, ID_GRAXIS_TICKMAJOR_DISPLAY, m_bMajorTickDisplay);
	DDX_Check(pDX, ID_GRAXIS_TICKMAJOR_INSIDE, m_bMajorTickInside);
	DDX_Check(pDX, ID_GRAXIS_TICKMAJOR_OUTSIDE, m_bMajorTickOutside);
	DDX_Check(pDX, ID_GRAXIS_TICKMAJOR_STEP_AUTO, m_bMajorTickStepAuto);
	DDX_Check(pDX, ID_GRAXIS_TICKMINOR_DISPLAY, m_bMinorTickDisplay);
	DDX_Check(pDX, ID_GRAXIS_TICKMINOR_INSIDE, m_bMinorTickInside);
	DDX_Check(pDX, ID_GRAXIS_TICKMINOR_OUTSIDE, m_bMinorTickOutside);
	DDX_Check(pDX, ID_GRAXIS_TICKMINOR_STEP_AUTO, m_bMinorTickStepAuto);
	DDX_Check(pDX, ID_GRAXIS_GRIDMAJOR_DISPLAY, m_bMajorGridDisplay);
	DDX_Check(pDX, ID_GRAXIS_GRIDMINOR_DISPLAY, m_bMinorGridDisplay);
	DDX_CBString(pDX, ID_GRAXIS_LABEL_FORMAT, m_sLabelFormat);
	DDX_Text(pDX, ID_GRAXIS_AXLETHICKNESS, m_nAxleThickness);
	DDV_MinMaxUInt(pDX, m_nAxleThickness, 1, 36);
	DDX_Text(pDX, ID_GRAXIS_TICKMAJOR_STEP, m_sMajorTickStep);
	DDX_Text(pDX, ID_GRAXIS_TICKMINOR_STEP, m_sMinorTickStep);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrAxisPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrAxisPage)
	ON_CBN_SELCHANGE(ID_GRAXIS_ID, OnSelchangeGraxisId)
	ON_BN_CLICKED(ID_GRAXIS_ADD, OnGraxisAdd)
	ON_BN_CLICKED(ID_GRAXIS_DEL, OnGraxisDel)
	ON_BN_CLICKED(ID_GRAXIS_TYPE_X, OnGraxisTypeX)
	ON_BN_CLICKED(ID_GRAXIS_TYPE_Y, OnGraxisTypeY)
	ON_BN_CLICKED(ID_GRAXIS_LOC_LOWBOUNDARY, OnGraxisLocLowboundary)
	ON_BN_CLICKED(ID_GRAXIS_LOC_MIDDLE, OnGraxisLocMiddle)
	ON_BN_CLICKED(ID_GRAXIS_LOC_HIGHBOUNDARY, OnGraxisLocHighboundary)
	ON_BN_CLICKED(ID_GRAXIS_LOC_ANY, OnGraxisLocAny)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRAXIS_TITLE_SPACEFACTOR_SPIN, OnDeltaposGraxisTitleSpacefactorSpin)
	ON_BN_CLICKED(ID_GRAXIS_LABEL_FONTATTR, OnGraxisLabelFontattr)
	ON_BN_CLICKED(ID_GRAXIS_TITLE_FONTATTR, OnGraxisTitleFontattr)
	ON_BN_CLICKED(ID_GRAXIS_AXIS_DISPLAY, OnGraxisAxisDisplay)
	ON_BN_CLICKED(ID_GRAXIS_TICKMAJOR_STEP_AUTO, OnGraxisTickmajorStepAuto)
	ON_BN_CLICKED(ID_GRAXIS_TICKMINOR_STEP_AUTO, OnGraxisTickminorStepAuto)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRAXIS_AXLETHICKNESS_SPIN, OnDeltaposGraxisAxlethicknessSpin)
	//}}AFX_MSG_MAP
   ON_CONTROL_RANGE(BN_CLICKED,ID_GRAXIS_DISPLAY_ON,ID_GRAXIS_DISPLAY_OFF,OnGraxisOnoffTool)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrAxisPage message handlers

BOOL CGrAxisPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   LOGFONT LogFont;
   GetFont()->GetLogFont(&LogFont);
   LogFont.lfUnderline=TRUE;
   m_MyFont.CreateFontIndirect(&LogFont);
   GetDlgItem(ID_GRAXIS_AXIS)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRAXIS_MAJORTICK)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRAXIS_MINORTICK)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRAXIS_TICKLABEL)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRAXIS_AXISTITLE)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRAXIS_MAJORGRID)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRAXIS_MINORGRID)->SetFont(&m_MyFont);

   m_ID.SetCurSel(-1);

   CGrAxisPage::SetCheckButtonsOfAxisType();
   CGrAxisPage::SetCheckButtonsOfAxisLocation();

   int nCount,nIndex;

   CComboBox *pBox=(CComboBox*)GetDlgItem(ID_GRAXIS_LABEL_FORMAT);
   nCount=sizeof(qLabelFormat)/sizeof(qLabelFormat[0]);
   for (nIndex=0;nIndex<nCount;nIndex++) pBox->AddString(qLabelFormat[nIndex]);
   pBox->SetCurSel(0);

   m_AxisColorBtn.SubclassDlgItem(ID_GRAXIS_COLOR,this);
   m_LabelColorBtn.SubclassDlgItem(ID_GRAXIS_LABEL_COLOR,this);
   m_TitleColorBtn.SubclassDlgItem(ID_GRAXIS_TITLE_COLOR,this);
   m_MajorGridColorBtn.SubclassDlgItem(ID_GRAXIS_GRIDMAJOR_COLOR,this);
   m_MinorGridColorBtn.SubclassDlgItem(ID_GRAXIS_GRIDMINOR_COLOR,this);

   CGrAxisPage::SetComboBoxStringsOfLineStyle(ID_GRAXIS_LINESTYLE);
   CGrAxisPage::SetComboBoxStringsOfLineStyle(ID_GRAXIS_GRIDMAJOR_LINESTYLE);
   CGrAxisPage::SetComboBoxStringsOfLineStyle(ID_GRAXIS_GRIDMINOR_LINESTYLE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrAxisPage::OnSelchangeGraxisId() 
{
	// TODO: Add your control notification handler code here

	int nIndex=m_ID.GetCurSel();
   if (nIndex==CB_ERR) return;
   if (nIndex==m_nPrecedingComboBoxSelection) return;
   if (m_nPrecedingComboBoxSelection>=0) {
      GetAxisDataFromDialog(m_nPrecedingComboBoxSelection+1);
      m_ID.DeleteString(m_nPrecedingComboBoxSelection);
      CString sReturn;
      sReturn.Format(
         "%d) %c \"%s\"",
         m_nPrecedingComboBoxSelection+1,
         m_nAxisType==TYPE_X ? 'x':'y',
         m_sTitle);
      m_ID.InsertString(m_nPrecedingComboBoxSelection,sReturn);
   }
   SetAxisDataToDialog(nIndex+1);
   m_nPrecedingComboBoxSelection=nIndex;
}

void CGrAxisPage::OnGraxisAdd() 
{
	// TODO: Add your control notification handler code here

}

void CGrAxisPage::OnGraxisDel() 
{
	// TODO: Add your control notification handler code here

   int nAxisIndex=m_ID.GetCurSel();
   if (nAxisIndex<0) return;
   nAxisIndex++;

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   CString sPara;
   sPara.Format("%s=%c",PLOTSCRIPT_TYPE,m_nAxisType==TYPE_X ? 'x':'y');

   int nFirst=SEGetOptionPosition(
      Script,
      PLOTSCRIPT_BEGINNING,1,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sPara,nAxisIndex,
      0);
   int nLength=SEGetOptionBlockLength(Script,nFirst);
   if (nLength==0) return;

   sPara=Script.Mid(nFirst,nLength);
   sPara.TrimLeft();
   sPara.TrimRight();
   int nResult=MessageBox(sPara,"Delete following ...",MB_ICONQUESTION|MB_YESNO);
   if (nResult!=IDYES) return;

   Script.Delete(nFirst,nLength);

   m_ID.DeleteString(nAxisIndex-1);
   if (m_ID.GetCount()<nAxisIndex) nAxisIndex--;
   m_ID.SetCurSel(nAxisIndex-1);
   SetAxisDataToDialog(nAxisIndex);
}

void CGrAxisPage::SetCheckButtonsOfAxisType()
{
   ((CButton*)GetDlgItem(ID_GRAXIS_TYPE_X))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRAXIS_TYPE_Y))->SetCheck(0);
   switch(m_nAxisType) {
   case TYPE_X : ((CButton*)GetDlgItem(ID_GRAXIS_TYPE_X))->SetCheck(1);break;
   case TYPE_Y : ((CButton*)GetDlgItem(ID_GRAXIS_TYPE_Y))->SetCheck(1);break;
   }
}

void CGrAxisPage::GetCheckButtonsOfAxisType()
{
   //m_nAxisType=((CButton*)GetDlgItem(ID_GRAXIS_TYPE_X))->GetCheck() ? TYPE_X:TYPE_Y;
}

void CGrAxisPage::SetCheckButtonsOfAxisLocation()
{
   ((CButton*)GetDlgItem(ID_GRAXIS_LOC_LOWBOUNDARY))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRAXIS_LOC_MIDDLE))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRAXIS_LOC_HIGHBOUNDARY))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRAXIS_LOC_ANY))->SetCheck(0);
   switch(m_nAxisLocationType) {
   case LOC_LOW : ((CButton*)GetDlgItem(ID_GRAXIS_LOC_LOWBOUNDARY))->SetCheck(1);break;
   case LOC_MIDDLE : ((CButton*)GetDlgItem(ID_GRAXIS_LOC_MIDDLE))->SetCheck(1);break;
   case LOC_HIGH : ((CButton*)GetDlgItem(ID_GRAXIS_LOC_HIGHBOUNDARY))->SetCheck(1);break;
   case LOC_ANY : ((CButton*)GetDlgItem(ID_GRAXIS_LOC_ANY))->SetCheck(1);break;
   }
   switch (m_nAxisLocationType) {
   case LOC_LOW :
   case LOC_MIDDLE :
   case LOC_HIGH :
      GetDlgItem(ID_GRAXIS_LOC_ANY_FROM)->EnableWindow(FALSE);
      GetDlgItem(ID_GRAXIS_LOC_ANY_TO)->EnableWindow(FALSE);
      GetDlgItem(ID_GRAXIS_LOC_ANY_AT)->EnableWindow(FALSE);
      break;
   case LOC_ANY :
      GetDlgItem(ID_GRAXIS_LOC_ANY_FROM)->EnableWindow(TRUE);
      GetDlgItem(ID_GRAXIS_LOC_ANY_TO)->EnableWindow(TRUE);
      GetDlgItem(ID_GRAXIS_LOC_ANY_AT)->EnableWindow(TRUE);
      break;
   }
}

void CGrAxisPage::GetCheckButtonsOfAxisLocation()
{

}

void CGrAxisPage::GetCheckButtonsOfAxisLocationAny()
{

}

void CGrAxisPage::OnGraxisTypeX() 
{
	// TODO: Add your control notification handler code here

   m_nAxisType=TYPE_X;
	CGrAxisPage::SetCheckButtonsOfAxisType();
}

void CGrAxisPage::OnGraxisTypeY() 
{
	// TODO: Add your control notification handler code here

	m_nAxisType=TYPE_Y;
	CGrAxisPage::SetCheckButtonsOfAxisType();
}

void CGrAxisPage::OnGraxisLocLowboundary() 
{
	// TODO: Add your control notification handler code here

   m_nAxisLocationType=LOC_LOW;
	CGrAxisPage::SetCheckButtonsOfAxisLocation();
}

void CGrAxisPage::OnGraxisLocMiddle() 
{
	// TODO: Add your control notification handler code here

	m_nAxisLocationType=LOC_MIDDLE;
	CGrAxisPage::SetCheckButtonsOfAxisLocation();
}

void CGrAxisPage::OnGraxisLocHighboundary() 
{
	// TODO: Add your control notification handler code here

	m_nAxisLocationType=LOC_HIGH;
	CGrAxisPage::SetCheckButtonsOfAxisLocation();
}

void CGrAxisPage::OnGraxisLocAny() 
{
	// TODO: Add your control notification handler code here

	m_nAxisLocationType=LOC_ANY;
	CGrAxisPage::SetCheckButtonsOfAxisLocation();
}

void CGrAxisPage::OnGraxisAxisDisplay() 
{
	// TODO: Add your control notification handler code here

   int bResult=((CButton*)GetDlgItem(ID_GRAXIS_AXIS_DISPLAY))->GetCheck();
   m_bAxisDisplay=bResult;
   GetDlgItem(ID_GRAXIS_LOC_LOWBOUNDARY)->EnableWindow(bResult);
   GetDlgItem(ID_GRAXIS_LOC_MIDDLE)->EnableWindow(bResult);
   GetDlgItem(ID_GRAXIS_LOC_HIGHBOUNDARY)->EnableWindow(bResult);
   GetDlgItem(ID_GRAXIS_LOC_ANY)->EnableWindow(bResult);
   if (m_nAxisLocationType!=LOC_ANY) bResult=FALSE;
   GetDlgItem(ID_GRAXIS_LOC_ANY_FROM)->EnableWindow(bResult);
   GetDlgItem(ID_GRAXIS_LOC_ANY_TO)->EnableWindow(bResult);
   GetDlgItem(ID_GRAXIS_LOC_ANY_AT)->EnableWindow(bResult);
}

void CGrAxisPage::SetComboBoxStringsOfLineStyle(int nID)
{
   CComboBox *cb=(CComboBox*)GetDlgItem(nID);
   int i,count=sizeof(qLineStyleStrings)/sizeof(qLineStyleStrings[0]);   
   for (i=0;i<count;i++) {
      cb->AddString(qLineStyleStrings[i]);
   }
   cb->SetCurSel(0);
}

void CGrAxisPage::OnGraxisTickmajorStepAuto() 
{
	// TODO: Add your control notification handler code here

   int bResult=((CButton*)GetDlgItem(ID_GRAXIS_TICKMAJOR_STEP_AUTO))->GetCheck();
   if (bResult) GetDlgItem(ID_GRAXIS_TICKMAJOR_STEP)->SetWindowText("0.0");
	GetDlgItem(ID_GRAXIS_TICKMAJOR_STEP)->EnableWindow(!bResult);
}

void CGrAxisPage::OnGraxisTickminorStepAuto() 
{
	// TODO: Add your control notification handler code here

   int bResult=((CButton*)GetDlgItem(ID_GRAXIS_TICKMINOR_STEP_AUTO))->GetCheck();
   if (bResult) GetDlgItem(ID_GRAXIS_TICKMINOR_STEP)->SetWindowText("0.0");
	GetDlgItem(ID_GRAXIS_TICKMINOR_STEP)->EnableWindow(!bResult);
}

void CGrAxisPage::OnDeltaposGraxisAxlethicknessSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

   CString sReturn;
   CWnd *pWnd=GetDlgItem(ID_GRAXIS_AXLETHICKNESS);
   pWnd->GetWindowText(sReturn);
   int nThickness=atoi((LPCTSTR)sReturn);
   nThickness+=pNMUpDown->iDelta*-1;
   sReturn.Format("%d",nThickness);
   pWnd->SetWindowText((LPCTSTR)sReturn);
	
	*pResult = 0;
}

void CGrAxisPage::OnDeltaposGraxisTitleSpacefactorSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

   CString sReturn;
   CWnd *pWnd=GetDlgItem(ID_GRAXIS_TITLE_SPACEFACTOR);
   pWnd->GetWindowText(sReturn);
   float factor=(float)atof((LPCTSTR)sReturn);
   switch (pNMUpDown->iDelta) {
   case -1 : factor+=0.5;break;
   case +1 : factor-=0.5;break;
   }
   sReturn.Format("%g",factor);
   pWnd->SetWindowText((LPCTSTR)sReturn);

	*pResult = 0;
}

void CGrAxisPage::OnGraxisLabelFontattr() 
{
	// TODO: Add your control notification handler code here
   
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   int nAxisIndex=m_ID.GetCurSel();
   if (nAxisIndex==CB_ERR) return;
   nAxisIndex++;
	
   CWnd *pWnd=GetFocus();
   CRect Rect;
   pWnd->GetWindowRect(&Rect);
	CSmallFontAttrDialog Dialog;
   Dialog.SetWindowGravityPos(Rect.CenterPoint());

   int nResult;
   char *pAddr;

   nResult=SEGetOptionValueInteger(
      10,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "label.height=",1,0);
   Dialog.m_nHeight=nResult;

   nResult=SEGetOptionValueInteger(
      (int)(Dialog.m_nHeight/2),Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "label.width=",1,0);
   Dialog.m_nWidth=nResult;

   Dialog.m_sAlignment=pAddr=SEGetOptionValueString(
      "LB",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "label.align=",1,0);
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
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "label.angle=",1,0);
   Dialog.m_nAngle=nResult;

   Dialog.m_ColorBtn.nCurrentColor=m_LabelColorBtn.nCurrentColor;
   /*
   nResult=SEGetOptionPosition(
      Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "label.color=",1,0);
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
   */

	int nResponse=Dialog.DoModal();
	if (nResponse==IDCANCEL) return;

   char *pScript;
   int nScript;
   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);
   
   CString sAxisType,sPara;
   sAxisType.Format("%s=%c",PLOTSCRIPT_TYPE,m_nAxisType==TYPE_X ? 'x':'y');

   sPara.Format("label.height=%d",Dialog.m_nHeight);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   sPara.Format("label.width=%d",Dialog.m_nWidth);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   sPara.Format("label.align=%s",Dialog.m_sAlignment);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   sPara.Format("label.angle=%d",Dialog.m_nAngle);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   sPara.Format("label.color=%d",Dialog.m_ColorBtn.nCurrentColor);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   Script=pScript;
   delete pScript;

   m_LabelColorBtn.nCurrentColor=Dialog.m_ColorBtn.nCurrentColor;
   m_LabelColorBtn.Invalidate();

   return;
}

void CGrAxisPage::OnGraxisTitleFontattr() 
{
	// TODO: Add your control notification handler code here

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   int nAxisIndex=m_ID.GetCurSel();
   if (nAxisIndex==CB_ERR) return;
   nAxisIndex++;
	
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
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "title.height=",1,0);
   Dialog.m_nHeight=nResult;

   nResult=SEGetOptionValueInteger(
      (int)(Dialog.m_nHeight/2),Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "title.width=",1,0);
   Dialog.m_nWidth=nResult;

   Dialog.m_sAlignment=pAddr=SEGetOptionValueString(
      "LB",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "title.align=",1,0);
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
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "title.angle=",1,0);
   Dialog.m_nAngle=nResult;

   Dialog.m_ColorBtn.nCurrentColor=m_TitleColorBtn.nCurrentColor;
   /*
   nResult=SEGetOptionPosition(
      Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nAxisIndex,
      "title.color=",1,0);
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
   */

	int nResponse=Dialog.DoModal();
	if (nResponse==IDCANCEL) return;

   char *pScript;
   int nScript;
   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   CString sAxisType,sPara;
   sAxisType.Format("%s=%c",PLOTSCRIPT_TYPE,m_nAxisType==TYPE_X ? 'x':'y');

   sPara.Format("title.height=%d",Dialog.m_nHeight);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   sPara.Format("title.width=%d",Dialog.m_nWidth);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   sPara.Format("title.align=%s",Dialog.m_sAlignment);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   sPara.Format("title.angle=%d",Dialog.m_nAngle);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   sPara.Format("title.color=%d",Dialog.m_ColorBtn.nCurrentColor);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,sAxisType,nAxisIndex,
      sPara,1,0);

   Script=pScript;
   delete pScript;

   m_TitleColorBtn.nCurrentColor=Dialog.m_ColorBtn.nCurrentColor;
   m_TitleColorBtn.Invalidate();

   return;
}

void CGrAxisPage::SetAxisDataToDialog(int nIndex)
{
   if (nIndex<=0) return;

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   char *pAddr;
   CString sPara;
   int nResult;
   double dValue;

   pAddr=SEGetOptionValueString(
      "x",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      0);
   switch (tolower(*pAddr)) {
   case 'x' : m_nAxisType=TYPE_X;break;
   case 'y' : m_nAxisType=TYPE_Y;break;
   }
   myFree(pAddr);

   pAddr=SEGetOptionValueString(
      "lower",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "loc=",1,
      0);
   switch (tolower(*pAddr)) {
   case 'l' : m_nAxisLocationType=LOC_LOW;break;
   case 'm' : m_nAxisLocationType=LOC_MIDDLE;break;
   case 'u' : m_nAxisLocationType=LOC_HIGH;break;
   case 'a' : m_nAxisLocationType=LOC_ANY;break;
   }
   myFree(pAddr);
   
   if (m_nAxisLocationType!=LOC_ANY) {
      m_dLocAnyFrom=0.0;
      m_dLocAnyTo=0.0;
      m_dLocAnyAt=0.0;
   } else {
      pAddr=SEGetOptionValueString(
         NULL,Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
         PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
         "loc.x=",1,0);
      if (pAddr) {
         sPara=pAddr;
         sPara.TrimLeft("(");
         sPara.TrimRight(")");
         switch (m_nAxisType) {
         case TYPE_X :
            m_dLocAnyFrom=atof(sPara);
            nResult=sPara.Find(",");
            sPara.Delete(0,nResult+1);
            m_dLocAnyTo=atof(sPara);
            break;
         case TYPE_Y :
            m_dLocAnyAt=atof(sPara);
            break;
         }
         myFree(pAddr);
      }
      pAddr=SEGetOptionValueString(
         NULL,Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
         PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
         "loc.y=",1,0);
      if (pAddr) {
         sPara=pAddr;
         sPara.TrimLeft("(");
         sPara.TrimRight(")");
         switch (m_nAxisType) {
         case TYPE_X :
            m_dLocAnyAt=atof(sPara);
            break;
         case TYPE_Y :
            m_dLocAnyFrom=atof(sPara);
            nResult=sPara.Find(",");
            sPara.Delete(0,nResult+1);
            m_dLocAnyTo=atof(sPara);
            break;
         }
         myFree(pAddr);
      }
   }

   pAddr=SEGetOptionValueString(
      "on",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "axle=",1,
      0);
   m_bAxisDisplay=tolower(pAddr[1])=='n' ? TRUE:FALSE;
   myFree(pAddr);

   pAddr=SEGetOptionValueString(
      "black",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "axle.color=",1,
      0);
   m_AxisColorBtn.nCurrentColor=isdigit(pAddr[0]) ?
      atoi((LPCTSTR)pAddr):
      GEColorByName(NULL,(LPCTSTR)pAddr);
   myFree(pAddr);
   m_AxisColorBtn.Invalidate();

   m_nAxleThickness=SEGetOptionValueInteger(
      1,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "axle.width=",1,
      0);

   pAddr=SEGetOptionValueString(
      "on",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "tickmajor=",1,
      0);
   m_bMajorTickDisplay=tolower(pAddr[1])=='n' ? TRUE:FALSE;
   myFree(pAddr);

   pAddr=SEGetOptionValueString(
      "inside",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "tickmajor.loc=",1,
      0);
   m_bMajorTickInside=m_bMajorTickOutside=FALSE;
   switch (tolower(*pAddr)) {
   case 'i' : m_bMajorTickInside=TRUE;break;
   case 'o' : m_bMajorTickOutside=TRUE;break;
   case 'c' : m_bMajorTickInside=m_bMajorTickOutside=TRUE;break;
   }
   myFree(pAddr);

   
   m_sMajorTickStep=SEGetOptionValueString(
      "0",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "tickmajor.step=",1,
      0);
   dValue=stod(m_sMajorTickStep);
   m_sMajorTickStep=dtos(dValue,"%.0z");
   m_bMajorTickStepAuto=dValue==0.0 ? TRUE:FALSE;

   pAddr=SEGetOptionValueString(
      "on",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "tickminor=",1,
      0);
   m_bMinorTickDisplay=tolower(pAddr[1])=='n' ? TRUE:FALSE;
   myFree(pAddr);

   pAddr=SEGetOptionValueString(
      "inside",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "tickminor.loc=",1,
      0);
   m_bMinorTickInside=m_bMinorTickOutside=FALSE;
   switch (tolower(*pAddr)) {
   case 'i' : m_bMinorTickInside=TRUE;break;
   case 'o' : m_bMinorTickOutside=TRUE;break;
   case 'c' : m_bMinorTickInside=m_bMinorTickOutside=TRUE;break;
   }
   myFree(pAddr);

   m_sMinorTickStep=SEGetOptionValueString(
      "0",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "tickminor.step=",1,
      0);
   dValue=stod(m_sMinorTickStep);
   m_sMinorTickStep=dtos(dValue,"%.0z");
   m_bMinorTickStepAuto=dValue==0.0 ? TRUE:FALSE;

   pAddr=SEGetOptionValueString(
      "on",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "label=",1,
      0);
   m_bLabelDisplay=tolower(pAddr[1])=='n' ? TRUE:FALSE;
   myFree(pAddr);

   pAddr=SEGetOptionValueString(
      "black",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "label.color=",1,
      0);
   m_LabelColorBtn.nCurrentColor=isdigit(pAddr[0]) ?
      atoi((LPCTSTR)pAddr):
      GEColorByName(NULL,(LPCTSTR)pAddr);
   myFree(pAddr);
   m_LabelColorBtn.Invalidate();

   m_sLabelFormat=pAddr=SEGetOptionValueString(
      "%g",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "label.format=",1,
      0);
   myFree(pAddr);
   if (!m_sLabelFormat.IsEmpty() && m_sLabelFormat[0]=='\"') {
      m_sLabelFormat.Delete(0,1);
      m_sLabelFormat.Delete(m_sLabelFormat.GetLength()-1,1);
   }

   m_sLabelEquation=pAddr=SEGetOptionValueString(
      NULL,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "label.eq=",1,
      0);
   if (pAddr) myFree(pAddr);
   if (!m_sLabelEquation.IsEmpty() && m_sLabelEquation[0]=='\"') {
      m_sLabelEquation.Delete(0,1);
      m_sLabelEquation.Delete(m_sLabelEquation.GetLength()-1,1);
   }

   m_sTitle=pAddr=SEGetOptionValueString(
      NULL,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "title=",1,
      0);
   if (pAddr) myFree(pAddr);
   if (!m_sTitle.IsEmpty() && m_sTitle[0]=='\"') {
      m_sTitle.Delete(0,1);
      m_sTitle.Delete(m_sTitle.GetLength()-1,1);
   }

   pAddr=SEGetOptionValueString(
      "t",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "title.show=",1,
      0);
   m_bTitleDisplay=tolower(pAddr[0])=='t' ? TRUE:FALSE;
   myFree(pAddr);

   pAddr=SEGetOptionValueString(
      "black",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "title.color=",1,
      0);
   m_TitleColorBtn.nCurrentColor=isdigit(pAddr[0]) ?
      atoi((LPCTSTR)pAddr):
      GEColorByName(NULL,(LPCTSTR)pAddr);
   myFree(pAddr);
   m_TitleColorBtn.Invalidate();

   m_dTitleSpaceFactor=SEGetOptionValueFloating(
      5.0,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "title.spaceFactor=",1,
      0);

   pAddr=SEGetOptionValueString(
      "off",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "gridmajor=",1,
      0);
   m_bMajorGridDisplay=tolower(pAddr[1])=='n' ? TRUE:FALSE;
   myFree(pAddr);

   pAddr=SEGetOptionValueString(
      "black",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "gridmajor.color=",1,
      0);
   m_MajorGridColorBtn.nCurrentColor=isdigit(pAddr[0]) ?
      atoi((LPCTSTR)pAddr):
      GEColorByName(NULL,(LPCTSTR)pAddr);
   myFree(pAddr);
   m_MajorGridColorBtn.Invalidate();

   CComboBox *pBox;

   pBox=(CComboBox*)GetDlgItem(ID_GRAXIS_GRIDMAJOR_LINESTYLE);
   pAddr=SEGetOptionValueString(
      "solid",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "gridmajor.dash_list=",1,
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

   pAddr=SEGetOptionValueString(
      "off",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "gridminor=",1,
      0);
   m_bMinorGridDisplay=tolower(pAddr[1])=='n' ? TRUE:FALSE;
   myFree(pAddr);

   pAddr=SEGetOptionValueString(
      "black",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "gridminor.color=",1,
      0);
   m_MinorGridColorBtn.nCurrentColor=isdigit(pAddr[0]) ?
      atoi((LPCTSTR)pAddr):
      GEColorByName(NULL,(LPCTSTR)pAddr);
   myFree(pAddr);
   m_MinorGridColorBtn.Invalidate();

   pBox=(CComboBox*)GetDlgItem(ID_GRAXIS_GRIDMINOR_LINESTYLE);
   pAddr=SEGetOptionValueString(
      "solid",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
      "gridminor.dash_list=",1,
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

   UpdateData(FALSE);
   SetCheckButtonsOfAxisType();
   SetCheckButtonsOfAxisLocation();
   OnGraxisTickmajorStepAuto();
   OnGraxisTickminorStepAuto();
}

void CGrAxisPage::GetAxisDataFromDialog(int nIndex)
{
   if (!UpdateData(TRUE)) return;
   if (nIndex<=0) return;

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   char *pScript;
   int nScript;
   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   CString sAxisType,sPara;
   sAxisType.Format("%s=%c",PLOTSCRIPT_TYPE,m_nAxisType==TYPE_X ? 'x':'y');

   sPara="loc=";
   switch (m_nAxisLocationType) {
   case LOC_LOW :   sPara+="lower";break;
   case LOC_MIDDLE: sPara+="middle";break;
   case LOC_HIGH:   sPara+="upper";break;
   case LOC_ANY:    sPara+="any";break;
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   switch (m_nAxisType) {
   case TYPE_X :
      sPara.Format("loc.x=(%1.2e,%1.2e)",m_dLocAnyFrom,m_dLocAnyTo);
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
         sAxisType,nIndex,sPara,1,0);
      sPara.Format("loc.y=%1.2e",m_dLocAnyAt);
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
         sAxisType,nIndex,sPara,1,0);
      break;
   case TYPE_Y :
      sPara.Format("loc.y=(%1.2e,%1.2e)",m_dLocAnyFrom,m_dLocAnyTo);
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
         sAxisType,nIndex,sPara,1,0);
      sPara.Format("loc.x=%1.2e",m_dLocAnyAt);
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
         sAxisType,nIndex,sPara,1,0);
      break;
   }

   sPara="axle=";
   switch (m_bAxisDisplay) {
   case TRUE : sPara+="on";break;
   case FALSE : sPara+="off";break;
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("axle.color=%d",m_AxisColorBtn.nCurrentColor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("axle.width=%d",m_nAxleThickness);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara="tickmajor=";
   switch (m_bMajorTickDisplay) {
   case TRUE : sPara+="on";break;
   case FALSE : sPara+="off";break;
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara="tickmajor.loc=";
   if (m_bMajorTickInside && m_bMajorTickOutside) {
      sPara+="cross";
   } else if (m_bMajorTickInside) {
      sPara+="inside";
   } else if (m_bMajorTickOutside) {
      sPara+="outside";
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("tickmajor.step=%g",stod(m_sMajorTickStep));
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara="tickminor=";
   switch (m_bMinorTickDisplay) {
   case TRUE : sPara+="on";break;
   case FALSE : sPara+="off";break;
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara="tickminor.loc=";
   if (m_bMinorTickInside && m_bMinorTickOutside) {
      sPara+="cross";
   } else if (m_bMinorTickInside) {
      sPara+="inside";
   } else if (m_bMajorTickOutside) {
      sPara+="outside";
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("tickminor.step=%g",stod(m_sMinorTickStep));
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara="label=";
   switch (m_bLabelDisplay) {
   case TRUE : sPara+="on";break;
   case FALSE : sPara+="off";break;
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("label.color=%d",m_LabelColorBtn.nCurrentColor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("label.format=%s",m_sLabelFormat);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("label.eq=\"%s\"",m_sLabelEquation);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("title=\"%s\"",m_sTitle);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara="title.show=";
   sPara+=m_bTitleDisplay ? "t":"f";
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("title.color=%d",m_TitleColorBtn.nCurrentColor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("title.spaceFactor=%.2f",m_dTitleSpaceFactor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara="gridmajor=";
   switch (m_bMajorGridDisplay) {
   case TRUE : sPara+="on";break;
   case FALSE : sPara+="off";break;
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("gridmajor.color=%d",m_MajorGridColorBtn.nCurrentColor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   CComboBox *pBox;

   pBox=(CComboBox*)GetDlgItem(ID_GRAXIS_GRIDMAJOR_LINESTYLE);
   pBox->GetLBText(pBox->GetCurSel(),sPara);
   sPara.TrimRight(" ._-");
   sPara.Insert(0,"gridmajor.dash_list=");
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara="gridminor=";
   switch (m_bMinorGridDisplay) {
   case TRUE : sPara+="on";break;
   case FALSE : sPara+="off";break;
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   sPara.Format("gridminor.color=%d",m_MinorGridColorBtn.nCurrentColor);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);

   pBox=(CComboBox*)GetDlgItem(ID_GRAXIS_GRIDMINOR_LINESTYLE);
   pBox->GetLBText(pBox->GetCurSel(),sPara);
   sPara.TrimRight(" ._-");
   sPara.Insert(0,"gridminor.dash_list=");
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,
      sAxisType,nIndex,sPara,1,0);
   
   Script=pScript;
   delete pScript;
}

BOOL CGrAxisPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL bResult=CPropertyPage::OnKillActive();

   GetAxisDataFromDialog(m_ID.GetCurSel()+1);

   return bResult;
}

BOOL CGrAxisPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return CPropertyPage::OnSetActive();

   int nResult,nCount,nIndex;
   char *pAddr;
   CString sPara;

   nResult=SEGetOptionPosition(
      Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_AXIS,1,0);
   nCount=SEGetOptionFrequencyInaRange(Script,nResult,PLOTSCRIPT_TYPE);
   if (!nCount) return CPropertyPage::OnSetActive();

   m_ID.ResetContent();
   for (nIndex=1;nIndex<=nCount;nIndex++) {
       pAddr=SEGetOptionValueString(
          "?",Script,
          PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
          PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
          0);
       sPara.Format("%d) %c ",nIndex,*pAddr);
       myFree(pAddr);
       pAddr=SEGetOptionValueString(
          "?",Script,
          PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
          PLOTSCRIPT_AXIS,1,PLOTSCRIPT_TYPE,nIndex,
          "title=",1,
          0);
       sPara+=pAddr;
       myFree(pAddr);
       m_ID.AddString(sPara);
   }
   if (nCount>0) {
      m_nPrecedingComboBoxSelection=0;
      m_ID.SetCurSel(m_nPrecedingComboBoxSelection);
      SetAxisDataToDialog(m_nPrecedingComboBoxSelection+1);
   }

   if (m_bFirstSetActive) UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

void CGrAxisPage::OnGraxisOnoffTool( int nID ) 
{
	// TODO: Add your control notification handler code here

   int bCheck=nID==ID_GRAXIS_DISPLAY_ON ? 1:0;

	((CButton*)GetDlgItem(ID_GRAXIS_AXIS_DISPLAY))->SetCheck(bCheck);
   ((CButton*)GetDlgItem(ID_GRAXIS_TICKMAJOR_DISPLAY))->SetCheck(bCheck);
   ((CButton*)GetDlgItem(ID_GRAXIS_TICKMINOR_DISPLAY))->SetCheck(bCheck);
   ((CButton*)GetDlgItem(ID_GRAXIS_LABEL_DISPLAY))->SetCheck(bCheck);
   ((CButton*)GetDlgItem(ID_GRAXIS_TITLE_DISPLAY))->SetCheck(bCheck);
   ((CButton*)GetDlgItem(ID_GRAXIS_GRIDMAJOR_DISPLAY))->SetCheck(bCheck);
   ((CButton*)GetDlgItem(ID_GRAXIS_GRIDMINOR_DISPLAY))->SetCheck(bCheck);
}

