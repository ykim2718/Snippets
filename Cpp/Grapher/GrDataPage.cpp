// GrDataPage.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrDataPage.h"
#include "GrPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Y.Kim

#include "FileDialogEx.h"
#include "Token.h"
#include "tools.h"
#include "CreateProcessWithRedirectedIO2.h" //20030423

/////////////////////////////////////////////////////////////////////////////
// CGrDataPage property page

IMPLEMENT_DYNCREATE(CGrDataPage, CPropertyPage)

CGrDataPage::CGrDataPage() : CPropertyPage(CGrDataPage::IDD)
{
	//{{AFX_DATA_INIT(CGrDataPage)
	m_bExchangeRowColumn = FALSE;
	m_sFromDataName = _T("");
	m_sFromScriptOption = _T("");
	m_sFromScriptPattern = _T("");
	m_sFromScriptSplit = _T("");
	m_bSortByXColumn = FALSE;
	m_bReuseFilesOnADisk = FALSE;
	m_sGrxyFile = _T("");
	m_sDataBlockIndex = _T("*");
	m_sGrFolder = _T("");
	//}}AFX_DATA_INIT
   m_nMatrixSourceType=MATRIX_FILE;
}

CGrDataPage::~CGrDataPage()
{
}

void CGrDataPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrDataPage)
	DDX_Check(pDX, ID_GRDATA_EXCHANGEROWCOLUMN, m_bExchangeRowColumn);
	DDX_CBString(pDX, ID_GRDATA_NAME, m_sFromDataName);
	DDX_Text(pDX, ID_GRDATA_FROMSCRIPT_OPTION, m_sFromScriptOption);
	DDX_Text(pDX, ID_GRDATA_FROMSCRIPT_PATTERN, m_sFromScriptPattern);
	DDX_Text(pDX, ID_GRDATA_FROMSCRIPT_SPLIT, m_sFromScriptSplit);
	DDX_Check(pDX, ID_GRDATA_SORTBYXCOLUMN, m_bSortByXColumn);
	DDX_Check(pDX, ID_GRDATA_REUSEFILEONADISK, m_bReuseFilesOnADisk);
	DDX_Text(pDX, ID_GRDATA_GRXYFILE, m_sGrxyFile);
	DDX_Text(pDX, ID_GRDATA_FROMFILE_BLOCKINDEX, m_sDataBlockIndex);
	DDX_Text(pDX, ID_GRDATA_GRFOLDER, m_sGrFolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrDataPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGrDataPage)
	ON_BN_CLICKED(ID_GRDATA_FROMFILE, OnGrdataFromFile)
	ON_BN_CLICKED(ID_GRDATA_FROMUSERFUNCTION, OnGrdataFromUserFunction)
	ON_BN_CLICKED(ID_GRDATA_FROMPREVIOUSMATRIX, OnGrdataFromPreviousMatrix)
	ON_BN_CLICKED(ID_GRDATA_FROMPREVIOUSCLONEMATRIX, OnGrdataFromPreviousCloneMatrix)
	ON_BN_CLICKED(ID_GRDATA_FROMSCRIPT, OnGrdataFromScript)
	ON_BN_CLICKED(ID_GRDATA_FILE_BROWSER, OnGrdataFromFileFileBrowser)
	ON_BN_CLICKED(ID_GRDATA_FROMSCRIPT_PATTERN_BROWSER, OnGrdataFromScriptPatternBrowser)
	ON_BN_CLICKED(ID_GRDATA_FROMSCRIPT_SPLIT_BROWSER, OnGrdataFromScriptSplitBrowser)
	ON_BN_CLICKED(ID_GRDATA_GRXYFILE_BROWSER, OnGrdataGrxyFileBrowser)
	ON_BN_CLICKED(ID_GRDATA_FILE_VIEWER, OnGrdataFromfileFileViewer)
	ON_BN_CLICKED(ID_GRDATA_FILE_DBIVIEWER, OnGrdataFileGetdbi)
	ON_BN_CLICKED(ID_GRDATA_FILE_APPLYALL, OnGrdataFileApplyall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrDataPage message handlers

BOOL CGrDataPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

   CGrDataPage::HandleAChangeOfRadioButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrDataPage::HandleAChangeOfRadioButtons()
{
   ((CButton*)GetDlgItem(ID_GRDATA_FROMFILE))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRDATA_FROMUSERFUNCTION))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRDATA_FROMPREVIOUSMATRIX))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRDATA_FROMPREVIOUSCLONEMATRIX))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRDATA_FROMSCRIPT))->SetCheck(0);
   GetDlgItem(ID_GRDATA_NAME)->EnableWindow(0);
   GetDlgItem(ID_GRDATA_FILE_BROWSER)->EnableWindow(0);
   GetDlgItem(ID_GRDATA_FILE_VIEWER)->EnableWindow(0);
   GetDlgItem(ID_GRDATA_FROMSCRIPT_PATTERN)->EnableWindow(0);
   GetDlgItem(ID_GRDATA_FROMSCRIPT_PATTERN_BROWSER)->EnableWindow(0);
   GetDlgItem(ID_GRDATA_FROMSCRIPT_SPLIT)->EnableWindow(0);
   GetDlgItem(ID_GRDATA_FROMSCRIPT_SPLIT_BROWSER)->EnableWindow(0);
   GetDlgItem(ID_GRDATA_FROMSCRIPT_OPTION)->EnableWindow(0);
   int nIDDlgItem;
   switch(m_nMatrixSourceType) {
   case MATRIX_FILE :
   case MATRIX_BYUSERFUNCTION :
   case MATRIX_PREV :
   case MATRIX_PREVCLONE :
      GetDlgItem(ID_GRDATA_NAME)->EnableWindow(1);
      GetDlgItem(ID_GRDATA_FILE_BROWSER)->EnableWindow(1);
      GetDlgItem(ID_GRDATA_FILE_VIEWER)->EnableWindow(1);
      switch(m_nMatrixSourceType) {
      case MATRIX_FILE : nIDDlgItem=ID_GRDATA_FROMFILE;break;
      case MATRIX_BYUSERFUNCTION : nIDDlgItem=ID_GRDATA_FROMUSERFUNCTION;break;
      case MATRIX_PREV : nIDDlgItem=ID_GRDATA_FROMPREVIOUSMATRIX;break;
      case MATRIX_PREVCLONE : nIDDlgItem=ID_GRDATA_FROMPREVIOUSCLONEMATRIX;break;
      }
      ((CButton*)GetDlgItem(nIDDlgItem))->SetCheck(1);
      break;
   case MATRIX_BYSCRIPT :
      ((CButton*)GetDlgItem(ID_GRDATA_FROMSCRIPT))->SetCheck(1);
      GetDlgItem(ID_GRDATA_FROMSCRIPT_PATTERN)->EnableWindow(1);
      GetDlgItem(ID_GRDATA_FROMSCRIPT_PATTERN_BROWSER)->EnableWindow(1);
      GetDlgItem(ID_GRDATA_FROMSCRIPT_SPLIT)->EnableWindow(1);
      GetDlgItem(ID_GRDATA_FROMSCRIPT_SPLIT_BROWSER)->EnableWindow(1);
      GetDlgItem(ID_GRDATA_FROMSCRIPT_OPTION)->EnableWindow(1);
      break;
   }
}

