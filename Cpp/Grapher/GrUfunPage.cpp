// GrUfunPage.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrUfunPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "plot.h"
#include "usrfunc.h"
#include "GrPropertySheet.h"

extern "C" {
extern const uFuncTableTag uDemoTag;
extern const uFuncTableTag uPolyCoeffsDrawingTag;
extern const uFuncTableTag uMatrixPrintTag;
extern const uFuncTableTag uMatrixHandlerTag;
extern const uFuncTableTag uMathParserTag;
extern const uFuncTableTag uMathParserExTag;
extern const char *DataPointReformer_Sample;
extern const char *DataPointReformer_Help;
extern const char *ColumnNormalizer_Sample;
extern const char *ColumnNormalizer_Help;
extern const char *ColumnGroupNormalizer_Sample;
extern const char *ColumnGroupNormalizer_Help;
extern const char *ColumnNoiseCleaner_Sample;
extern const char *ColumnNoiseCleaner_Help;
extern const char *IdealMosCapacitor_Sample;
extern const char *IdealMosCapacitor_Help;
extern const char *IdealMosCapacitorEx_Sample;
extern const char *IdealMosCapacitorEx_Help;
extern const char *JunctionDiodeRegressor_Sample;
extern const char *JunctionDiodeRegressor_Help;
extern const char *MaserjianModel_Sample;
extern const char *MaserjianModel_Help;
extern const uFuncTableTag uMosCapacitorRegressorTag;
extern const uFuncTableTag uMosDiodeRegressorTag;
extern const uFuncTableTag uNormConductanceTag;
extern const char *PolynomialFit_Sample;
extern const char *PolynomialFit_Help;
extern const char *SplitCV_Sample;
extern const char *SplitCV_Help;
extern const char *TwoFreqCapacitanceModel_Sample;
extern const char *TwoFreqCapacitanceModel_Help;
extern const char *MOSFETIdVg_Sample;
extern const char *MOSFETIdVg_Help;
};

static
struct {
   const char *qName;
   const char *qSample;
   const char *qHelp;
} FunctionTable[] = {
{uDemoTag.qName,uDemoTag.qSample,uDemoTag.qHelp},
{uPolyCoeffsDrawingTag.qName,uPolyCoeffsDrawingTag.qSample,uPolyCoeffsDrawingTag.qHelp},
{uMatrixPrintTag.qName,uMatrixPrintTag.qSample,uMatrixPrintTag.qHelp},
{uMatrixHandlerTag.qName,uMatrixHandlerTag.qSample,uMatrixHandlerTag.qHelp},
{uMathParserTag.qName,uMathParserTag.qSample,uMathParserTag.qHelp},
{uMathParserExTag.qName,uMathParserExTag.qSample,uMathParserExTag.qHelp},
{"DataPointReformer",DataPointReformer_Sample,DataPointReformer_Help},
{"ColumnNormalizer",ColumnNormalizer_Sample,ColumnNormalizer_Help},
{"ColumnGroupNormalizer",ColumnGroupNormalizer_Sample,ColumnGroupNormalizer_Help},
{"ColumnNoiseCleaner",ColumnNoiseCleaner_Sample,ColumnNoiseCleaner_Help},
{"IdealMosCapacitor",IdealMosCapacitor_Sample,IdealMosCapacitor_Help},
{"IdealMosCapacitorEx",IdealMosCapacitorEx_Sample,IdealMosCapacitorEx_Help},
{"JunctionDiodeRegressor(J-V)",JunctionDiodeRegressor_Sample,JunctionDiodeRegressor_Help},
{"MaserjianModel",MaserjianModel_Sample,MaserjianModel_Help},
{uMosCapacitorRegressorTag.qName,uMosCapacitorRegressorTag.qSample,uMosCapacitorRegressorTag.qHelp},
{uMosDiodeRegressorTag.qName,uMosDiodeRegressorTag.qSample,uMosDiodeRegressorTag.qHelp},
{uNormConductanceTag.qName,uNormConductanceTag.qSample,uNormConductanceTag.qHelp},
{"PolynomialFit",PolynomialFit_Sample,PolynomialFit_Help},
{"SplitCV",SplitCV_Sample,SplitCV_Help},
{"TwoFreqCapacitanceModel",TwoFreqCapacitanceModel_Sample,TwoFreqCapacitanceModel_Help},

{"MOSFETIdVg",MOSFETIdVg_Sample,MOSFETIdVg_Help},

{"GetInterpolatedValue",
 "type=GetInterpolatedValue\r\n"
 "option=0 argument=0.0 \r\n"
 "! option => interpolation method for x-y curve. \r\n"
 "!        0 : polymoial interplation \r\n"
 "! argument => <d> => x axis value to interpolate. ",
 ""},

{"NORMSDIST",
 "type=NORMSDIST\r\n"
 "nrl=1 nrh=201 ncl=1 nch=2 drl=1e-3 drh=1 dcl=0.1 dch=0.9",
 ""},

{"ShiftAndRatioMethod",
 "type=ShiftAndRatioMethod\r\n"
 "argument=\" bias=__,__,__ length=__,__,..,__ \"",
 ""}

};

