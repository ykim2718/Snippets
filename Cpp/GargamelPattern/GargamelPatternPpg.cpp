// GargamelPatternPpg.cpp : Implementation of the CGargamelPatternPropPage property page class.

#include "stdafx.h"
#include "GargamelPattern.h"
#include "GargamelPatternPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGargamelPatternPropPage, COlePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

extern CGargamelPatternPropPage* g_pGargamelPattern; // shik96,2001.0131, I am crazy !

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGargamelPatternPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CGargamelPatternPropPage)
	ON_BN_CLICKED(ID_PATTERN_ADD, OnPatternAdd)
	ON_BN_CLICKED(ID_PATTERN_ADD_WIZARD, OnPatternAddWizard)
	ON_BN_CLICKED(ID_PATTERN_INS, OnPatternIns)
	ON_BN_CLICKED(ID_PATTERN_DEL, OnPatternDel)
	ON_BN_CLICKED(ID_PATTERN_CLEAR, OnPatternClear)
	ON_BN_CLICKED(ID_PATTERN_MOVEUP, OnPatternMoveup)
	ON_BN_CLICKED(ID_PATTERN_MOVEDOWN, OnPatternMovedown)
	ON_BN_CLICKED(ID_PATTERN_ALIAS_CHANGE, OnPatternAliasChange)
	ON_BN_CLICKED(ID_PATTERN_SUPERSEDING, OnPatternSuperseding)
	ON_BN_CLICKED(ID_PATTERN_SCRIPT_READ_ATTACH, OnPatternScriptReadAttach)
	ON_BN_CLICKED(ID_PATTERN_ALIAS_AUTO_TB, OnPatternAliasAutoTb)
	ON_BN_CLICKED(ID_PATTERN_ALIAS_AUTO_TRY, OnPatternAliasAutoTry)
	ON_CBN_SELCHANGE(ID_PATTERN_ALIAS_METHOD, OnSelchangePatternAliasMethod)
	ON_BN_CLICKED(ID_PATTERN_FORMAT_HELP, OnPatternFormatHelp)
	ON_WM_SETFOCUS()
	ON_NOTIFY(NM_DBLCLK, ID_PATTERN_LISTCTRL, OnDblclkPatternListctrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGargamelPatternPropPage, "GARGAMELPATTERN.GargamelPatternPropPage.1",
	0x3340693b, 0xf75f, 0x11d4, 0x9e, 0x85, 0, 0, 0xe8, 0xc3, 0x6, 0x4a)


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternPropPage::CGargamelPatternPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGargamelPatternPropPage

BOOL CGargamelPatternPropPage::CGargamelPatternPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GARGAMELPATTERN_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternPropPage::CGargamelPatternPropPage - Constructor

CGargamelPatternPropPage::CGargamelPatternPropPage() :
	COlePropertyPage(IDD, IDS_GARGAMELPATTERN_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CGargamelPatternPropPage)
	m_sPatternText = _T("");
	m_sPatternAlias = _T("");
	m_sEquation = _T("");
	m_bAliasAuto = FALSE;
	m_sFormat = _T("");
	m_nAliasFrom = 0;
	m_nAliasTo = 0;
	m_sCutHighNo = _T("");
	m_sCutLowNo = _T("");
	m_nGrabFirstNo = 1;
	m_nGrabLastNo = 1;
	//}}AFX_DATA_INIT

   m_WizardModeless=NULL;
   m_sEquation = _T("z");
   m_sFindWhat.Empty();
   m_sReplaceWith.Empty();

   CWinApp* pApp=AfxGetApp();
   m_sLastDirectory=pApp->GetProfileString(RegKeySettings,RegKeyLastDirectoryAtPattern);
   int nCount=pApp->GetProfileInt(RegKeySettings,RegKeyExecCount,0);
   pApp->WriteProfileInt(RegKeySettings,RegKeyExecCount,++nCount);

   g_pGargamelPattern=this;
}