void CGrDataPage::OnGrdataFromFile() 
{
	// TODO: Add your control notification handler code here

	m_nMatrixSourceType=MATRIX_FILE;
   CGrDataPage::HandleAChangeOfRadioButtons();
}

void CGrDataPage::OnGrdataFromUserFunction() 
{
	// TODO: Add your control notification handler code here

	m_nMatrixSourceType=MATRIX_BYUSERFUNCTION;
   CGrDataPage::HandleAChangeOfRadioButtons();
}

void CGrDataPage::OnGrdataFromPreviousMatrix() 
{
	// TODO: Add your control notification handler code here

	m_nMatrixSourceType=MATRIX_PREV;
   CGrDataPage::HandleAChangeOfRadioButtons();
}

void CGrDataPage::OnGrdataFromPreviousCloneMatrix() 
{
	// TODO: Add your control notification handler code here

	m_nMatrixSourceType=MATRIX_PREVCLONE;
   CGrDataPage::HandleAChangeOfRadioButtons();
}

void CGrDataPage::OnGrdataFromScript() 
{
	// TODO: Add your control notification handler code here

	m_nMatrixSourceType=MATRIX_BYSCRIPT;
   CGrDataPage::HandleAChangeOfRadioButtons();
}

void CGrDataPage::OnGrdataFromFileFileBrowser() 
{
	// TODO: Add your control notification handler code here

   UpdateData(TRUE);

   char qBuffer[1024]; //20030309
   GetCurrentDirectory(sizeof(qBuffer),qBuffer); //20030309
   char *pFullPath=yGetFolderFromFullPath(
      m_sFromDataName,m_sFromDataName.GetLength()); //20030308
   char qFilter[]="Output files (*.out)|*.out|"
                  "Data files (*.dat)|*.dat|"
                  "Text files (*.txt)|*.txt|"
                  "All Files (*.*)|*.*||";
   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      qFilter,NULL);
   fDialog.m_ofn.lpstrInitialDir=pFullPath;
   int nResult=fDialog.DoModal();
   freeEx(pFullPath);
   SetCurrentDirectory(qBuffer); //20030309

   if (nResult==IDCANCEL) return;
   m_sFromDataName=fDialog.GetPathName();

   //Y.Kim,20030216
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString sGrFolder=pSheet->GetFolderFromFilePath(pSheet->m_sGrFile);
   CString sFileFolder=pSheet->GetFolderFromFilePath(m_sFromDataName);
   /* 20030220
   int nGrFolder=sGrFolder.GetLength();
   int nFileFolder=sFileFolder.GetLength();
   int nMinLength=nGrFolder>nFileFolder ? nFileFolder:nGrFolder;
   if (nGrFolder>nFileFolder)
      sGrFolder.Delete(nMinLength,nGrFolder-nMinLength);
   if (nFileFolder>nGrFolder)
      sFileFolder.Delete(nMinLength,nFileFolder-nMinLength);
   if (!sGrFolder.CompareNoCase(sFileFolder))
      m_sFromDataName.Delete(0,nMinLength);
   */
   // 20030220 in str.c
   char *pFolder=yGetRelativePath(sGrFolder,sFileFolder);
   m_sFromDataName=pFolder+fDialog.GetFileName();
   freeEx(pFolder);

   UpdateData(FALSE);
}

