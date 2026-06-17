// GrXyzbPage.cpp : implementation file
//

#include "stdafx.h"
#include "grapher.h"
#include "GrXyzbPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Y.Kim

#include <float.h>
#include "GrPropertySheet.h"
#include "str.h"

/////////////////////////////////////////////////////////////////////////////
// CGrXyzbPage property page

IMPLEMENT_DYNCREATE(CGrXyzbPage, CPropertyPage)

CGrXyzbPage::CGrXyzbPage() : CPropertyPage(CGrXyzbPage::IDD)
{
	//{{AFX_DATA_INIT(CGrXyzbPage)
	m_bXlbAll = FALSE;
	m_bYlbAll = FALSE;
	m_bZlbAll = FALSE;
	m_bXubAll = FALSE;
	m_bYubAll = FALSE;
	m_bZubAll = FALSE;
	m_bXlbAuto = TRUE;
	m_bXubAuto = TRUE;
	m_bYlbAuto = TRUE;
	m_bYubAuto = TRUE;
	m_bZlbAuto = TRUE;
	m_bZubAuto = TRUE;
	m_sXlb = _T("");
	m_sXub = _T("");
	m_sYlb = _T("");
	m_sYub = _T("");
	m_sZlb = _T("");
	m_sZub = _T("");
	m_dXlbData = 0.0;
	m_dXubData = 0.0;
	m_dYlbData = 0.0;
	m_dYubData = 0.0;
	m_dZlbData = 0.0;
	m_dZubData = 0.0;
	//}}AFX_DATA_INIT
}

CGrXyzbPage::~CGrXyzbPage()
{
}

void CGrXyzbPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrXyzbPage)
	DDX_Control(pDX, ID_GRXYZB_COLUMNS, m_XYZListBox);
	DDX_Check(pDX, ID_GRXYZB_XLB_ALL, m_bXlbAll);
	DDX_Check(pDX, ID_GRXYZB_YLB_ALL, m_bYlbAll);
	DDX_Check(pDX, ID_GRXYZB_ZLB_ALL, m_bZlbAll);
	DDX_Check(pDX, ID_GRXYZB_XUB_ALL, m_bXubAll);
	DDX_Check(pDX, ID_GRXYZB_YUB_ALL, m_bYubAll);
	DDX_Check(pDX, ID_GRXYZB_ZUB_ALL, m_bZubAll);
	DDX_Check(pDX, ID_GRXYZB_XLB_AUTO, m_bXlbAuto);
	DDX_Check(pDX, ID_GRXYZB_XUB_AUTO, m_bXubAuto);
	DDX_Check(pDX, ID_GRXYZB_YLB_AUTO, m_bYlbAuto);
	DDX_Check(pDX, ID_GRXYZB_YUB_AUTO, m_bYubAuto);
	DDX_Check(pDX, ID_GRXYZB_ZLB_AUTO, m_bZlbAuto);
	DDX_Check(pDX, ID_GRXYZB_ZUB_AUTO, m_bZubAuto);
	DDX_Text(pDX, ID_GRXYZB_XLB_DATA, m_dXlbData);
	DDX_Text(pDX, ID_GRXYZB_XUB_DATA, m_dXubData);
	DDX_Text(pDX, ID_GRXYZB_YLB_DATA, m_dYlbData);
	DDX_Text(pDX, ID_GRXYZB_YUB_DATA, m_dYubData);
	DDX_Text(pDX, ID_GRXYZB_ZLB_DATA, m_dZlbData);
	DDX_Text(pDX, ID_GRXYZB_ZUB_DATA, m_dZubData);
	DDX_Text(pDX, ID_GRXYZB_XLB, m_sXlb);
	DDX_Text(pDX, ID_GRXYZB_XUB, m_sXub);
	DDX_Text(pDX, ID_GRXYZB_YLB, m_sYlb);
	DDX_Text(pDX, ID_GRXYZB_YUB, m_sYub);
	DDX_Text(pDX, ID_GRXYZB_ZLB, m_sZlb);
	DDX_Text(pDX, ID_GRXYZB_ZUB, m_sZub);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrXyzbPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrXyzbPage)
	//}}AFX_MSG_MAP
   ON_CONTROL_RANGE(BN_CLICKED,ID_GRXYZB_XLB_AUTO,ID_GRXYZB_ZUB_AUTO,OnGrxyzbAutoButtons)
	ON_CONTROL_RANGE(BN_CLICKED,ID_GRXYZB_XLB_ALL,ID_GRXYZB_ZUB_ALL,OnGrxyzbApplyAll)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrXyzbPage message handlers

