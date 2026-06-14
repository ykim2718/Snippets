// GrGlobPage.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrGlobPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "plot.h"
#include "GrPropertySheet.h"
#include "SmallFontAttrDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CGrGlobPage property page

IMPLEMENT_DYNCREATE(CGrGlobPage, CPropertyPage)

CGrGlobPage::CGrGlobPage() : CPropertyPage(CGrGlobPage::IDD)
{
	//{{AFX_DATA_INIT(CGrGlobPage)
	m_sHeader = _T("");
	m_dTitleSpaceFactor = 1.0;
	m_bEchoPlotPoints = FALSE;
	//}}AFX_DATA_INIT
   m_nPageDirection=Portrait;
}

CGrGlobPage::~CGrGlobPage()
{
}

void CGrGlobPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrGlobPage)
	DDX_Text(pDX, ID_GRGLOB_HEADER, m_sHeader);
	DDV_MaxChars(pDX, m_sHeader, 256);
	DDX_Text(pDX, ID_GRGLOB_HEADER_SPACEFACTOR, m_dTitleSpaceFactor);
	DDV_MinMaxDouble(pDX, m_dTitleSpaceFactor, -16., 16.);
	DDX_Check(pDX, ID_GRGLOB_LOG_ECHOPLOTPOINTS, m_bEchoPlotPoints);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrGlobPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrGlobPage)
	ON_BN_CLICKED(ID_GRGLOB_HEADER_ATTRIBUTE, OnGrglobHeaderAttribute)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRGLOB_HEADER_SPACEFACTOR_SPIN, OnDeltaposGrglobHeaderSpacefactorSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrGlobPage message handlers

BOOL CGrGlobPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CGrGlobPage::SetCheckButtonsOfPageDirection();
   //
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrGlobPage::SetCheckButtonsOfPageDirection()
{
   ((CButton*)GetDlgItem(ID_GRGLOB_LANDSCAPE))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRGLOB_PORTRAIT))->SetCheck(0);
   switch(m_nPageDirection) {
   case Landscape : ((CButton*)GetDlgItem(ID_GRGLOB_LANDSCAPE))->SetCheck(1);break;
   case Portrait : ((CButton*)GetDlgItem(ID_GRGLOB_PORTRAIT))->SetCheck(1);break;
   }
}

void CGrGlobPage::GetCheckButtonsOfPageDirection()
{
   if (((CButton*)GetDlgItem(ID_GRGLOB_PORTRAIT))->GetCheck())
      m_nPageDirection=Portrait;
   else if (((CButton*)GetDlgItem(ID_GRGLOB_LANDSCAPE))->GetCheck())
      m_nPageDirection=Landscape;
}

BOOL CGrGlobPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bResult=CPropertyPage::OnKillActive();

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return bResult;

   GetCheckButtonsOfPageDirection();

   char *pScript;
   int nScript;
   CString sPara;

   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   sPara.Format("txt=\"%s\"",m_sHeader);
   SESetOptionParameter(
      pScript,nScript,PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,
      sPara,1,0);

   sPara.Format("txt.spaceFactor=%.3f",m_dTitleSpaceFactor);
   SESetOptionParameter(
      pScript,nScript,PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,
      sPara,1,0);

   switch (m_nPageDirection) {
   case Landscape :
      sPara="landscape";
      SEDelOptionParameter(
         pScript,PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GOUT,1,"portrait",1,0);
      break;
   case Portrait :
      sPara="portrait";
      SEDelOptionParameter(
         pScript,PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GOUT,1,"landscape",1,0);
      break;
   }
   SESetOptionParameter(
      pScript,nScript,PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GOUT,1,
      sPara,1,0);

   sPara.Format("bEchoPlotPoints=%d",m_bEchoPlotPoints);
   SESetOptionParameter(
      pScript,nScript,PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GOUT,1,
      sPara,1,0);

   Script=pScript;
   delete pScript;
   
   return true;
}

