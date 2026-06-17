// GrAttrPage.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrAttrPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "GrPropertySheet.h"

// Sequence and name have a special meaning. Do not change this.
static char *ppType[]={ "genetic","genetic+","moment","flat3d","bar","area","column","pie" };
static char *ppXScale[]={ "xlin","xlog","xnormal","xseries" };
static char *ppYScale[]={ "ylin","ylog","ynormal" };
static char *ppZScale[]={ "zlin","zlog" };

/////////////////////////////////////////////////////////////////////////////
// CGrAttrPage property page

IMPLEMENT_DYNCREATE(CGrAttrPage, CPropertyPage)

CGrAttrPage::CGrAttrPage() : CPropertyPage(CGrAttrPage::IDD)
{
	//{{AFX_DATA_INIT(CGrAttrPage)
	m_bAttrPrevious = FALSE;
	//}}AFX_DATA_INIT
   m_attrType=Genetic;
   m_dimension=TwoDimension;
   m_xScale=m_yScale=m_zScale=Linear;
}

CGrAttrPage::~CGrAttrPage()
{
}

void CGrAttrPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrAttrPage)
	DDX_Check(pDX, ID_GRATTR_PREVIOUS, m_bAttrPrevious);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrAttrPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrAttrPage)
	ON_BN_CLICKED(ID_GRATTR_TYPE_GENETIC, OnGrattrTypeGenetic)
	ON_BN_CLICKED(ID_GRATTR_TYPE_MOMENT, OnGrattrTypeMoment)
	ON_BN_CLICKED(ID_GRATTR_TYPE_AREA, OnGrattrTypeArea)
	ON_BN_CLICKED(ID_GRATTR_TYPE_BAR, OnGrattrTypeBar)
	ON_BN_CLICKED(ID_GRATTR_TYPE_COLUMN, OnGrattrTypeColumn)
	ON_BN_CLICKED(ID_GRATTR_TYPE_PIE, OnGrattrTypePie)
	ON_BN_CLICKED(ID_GRATTR_DIM_2D, OnGrattrDim2d)
	ON_BN_CLICKED(ID_GRATTR_DIM_3D, OnGrattrDim3d)
	ON_BN_CLICKED(ID_GRATTR_SCALE_X_LINEAR, OnGrattrScaleXLinear)
	ON_BN_CLICKED(ID_GRATTR_SCALE_X_LOGARITHMIC, OnGrattrScaleXLogarithmic)
	ON_BN_CLICKED(ID_GRATTR_SCALE_X_NORMAL, OnGrattrScaleXNormal)
	ON_BN_CLICKED(ID_GRATTR_SCALE_X_WEIBULL, OnGrattrScaleXWeibull)
	ON_BN_CLICKED(ID_GRATTR_SCALE_X_SERIES, OnGrattrScaleXSeries)
	ON_BN_CLICKED(ID_GRATTR_SCALE_Y_LINEAR, OnGrattrScaleYLinear)
	ON_BN_CLICKED(ID_GRATTR_SCALE_Y_LOGARITHMIC, OnGrattrScaleYLogarithmic)
	ON_BN_CLICKED(ID_GRATTR_SCALE_Y_NORMAL, OnGrattrScaleYNormal)
	ON_BN_CLICKED(ID_GRATTR_SCALE_Y_WEIBULL, OnGrattrScaleYWeibull)
	ON_BN_CLICKED(ID_GRATTR_TYPE_FLAT3D, OnGrattrTypeFlat3d)
	ON_BN_CLICKED(ID_GRATTR_TYPE_GENETICPLUS, OnGrattrTypeGeneticplus)
	ON_BN_CLICKED(ID_GRATTR_SCALE_Z_LINEAR, OnGrattrScaleZLinear)
	ON_BN_CLICKED(ID_GRATTR_SCALE_Z_LOGARITHMIC, OnGrattrScaleZLogarithmic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrAttrPage message handlers

BOOL CGrAttrPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrAttrPage::SetCheckButtonsOfType()
{
   ((CButton*)GetDlgItem(ID_GRATTR_TYPE_GENETIC))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_TYPE_GENETICPLUS))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_TYPE_MOMENT))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_TYPE_FLAT3D))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_TYPE_AREA))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_TYPE_BAR))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_TYPE_COLUMN))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_TYPE_PIE))->SetCheck(0);
   switch(m_attrType) {
   case Genetic : ((CButton*)GetDlgItem(ID_GRATTR_TYPE_GENETIC))->SetCheck(1);break;
   case GeneticPlus : ((CButton*)GetDlgItem(ID_GRATTR_TYPE_GENETICPLUS))->SetCheck(1);break;
   case Moment : ((CButton*)GetDlgItem(ID_GRATTR_TYPE_MOMENT))->SetCheck(1);break;
   case Flat3D : ((CButton*)GetDlgItem(ID_GRATTR_TYPE_FLAT3D))->SetCheck(1);break;
   case Area : ((CButton*)GetDlgItem(ID_GRATTR_TYPE_AREA))->SetCheck(1);break;
   case Bar : ((CButton*)GetDlgItem(ID_GRATTR_TYPE_BAR))->SetCheck(1);break;
   case Column : ((CButton*)GetDlgItem(ID_GRATTR_TYPE_COLUMN))->SetCheck(1);break;
   case Pie : ((CButton*)GetDlgItem(ID_GRATTR_TYPE_PIE))->SetCheck(1);break;
   }
}