CGargamelPatternPropPage::~CGargamelPatternPropPage() //shik96
{
   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileString(
      RegKeySettings,RegKeyLastDirectoryAtPattern,m_sLastDirectory);
}

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternPropPage::DoDataExchange - Moves data between page and properties

void CGargamelPatternPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGargamelPatternPropPage)
	DDX_Control(pDX, ID_PATTERN_ATTRIBUTE, m_Attribute);
	DDX_Control(pDX, ID_PATTERN_ALIAS_METHOD, m_AliasAutoMethod);
	DDX_Control(pDX, ID_PATTERN_LISTCTRL, m_ListCtrl);
	DDX_Text(pDX, ID_PATTERN_TEXT, m_sPatternText);
	DDV_MaxChars(pDX, m_sPatternText, 128);
	DDX_Text(pDX, ID_PATTERN_ALIAS, m_sPatternAlias);
	DDV_MaxChars(pDX, m_sPatternAlias, 68);
	DDX_Text(pDX, ID_PATTERN_EQUATION, m_sEquation);
	DDV_MaxChars(pDX, m_sEquation, 68);
	DDX_Check(pDX, ID_PATTERN_ALIAS_AUTO_TB, m_bAliasAuto);
	DDX_CBString(pDX, ID_PATTERN_FORMAT, m_sFormat);
	DDV_MaxChars(pDX, m_sFormat, 12);
	DDX_Text(pDX, ID_PATTERN_ALIAS_NO_FROM, m_nAliasFrom);
	DDX_Text(pDX, ID_PATTERN_ALIAS_NO_TO, m_nAliasTo);
	DDX_Text(pDX, ID_PATTERN_CUTHIGH, m_sCutHighNo);
	DDV_MaxChars(pDX, m_sCutHighNo, 12);
	DDX_Text(pDX, ID_PATTERN_CUTLOW, m_sCutLowNo);
	DDV_MaxChars(pDX, m_sCutLowNo, 12);
	DDX_Text(pDX, ID_PATTERN_GRAB_FIRST_NO, m_nGrabFirstNo);
	DDV_MinMaxInt(pDX, m_nGrabFirstNo, 0, 99);
	DDX_Text(pDX, ID_PATTERN_GRAB_LAST_NO, m_nGrabLastNo);
	DDV_MinMaxInt(pDX, m_nGrabLastNo, 0, 99);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternPropPage message handlers

