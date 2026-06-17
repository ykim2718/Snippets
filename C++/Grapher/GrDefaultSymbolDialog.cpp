// GrDefaultSymbolDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrDefaultSymbolDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "GrPropertySheet.h"
#include "Token.h"
#include "geWindow.h"
#include "plotse.h"

static char *qLineStyleStrings[]={
   "solid",
   "longdashed",
   "shortdashed",
   "dashdotted",
   "dotted"
};
static char *qLineWidthStrings[]={
   "1","2","5","10","20"
};

#define PLOTSCRIPT_SLCT_TYPE       "type="
#define PLOTSCRIPT_SLCT_COPY       "nCopy="
#define PLOTSCRIPT_SLCT_SYMB_COLOR "symbol.color="
#define PLOTSCRIPT_SLCT_LINE_COLOR "line.color="
#define PLOTSCRIPT_SLCT_SOLID      "solid"
#define PLOTSCRIPT_SLCT_HOLLOW     "hollow"
#define PLOTSCRIPT_SLCT_SYMB_SIZE  "symbol.size="
#define PLOTSCRIPT_SLCT_LINE_ON    "line=on"
#define PLOTSCRIPT_SLCT_LINE_OFF   "line=off"
#define PLOTSCRIPT_SLCT_LINE_WIDTH "line.width="
#define PLOTSCRIPT_SLCT_LINE_STYLE "line.dash_list="
#define PLOTSCRIPT_SLCT_LGND_TEXT  "legend.txt="
#define PLOTSCRIPT_SLCT_LGND_SIZE  "legend.size="

const char *qqDefaultSymbols[]={
   "type=01 nCopy=%d symbol.color=blue line.color=blue solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=02 nCopy=%d symbol.color=magenta line.color=magenta solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=03 nCopy=%d symbol.color=SkyBlue line.color=SkyBlue solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=04 nCopy=%d symbol.color=aquamarine line.color=aquamarine solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=05 nCopy=%d symbol.color=GreenYellow line.color=GreenYellow solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=06 nCopy=%d symbol.color=khaki line.color=khaki solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=07 nCopy=%d symbol.color=salmon line.color=salmon solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=08 nCopy=%d symbol.color=pink line.color=pink solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=09 nCopy=%d symbol.color=violet line.color=violet solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=10 nCopy=%d symbol.color=purple line.color=purple solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=11 nCopy=%d symbol.color=red line.color=red solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=12 nCopy=%d symbol.color=plum line.color=plum solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=13 nCopy=%d symbol.color=maroon line.color=maroon solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=14 nCopy=%d symbol.color=coral line.color=coral solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=15 nCopy=%d symbol.color=tomato line.color=tomato solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=16 nCopy=%d symbol.color=navy line.color=navy solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=17 nCopy=%d symbol.color=bisque line.color=bisque solid symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=01 nCopy=%d symbol.color=blue line.color=blue hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=02 nCopy=%d symbol.color=magenta line.color=magenta hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=03 nCopy=%d symbol.color=SkyBlue line.color=SkyBlue hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=04 nCopy=%d symbol.color=aquamarine line.color=aquamarine hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=05 nCopy=%d symbol.color=GreenYellow line.color=GreenYellow hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=06 nCopy=%d symbol.color=khaki line.color=khaki hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=07 nCopy=%d symbol.color=salmon line.color=salmon hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=08 nCopy=%d symbol.color=pink line.color=pink hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=09 nCopy=%d symbol.color=violet line.color=violet hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=10 nCopy=%d symbol.color=purple line.color=purple hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=11 nCopy=%d symbol.color=red line.color=red hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=12 nCopy=%d symbol.color=plum line.color=plum hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=13 nCopy=%d symbol.color=maroon line.color=maroon hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=14 nCopy=%d symbol.color=coral line.color=coral hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=15 nCopy=%d symbol.color=tomato line.color=tomato hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=16 nCopy=%d symbol.color=navy line.color=navy hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5",
   "type=17 nCopy=%d symbol.color=bisque line.color=bisque hollow symbol.size=5"
   "        line=on line.width=2 line.dash_list=solid"
   "        legend.txt=\"%s\" legend.size=10 legend.symbolsize=5"
};

/////////////////////////////////////////////////////////////////////////////
// CGrDefaultSymbolDialog dialog