BOOL CGrXyzbPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   LOGFONT LogFont;
   GetFont()->GetLogFont(&LogFont);
   LogFont.lfUnderline=TRUE;
   m_MyFont.CreateFontIndirect(&LogFont);
   GetDlgItem(ID_GRXYZB_VARIABLES)->SetFont(&m_MyFont);
   GetDlgItem(ID_GRXYZB_BOUNDARY)->SetFont(&m_MyFont);

   OnGrxyzbAutoButtons(ID_GRXYZB_XLB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_XUB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_YLB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_YUB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_ZLB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_ZUB_AUTO);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CGrXyzbPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   double dValue;
   char *qFormat="%z"; // 20030803. %.1z->%z

   dValue=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,"xlb=",1,0);;
   m_bXlbAuto=dValue==DBL_MIN ? TRUE:FALSE;
   if (dValue==DBL_MIN) dValue=GetValueFromGrLog(".xlb=",0);
   m_sXlb=dtos(dValue,qFormat);

   dValue=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,"xub=",1,0);
   m_bXubAuto=dValue==DBL_MIN ? TRUE:FALSE;
   if (dValue==DBL_MIN) dValue=GetValueFromGrLog("xub=",0);
   m_sXub=dtos(dValue,qFormat);

   dValue=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,"ylb=",1,0);
   m_bYlbAuto=dValue==DBL_MIN ? TRUE:FALSE;
   if (dValue==DBL_MIN) dValue=GetValueFromGrLog(".ylb=",0);
   m_sYlb=dtos(dValue,qFormat);

   dValue=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,"yub=",1,0);
   m_bYubAuto=dValue==DBL_MIN ? TRUE:FALSE;
   if (dValue==DBL_MIN) dValue=GetValueFromGrLog("yub=",0);
   m_sYub=dtos(dValue,qFormat);

   dValue=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,"zlb=",1,0);
   m_bZlbAuto=dValue==DBL_MIN ? TRUE:FALSE;
   if (dValue==DBL_MIN) dValue=GetValueFromGrLog(".zlb=",0);
   m_sZlb=dtos(dValue,qFormat);

   dValue=SEGetOptionValueFloating(DBL_MIN,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,"zub=",1,0);
   m_bZubAuto=dValue==DBL_MIN ? TRUE:FALSE;
   if (dValue==DBL_MIN) dValue=GetValueFromGrLog("zub=",0);
   m_sZub=dtos(dValue,qFormat);

   m_dXlbData=m_dXlbData=m_dYlbData=m_dYubData=m_dZlbData=m_dZubData=0.0;
   m_dXlbData=GetValueFromGrLog("xmin=",0);
   m_dXubData=GetValueFromGrLog("xmax=",0);
   m_dYlbData=GetValueFromGrLog("ymin=",0);
   m_dYubData=GetValueFromGrLog("ymax=",0);
   m_dZlbData=GetValueFromGrLog("zmin=",0);
   m_dZubData=GetValueFromGrLog("zmax=",0);

   UpdateData(false);

   OnGrxyzbAutoButtons(ID_GRXYZB_XLB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_XUB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_YLB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_YUB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_ZLB_AUTO);
   OnGrxyzbAutoButtons(ID_GRXYZB_ZUB_AUTO);

	return CPropertyPage::OnSetActive();
}

BOOL CGrXyzbPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class

   BOOL bResult=CPropertyPage::OnKillActive();
   if (!bResult) return bResult;
   
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return bResult;

   if (!m_bXlbAuto && !m_bXubAuto && stod(m_sXlb)>=stod(m_sXub)) {
      MessageBox("X: LOW can not be equal or greater than HIGH.",NULL,MB_ICONWARNING);
      return FALSE;
   }
   if (!m_bYlbAuto && !m_bYubAuto && stod(m_sYlb)>=stod(m_sYub)) {
      MessageBox("Y: LOW can not be equal or greater than HIGH.",NULL,MB_ICONWARNING);
      return FALSE;
   }
   if (!m_bZlbAuto && !m_bZubAuto && stod(m_sZlb)>=stod(m_sZub)) {
      MessageBox("Z: LOW can not be equal or greater than HIGH.",NULL,MB_ICONWARNING);
      return FALSE;
   }

   char *pScript;
   int nScript;
   CString sPara;

   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   sPara.Format("xlb=%g",stod(m_sXlb));
   if (m_bXlbAuto) sPara.Replace("=","=*");
   SetGrScript(pScript,nScript,pSheet->m_nPlotIndex,sPara);

   sPara.Format("xub=%g",stod(m_sXub));
   if (m_bXubAuto) sPara.Replace("=","=*");
   SetGrScript(pScript,nScript,pSheet->m_nPlotIndex,sPara);

   sPara.Format("ylb=%g",stod(m_sYlb));
   if (m_bYlbAuto) sPara.Replace("=","=*");
   SetGrScript(pScript,nScript,pSheet->m_nPlotIndex,sPara);

   sPara.Format("yub=%g",stod(m_sYub));
   if (m_bYubAuto) sPara.Replace("=","=*");
   SetGrScript(pScript,nScript,pSheet->m_nPlotIndex,sPara);

   sPara.Format("zlb=%g",stod(m_sZlb));
   if (m_bZlbAuto) sPara.Replace("=","=*");
   SetGrScript(pScript,nScript,pSheet->m_nPlotIndex,sPara);

   sPara.Format("zub=%g",stod(m_sZub));
   if (m_bZubAuto) sPara.Replace("=","=*");
   SetGrScript(pScript,nScript,pSheet->m_nPlotIndex,sPara);

   Script=pScript;
   delete pScript;

   return bResult;
}