void CGrDataPage::OnGrdataFromScriptPatternBrowser() 
{
	// TODO: Add your control notification handler code here

   char qFilter[]="Pattern In-Files (*.in)|*.in|All Files (*.*)|*.*||";
   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      qFilter,NULL);
   fDialog.m_ofn.lpstrInitialDir="";
   int nResponse=fDialog.DoModal();
	if (nResponse!=IDOK) return;
   m_sFromScriptPattern=fDialog.GetPathName();
   
   //Y.Kim,20030220
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString sGrFolder=pSheet->GetFolderFromFilePath(pSheet->m_sGrFile);
   CString sFileFolder=pSheet->GetFolderFromFilePath(m_sFromScriptPattern);
   // 20030220 in str.c
   char *pFolder=yGetRelativePath(sGrFolder,sFileFolder);
   m_sFromScriptPattern=pFolder+fDialog.GetFileName();
   freeEx(pFolder);

   UpdateData(FALSE);
}

void CGrDataPage::OnGrdataFromScriptSplitBrowser() 
{
	// TODO: Add your control notification handler code here
	
   char qFilter[]="Split In-Files (*.in)|*.in|All Files (*.*)|*.*||";
   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      qFilter,NULL);
   fDialog.m_ofn.lpstrInitialDir="";
   int nResponse=fDialog.DoModal();
	if (nResponse!=IDOK) return;
   m_sFromScriptSplit=fDialog.GetPathName();
   UpdateData(FALSE);
}