CGrDefaultSymbolDialog::CGrDefaultSymbolDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGrDefaultSymbolDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrDefaultSymbolDialog)
	m_bLineConnection = TRUE;
	m_nLegendSize = 2;
	m_sLegendText = _T("");
	m_nSymbSize = 2;
	m_bSymbSolid = TRUE;
	m_sLineStyle = _T("");
	m_sLineWidth = _T("");
	//}}AFX_DATA_INIT
   m_nDefaultSymbolIndex=0;
   m_nDefaultSymbolTotal=0;
   m_pApp=AfxGetApp();
}

void CGrDefaultSymbolDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrDefaultSymbolDialog)
	DDX_Control(pDX, ID_GRDEFAULTSYMBOL_SLIDER, m_Slider);
	DDX_Check(pDX, ID_GRDEFAULTSYMBOL_CB_LINECONNECTION, m_bLineConnection);
	DDX_Text(pDX, ID_GRDEFAULTSYMBOL_LEGEND_SIZE, m_nLegendSize);
	DDV_MinMaxUInt(pDX, m_nLegendSize, 1, 16);
	DDX_Text(pDX, ID_GRDEFAULTSYMBOL_LEGEND_TEXT, m_sLegendText);
	DDV_MaxChars(pDX, m_sLegendText, 32);
	DDX_Text(pDX, ID_GRDEFAULTSYMBOL_SIZE, m_nSymbSize);
	DDV_MinMaxUInt(pDX, m_nSymbSize, 1, 16);
	DDX_Check(pDX, ID_GRDEFAULTSYMBOL_SOLID, m_bSymbSolid);
	DDX_CBString(pDX, ID_GRDEFAULTSYMBOL_LINE_STYLE, m_sLineStyle);
	DDV_MaxChars(pDX, m_sLineStyle, 32);
	DDX_CBString(pDX, ID_GRDEFAULTSYMBOL_LINE_THICKNESS, m_sLineWidth);
	DDV_MaxChars(pDX, m_sLineWidth, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrDefaultSymbolDialog, CDialog)
	//{{AFX_MSG_MAP(CGrDefaultSymbolDialog)
	ON_BN_CLICKED(ID_GRDEFAULTSYMBOL_LOAD, OnGrdefaultsymbolLoad)
	ON_BN_CLICKED(ID_GRDEFAULTSYMBOL_SAVE, OnGrdefaultsymbolSave)
	ON_BN_CLICKED(ID_GRDEFAULTSYMBOL_ADD, OnGrdefaultsymbolAdd)
	ON_BN_CLICKED(ID_GRDEFAULTSYMBOL_DEL, OnGrdefaultsymbolDel)
	ON_BN_CLICKED(ID_GRDEFAULTSYMBOL_SOLID, OnGrdefaultsymbolSolid)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRDEFAULTSYMBOL_SIZE_SPIN, OnDeltaposGrdefaultsymbolSizeSpin)
	ON_NOTIFY(UDN_DELTAPOS, ID_GRDEFAULTSYMBOL_LEGEND_SIZE_SPIN, OnDeltaposGrdefaultsymbolLegendSizeSpin)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(ID_GRDEFAULTSYMBOL_RESET, OnGrdefaultsymbolDefault)
	ON_BN_CLICKED(ID_GRDEFAULTSYMBOL_PREV, OnGrdefaultsymbolPrev)
	ON_BN_CLICKED(ID_GRDEFAULTSYMBOL_Next, OnGRDEFAULTSYMBOLNext)
	//}}AFX_MSG_MAP
   ON_MESSAGE(WM_COLORBTNMESSAGE,OnMyMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrDefaultSymbolDialog message handlers

void CGrDefaultSymbolDialog::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

   if (wParam==WM_COLORBTNMESSAGE) {
      switch (lParam) {
      case ID_GRDEFAULTSYMBOL_COLOR :
         m_SymbTypeBtn.m_nSymbFillColor=m_SymbFillColorBtn.nCurrentColor;
         break;
      case ID_GRDEFAULTSYMBOL_LINE_COLOR :
         m_SymbTypeBtn.m_nSymbStrokeColor=m_SymbStrokeColorBtn.nCurrentColor;
         break;
      }
      m_SymbTypeBtn.Invalidate();
   }
}

void CGrDefaultSymbolDialog::SetComboBoxStringsOfLineWidth(int nID)
{
   CComboBox *cb=(CComboBox*)GetDlgItem(nID);
   int i,count=sizeof(qLineWidthStrings)/sizeof(qLineWidthStrings[0]);   
   for (i=0;i<count;i++) {
      cb->AddString(qLineWidthStrings[i]);
   }
   cb->SetCurSel(0);
}