void CGrXyzbPage::OnGrxyzbAutoButtons( UINT nID ) 
{
	// TODO: Add your control notification handler code here

   CWnd *pWnd;
	switch (nID) {
   case ID_GRXYZB_XLB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_XLB_AUTO);break;
   case ID_GRXYZB_XUB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_XUB_AUTO);break;
   case ID_GRXYZB_YLB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_YLB_AUTO);break;
   case ID_GRXYZB_YUB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_YUB_AUTO);break;
   case ID_GRXYZB_ZLB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_ZLB_AUTO);break;
   case ID_GRXYZB_ZUB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_ZUB_AUTO);break;
   }
   int bCheck=((CButton*)pWnd)->GetCheck();
   switch (nID) {
   case ID_GRXYZB_XLB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_XLB);break;
   case ID_GRXYZB_XUB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_XUB);break;
   case ID_GRXYZB_YLB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_YLB);break;
   case ID_GRXYZB_YUB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_YUB);break;
   case ID_GRXYZB_ZLB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_ZLB);break;
   case ID_GRXYZB_ZUB_AUTO : pWnd=GetDlgItem(ID_GRXYZB_ZUB);break;
   }
	pWnd->EnableWindow(!bCheck);
}

double CGrXyzbPage::GetValueFromGrLog(const char *qPara, double dDefault)
{
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrLog;
   if (Script.IsEmpty()) return dDefault;
   double dReturn=SEGetOptionValueFloating(dDefault,Script,qPara,pSheet->m_nPlotIndex,0);
   return dReturn;
}

void CGrXyzbPage::SetGrScript(
   const char *pScript, int nScript, int nPlotIndex, const char *qPara )
{
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,nPlotIndex,
      PLOTSCRIPT_SLCT,1,PLOTSCRIPT_4UNDERSCORES,1,
      qPara,1,0);
}

void CGrXyzbPage::OnGrxyzbApplyAll( UINT nID )
{
	// TODO: Add your control notification handler code here

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;
   char *pScript;
   int nScript;
   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   UpdateData(true);

   CString sPara;
   switch (nID) {
   case ID_GRXYZB_XLB_ALL : sPara.Format("xlb=%g",stod(m_sXlb));break;
   case ID_GRXYZB_XUB_ALL : sPara.Format("xub=%g",stod(m_sXub));break;
   case ID_GRXYZB_YLB_ALL : sPara.Format("ylb=%g",stod(m_sYlb));break;
   case ID_GRXYZB_YUB_ALL : sPara.Format("yub=%g",stod(m_sYub));break;
   case ID_GRXYZB_ZLB_ALL : sPara.Format("zlb=%g",stod(m_sZlb));break;
   case ID_GRXYZB_ZUB_ALL : sPara.Format("zub=%g",stod(m_sZub));break;
   }
   switch (nID) {
   case ID_GRXYZB_XLB_ALL : if (m_bXlbAuto) sPara.Replace("=","=*");break;
   case ID_GRXYZB_XUB_ALL : if (m_bXubAuto) sPara.Replace("=","=*");break;
   case ID_GRXYZB_YLB_ALL : if (m_bYlbAuto) sPara.Replace("=","=*");break;
   case ID_GRXYZB_YUB_ALL : if (m_bYubAuto) sPara.Replace("=","=*");break;
   case ID_GRXYZB_ZLB_ALL : if (m_bZlbAuto) sPara.Replace("=","=*");break;
   case ID_GRXYZB_ZUB_ALL : if (m_bZubAuto) sPara.Replace("=","=*");break;
   }
   for (int nIndex=1;nIndex<=pSheet->m_nPlotTotal;nIndex++) {
      SetGrScript(pScript,nScript,nIndex,sPara);
   }

   Script=pScript;
   delete pScript;
}