BOOL CGargamelPatternPropPage::OnInitDialog() 
{
	COlePropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   LCEX_COLUMHEADER Columns[]={
      "Pattern",200,
      "Alias",100,
      "1stNo",30,
      "LastNo",30,
      "Format",60,
      "Equation",120,
      "LC",40,
      "UC",40
   };
   int nColumn=sizeof(Columns)/sizeof(Columns[0]);
   m_ListCtrl.SetColumnHeaders(nColumn,Columns);
   m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

   int nCount,nIndex;

   nCount=sizeof(qPatternAttributeString)/sizeof(qPatternAttributeString[0]);   
   for (nIndex=0;nIndex<nCount;nIndex++)
      m_Attribute.AddString((LPCTSTR)qPatternAttributeString[nIndex]);
   m_Attribute.SetCurSel(PATTERN_ATTRIBUTE_NONE);
      
   ((CButton*)GetDlgItem(ID_PATTERN_ALIAS_AUTO_TB))->SetCheck(TRUE);

   nCount=sizeof(qAliasMethodString)/sizeof(qAliasMethodString[0]);   
   for (nIndex=0;nIndex<nCount;nIndex++)
      m_AliasAutoMethod.AddString((LPCTSTR)qAliasMethodString[nIndex]);
   m_AliasAutoMethod.SetCurSel(ALIAS_METHOD_PATTERN);

   CComboBox *pBox=(CComboBox*)GetDlgItem(ID_FORMAT_HELP);
   nCount=sizeof(qDataFormatString)/sizeof(qDataFormatString[0]);   
   for (nIndex=0;nIndex<nCount;nIndex++)
      pBox->AddString((LPCTSTR)qDataFormatString[nIndex]);
   pBox->SetCurSel(3);
   
   OnPatternAliasAutoTb();

   SetEnableDisableButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGargamelPatternPropPage::OnPatternAdd() 
{
	// TODO: Add your control notification handler code here

	CString String=CGargamelPatternPropPage::GetStringToBeAdded();
   if (String.IsEmpty()) return;
   m_ListCtrl.AddRow((LPCTSTR)String);
   SetEnableDisableButtons();
}

void CGargamelPatternPropPage::OnPatternAddWizard() 
{
	// TODO: Add your control notification handler code here

   if (m_WizardModeless == NULL) {
		m_WizardModeless = new CGargamelPatternWizard();
      m_WizardModeless->Create();
      m_WizardModeless->SetParentCWnd(this);
   } else
		m_WizardModeless->SetActiveWindow();
   m_WizardModeless->ShowWindow(SW_SHOW);
   SetEnableDisableButtons();
}

void CGargamelPatternPropPage::OnPatternIns() 
{
	// TODO: Add your control notification handler code here

   CString String=CGargamelPatternPropPage::GetStringToBeAdded();
   if (String.IsEmpty()) return;
   m_ListCtrl.InsertRow((LPCTSTR)String);
}

void CGargamelPatternPropPage::OnPatternDel() 
{
	// TODO: Add your control notification handler code here

	m_ListCtrl.DeleteRows();
   SetEnableDisableButtons();
}

void CGargamelPatternPropPage::OnPatternClear() 
{
	// TODO: Add your control notification handler code here

   m_ListCtrl.Clear();
   SetEnableDisableButtons();
}

void CGargamelPatternPropPage::OnPatternMoveup() 
{
	// TODO: Add your control notification handler code here

	POSITION nPos=m_ListCtrl.GetFirstSelectedItemPosition();
   if (!nPos) return;
   int nItem=m_ListCtrl.GetNextSelectedItem(nPos);
   if (!nItem) return;
   m_ListCtrl.MoveRow(nItem,nItem-1);
}

void CGargamelPatternPropPage::OnPatternMovedown() 
{
	// TODO: Add your control notification handler code here

	POSITION nPos=m_ListCtrl.GetFirstSelectedItemPosition();
   if (!nPos) return;
   int nItem=m_ListCtrl.GetNextSelectedItem(nPos);
   if (nItem>=(m_ListCtrl.GetItemCount()-1)) return;
   m_ListCtrl.MoveRow(nItem,nItem+1);
}

void CGargamelPatternPropPage::OnPatternFormatHelp() 
{
	// TODO: Add your control notification handler code here

   AfxMessageBox(
      "[Format Specification] \n"
      "%s = string \n"
      "%.0f = decimal integer (%d) : 1\n"
      "%.4f = floating point number format named f format : 1.2345 \n"
      "%.2e = floating point number format named e format : 1.23e45 \n"
      "%.2z = intelligent f format : 1.23p (=1.23e-12), 1.23M (=1.23e6)",
      MB_ICONINFORMATION);
}

void CGargamelPatternPropPage::OnPatternAliasChange() 
{
	// TODO: Add your control notification handler code here

	int nCount=m_ListCtrl.GetItemCount();
   if (!nCount) return;
   CString sItem;
   const char cSingleQuotation='\'';
   while (nCount--) {
      sItem=m_ListCtrl.GetItemText(nCount,1);
      switch (sItem[0]) { 
      case cSingleQuotation :
         sItem.Delete(0);
         sItem.Delete(sItem.GetLength()-1);
         break;
      default :
         sItem.Insert(0,cSingleQuotation);
         sItem.Insert(sItem.GetLength(),cSingleQuotation);
         break;
      }
      m_ListCtrl.SetItemText(nCount,1,(LPCTSTR)sItem);
   }
}

void CGargamelPatternPropPage::OnPatternSuperseding() 
{
	// TODO: Add your control notification handler code here

	CGargamelPatternSuperseding Dialog(this,m_sFindWhat,m_sReplaceWith);
   int nResult=Dialog.DoModal();
   if (nResult==IDCANCEL) return;
   if (Dialog.m_sFindWhat.IsEmpty()) return;
   int nCount=m_ListCtrl.GetItemCount();
   if (!nCount) return;
   CString sItem;
   while (nCount--) {
      if (Dialog.m_bFindWhatInPattern) {
         sItem=m_ListCtrl.GetItemText(nCount,0);
         sItem.Replace((LPCTSTR)Dialog.m_sFindWhat,(LPCTSTR)Dialog.m_sReplaceWith);
         m_ListCtrl.SetItemText(nCount,0,(LPCTSTR)sItem);
      }
      if (Dialog.m_bFindWhatInAlias) {
         sItem=m_ListCtrl.GetItemText(nCount,1);
         sItem.Replace((LPCTSTR)Dialog.m_sFindWhat,(LPCTSTR)Dialog.m_sReplaceWith);
         m_ListCtrl.SetItemText(nCount,1,(LPCTSTR)sItem);
      }
      if (Dialog.m_bFindWhatIn1stNo) {
         sItem=m_ListCtrl.GetItemText(nCount,2);
         sItem.Replace((LPCTSTR)Dialog.m_sFindWhat,(LPCTSTR)Dialog.m_sReplaceWith);
         m_ListCtrl.SetItemText(nCount,2,(LPCTSTR)sItem);
      }
      if (Dialog.m_bFindWhatInLastNo) {
         sItem=m_ListCtrl.GetItemText(nCount,3);
         sItem.Replace((LPCTSTR)Dialog.m_sFindWhat,(LPCTSTR)Dialog.m_sReplaceWith);
         m_ListCtrl.SetItemText(nCount,3,(LPCTSTR)sItem);
      }
      if (Dialog.m_bFindWhatInFormat) {
         sItem=m_ListCtrl.GetItemText(nCount,4);
         sItem.Replace((LPCTSTR)Dialog.m_sFindWhat,(LPCTSTR)Dialog.m_sReplaceWith);
         m_ListCtrl.SetItemText(nCount,4,(LPCTSTR)sItem);
      }
      if (Dialog.m_bFindWhatInEquation) {
         sItem=m_ListCtrl.GetItemText(nCount,5);
         sItem.Replace((LPCTSTR)Dialog.m_sFindWhat,(LPCTSTR)Dialog.m_sReplaceWith);
         m_ListCtrl.SetItemText(nCount,5,(LPCTSTR)sItem);
      }
      if (Dialog.m_bFindWhatInLC) {
         sItem=m_ListCtrl.GetItemText(nCount,6);
         sItem.Replace((LPCTSTR)Dialog.m_sFindWhat,(LPCTSTR)Dialog.m_sReplaceWith);
         m_ListCtrl.SetItemText(nCount,6,(LPCTSTR)sItem);
      }
      if (Dialog.m_bFindWhatInUC) {
         sItem=m_ListCtrl.GetItemText(nCount,7);
         sItem.Replace((LPCTSTR)Dialog.m_sFindWhat,(LPCTSTR)Dialog.m_sReplaceWith);
         m_ListCtrl.SetItemText(nCount,7,(LPCTSTR)sItem);
      }
   }
   m_sFindWhat=Dialog.m_sFindWhat;
   m_sReplaceWith=Dialog.m_sReplaceWith;
}

void CGargamelPatternPropPage::OnPatternScriptReadAttach() 
{
	// TODO: Add your control notification handler code here

	CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "Gargamel Input Files (*.in)|*.in|All Files (*.*)|*.*||");
   fDialog.m_ofn.lpstrInitialDir=(LPCTSTR)m_sLastDirectory;
   if (fDialog.DoModal()==IDCANCEL) return;
   CString sFile=fDialog.GetPathName();
   if (sFile.IsEmpty()) return;
   CFile hFile(sFile,CFile::modeRead);
   int length=hFile.GetLength();
   char *pStream=new char[length*sizeof(TCHAR)];
   hFile.ReadHuge(pStream,length);
   hFile.Close();

   HRESULT hResult=NO_ERROR;
   IAnyfind* pAnyfind;
   hResult=::CoCreateInstance(
      IID_ANYFINDCLASS,NULL,CLSCTX_INPROC_SERVER,
      IID_IANYFIND,(void**)&pAnyfind);
   if (FAILED(hResult)) {
      switch (hResult) {
      case REGDB_E_CLASSNOTREG :
         AfxMessageBox(
            "shik96@samsung.co.kr \n\n"
            "Watch out ! (hResult=REGDB_E_CLASSNOTREG) \n\n"
            "A specified class is not registered in the registration \n"
            "database. Also can indicate that the type of server you \n"
            "requested in the CLSCTX enumeration is not registered or \n"
            "the values for the server types in the registry are corrupt.",
            MB_ICONSTOP
            );
         break;
      case CLASS_E_NOAGGREGATION :
         AfxMessageBox(
            "shik96@samsung.co.kr \n\n"
            "Watch out ! (hResult=CLASS_E_NOAGGREGATION) \n\n"
            "This class cannot be created as part of an aggregate. ",
            MB_ICONSTOP
            );
         break;
      }
      return;
   }
   //:)

   char *sDumpFileName,*lfsPattern,*lfsSplit;
   int nSearchType,nColumnarMatrixType,bNumericAlias,nPostProcessType;
   int nResult=pAnyfind->_AFGetParametersFromScript(
      pStream,
      &sDumpFileName,
      &nSearchType,&nColumnarMatrixType,&bNumericAlias,
      &nPostProcessType,
      &lfsPattern,&lfsSplit);
   delete pStream;
   if (!nResult) {
      MessageBox("Error, script file is invalid.",NULL,MB_OK|MB_ICONSTOP);
      return;
   }
   CString Stream=lfsPattern;
   pAnyfind->_AFReleaseString(sDumpFileName);
   pAnyfind->_AFReleaseString(lfsPattern);
   pAnyfind->_AFReleaseString(lfsSplit);

   Stream.TrimLeft();
   Stream.TrimRight();
   SetScriptToDialog(Stream,TRUE);

   if (!sFile.IsEmpty()) {
      int nPos=sFile.ReverseFind('\\');
      if (nPos!=-1) {
         sFile.Delete(nPos,sFile.GetLength()-nPos);
         m_sLastDirectory=sFile;
      }
   }

   SetEnableDisableButtons();
}