BOOL CGrGlobPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return CPropertyPage::OnSetActive();

   char *pAddr;
   int nResult;

   m_sHeader=pAddr=SEGetOptionValueString(
      NULL,Script,PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"txt=",1,0);
   myFree(pAddr);
   if (!m_sHeader.IsEmpty()) {
      m_sHeader.TrimLeft('\"');
      m_sHeader.TrimRight('\"');
   }

   m_dTitleSpaceFactor=SEGetOptionValueFloating(1.0,Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"txt.spaceFactor=",1,0);

   nResult=SEGetOptionPosition(Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GOUT,1,"landscape",1,0);
   m_nPageDirection=nResult<0 ? Portrait:Landscape;

   SetCheckButtonsOfPageDirection();

   m_bEchoPlotPoints=SEGetOptionValueInteger(1,Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GOUT,1,"bEchoPlotPoints",1,0);

   if (m_bFirstSetActive) UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

void CGrGlobPage::OnGrglobHeaderAttribute() 
{
	// TODO: Add your control notification handler code here

   CWnd *pWnd=GetFocus();
   CRect Rect;
   pWnd->GetWindowRect(&Rect);
	CSmallFontAttrDialog Dialog;
   Dialog.SetWindowGravityPos(Rect.CenterPoint());

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;
   int nResult;
   char *pAddr;

   nResult=SEGetOptionValueInteger (10,Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"t.size=",1,0);
   Dialog.m_nHeight=nResult;
   Dialog.m_nWidth=nResult/2;

   nResult=SEGetOptionValueInteger(5,Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"t.width=",1,0);
   Dialog.m_nWidth=nResult;

   nResult=SEGetOptionValueInteger(10,Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"t.height=",1,0);
   Dialog.m_nHeight=nResult;

   Dialog.m_sAlignment=pAddr=SEGetOptionValueString(
      "LB",Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"t.align=",1,0);
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

   nResult=SEGetOptionValueInteger(0,Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"t.angle=",1,0);
   Dialog.m_nAngle=nResult;

   nResult=SEGetOptionPosition(Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"t.color=",1,0);
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

   nResult=SEGetOptionPosition(Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"t.size=",1,0);
   if (nResult>=0) {
      int nCount=SEGetOptionLength(Script,nResult);
      Script.Delete(nResult,nCount);
   }

   char *pScript;
   int nScript,bResult;
   CString sTemp;
   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   SEDelOptionParameter(pScript,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,"t.size=",1,0);

   sTemp.Format("t.width=%d",Dialog.m_nWidth);
   bResult=SESetOptionParameter(pScript,nScript,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,sTemp,1,0);
   if (!bResult) goto R;

   sTemp.Format("t.height=%d",Dialog.m_nHeight);
   bResult=SESetOptionParameter(pScript,nScript,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,sTemp,1,0);
   if (!bResult) goto R;

   sTemp.Format("t.align=%s",Dialog.m_sAlignment);
   bResult=SESetOptionParameter(pScript,nScript,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,sTemp,1,0);
   if (!bResult) goto R;

   sTemp.Format("t.angle=%d",Dialog.m_nAngle);
   bResult=SESetOptionParameter(pScript,nScript,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,sTemp,1,0);
   if (!bResult) goto R;

   sTemp.Format("t.color=%d",Dialog.m_ColorBtn.nCurrentColor);
   bResult=SESetOptionParameter(pScript,nScript,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_GTXT,1,sTemp,1,0);
   if (!bResult) goto R;

   Script=pScript;
R: delete pScript;
   return;
}

void CGrGlobPage::OnDeltaposGrglobHeaderSpacefactorSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
   CString sReturn;
   CWnd *pWnd=GetDlgItem(ID_GRGLOB_HEADER_SPACEFACTOR);
   pWnd->GetWindowText(sReturn);
   float factor=(float)atof((LPCTSTR)sReturn);
   switch (pNMUpDown->iDelta) {
   case -1 : factor+=0.25;break;
   case +1 : factor-=0.25;break;
   }
   sReturn.Format("%.2f",factor);
   pWnd->SetWindowText((LPCTSTR)sReturn);

   //
   *pResult = 0;
}
