// GrTextPage.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrTextPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "number.h"
#include "plot.h"
#include "SmallFontAttrDialog.h"
#include "GrPropertySheet.h"
#include "Token.h"

/////////////////////////////////////////////////////////////////////////////
// CGrTextPage property page

IMPLEMENT_DYNCREATE(CGrTextPage, CPropertyPage)

CGrTextPage::CGrTextPage() : CPropertyPage(CGrTextPage::IDD)
{
	//{{AFX_DATA_INIT(CGrTextPage)
	m_sText01 = _T("");
	m_sText02 = _T("");
	m_sText03 = _T("");
	m_sText04 = _T("");
	//}}AFX_DATA_INIT
}

CGrTextPage::~CGrTextPage()
{
}

void CGrTextPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrTextPage)
	DDX_Control(pDX, ID_GRTEXT_LISTCTRL, m_ListCtrlEx);
	DDX_Text(pDX, ID_GRTEXT_TEXT01, m_sText01);
	DDV_MaxChars(pDX, m_sText01, 64);
	DDX_Text(pDX, ID_GRTEXT_TEXT02, m_sText02);
	DDV_MaxChars(pDX, m_sText02, 64);
	DDX_Text(pDX, ID_GRTEXT_TEXT03, m_sText03);
	DDV_MaxChars(pDX, m_sText03, 64);
	DDX_Text(pDX, ID_GRTEXT_TEXT04, m_sText04);
	DDV_MaxChars(pDX, m_sText04, 64);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGrTextPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrTextPage)
	ON_BN_CLICKED(ID_GRTEXT_TEXT01_BTN, OnGrtextText01Btn)
	ON_BN_CLICKED(ID_GRTEXT_TEXT02_BTN, OnGrtextText02Btn)
	ON_BN_CLICKED(ID_GRTEXT_TEXT03_BTN, OnGrtextText03Btn)
	ON_BN_CLICKED(ID_GRTEXT_TEXT04_BTN, OnGrtextText04Btn)
	ON_BN_CLICKED(ID_GRTEXT_LISTCTRL_ADD, OnGrtextListctrlAdd)
	ON_BN_CLICKED(ID_GRTEXT_LISTCTRL_DELETE, OnGrtextListctrlDelete)
	ON_BN_CLICKED(ID_GRTEXT_LISTCTRL_BTN, OnGrtextListctrlBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrTextPage message handlers

BOOL CGrTextPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   LCEX_COLUMHEADER Columns[]={"type",30,"x",40,"y",40,"text",400};
   int nColumn=sizeof(Columns)/sizeof(Columns[0]);
   m_ListCtrlEx.SetColumnHeaders(nColumn,Columns);
   m_ListCtrlEx.SetExtendedStyle(
      LVS_EX_FULLROWSELECT | 
      LVS_EX_ONECLICKACTIVATE | 
      LVS_EX_UNDERLINEHOT );
      //LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int GetTypeMatchedTextIndex(
   const char *pScript, int nPlotIndex, int nTextType, int nTextIndex)
{
   if (nPlotIndex<=0 || nTextIndex<=0) return 0;

   int nPos=SEGetOptionPosition(
      pScript,PLOTSCRIPT_PLOT,nPlotIndex,PLOTSCRIPT_TEXT,1,0);
   int nCount=SEGetOptionFrequencyInaRange(pScript,nPos,PLOTSCRIPT_TYPE);
   int nResult;
   for (int nIndex=1;nIndex<=nCount;nIndex++) {
      nResult=SEGetOptionValueInteger(
         -1,pScript,
         PLOTSCRIPT_PLOT,nPlotIndex,
         PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,
         0);
      if (nResult==nTextType) {
         nTextIndex--;
         if (!nTextIndex) return nIndex;
      }
   }
   return -(nCount+1);
}