void CGrDefaultSymbolDialog::SetComboBoxStringsOfLineStyle(int nID)
{
   CComboBox *cb=(CComboBox*)GetDlgItem(nID);
   int i,count=sizeof(qLineStyleStrings)/sizeof(qLineStyleStrings[0]);   
   for (i=0;i<count;i++) {
      cb->AddString(qLineStyleStrings[i]);
   }
   cb->SetCurSel(0);
}

BOOL CGrDefaultSymbolDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING,IDM_GR_PLOT_DEFAULTSYMBOL,"View script ...");
	}

	m_SymbFillColorBtn.SubclassDlgItem(ID_GRDEFAULTSYMBOL_COLOR,this);
   m_SymbStrokeColorBtn.SubclassDlgItem(ID_GRDEFAULTSYMBOL_LINE_COLOR,this);
   m_SymbTypeBtn.SubclassDlgItem(ID_GRDEFAULTSYMBOL_TYPE,this);

   SetComboBoxStringsOfLineStyle(ID_GRDEFAULTSYMBOL_LINE_STYLE);
   SetComboBoxStringsOfLineWidth(ID_GRDEFAULTSYMBOL_LINE_THICKNESS);
   
   CGrDefaultSymbolDialog::OnGrdefaultsymbolLoad();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrDefaultSymbolDialog::OnGrdefaultsymbolLoad() 
{
	// TODO: Add your control notification handler code here

   m_nDefaultSymbolTotal=0;
   CString sIndex,sReturn("Nothing");
   while (!sReturn.IsEmpty()) {
      sIndex.Format(RegKeyDefaultSymbolFormat,m_nDefaultSymbolTotal);
      sReturn=m_pApp->GetProfileString(RegKeyGrAttributes,sIndex);
      m_nDefaultSymbolTotal++;
   }
   m_nDefaultSymbolTotal--;

   if (m_nDefaultSymbolTotal<=m_nDefaultSymbolIndex)
      m_nDefaultSymbolIndex=0;
   m_Slider.SetRange(0,m_nDefaultSymbolTotal-1,TRUE);
   m_Slider.SetPos(m_nDefaultSymbolIndex);
   m_Slider.SetTicFreq(1);

   CGrDefaultSymbolDialog::UpdateDialogControl();
}

void CGrDefaultSymbolDialog::OnGrdefaultsymbolSave() 
{
	// TODO: Add your control notification handler code here

   CString sCurrent=CGrDefaultSymbolDialog::GetCurrentScript();
   CString sIndex;
   sIndex.Format(RegKeyDefaultSymbolFormat,m_nDefaultSymbolIndex);   
   m_pApp->WriteProfileString(RegKeyGrAttributes,sIndex,sCurrent);
}

void CGrDefaultSymbolDialog::OnGrdefaultsymbolAdd() 
{
	// TODO: Add your control notification handler code here

	CString sCurrent=CGrDefaultSymbolDialog::GetCurrentScript();
   CString sIndex;
   sIndex.Format(RegKeyDefaultSymbolFormat,m_nDefaultSymbolTotal);
   m_pApp->WriteProfileString(RegKeyGrAttributes,sIndex,sCurrent);
   m_nDefaultSymbolIndex=m_nDefaultSymbolTotal++;

   m_Slider.SetRange(0,m_nDefaultSymbolTotal-1,TRUE);
   m_Slider.SetPos(m_nDefaultSymbolIndex);

   CGrDefaultSymbolDialog::OnVScroll(0,0,0);
   CGrDefaultSymbolDialog::UpdateDialogControl();
}

#include <WINERROR.H>

void CGrDefaultSymbolDialog::OnGrdefaultsymbolDel() 
{
	// TODO: Add your control notification handler code here

   if (!m_nDefaultSymbolTotal) return;

   CString sIndex,sReturn;
   for (int nIndex=m_nDefaultSymbolIndex;nIndex<m_nDefaultSymbolTotal;nIndex++) {
      sIndex.Format(RegKeyDefaultSymbolFormat,nIndex+1);
      sReturn=m_pApp->GetProfileString(RegKeyGrAttributes,sIndex);
      sIndex.Format(RegKeyDefaultSymbolFormat,nIndex);
      m_pApp->WriteProfileString(RegKeyGrAttributes,sIndex,sReturn);
   }
   m_pApp->WriteProfileString(RegKeyGrAttributes,sIndex,0);

   m_nDefaultSymbolIndex--;
   m_nDefaultSymbolTotal--;

   m_Slider.SetRange(0,m_nDefaultSymbolTotal-1,TRUE);
   m_Slider.SetPos(m_nDefaultSymbolIndex);

   CGrDefaultSymbolDialog::OnVScroll(0,0,0);
   CGrDefaultSymbolDialog::UpdateDialogControl();
}