void CGargamelPatternPropPage::OnPatternAliasAutoTb() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
   GetDlgItem(ID_PATTERN_ALIAS)->EnableWindow(!m_bAliasAuto);
   GetDlgItem(ID_PATTERN_ALIAS_METHOD)->EnableWindow(m_bAliasAuto);
   GetDlgItem(ID_PATTERN_ALIAS_NO_FROM)->EnableWindow(m_bAliasAuto);
   GetDlgItem(ID_PATTERN_ALIAS_NO_TO)->EnableWindow(m_bAliasAuto);
   GetDlgItem(ID_PATTERN_ALIAS_AUTO_TRY)->EnableWindow(m_bAliasAuto);
   if (m_bAliasAuto)
      CGargamelPatternPropPage::OnSelchangePatternAliasMethod();
}

void CGargamelPatternPropPage::OnPatternAliasAutoTry() 
{
	// TODO: Add your control notification handler code here

   if (!m_bAliasAuto) return;
   GetDlgItem(ID_PATTERN_ALIAS)->SetWindowText(NULL);
   UpdateData(TRUE);
   m_sPatternAlias=GetAliasString(
      m_sPatternText,m_AliasAutoMethod.GetCurSel(),m_nAliasFrom,m_nAliasTo);
   UpdateData(FALSE);	
}