void CGrTextPage::SetTextFontAttributeFromDialog(int nType,int nIndexOfTheSameType)
{
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   CSmallFontAttrDialog Dialog;
   int nIndex,nResult;
   char *pAddr;

   nIndex=GetTypeMatchedTextIndex(Script,pSheet->m_nPlotIndex,nType,nIndexOfTheSameType);
   if (nIndex<=0) return;

   nResult=SEGetOptionValueInteger (
      10,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,
      "t.height=",1,0);
   Dialog.m_nHeight=nResult;

   nResult=SEGetOptionValueInteger(
      (int)(Dialog.m_nHeight/2),Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,
      "t.width=",1,0);
   Dialog.m_nWidth=nResult;

   Dialog.m_sAlignment=pAddr=SEGetOptionValueString(
      "LB",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,
      "t.align=",1,0);
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
      PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,
      "t.angle=",1,0);
   Dialog.m_nAngle=nResult;

   //Dialog.m_ColorBtn.nCurrentColor=m_TitleColorBtn.nCurrentColor;
   nResult=SEGetOptionPosition(
      Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,
      "t.color=",1,0);
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

   CWnd *pWnd=GetFocus();
   CRect Rect;
   pWnd->GetWindowRect(&Rect);
   Dialog.SetWindowGravityPos(Rect.CenterPoint());
	int nResponse=Dialog.DoModal();
	if (nResponse==IDCANCEL) return;

   char *pScript;
   int nScript;
   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   CString sTextType,sPara;
   sTextType.Format("type=%d",nType);

   sPara.Format("t.height=%d",Dialog.m_nHeight);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_TEXT,1,sTextType,nIndex,
      sPara,1,0);

   sPara.Format("t.width=%d",Dialog.m_nWidth);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_TEXT,1,sTextType,nIndex,
      sPara,1,0);

   sPara.Format("t.align=%s",Dialog.m_sAlignment);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_TEXT,1,sTextType,nIndex,
      sPara,1,0);

   sPara.Format("t.angle=%d",Dialog.m_nAngle);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_TEXT,1,sTextType,nIndex,
      sPara,1,0);

   sPara.Format("t.color=%d",Dialog.m_ColorBtn.nCurrentColor);
   nResult=SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
      PLOTSCRIPT_TEXT,1,sTextType,nIndex,
      sPara,1,0);

   Script=pScript;
   delete pScript;

   return;
}

void CGrTextPage::OnGrtextText01Btn() 
{
	// TODO: Add your control notification handler code here
	
   UpdateData(TRUE);
   if (m_sText01.IsEmpty()) return;
   GetTextDataFromDialog();
   SetTextFontAttributeFromDialog(1);
}

void CGrTextPage::OnGrtextText02Btn() 
{
	// TODO: Add your control notification handler code here
	
   UpdateData(TRUE);
   if (m_sText02.IsEmpty()) return;
   GetTextDataFromDialog();
   SetTextFontAttributeFromDialog(2);
}

void CGrTextPage::OnGrtextText03Btn() 
{
	// TODO: Add your control notification handler code here
	
   UpdateData(TRUE);
   if (m_sText03.IsEmpty()) return;
   GetTextDataFromDialog();
   SetTextFontAttributeFromDialog(3);
}

void CGrTextPage::OnGrtextText04Btn() 
{
	// TODO: Add your control notification handler code here
	
   UpdateData(TRUE);
   if (m_sText04.IsEmpty()) return;
   GetTextDataFromDialog();
   SetTextFontAttributeFromDialog(4);
}

void CGrTextPage::SetTypeMatchedTextOfScript(
   const char *pScript, int nScript, int nPlotIndex,
   int nType, int nIndexOfTheSameType, const char *pPara)
{
   CString sTextType,sPara;
   sTextType.Format("type=%d",nType);
   sPara.Format("txt=\"%s\"",pPara);

   int nIndex=GetTypeMatchedTextIndex(pScript,nPlotIndex,nType,nIndexOfTheSameType);

   if (pPara) {
      if (nIndex>0) {
         SEDelOptionParameter(
            pScript,
            PLOTSCRIPT_PLOT,nPlotIndex,PLOTSCRIPT_TEXT,1,
            PLOTSCRIPT_TYPE,nIndex,sPara,1,
            0);
      } else {
         int nPos=SEGetOptionPosition(
            pScript,PLOTSCRIPT_PLOT,nPlotIndex,PLOTSCRIPT_TEXT,1,0);
         int nCount=SEGetOptionFrequencyInaRange(pScript,nPos,PLOTSCRIPT_TYPE);
         nIndex=nCount+1;
      }
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,nPlotIndex,PLOTSCRIPT_TEXT,1,
         sTextType,nIndex,sPara,1,
         0);
   } else if (nIndex>0) {
      SEDelOptionParameter(
         pScript,
         PLOTSCRIPT_PLOT,nPlotIndex,PLOTSCRIPT_TEXT,1,
         PLOTSCRIPT_TYPE,nIndex,sPara,1,
         0);
   }
}