void CGrDataPage::OnGrdataGrxyFileBrowser() 
{
	// TODO: Add your control notification handler code here
	
   char qFilter[]="Grxy Files (*.grxy)|*.grxy|All Files (*.*)|*.*||";
   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      qFilter,NULL);
   fDialog.m_ofn.lpstrInitialDir="";
   int nResponse=fDialog.DoModal();
	if (nResponse!=IDOK) return;
   m_sGrxyFile=fDialog.GetPathName();
   UpdateData(FALSE);
}

BOOL CGrDataPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL bResult=CPropertyPage::OnKillActive();
   if (!bResult) return bResult;
   
   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return bResult;

   char *pScript,*pAddr;
   int nScript;
   CString sPara,sTypePara;

   nScript=Script.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,(LPCTSTR)Script);

   switch (m_nMatrixSourceType) { //20030320
   case MATRIX_FILE :sTypePara="type=file";break;
   case MATRIX_PREV :sTypePara="type=prev";break;
   case MATRIX_PREVCLONE :sTypePara="type=clone";break;
   case MATRIX_BYUSERFUNCTION :sTypePara="type=user";break;
   case MATRIX_BYSCRIPT :sTypePara="type=script";break;
   }
   switch (m_nMatrixSourceType) {
   case MATRIX_FILE :
   case MATRIX_PREV :
   case MATRIX_PREVCLONE :
   case MATRIX_BYUSERFUNCTION :
      sPara.Format("file=%s",m_sFromDataName);
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_DATA,1,
         sTypePara,1,sPara,1,
         0);
      break;
   case MATRIX_BYSCRIPT :
      m_sFromScriptPattern.TrimLeft();
      m_sFromScriptPattern.TrimRight();
      m_sFromScriptSplit.TrimLeft();
      m_sFromScriptSplit.TrimRight();
      m_sFromScriptOption.TrimLeft();
      m_sFromScriptOption.TrimRight();
      sPara.Format("\"%s|%s|%s\"",
         m_sFromScriptPattern,m_sFromScriptSplit,m_sFromScriptOption);
      for (int nIndex=1;;nIndex++) {
         pAddr=(char*)SEGetOptionValueString(
            NULL,pScript,
            PLOTSCRIPT_GLOB,1,
            PLOTSCRIPT_EXEC,1,"file=",nIndex,
            0);
         if (pAddr) {
            CToken Token(pAddr,"|\"");
            myFree(pAddr);
            m_sFromScriptPattern=Token.GetTokenByIndex(0);
            m_sFromScriptSplit=Token.GetTokenByIndex(1);
            m_sFromScriptOption=Token.GetTokenByIndex(2);
            m_sFromScriptPattern.TrimLeft();
            m_sFromScriptPattern.TrimRight();
            m_sFromScriptSplit.TrimLeft();
            m_sFromScriptSplit.TrimRight();
            m_sFromScriptOption.TrimLeft();
            m_sFromScriptOption.TrimRight();
            CString sTarget;
            sTarget.Format("\"%s|%s|%s\"",
               m_sFromScriptPattern,m_sFromScriptSplit,m_sFromScriptOption);
            if (!sPara.CompareNoCase(sTarget)) {
               sPara.Format("file=%02d",nIndex-1);
               SESetOptionParameter(
                  pScript,nScript,
                  PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_DATA,1,
                  sTypePara,1,sPara,1,
                  0);
               break;
            }
         } else {
            sPara.Insert(0,"file=");
            SESetOptionParameter(
               pScript,nScript,
               PLOTSCRIPT_GLOB,1,
               PLOTSCRIPT_EXEC,1,sPara,nIndex,
               0);
            sPara.Format("file=%02d",nIndex-1);
            SESetOptionParameter(
               pScript,nScript,
               PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_DATA,1,
               sTypePara,1,sPara,1,
               0);
            break;
         }
      }
      break;
   }

   m_sGrxyFile.TrimLeft();
   m_sGrxyFile.TrimRight();
   sPara.Format("xyfile=\"%s\"",m_sGrxyFile);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_DATA,1,
      sTypePara,1,sPara,1,
      0);

   //20030311
   sPara.Format("block=%s",m_sDataBlockIndex);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_DATA,1,
      sTypePara,1,sPara,1,
      0);

   sPara.Format("bReuseIfExist=%d",m_bReuseFilesOnADisk?1:0);
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_EXEC,1,sPara,1,
      0);

   switch (m_bExchangeRowColumn) {
   case TRUE : break;
   case FALSE : break;
   }

   switch (m_bSortByXColumn) {
   case TRUE : break;
   case FALSE : break;
   }

   Script=pScript;
   delete pScript;

   return bResult;
}