void CGrAttrPage::GetCheckButtonsOfType()
{
   if (((CButton*)GetDlgItem(ID_GRATTR_TYPE_GENETIC))->GetCheck())
      m_attrType=Genetic;
   else if (((CButton*)GetDlgItem(ID_GRATTR_TYPE_GENETICPLUS))->GetCheck())
      m_attrType=GeneticPlus;
   else if (((CButton*)GetDlgItem(ID_GRATTR_TYPE_MOMENT))->GetCheck())
      m_attrType=Moment;
   else if (((CButton*)GetDlgItem(ID_GRATTR_TYPE_FLAT3D))->GetCheck())
      m_attrType=Flat3D;
   else if (((CButton*)GetDlgItem(ID_GRATTR_TYPE_AREA))->GetCheck())
      m_attrType=Area;
   else if (((CButton*)GetDlgItem(ID_GRATTR_TYPE_BAR))->GetCheck())
      m_attrType=Bar;
   else if (((CButton*)GetDlgItem(ID_GRATTR_TYPE_COLUMN))->GetCheck())
      m_attrType=Column;
   else if (((CButton*)GetDlgItem(ID_GRATTR_TYPE_PIE))->GetCheck())
      m_attrType=Pie;
}

void CGrAttrPage::SetCheckButtonsOfDimension()
{
   //m_attrDimension=TwoDimension;
   ((CButton*)GetDlgItem(ID_GRATTR_DIM_2D))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_DIM_3D))->SetCheck(0);
   switch(m_dimension) {
   case TwoDimension : ((CButton*)GetDlgItem(ID_GRATTR_DIM_2D))->SetCheck(1);break;
   case ThreeDimension : ((CButton*)GetDlgItem(ID_GRATTR_DIM_3D))->SetCheck(1);break;
   }
}

void CGrAttrPage::GetCheckButtonsOfDimension()
{
   if (((CButton*)GetDlgItem(ID_GRATTR_DIM_2D))->GetCheck())
      m_dimension=TwoDimension;
   else if (((CButton*)GetDlgItem(ID_GRATTR_DIM_3D))->GetCheck())
      m_dimension=ThreeDimension;
}

void CGrAttrPage::SetCheckButtonsOfXScale()
{
   //m_attrDimension=TwoDimension;
   if (m_xScale==Normal || m_xScale==Weibull) {
      if (m_yScale==Normal || m_yScale==Weibull) {
         MessageBox("X and Y scale be not Gaussian or Weibull simultaneouly.",NULL,MB_ICONWARNING);
         //return;
      }
   }
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_LINEAR))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_LOGARITHMIC))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_NORMAL))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_WEIBULL))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_SERIES))->SetCheck(0);
   switch(m_xScale) {
   case Linear : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_LINEAR))->SetCheck(1);break;
   case Logarithmic : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_LOGARITHMIC))->SetCheck(1);break;
   case Normal : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_NORMAL))->SetCheck(1);break;
   case Weibull : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_WEIBULL))->SetCheck(1);break;
   case Series : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_X_SERIES))->SetCheck(1);break;
   }
}