void CGargamelPatternPropPage::OnSelchangePatternAliasMethod() 
{
	// TODO: Add your control notification handler code here

	switch (m_AliasAutoMethod.GetCurSel()) {
   case ALIAS_METHOD_TOKEN :
      GetDlgItem(ID_PATTERN_ALIAS_NO_FROM)->EnableWindow(TRUE);
      GetDlgItem(ID_PATTERN_ALIAS_NO_TO)->EnableWindow(FALSE);
      break;
   case ALIAS_METHOD_OFFSET :
      GetDlgItem(ID_PATTERN_ALIAS_NO_FROM)->EnableWindow(TRUE);
      GetDlgItem(ID_PATTERN_ALIAS_NO_TO)->EnableWindow(TRUE);
      break;
   case ALIAS_METHOD_PATTERN :
      GetDlgItem(ID_PATTERN_ALIAS_NO_FROM)->EnableWindow(FALSE);
      GetDlgItem(ID_PATTERN_ALIAS_NO_TO)->EnableWindow(FALSE);
      break;
   }
}

CString CGargamelPatternPropPage::GetAliasString(CString String, int nMethod, int nFrom, int nTo)
{
   CString sAlias("null");
   String.TrimLeft();
   String.TrimRight();
   if (String.IsEmpty()) return sAlias;
   switch (nMethod) {
   case ALIAS_METHOD_TOKEN :
      {
      CToken Token(String," ");
      sAlias.Empty();
      /* 2001.0224
      for (int nIndex=nFrom;nIndex<=nTo;nIndex++) {
         sAlias+=Token.GetTokenByIndex(nIndex);
         sAlias+=" ";
      }
      */
      sAlias+=Token.GetTokenByIndex(nFrom);
      sAlias.TrimRight();
      }
      break;
   case ALIAS_METHOD_OFFSET :
      if (nFrom>nTo) SWAP(nFrom,nTo);
      sAlias=String.Mid(nFrom,nTo-nFrom+1);
      break;
   case ALIAS_METHOD_PATTERN :
      sAlias=StringCompact(String);
      break;
   }
   sAlias.TrimLeft();
   sAlias.TrimRight();
   return sAlias;
}