void CGrDefaultSymbolDialog::OnGrdefaultsymbolDefault() 
{
	// TODO: Add your control notification handler code here

   int nCount=sizeof(qqDefaultSymbols)/sizeof(qqDefaultSymbols[0]);
   CString sMessage;
   sMessage.Format(
      "%d default symbols are about to be saved to the system registry\n"
      "ignoring the previous.\n"
      "Proceed ?",nCount);
   int nResult=MessageBox(sMessage,NULL,MB_ICONQUESTION|MB_YESNO);
   if (nResult==IDNO) return;

   CString sIndex;
   for (int nIndex=0;nIndex<nCount;nIndex++) {
      sIndex.Format(RegKeyDefaultSymbolFormat,nIndex);
      m_pApp->WriteProfileString(
         RegKeyGrAttributes,sIndex,qqDefaultSymbols[nIndex]);
   }
   CString sReturn("Nothing");
   while (!sReturn.IsEmpty()) {
      sIndex.Format(RegKeyDefaultSymbolFormat,nIndex);
      sReturn=m_pApp->GetProfileString(RegKeyGrAttributes,sIndex);
      m_pApp->WriteProfileString(RegKeyGrAttributes,sIndex,"");
      nIndex++;
   }

   CGrDefaultSymbolDialog::OnGrdefaultsymbolLoad();
}

void CGrDefaultSymbolDialog::OnGrdefaultsymbolSolid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_SymbTypeBtn.m_bFillSymbol=m_bSymbSolid;
   m_SymbTypeBtn.m_bStrokeSymbol=TRUE;
   m_SymbTypeBtn.Invalidate();
}

void CGrDefaultSymbolDialog::OnDeltaposGrdefaultsymbolSizeSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
   switch (pNMUpDown->iDelta) {
   case -1 : m_nSymbSize++;break;
   case +1 : m_nSymbSize--;break;
   }
   if (m_nSymbSize<1) m_nSymbSize=1;
   if (m_nSymbSize>16) m_nSymbSize=16;
   UpdateData(FALSE);
   //
	*pResult = 0;
}

void CGrDefaultSymbolDialog::OnDeltaposGrdefaultsymbolLegendSizeSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
   switch (pNMUpDown->iDelta) {
   case -1 : m_nLegendSize++;break;
   case +1 : m_nLegendSize--;break;
   }
   if (m_nLegendSize<1) m_nLegendSize=1;
   if (m_nLegendSize>32) m_nLegendSize=32;
   UpdateData(FALSE);
	//
	*pResult = 0;
}

BOOL CGrDefaultSymbolDialog::GetParameterValue(
     CString &string,const char *parameter,CString &value)
{
   value=_T("");
   int i,j;
   if ((i=string.Find(parameter))>=0) {
      i+=strlen(parameter);
      j=string.Find(' ',i);
      value= (j==-1) ? string.Mid(i):string.Mid(i,j-i);
      //value.TrimLeft();
      //value.TrimRight();
      return TRUE;
   }
   return FALSE;
}