void CGrAttrPage::GetCheckButtonsOfXScale()
{
}

void CGrAttrPage::SetCheckButtonsOfYScale()
{
   //m_attrDimension=TwoDimension;
   if (m_xScale==Normal || m_xScale==Weibull) {
      if (m_yScale==Normal || m_yScale==Weibull) {
         MessageBox("X and Y scale be not Gaussian or Weibull simultaneouly.",NULL,MB_ICONWARNING);
         //return;
      }
   }
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Y_LINEAR))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Y_LOGARITHMIC))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Y_NORMAL))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Y_WEIBULL))->SetCheck(0);
   switch(m_yScale) {
   case Linear : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Y_LINEAR))->SetCheck(1);break;
   case Logarithmic : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Y_LOGARITHMIC))->SetCheck(1);break;
   case Normal : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Y_NORMAL))->SetCheck(1);break;
   case Weibull : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Y_WEIBULL))->SetCheck(1);break;
   }
}

void CGrAttrPage::GetCheckButtonsOfYScale()
{
}

void CGrAttrPage::SetCheckButtonsOfZScale()
{
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Z_LINEAR))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Z_LOGARITHMIC))->SetCheck(0);
   switch(m_zScale) {
   case Linear : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Z_LINEAR))->SetCheck(1);break;
   case Logarithmic : ((CButton*)GetDlgItem(ID_GRATTR_SCALE_Z_LOGARITHMIC))->SetCheck(1);break;
   }
}

void CGrAttrPage::OnGrattrTypeGenetic() 
{
	// TODO: Add your control notification handler code here
   m_attrType=Genetic;
   CGrAttrPage::SetCheckButtonsOfType();
}

void CGrAttrPage::OnGrattrTypeGeneticplus() 
{
	// TODO: Add your control notification handler code here
	m_attrType=GeneticPlus;
   CGrAttrPage::SetCheckButtonsOfType();
}

void CGrAttrPage::OnGrattrTypeMoment() 
{
	// TODO: Add your control notification handler code here
   m_attrType=Moment;
   CGrAttrPage::SetCheckButtonsOfType();
}

void CGrAttrPage::OnGrattrTypeFlat3d() 
{
	// TODO: Add your control notification handler code here
	m_attrType=Flat3D;
   CGrAttrPage::SetCheckButtonsOfType();
}

void CGrAttrPage::OnGrattrTypeArea() 
{
	// TODO: Add your control notification handler code here
   m_attrType=Area;
   CGrAttrPage::SetCheckButtonsOfType();	
}

void CGrAttrPage::OnGrattrTypeBar() 
{
	// TODO: Add your control notification handler code here
   m_attrType=Bar;
   CGrAttrPage::SetCheckButtonsOfType();
}

void CGrAttrPage::OnGrattrTypeColumn() 
{
	// TODO: Add your control notification handler code here
   m_attrType=Column;
	CGrAttrPage::SetCheckButtonsOfType();
}

void CGrAttrPage::OnGrattrTypePie() 
{
	// TODO: Add your control notification handler code here
   m_attrType=Pie;
	CGrAttrPage::SetCheckButtonsOfType();
}

void CGrAttrPage::OnGrattrDim2d() 
{
	// TODO: Add your control notification handler code here
   m_dimension=TwoDimension;
	CGrAttrPage::SetCheckButtonsOfDimension();
}

void CGrAttrPage::OnGrattrDim3d() 
{
	// TODO: Add your control notification handler code here
   m_dimension=ThreeDimension;
	CGrAttrPage::SetCheckButtonsOfDimension();
}

void CGrAttrPage::OnGrattrScaleXLinear() 
{
	// TODO: Add your control notification handler code here
   m_xScale=Linear;
   CGrAttrPage::SetCheckButtonsOfXScale();
}

void CGrAttrPage::OnGrattrScaleXLogarithmic() 
{
	// TODO: Add your control notification handler code here
	m_xScale=Logarithmic;
   CGrAttrPage::SetCheckButtonsOfXScale();
}