CString CGargamelPatternPropPage::GetStringToBeAdded()
{
   UpdateData(TRUE);
   // m_sPatternText
   if (m_sPatternText.IsEmpty()) return _T("");
   m_sPatternText.TrimLeft();
   m_sPatternText.TrimRight();
   // m_sPatternAlias
   if (m_bAliasAuto) {
      switch (m_AliasAutoMethod.GetCurSel()) {
      case ALIAS_METHOD_TOKEN :
         m_nAliasTo=m_nAliasFrom;
         break;
      case ALIAS_METHOD_OFFSET :
         if (m_nAliasFrom>m_nAliasTo) {
            int nTmp=m_nAliasFrom;
            m_nAliasFrom=m_nAliasTo;
            m_nAliasTo=nTmp;
         }
         break;
      case ALIAS_METHOD_PATTERN :
         break;
      }
      m_sPatternAlias=GetAliasString(
         m_sPatternText,m_AliasAutoMethod.GetCurSel(),m_nAliasFrom,m_nAliasTo);
   } else if (m_sPatternAlias.IsEmpty())
      m_sPatternAlias="null";
   m_sPatternAlias.TrimLeft();
   m_sPatternAlias.TrimRight();
   //m_sPatternAlias.Replace(' ','_'); 2001.0209
   // m_nGrabFirstNo,m_nGrabLastNo
   if (m_nGrabFirstNo>m_nGrabLastNo) {
      int tmp=m_nGrabFirstNo;
      m_nGrabFirstNo=m_nGrabLastNo;
      m_nGrabLastNo=tmp;
   }
   switch (m_Attribute.GetCurSel()) {
   default :
   case PATTERN_ATTRIBUTE_NONE :
      break;
   case PATTERN_ATTRIBUTE_TRACKING :
      m_nGrabFirstNo=0;m_nGrabLastNo=1;
      break;
   case PATTERN_ATTRIBUTE_CALCULATING :
      m_nGrabFirstNo=m_nGrabLastNo=0;
      break;
   }
   // m_sFormat
   if (m_sFormat.IsEmpty()) m_sFormat="%s";
   m_sFormat.Replace(" ","");
   // m_sEquation
   if (m_sEquation.IsEmpty()) m_sEquation="z";
   m_sEquation.Replace(" ","");
   if (m_sEquation.Find("=")==-1) {
      m_sEquation.Insert(0,"z=");
   }
   // m_sCutLowNo,m_sCutHighNo
   if (m_sCutLowNo.IsEmpty()) m_sCutLowNo="0";
   if (m_sCutHighNo.IsEmpty()) m_sCutHighNo="0";
   //
   CString rString;
   rString.Format("%s\n%s\n%d\n%d\n%s\n%s\n%s\n%s",
      m_sPatternText,m_sPatternAlias,m_nGrabFirstNo,m_nGrabLastNo,m_sFormat,m_sEquation,
      m_sCutLowNo,m_sCutHighNo);
   return rString;
}