/////////////////////////////////////////////////////////////////////////////
// CGrUfunPage property page

IMPLEMENT_DYNCREATE(CGrUfunPage, CPropertyPage)

CGrUfunPage::CGrUfunPage() : CPropertyPage(CGrUfunPage::IDD)
{
	//{{AFX_DATA_INIT(CGrUfunPage)
	m_sText = _T("");
	//}}AFX_DATA_INIT
}

CGrUfunPage::~CGrUfunPage()
{
}

void CGrUfunPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrUfunPage)
	DDX_Text(pDX, ID_GRUFUN_TEXT, m_sText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrUfunPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrUfunPage)
	ON_BN_CLICKED(ID_GRUFUN_HELP, OnGrufunHelp)
	ON_BN_CLICKED(ID_GRUFUN_CLEAR, OnGrufunClear)
	ON_BN_CLICKED(ID_GRUFUN_TRY, OnGrufunTry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrUfunPage message handlers

BOOL CGrUfunPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   LOGFONT LogFont;
   GetFont()->GetLogFont(&LogFont);
   m_MyFont.CreateFont(
      LogFont.lfHeight,0,0,0,
      FW_NORMAL,FALSE,FALSE,
      FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,0x40,
      DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE,"Courier New");
   GetDlgItem(ID_GRUFUN_TEXT)->SetFont(&m_MyFont);

   CComboBox* pBox=(CComboBox*)GetDlgItem(ID_GRUFUN_LIST);
   pBox->ResetContent();
   int nCount=sizeof(FunctionTable)/sizeof(FunctionTable[0]);
   for (int nIndex=0;nIndex<nCount;nIndex++) {
      pBox->AddString(FunctionTable[nIndex].qName);
   }
   pBox->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CGrUfunPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL bResult=CPropertyPage::OnKillActive();

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return bResult;

   int nIndex=SEGetOptionPosition(
      Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_UFUN,1,
      0);
   if (nIndex>0) {
      int nCount=SEGetOptionBlockLength(Script,nIndex);
      Script.Delete(nIndex,nCount);
   } else {
      nIndex=SEGetSafeOptionPosition(
         Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
         PLOTSCRIPT_UFUN,1,
         0);
   }

   if (!m_sText.IsEmpty()) { //20030224
      //m_sText.TrimLeft();
      m_sText.TrimRight();
      Script.Insert(nIndex,m_sText+PLOTSCRIPT_LINEEND);
      Script.Insert(nIndex," ");
      Script.Insert(nIndex,PLOTSCRIPT_UFUN);
   }

   return bResult;
}