BOOL CGrDataPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

   CGrPropertySheet *pSheet=(CGrPropertySheet*)GetParentOwner();
   CString &Script=pSheet->m_sGrScript;
   if (Script.IsEmpty()) return CPropertyPage::OnSetActive();

   char *pAddr;

   pAddr=SEGetOptionValueString(
      "file",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_DATA,1,
      PLOTSCRIPT_TYPE,1,
      0);
   if (pAddr) {
      switch (tolower(*pAddr)) { //[type=file|prev|clone|user|script]
      default  :
      case 'f' : m_nMatrixSourceType=MATRIX_FILE;break;
      case 'p' : m_nMatrixSourceType=MATRIX_PREV;break;
      case 'c' : m_nMatrixSourceType=MATRIX_PREVCLONE;break;
      case 'u' : m_nMatrixSourceType=MATRIX_BYUSERFUNCTION;break;
      case 's' : m_nMatrixSourceType=MATRIX_BYSCRIPT;break;
      }
      myFree(pAddr);
   } else {
      m_nMatrixSourceType=MATRIX_FILE;
   }

   pAddr=SEGetOptionValueString(
      NULL,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_DATA,1,
      PLOTSCRIPT_TYPE,1,"file=",1,
      0);
   switch (m_nMatrixSourceType) {
   case MATRIX_FILE :
   case MATRIX_PREV :
   case MATRIX_PREVCLONE :
   case MATRIX_BYUSERFUNCTION :
      m_sFromDataName=pAddr;
      break;
   case MATRIX_BYSCRIPT :
      if (!pAddr) break; //20030320
      int nIndex=atoi(pAddr)+1;
      myFree(pAddr);
      pAddr=SEGetOptionValueString(
         NULL,Script,
         PLOTSCRIPT_GLOB,1,PLOTSCRIPT_EXEC,1,
         "file=",nIndex,
         0);
      if (!pAddr) break;
      strdelete(pAddr,0,1);
      strdelete(pAddr,strlen(pAddr)-1,1);
      strtrim(pAddr);
      CToken Token(pAddr,"|");
      m_sFromScriptPattern=Token.GetTokenByIndex(0);
      m_sFromScriptSplit=Token.GetTokenByIndex(1);
      m_sFromScriptOption=Token.GetTokenByIndex(2);
      m_sFromScriptPattern.TrimLeft();
      m_sFromScriptPattern.TrimRight();
      m_sFromScriptSplit.TrimLeft();
      m_sFromScriptSplit.TrimRight();
      m_sFromScriptOption.TrimLeft();
      m_sFromScriptOption.TrimRight();
      break;
   }
   freeEx(pAddr);

   //20030311
   CComboBox *pBox=(CComboBox*)GetDlgItem(ID_GRDATA_NAME);
   CString sFile;
   pBox->ResetContent();
   for (int nIndex=0;nIndex<=pSheet->m_nPlotIndex;nIndex++) {
      pAddr=SEGetOptionValueString(
         NULL,Script,
         PLOTSCRIPT_PLOT,nIndex,PLOTSCRIPT_DATA,1,
         PLOTSCRIPT_TYPE,1,"file=",1,
         0);
      sFile=pAddr;
      sFile.TrimRight();
      if (!sFile.IsEmpty()) {
         if (LB_ERR==pBox->FindStringExact(-1,sFile)) { //20030428
            pBox->AddString(pAddr);
         }
      }
   }

   m_sGrxyFile=pAddr=SEGetOptionValueString(
      NULL,Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_DATA,1,
      PLOTSCRIPT_TYPE,1,"xyfile=",1,
      0);
   if (pAddr) {
      myFree(pAddr);
      m_sGrxyFile.Delete(0);
      m_sGrxyFile.Delete(m_sGrxyFile.GetLength()-1);
      m_sGrxyFile.TrimLeft();
      m_sGrxyFile.TrimRight();
   }

   //20030311
   m_sDataBlockIndex=SEGetOptionValueString(
      "*",Script,
      PLOTSCRIPT_PLOT,pSheet->m_nPlotIndex,PLOTSCRIPT_DATA,1,
      PLOTSCRIPT_TYPE,1,"block=",1,
      0);

   m_bReuseFilesOnADisk=SEGetOptionValueInteger(
      0,Script,
      PLOTSCRIPT_GLOB,1,PLOTSCRIPT_EXEC,1,"bReuseIfExist=",1,
      0);

   CGrDataPage::HandleAChangeOfRadioButtons();
   m_sGrFolder=pSheet->GetFolderFromFilePath(pSheet->m_sGrFile);

   if (m_bFirstSetActive) UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