void CGargamelPatternPropPage::SetScriptToDialog(const CString &Stream, BOOL bAttachment)
{
   if (Stream.IsEmpty()) {
      m_ListCtrl.Clear();
      return;
   }
   if (!bAttachment) m_ListCtrl.Clear();

   CString String,sPattern,sAlias,sRight;
   int nPos;
   const char *qDelimiters=" \t\n\f\r";
   CToken Token(Stream,"\n"),Token2(NULL,qDelimiters);
   while (Token.IsNext()) {
      String=Token.GetNextToken();
      nPos=String.ReverseFind('\"');
      if (nPos==-1) return;
      sPattern=String.Left(++nPos);
      sPattern.Delete(0);                     // Opening Double Quotation Mark 
      sPattern.Delete(sPattern.GetLength()-1); // Closing Double Quotation Mark
      sRight=String.Mid(nPos);
      sRight.TrimLeft();
      sRight.TrimRight();
      sAlias=sRight;
      sAlias.MakeReverse();
      for (int nCount=1;nCount<=6;nCount++) {
         nPos=sAlias.FindOneOf(qDelimiters);
         sAlias.Delete(0,nPos);
         sAlias.TrimLeft();
      }
      sAlias.MakeReverse();
      sRight.Delete(0,sAlias.GetLength());
      //sRight.Replace(sAlias,"");
      sRight.TrimLeft();
      Token2=sRight;
      sRight=_T("");
      while (Token2.IsNext()) {
         sRight+="\n"+Token2.GetNextToken();
      }
      String=sPattern+"\n"+sAlias+sRight;
      m_ListCtrl.AddRow((LPCTSTR)String);
   }

   SetEnableDisableButtons(); //2001.0409
}

void CGargamelPatternPropPage::SetRemotely(CString aString)
{
   UpdateData(TRUE);
   m_sPatternText=aString;
   UpdateData(FALSE);
   OnPatternAdd();
}