CString CGrDefaultSymbolDialog::GetCurrentScript()
{
   CGrDefaultSymbolDialog::UpdateMemberData();

   CString sIndex,sReturn;
   sIndex.Format(RegKeyDefaultSymbolFormat,m_nDefaultSymbolIndex);   
   sReturn=m_pApp->GetProfileString(RegKeyGrAttributes,sIndex);

   if (sReturn.IsEmpty()) sReturn=qqDefaultSymbols[0];

   CString sTemp;
   int nScript=sReturn.GetLength()*3;
   char *pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)sReturn);

   sTemp.Format("%s%d",PLOTSCRIPT_SLCT_TYPE,m_SymbTypeBtn.m_nSymbolIndex);
   SESetOptionParameter(pScript,nScript,sTemp,1,0);
   sTemp.Format("%s%d",PLOTSCRIPT_SLCT_SYMB_COLOR,m_SymbFillColorBtn.nCurrentColor);
   SESetOptionParameter(pScript,nScript,sTemp,1,0);
   sTemp.Format("%s%d",PLOTSCRIPT_SLCT_LINE_COLOR,m_SymbStrokeColorBtn.nCurrentColor);
   SESetOptionParameter(pScript,nScript,sTemp,1,0);
   SEDelOptionParameter(pScript,PLOTSCRIPT_SLCT_HOLLOW,1,0);
   SEDelOptionParameter(pScript,PLOTSCRIPT_SLCT_SOLID,1,0);
   SESetOptionParameter(pScript,nScript,
      m_bSymbSolid ? PLOTSCRIPT_SLCT_SOLID:PLOTSCRIPT_SLCT_HOLLOW,1,0);
   sTemp.Format("%s%d",PLOTSCRIPT_SLCT_SYMB_SIZE,m_nSymbSize);
   SESetOptionParameter(pScript,nScript,sTemp,1,0);
   SEDelOptionParameter(pScript,PLOTSCRIPT_SLCT_LINE_ON,1,0);
   SEDelOptionParameter(pScript,PLOTSCRIPT_SLCT_LINE_OFF,1,0);
   SESetOptionParameter(pScript,nScript,
      m_bLineConnection ? PLOTSCRIPT_SLCT_LINE_ON:PLOTSCRIPT_SLCT_LINE_OFF,1,0);
   sTemp.Format("%s%s",PLOTSCRIPT_SLCT_LINE_WIDTH,m_sLineWidth);
   SESetOptionParameter(pScript,nScript,sTemp,1,0);
   sTemp.Format("%s%s",PLOTSCRIPT_SLCT_LINE_STYLE,m_sLineStyle);
   SESetOptionParameter(pScript,nScript,sTemp,1,0);
   if (!m_sLegendText.IsEmpty()) {
      sTemp=m_sLegendText;
      if (sTemp[0]=='\"') sTemp.Delete(0);
      if (sTemp[sTemp.GetLength()-1]=='\"') sTemp.Delete(sTemp.GetLength()-1);
      sTemp.Format("%s\"%s\"",PLOTSCRIPT_SLCT_LGND_TEXT,sTemp);
      SESetOptionParameter(pScript,nScript,sTemp,1,0);
   }
   sTemp.Format("%s%d",PLOTSCRIPT_SLCT_LGND_SIZE,m_nLegendSize);
   SESetOptionParameter(pScript,nScript,sTemp,1,0);

   sReturn=pScript;
   delete pScript;

   return sReturn;
}