BOOL CGrUfunPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return CPropertyPage::OnSetActive();

   int nIndex=SEGetOptionPosition(
      Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_UFUN,1,
      0);
   if (nIndex>0) {
      int nCount=SEGetOptionBlockLength(Script,nIndex);
      m_sText=Script.Mid(nIndex,nCount);
      if (!strncmp(m_sText,PLOTSCRIPT_UFUN,strlen(PLOTSCRIPT_UFUN))) {
         m_sText.Delete(0,strlen(PLOTSCRIPT_UFUN));
         m_sText.TrimLeft();
         m_sText.TrimRight();
      }
      // 20030430,Y.Kim
      nIndex=0;
      do {
         while (!isspace(m_sText[nIndex])) nIndex++;
         m_sText.Insert(nIndex,"\r\n");
      }  while ((nIndex=m_sText.Find("type=",nIndex))!=-1);
      // 20030224,Y.Kim
      while (m_sText.Replace("\n ","\n"));
      // 20030501,Y.Kim
      while (m_sText.Replace("\r\n\r\n","\r\n"));
   } else {
      m_sText.Empty();
   }

   if (m_bFirstSetActive) UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

void CGrUfunPage::OnGrufunTry() 
{
	// TODO: Add your control notification handler code here

   CComboBox *pBox=(CComboBox*)GetDlgItem(ID_GRUFUN_LIST);
   int nSelection=pBox->GetCurSel();
   
   UpdateData(TRUE); // 20030224

   int nCount=sizeof(FunctionTable)/sizeof(FunctionTable[0]);
   if (nSelection>=nCount) return;
   CString sSample=FunctionTable[nSelection].qSample;
   while (sSample.Replace(" \n"," \r\n")); //20030517
   while (sSample.Replace(" \r","\r")); //20030517
   sSample.TrimRight(); //20030517
   m_sText.TrimRight();
   if (!m_sText.IsEmpty()) m_sText+="\r\n\r\n";
   m_sText+=sSample;

   UpdateData(FALSE);

   //Y.Kim,20030216
   nCount=m_sText.GetLength();
   CEdit *pEdit=(CEdit*)GetDlgItem(ID_GRUFUN_TEXT);
   pEdit->SetSel(nCount,nCount);
}

void CGrUfunPage::OnGrufunClear() 
{
	// TODO: Add your control notification handler code here
	
   m_sText.Empty();
   UpdateData(FALSE);
}

void CGrUfunPage::OnGrufunHelp() 
{
	// TODO: Add your control notification handler code here

   CComboBox *pBox=(CComboBox*)GetDlgItem(ID_GRUFUN_LIST);
   int nSelection=pBox->GetCurSel();

   //20030517
   CString sCaption="Grapher User-Function Help : ";
   sCaption+=FunctionTable[nSelection].qName;
   CString sHelp=FunctionTable[nSelection].qHelp;
   //while (sHelp.Replace(" \n","\n")); 20030904
   sHelp.TrimRight();
   if (sHelp.IsEmpty()) {
      sHelp=
         "*[type=<s>] [option=<d>|<c>] [suboption|set=<i>] \n"
         "[nrl=<i>] [nrh=<i>] [ncl=<i>] [nch=<i>] \n"
         "[argument|model=<s>] \n"
         "[argument2|xy|xyz|xyt=(<f>,<f>)...(<f>,<f>)|(<f>,<f>,<f>)...(<f>,<f>,<f>)] \n"
         "[argument3=<s>] \n"
         "[argument4=<s>] \n"
         "[sweep|range=<f>,..,<f>] <---------- start,stop,step \n"
         "[rline=on|off]  <------------- line result \n"
         "[rtext=on|off] <-------------- text result \n"
         "[rline.def] <----------------- line gc attr \n"
         "[rtext.def] <----------------- text attr";
   }
   MessageBox(sHelp,sCaption,MB_ICONINFORMATION);
}