void CGrAttrPage::OnGrattrScaleXNormal() 
{
	// TODO: Add your control notification handler code here
	m_xScale=Normal;
   CGrAttrPage::SetCheckButtonsOfXScale();
}

void CGrAttrPage::OnGrattrScaleXSeries() 
{
	// TODO: Add your control notification handler code here
	m_xScale=Series;
   CGrAttrPage::SetCheckButtonsOfXScale();
}

void CGrAttrPage::OnGrattrScaleXWeibull() 
{
	// TODO: Add your control notification handler code here
	m_xScale=Weibull;
   CGrAttrPage::SetCheckButtonsOfXScale();
}

void CGrAttrPage::OnGrattrScaleYLinear() 
{
	// TODO: Add your control notification handler code here
	m_yScale=Linear;
   CGrAttrPage::SetCheckButtonsOfYScale();
}

void CGrAttrPage::OnGrattrScaleYLogarithmic() 
{
	// TODO: Add your control notification handler code here
	m_yScale=Logarithmic;
   CGrAttrPage::SetCheckButtonsOfYScale();
}

void CGrAttrPage::OnGrattrScaleYNormal() 
{
	// TODO: Add your control notification handler code here
	m_yScale=Normal;
   CGrAttrPage::SetCheckButtonsOfYScale();
}

void CGrAttrPage::OnGrattrScaleYWeibull() 
{
	// TODO: Add your control notification handler code here
	m_yScale=Weibull;
   CGrAttrPage::SetCheckButtonsOfYScale();
}

void CGrAttrPage::OnGrattrScaleZLinear() 
{
	// TODO: Add your control notification handler code here
	m_zScale=Normal;
   CGrAttrPage::SetCheckButtonsOfZScale();
}

void CGrAttrPage::OnGrattrScaleZLogarithmic() 
{
	// TODO: Add your control notification handler code here
	m_zScale=Logarithmic;
   CGrAttrPage::SetCheckButtonsOfZScale();
}

BOOL CGrAttrPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL bResult=CPropertyPage::OnKillActive();

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return bResult;

   char *pScript;
   int nScript;
   CString sPara;

   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   int nTotal,nIndex;

   switch (m_dimension) {
   case TwoDimension :   break;
   case ThreeDimension : break;
   }

   switch (m_attrType) {
   case Genetic : sPara=ppType[0];break;
   case GeneticPlus : sPara=ppType[1];break;
   case Moment :  sPara=ppType[2];break;
   case Flat3D :  sPara=ppType[3];break;
   case Area :    sPara=ppType[4];break;
   case Bar :     sPara=ppType[5];break;
   case Column :  sPara=ppType[6];break;
   case Pie :     sPara=ppType[7];break;
   }
   nTotal=sizeof(ppType)/sizeof(ppType[0]);
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      SEDelOptionParameter(
         pScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         ppType[nIndex],1,0);
   }
   bResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
      sPara,1,0);
   if (!bResult) goto R;

   switch (m_xScale) {
   case Linear :      sPara="xlin";    break;
   case Logarithmic : sPara="xlog";    break;
   case Series :      sPara="xseries"; break;
   case Normal :      sPara="xnormal"; break;
   case Weibull :     sPara="xweibull";break;
   }
   nTotal=sizeof(ppXScale)/sizeof(ppXScale[0]);
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      SEDelOptionParameter(
         pScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         ppXScale[nIndex],1,0);
   }
   bResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
      sPara,1,0);
   if (!bResult) goto R;

   switch (m_yScale) {
   case Linear :      sPara="ylin";    break;
   case Logarithmic : sPara="ylog";    break;
   case Normal :      sPara="ynormal"; break;
   case Weibull :     sPara="yweibull";break;
   }
   nTotal=sizeof(ppYScale)/sizeof(ppYScale[0]);
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      SEDelOptionParameter(
         pScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         ppYScale[nIndex],1,0);
   }
   bResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
      sPara,1,0);
   if (!bResult) goto R;

   switch (m_zScale) {
   case Linear :      sPara="zlin";    break;
   case Logarithmic : sPara="zlog";    break;
   }
   nTotal=sizeof(ppZScale)/sizeof(ppZScale[0]);
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      SEDelOptionParameter(
         pScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         ppZScale[nIndex],1,0);
   }
   bResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
      sPara,1,0);
   if (!bResult) goto R;

   SEDelOptionParameter( //20030309
      pScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
      m_bAttrPrevious ? "nbck":"back",1,0);
   sPara=m_bAttrPrevious ? "back":"nbck";
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
      sPara,1,0);

   Script=pScript;