void CGrDefaultSymbolDialog::UpdateDialogControl() // script->member->control
{
   CString sIndex,sReturn;
   sIndex.Format(RegKeyDefaultSymbolFormat,m_nDefaultSymbolIndex);   
   sReturn=m_pApp->GetProfileString(RegKeyGrAttributes,sIndex);
   if (sReturn.IsEmpty()) {
      CString sText;
      GetWindowText(sText);
      int nLoc=sText.Find('-');
      if (nLoc>0) sText.Delete(nLoc,sText.GetLength()-nLoc);
      sText.TrimRight();
      sText+=" - Nothing";
      SetWindowText((LPCTSTR)sText);
      return;
   }

   CString sType,sColor,sSize,sDashList;
   int nSize,nResult;

   GetParameterValue(sReturn,PLOTSCRIPT_SLCT_TYPE,sType);
   m_SymbTypeBtn.m_nSymbolIndex=atoi(sType);

   GetParameterValue(sReturn,PLOTSCRIPT_SLCT_SYMB_COLOR,sColor);
   m_SymbFillColorBtn.nCurrentColor=isdigit(sColor[0]) ?
      atoi((LPCTSTR)sColor):
      GEColorByName(NULL,(LPCTSTR)sColor);
   m_SymbFillColorBtn.Invalidate();

   GetParameterValue(sReturn,PLOTSCRIPT_SLCT_LINE_COLOR,sColor);
   m_SymbStrokeColorBtn.nCurrentColor=isdigit(sColor[0]) ?
      atoi((LPCTSTR)sColor):
      GEColorByName(NULL,(LPCTSTR)sColor);
   m_SymbStrokeColorBtn.Invalidate();

   nResult=SEGetOptionPosition(sReturn,PLOTSCRIPT_SLCT_SOLID,1,0);
   m_bSymbSolid=nResult>0 ? TRUE:FALSE;

   GetParameterValue(sReturn,PLOTSCRIPT_SLCT_SYMB_SIZE,sSize);
   nSize=atoi((LPCTSTR)sSize);
   m_nSymbSize=nSize>0 ? nSize:5;

   m_bLineConnection=sReturn.Find(PLOTSCRIPT_SLCT_LINE_ON)==-1 ? FALSE:TRUE;

   GetParameterValue(sReturn,PLOTSCRIPT_SLCT_LINE_WIDTH,m_sLineWidth);

   GetParameterValue(sReturn,PLOTSCRIPT_SLCT_LINE_STYLE,m_sLineStyle);

   GetParameterValue(sReturn,PLOTSCRIPT_SLCT_LGND_TEXT,m_sLegendText);
   if (m_sLegendText[0]=='\"') {
      int nEnd=m_sLegendText.GetLength()-1;
      if (m_sLegendText[nEnd]=='\"') {
         m_sLegendText.Delete(nEnd);
         m_sLegendText.Delete(0);
         m_sLegendText.TrimLeft();
         m_sLegendText.TrimRight();
      }
   }
   GetParameterValue(sReturn,PLOTSCRIPT_SLCT_LGND_SIZE,sSize);
   nSize=atoi((LPCTSTR)sSize);
   m_nLegendSize=nSize>0 ? nSize:5;

   m_SymbTypeBtn.m_nSymbFillColor=m_SymbFillColorBtn.nCurrentColor;
   m_SymbTypeBtn.m_nSymbStrokeColor=m_SymbStrokeColorBtn.nCurrentColor;
   m_SymbTypeBtn.m_bFillSymbol=m_bSymbSolid;
   m_SymbTypeBtn.m_bStrokeSymbol=TRUE;
   m_SymbTypeBtn.Invalidate();

   UpdateData(FALSE);

   CString sText;
   GetWindowText(sText);
   int nLoc=sText.Find('-');
   if (nLoc>0) sText.Delete(nLoc,sText.GetLength()-nLoc);
   sText.TrimRight();
   CString sTemp;
   switch (m_nDefaultSymbolIndex%10) {
   case 0 : sTemp.Format(" - %dst in %d",m_nDefaultSymbolIndex+1,m_nDefaultSymbolTotal);break;
   case 1 : sTemp.Format(" - %dnd in %d",m_nDefaultSymbolIndex+1,m_nDefaultSymbolTotal);break;
   case 2 : sTemp.Format(" - %drd in %d",m_nDefaultSymbolIndex+1,m_nDefaultSymbolTotal);break;
   default: sTemp.Format(" - %dth in %d",m_nDefaultSymbolIndex+1,m_nDefaultSymbolTotal);break;
   }
   sText+=sTemp;
   SetWindowText((LPCTSTR)sText);
}

void CGrDefaultSymbolDialog::UpdateMemberData() // member<-control
{
   UpdateData(TRUE);
   m_nDefaultSymbolIndex;
   m_SymbTypeBtn.m_nSymbolIndex;
   CString sSymbFillColor=GEColorName(NULL,m_SymbFillColorBtn.nCurrentColor);
   CString sSymbLineColor=GEColorName(NULL,m_SymbStrokeColorBtn.nCurrentColor);
   m_bSymbSolid;
   m_nSymbSize;
   m_bLineConnection;
   m_sLineWidth;
   m_sLineStyle;
   m_sLegendText;
   m_nLegendSize;
}

void CGrDefaultSymbolDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
   //

   //CSliderCtrl *ctrl=(CSliderCtrl*)pScrollBar;
   CSliderCtrl *ctrl=(CSliderCtrl*)GetDlgItem(ID_GRDEFAULTSYMBOL_SLIDER);
   int nCurrentPos=ctrl->GetPos();
   if (m_nDefaultSymbolIndex==nCurrentPos) return;
   m_nDefaultSymbolIndex=nCurrentPos;

   CGrDefaultSymbolDialog::UpdateDialogControl();
}

void CGrDefaultSymbolDialog::OnGrdefaultsymbolPrev() 
{
	// TODO: Add your control notification handler code here

	m_Slider.SendMessage(WM_KEYDOWN,VK_UP,0);
}

void CGrDefaultSymbolDialog::OnGRDEFAULTSYMBOLNext() 
{
	// TODO: Add your control notification handler code here
	
   m_Slider.SendMessage(WM_KEYDOWN,VK_DOWN,0);
}