void CGrTextPage::GetTextDataFromDialog()
{
   UpdateData(TRUE);

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   char *pScript;
   int nScript;
   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   SetTypeMatchedTextOfScript(pScript,nScript,pSheet->m_nPlotIndex,1,1,m_sText01);
   SetTypeMatchedTextOfScript(pScript,nScript,pSheet->m_nPlotIndex,2,1,m_sText02);
   SetTypeMatchedTextOfScript(pScript,nScript,pSheet->m_nPlotIndex,3,1,m_sText03);
   SetTypeMatchedTextOfScript(pScript,nScript,pSheet->m_nPlotIndex,4,1,m_sText04);

   Script=pScript;
   delete pScript;
}

BOOL CGrTextPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class

   BOOL bResult=CPropertyPage::OnKillActive();
   if (!bResult) return bResult;

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return bResult;
   
   char *pScript;
   int nScript;
   CString sPara;

   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   SetTypeMatchedTextOfScript(pScript,nScript,pSheet->m_nPlotIndex,1,1,m_sText01);
   SetTypeMatchedTextOfScript(pScript,nScript,pSheet->m_nPlotIndex,2,1,m_sText02);
   SetTypeMatchedTextOfScript(pScript,nScript,pSheet->m_nPlotIndex,3,1,m_sText03);
   SetTypeMatchedTextOfScript(pScript,nScript,pSheet->m_nPlotIndex,4,1,m_sText04);

   sPara="type=0";
   CString sRow,sX,sY,sText;
   int nCount=m_ListCtrlEx.GetRowCount(),nResult;
   for (int nIndex=0;nIndex<nCount;nIndex++) {
      sRow=m_ListCtrlEx.GetRow(nIndex);
      nResult=sRow.Find(m_ListCtrlEx.m_sRowStringDivider);
      sRow.Delete(0,nResult+1);
      nResult=sRow.Find(m_ListCtrlEx.m_sRowStringDivider);
      sX=sRow.Left(nResult++);
      sRow.Delete(0,nResult);
      nResult=sRow.Find(m_ListCtrlEx.m_sRowStringDivider);
      sY=sRow.Left(nResult++);
      sRow.Delete(0,nResult);
      sText=sRow;
      if (!isnumstr(sX) || !isnumstr(sY)) continue;
      if (sText.IsEmpty()) continue;
      nResult=GetTypeMatchedTextIndex(
         pScript,pSheet->m_nPlotIndex,0,nIndex+1);
      if (nResult<0) nResult=nResult*-1;
      sX.Insert(0,"x=");
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_TEXT,1,
         sPara,nResult,sX,1,0);
      sY.Insert(0,"y=");
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_TEXT,1,
         sPara,nResult,sY,1,0);
      sText.Insert(0,"txt=\"");
      sText+="\"";
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_TEXT,1,
         sPara,nResult,sText,1,0);
   }
   
   Script=pScript;
   delete pScript;

	return bResult;
}

BOOL CGrTextPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return CPropertyPage::OnSetActive();

   m_sText01.Empty();
   m_sText02.Empty();
   m_sText03.Empty();
   m_sText04.Empty();
   m_ListCtrlEx.DeleteAllItems();
   UpdateData(FALSE);

   char *pAddr;
   CString sPara,sRow;
   int nPos,nIndex,nCount,nResult;
   double dX,dY;

   nPos=SEGetOptionPosition(
      Script,PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_TEXT,1,0);
   nCount=SEGetOptionFrequencyInaRange(Script,nPos,PLOTSCRIPT_TYPE);
   for (nIndex=1;nIndex<=nCount;nIndex++) {
      nResult=SEGetOptionValueInteger(
         -1,Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
         PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,
         0);
      if (nResult<0) continue;
      pAddr=SEGetOptionValueString(
         NULL,Script,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
         PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,"txt=",1,
         0);
      strdelete(pAddr,0,1);
      strdelete(pAddr,strlen(pAddr)-1,1);
      switch (nResult) {
      case 1 : m_sText01=pAddr;break;
      case 2 : m_sText02=pAddr;break;
      case 3 : m_sText03=pAddr;break;
      case 4 : m_sText04=pAddr;break;
      case 0 :
         dX=SEGetOptionValueFloating(
            DBL_MAX,Script,
            PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
            PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,"x=",1,
            0);
         dY=SEGetOptionValueFloating(
            DBL_MAX,Script,
            PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
            PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,"y=",1,
            0);
         sRow="any\n";
         sRow+=dX==DBL_MAX ? "?":dtos(dX,"%g");
         sRow+="\n";
         sRow+=dY==DBL_MAX ? "?":dtos(dY,"%g");
         sRow+="\n";
         sRow+=pAddr;
         m_ListCtrlEx.AddRow(sRow);
         break;
      }
      freeEx(pAddr);
   }

   if (!m_ListCtrlEx.GetRowCount()) OnGrtextListctrlAdd();

   if (m_bFirstSetActive) UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