CString CGargamelPatternPropPage::GetScriptFromDialog()
{
   if (m_WizardModeless) m_WizardModeless->ShowWindow(SW_HIDE);
   UpdateData(TRUE);
   int nTotal=m_ListCtrl.GetRowCount();
   if (!nTotal) return _T("");

   CString sReturn(_T(""));   

   for (int i=0;i<nTotal;i++) {
      CString sLine=m_ListCtrl.GetRow(i);
      CToken Token(sLine,"\n");
      CString sPattern,sAlias,sFirstNo,sLastNo,sFormat,sEquation,
              sLowerCut,sUpperCut;
      sPattern=Token.GetTokenByIndex(GARGAMEL_INDEXOF_PATTERN);
      sAlias=Token.GetTokenByIndex(GARGAMEL_INDEXOF_ALIAS);
      sFirstNo=Token.GetTokenByIndex(GARGAMEL_INDEXOF_FIRSTNO);
      sLastNo=Token.GetTokenByIndex(GARGAMEL_INDEXOF_LASTNO);
      sFormat=Token.GetTokenByIndex(GARGAMEL_INDEXOF_FORMAT);
      sEquation=Token.GetTokenByIndex(GARGAMEL_INDEXOF_EQUATION);
      sLowerCut=Token.GetTokenByIndex(GARGAMEL_INDEXOF_LOWERCUT);
      sUpperCut=Token.GetTokenByIndex(GARGAMEL_INDEXOF_UPPERCUT);
      //
      if (sAlias.Find('\"')>=0) {
         sLine.Format(
            "Warning, double quotation mark is not permitted in the alias !"
            "\n\nalias=%s",
            (LPCTSTR)sAlias);
         MessageBox((LPCTSTR)sLine,NULL,MB_ICONWARNING);
         return sReturn;
      }
      //sAlias.Replace(" ","_"); 2001.0209
      if (sFormat.Find("%s")<0) {
         if (atof(sLowerCut)>atof(sUpperCut)) {
            sLine.Format(
               "Warning, LC > UC under numerical searching condition at sLine %d !"
               "\n\nlc(LowerCut)=%s \nuc(UpperCut)=%s",
               i+1,(LPCTSTR)sLowerCut,(LPCTSTR)sUpperCut);
            MessageBox((LPCTSTR)sLine,NULL,MB_ICONWARNING);
            return sReturn;
         }
      }
      //
      if (sPattern[0]=='\"'
         &&sPattern[sPattern.GetLength()-1]=='\"') {
         sPattern.SetAt(0,' ');
         sPattern.SetAt(sPattern.GetLength()-1,' ');
         sPattern.TrimLeft();
         sPattern.TrimRight();
      }
      sLine.Format(
         GARGAMEL_PATTERN_SAVE_FORMAT,
         sPattern,sAlias,sFirstNo,sLastNo,sFormat,sEquation,sLowerCut,sUpperCut);
      sReturn+=sLine;
      sReturn+=GARGAMEL_SCRIPT_LINE_END;
   }

   sReturn.TrimRight();
   return sReturn;
}

CString CGargamelPatternPropPage::StringCompact(const char *qString)
{
   CString sReturn(qString);   
   sReturn.TrimLeft();
   sReturn.TrimRight();
   if (sReturn.IsEmpty()) return sReturn;
   CString sReplace;
   int nCount=sReturn.GetLength()-2;
   while (nCount--)
      sReplace.Insert(0," ");
   while (sReplace.GetLength()>1) {
      sReturn.Replace(sReplace," ");
      sReplace.Delete(0);
   }
   return sReturn;
}

void CGargamelPatternPropPage::SetEnableDisableButtons()
{
   int bEnable=m_ListCtrl.GetItemCount();
   GetDlgItem(ID_PATTERN_INS)->EnableWindow(bEnable);
   GetDlgItem(ID_PATTERN_DEL)->EnableWindow(bEnable);
   GetDlgItem(ID_PATTERN_CLEAR)->EnableWindow(bEnable);
   GetDlgItem(ID_PATTERN_MOVEUP)->EnableWindow(bEnable);
   GetDlgItem(ID_PATTERN_MOVEDOWN)->EnableWindow(bEnable);
   GetDlgItem(ID_PATTERN_ALIAS_CHANGE)->EnableWindow(bEnable);
   GetDlgItem(ID_PATTERN_SUPERSEDING)->EnableWindow(bEnable);
}

void CGargamelPatternPropPage::OnSetFocus(CWnd* pOldWnd) 
{
	COlePropertyPage::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here

	SetEnableDisableButtons(); // not work. why ??
}

void CGargamelPatternPropPage::OnDblclkPatternListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

   POSITION nPos=m_ListCtrl.GetFirstSelectedItemPosition();
   if (!nPos) return;
   int nRow=m_ListCtrl.GetNextSelectedItem(nPos);
	CString sReturn=m_ListCtrl.GetRow(nRow);
   AfxMessageBox(sReturn,MB_OK,0);

	*pResult = 0;
}