R: delete pScript;
   if (!bResult)
      MessageBox("Internal error take place !",NULL,MB_ICONWARNING);
   return bResult;
}

BOOL CGrAttrPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return CPropertyPage::OnSetActive();

   int nIndex,nResult;
   int nTotal=sizeof(ppType)/sizeof(ppType[0]);
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      if (!nIndex) {
         m_attrType=Genetic;
      }
      nResult=SEGetOptionPosition(Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         ppType[nIndex],1,0);
      if (nResult>=0) {
         switch (nIndex) {
         case 0 : m_attrType=Genetic;break;
         case 1 : m_attrType=GeneticPlus;break;
         case 2 : m_attrType=Moment;break;
         case 3 : m_attrType=Flat3D;break;
         case 4 : m_attrType=Area;break;
         case 5 : m_attrType=Bar;break;
         case 6 : m_attrType=Column;break;
         case 7 : m_attrType=Pie;break;
         }
         break;
      }
   }
   nTotal=sizeof(ppXScale)/sizeof(ppXScale[0]);
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      if (!nIndex) {
         m_xScale=Linear;
      }
      nResult=SEGetOptionPosition(Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         ppXScale[nIndex],1,0);
      if (nResult>=0) {
         switch (nIndex) {
         case 0 : m_xScale=Linear;break;
         case 1 : m_yScale=Linear;break;
         case 2 : m_zScale=Linear;break;
         case 3 : m_xScale=Logarithmic;break;
         case 4 : m_yScale=Logarithmic;break;
         case 5 : m_zScale=Logarithmic;break;
         case 6 : m_xScale=Normal;break;
         case 7 : m_yScale=Normal;break;
         case 8 : m_xScale=Series;break;
         }
         break;
      }
   }
   nTotal=sizeof(ppXScale)/sizeof(ppXScale[0]);
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      if (!nIndex) {
         m_xScale=Linear;
      }
      nResult=SEGetOptionPosition(Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         ppXScale[nIndex],1,0);
      if (nResult>=0) {
         switch (nIndex) {
         case 0 : m_xScale=Linear;break;
         case 1 : m_xScale=Logarithmic;break;
         case 2 : m_xScale=Normal;break;
         case 3 : m_xScale=Series;break;
         }
         break;
      }
   }
   nTotal=sizeof(ppYScale)/sizeof(ppYScale[0]);
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      if (!nIndex) {
         m_yScale=Linear;
      }
      nResult=SEGetOptionPosition(Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         ppYScale[nIndex],1,0);
      if (nResult>=0) {
         switch (nIndex) {
         case 0 : m_yScale=Linear;break;
         case 1 : m_yScale=Logarithmic;break;
         case 2 : m_yScale=Normal;break;
         }
         break;
      }
   }
   nTotal=sizeof(ppZScale)/sizeof(ppZScale[0]);
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      if (!nIndex) {
         m_zScale=Linear;
      }
      nResult=SEGetOptionPosition(Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
         ppZScale[nIndex],1,0);
      if (nResult>=0) {
         switch (nIndex) {
         case 0 : m_zScale=Linear;break;
         case 1 : m_zScale=Logarithmic;break;
         }
         break;
      }
   }

   nResult=SEGetOptionPosition(Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
      "back",1,0);
   m_bAttrPrevious=nResult>=0 ? TRUE:FALSE;
   nResult=SEGetOptionPosition(Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_ATTR,1,
      "nbck",1,0);
   if (nResult>=0) m_bAttrPrevious=FALSE; //20030308

   CGrAttrPage::SetCheckButtonsOfType();
   CGrAttrPage::SetCheckButtonsOfDimension();
   CGrAttrPage::SetCheckButtonsOfXScale();
   CGrAttrPage::SetCheckButtonsOfYScale();
   CGrAttrPage::SetCheckButtonsOfZScale();

   if (m_bFirstSetActive) UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}