void CGrDataPage::OnGrdataFromfileFileViewer() 
{
	// TODO: Add your control notification handler code here

   UpdateData(TRUE);
   if (m_sFromDataName.IsEmpty()) return;
   CWinApp *pApp=AfxGetApp();
   CString sExe=pApp->GetProfileString(RegKeySettings,RegKeyTextViewer);
   if (sExe.IsEmpty()) {
      AfxMessageBox(
         _T("Set your script editor program in advance."),
         MB_ICONEXCLAMATION);
      return;
   }
   sExe+=" \""+m_sFromDataName+"\"";
   WinExec((LPCTSTR)sExe,SW_SHOWDEFAULT);
}

void CGrDataPage::OnGrdataFileGetdbi() //20030421
{
	// TODO: Add your control notification handler code here

   UpdateData(TRUE);
   if (m_sFromDataName.IsEmpty()) return;
   if (m_nMatrixSourceType!=MATRIX_FILE) return;

   CWinApp *pApp=AfxGetApp();
   CString sExe=pApp->GetProfileString(RegKeySettings,RegKeyDbiViewer);
   if (sExe.IsEmpty()) {
      AfxMessageBox(
         _T("You lost the supplementary execution file named \"getdbi.exe\".\n"
            "Otherwise, installation was not perfect."),
         MB_ICONEXCLAMATION);
      return;
   }

	CString sCommand,sReturn;
   sCommand.Format("\"%s\" \"%s\"",sExe,m_sFromDataName);
   CreateProcessWithRedirectedIO2(sCommand,sReturn,TRUE);
   if (strcount(sReturn,": ")==1) sReturn.Replace(": ",": \n");
   sReturn.Insert(0,"\n\n");
   sReturn.Insert(0,sExe);
   MessageBox(sReturn,NULL,MB_ICONINFORMATION);
}

void CGrDataPage::OnGrdataFileApplyall() //20031112
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

   CString sTypePara,sPara;
   sPara.Format("file=%s",m_sFromDataName);
   char *pAddr;
   for (int nPlotIndex=1;nPlotIndex<=pSheet->m_nPlotTotal;nPlotIndex++) {
      pAddr=SEGetOptionValueString(
      "",Script,
      PLOTSCRIPT_PLOT,nPlotIndex,PLOTSCRIPT_DATA,1,
      PLOTSCRIPT_TYPE,1,
      0);
      if (!pAddr) continue;
      strtolower(pAddr);
      //if (!(strequ(pAddr,"file")||strequ(pAddr,"prev"))) goto N;
      sTypePara.Format("%s=%s",PLOTSCRIPT_TYPE,pAddr);
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_PLOT,nPlotIndex,PLOTSCRIPT_DATA,1,
         sTypePara,1,sPara,1,
         0);
//N:
      freeEx(pAddr);
   }

   Script=pScript;
   delete pScript;
}