void CGrTextPage::OnGrtextListctrlAdd() 
{
	// TODO: Add your control notification handler code here

   const char *qDefault="new\n?\n?\n...";

   int nCount=m_ListCtrlEx.GetRowCount();
   if (nCount) {
      CString sReturn=m_ListCtrlEx.GetRow(nCount-1);
      int nPos=sReturn.Find('\n');
      sReturn.Delete(0,nPos+1);
      if (!isnumchr(sReturn[0])) return;
      nPos=sReturn.Find('\n');
      sReturn.Delete(0,nPos+1);
      if (!isnumchr(sReturn[0])) return;
   }
   m_ListCtrlEx.AddRow(qDefault);
}

void CGrTextPage::OnGrtextListctrlDelete() 
{
	// TODO: Add your control notification handler code here

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;
   int nScript=Script.GetLength()*2;
   char *pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   POSITION nPos=m_ListCtrlEx.GetFirstSelectedItemPosition();
   CToken Token(NULL,m_ListCtrlEx.m_sRowStringDivider);
   double dX,dY,dReturnX,dReturnY;
   CString sText,sReturn;
   int nTextIndex,nIndex,nCount;
   while (nPos) {
      Token=m_ListCtrlEx.GetRow(m_ListCtrlEx.GetNextSelectedItem(nPos));
      dX=atof(Token.GetTokenByIndex(1));
      dY=atof(Token.GetTokenByIndex(2));
      sText=Token.GetTokenByIndex(3);
      for (nTextIndex=nIndex=1;nIndex>0;nTextIndex++) {
         nIndex=GetTypeMatchedTextIndex(pScript,pSheet->m_nPlotIndex,0,nTextIndex);
         dReturnX=SEGetOptionValueFloating(
            DBL_MAX,pScript,
            PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
            PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,"x=",1,
            0);
         dReturnY=SEGetOptionValueFloating(
            DBL_MAX,pScript,
            PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
            PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,"y=",1,
            0);
         sReturn=SEGetOptionValueString(
            NULL,pScript,
            PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
            PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,"txt=",1,
            0);
         sReturn.Delete(0);
         sReturn.Delete(sReturn.GetLength()-1);
         if (dX==dReturnX &&
             dY==dReturnY &&
             !sText.Compare(sReturn)) {
            nIndex=SEGetOptionPosition(
               pScript,
               PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,
               PLOTSCRIPT_TEXT,1,PLOTSCRIPT_TYPE,nIndex,
               0);
            nCount=SEGetOptionBlockLength(pScript,nIndex);
            strdelete(pScript,nIndex,nCount);
            break;
         }
      }
   }

   Script=pScript;
   delete pScript;

   m_ListCtrlEx.DeleteRows();
}

void CGrTextPage::OnGrtextListctrlBtn() 
{
	// TODO: Add your control notification handler code here

   if (m_ListCtrlEx.GetSelectedCount()!=1) {
      CString sMessage;
      sMessage="Warning, select just one item in the ListCtrl of Placing-Anywhere\n"
         "before you modify the font attribute.";
      MessageBox(sMessage,"Warning ...",MB_ICONWARNING);
      return;
   }
   POSITION Pos=m_ListCtrlEx.GetFirstSelectedItemPosition();
   int nIndexOfTheSameType=m_ListCtrlEx.GetNextSelectedItem(Pos)+1;

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return;

   int nIndex=GetTypeMatchedTextIndex(Script,pSheet->m_nPlotIndex,0,nIndexOfTheSameType);
   if (nIndex<=0) {
      CToken Token(NULL,"\n");
      Token=m_ListCtrlEx.GetRow(m_ListCtrlEx.GetFirstSelectedRowIndex());

      char *pScript;
      int nScript;
      nScript=Script.GetLength()*2;
      pScript=new char[nScript];
      strcpy(pScript,(LPCTSTR)Script);

      CString sPara;
      sPara.Format("x=%.3e",atof(Token.GetTokenByIndex(1)));
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_TEXT,1,
         "type=0",-nIndex,sPara,1,
         0);
      sPara.Format("y=%.3e",atof(Token.GetTokenByIndex(2)));
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_TEXT,1,
         "type=0",-nIndex,sPara,1,
         0);
      sPara.Format("txt=\"%s\"",Token.GetTokenByIndex(3));
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_TEXT,1,
         "type=0",-nIndex,sPara,1,
         0);

      Script=pScript;
      delete pScript;
   }

   SetTextFontAttributeFromDialog(0,nIndexOfTheSameType);
}
