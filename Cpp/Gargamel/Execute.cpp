// Execute.cpp : implementation file
//

#include "stdafx.h"
#include "Gargamel.h"
#include "Execute.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Y.Kim,20030206

#include <objbase.h>

#include "FileDialogEx.h"
#include "Token.h"
#include "number.h"

#define GARGAMEL_FILE_EXT  "ga"  //Y.Kim,20030211
#define GARGAMEL_FILE_TAIL ".ga" //Y.Kim,20030211

static char InFileFilter[]
="Gargamel input files (*.ga)|*.ga|Gargamel old-fashioned input files (*.in)|*.in|"
 "All files (*.*)|*.*||";
static char OutFileFilter[]
="Gargamel output Files (*.out)|*.out|All files (*.*)|*.*||";

/////////////////////////////////////////////////////////////////////////////
// CExecute property page

IMPLEMENT_DYNCREATE(CExecute, CDialog)

CExecute::CExecute(CWnd* pParent /*=NULL*/)
   : CDialog(CExecute::IDD,pParent)
{
	//{{AFX_DATA_INIT(CExecute)
	m_sDumpFileName = _T("");
	m_bNumericAlias = FALSE;
	m_bSynchronizeOutFileName = FALSE;
	m_bComposite = FALSE;
	//}}AFX_DATA_INIT

   m_sGargamelVersion="2003.0215";

   m_sInputFile=_T("");
   m_sOutputFileHeader=_T("");
   m_nSearchType=AFLIST::AF_ABSOLUTE;
   m_nColumnarMatrixType=AF_ROWCOL_EXCHANGE_NONE;
   m_nPostProcessType=0;

   m_AFlist=0;
   m_string2d=0;
   m_nrl=m_nrh=m_ncl=m_nch=0;

   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileString(RegKeySettings,RegKeyVersion,m_sGargamelVersion);
   int nExecCount=pApp->GetProfileInt(RegKeySettings,RegKeyExecCount,0);
   pApp->WriteProfileInt(RegKeySettings,RegKeyExecCount,++nExecCount);
   m_bSynchronizeOutFileName=pApp->GetProfileInt(RegKeySettings,RegKeySynchOutFileName,0);
   CString sReturn;
   sReturn=pApp->GetProfileString(RegKeySettings,RegKeyLastDirectoryAtExecute);
   m_sLastDirectory=sReturn;
}

CExecute::~CExecute()
{
   if (m_AFlist)
      m_pApp->m_pAnyfind->_AFClose(m_AFlist);
   if (m_string2d)
      m_pApp->m_pAnyfind->_AFReleaseString2D(m_string2d,m_nrl,m_nrh,m_ncl,m_nch);
   m_AFlist=0;
   m_string2d=0;
   m_nrl=m_nrh=m_ncl=m_nch=0;

   m_pApp->WriteProfileInt(RegKeySettings,RegKeySynchOutFileName,m_bSynchronizeOutFileName);
   m_pApp->WriteProfileString(RegKeySettings,RegKeyLastDirectoryAtExecute,m_sLastDirectory);
}

void CExecute::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExecute)
	DDX_Control(pDX, ID_OPTION_NUMPOSTPROCESS, m_PostProcessType);
	DDX_Control(pDX, ID_PROGRESS, m_Progress);
	DDX_Text(pDX, ID_DUMPFILENAME, m_sDumpFileName);
	DDV_MaxChars(pDX, m_sDumpFileName, 128);
	DDX_Check(pDX, ID_OPTION_NUMERICALIAS, m_bNumericAlias);
	DDX_Check(pDX, ID_SYNCHRONIZE_OUTFILENAME, m_bSynchronizeOutFileName);
	DDX_Check(pDX, ID_OPTION_COMPOSITE, m_bComposite);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExecute, CDialog)
	//{{AFX_MSG_MAP(CExecute)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(ID_EXECUTE_GARGAMEL, OnExecuteGargamel)
	ON_BN_CLICKED(ID_SYNCHRONIZE_OUTFILENAME, OnSynchronizeOutfilename)
	ON_BN_CLICKED(ID_EXECUTE_LOAD, OnExecuteLoad)
	ON_BN_CLICKED(ID_EXECUTE_SAVE, OnExecuteSave)
	ON_BN_CLICKED(ID_EXECUTE_SAVEAS, OnExecuteSaveAs)
	ON_BN_CLICKED(ID_EXECUTE_DUMP, OnExecuteDump)
	ON_BN_CLICKED(ID_EXECUTE_DUMPAS, OnExecuteDumpAs)
	ON_BN_CLICKED(ID_EXECUTE_DUMPANDVIEW, OnExecuteDumpAndView)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_EXECUTE_VIEW, OnExecuteView)
	ON_CBN_SELCHANGE(ID_OPTION_NUMPOSTPROCESS, OnSelchangeOptionNumpostprocess)
	ON_BN_CLICKED(ID_EXECUTE_EXAMPLE, OnExecuteExample)
	ON_BN_CLICKED(ID_DISMISS, OnDismiss)
	//}}AFX_MSG_MAP

   //Y.Kim,20030206
	ON_BN_CLICKED(ID_OPTION_SEARCH_ABSOLUTE, OnOptionSearchWays)
	ON_BN_CLICKED(ID_OPTION_SEARCH_SEQUENTIAL, OnOptionSearchWays)
	ON_BN_CLICKED(ID_OPTION_SEARCH_WILD, OnOptionSearchWays)
	ON_BN_CLICKED(ID_OPTION_SEARCH_BLOCK, OnOptionSearchWays)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExecute message handlers

static CWnd *AFExtractExSynchronizer_pWindow=NULL;
static int AFExtractExSynchronizer_nStart=0;
static int AFExtractExSynchronizer_nEnd=0;
static int AFExtractExSynchronizer(char *sFile)
{
   if (!AFExtractExSynchronizer_pWindow) return FALSE;
   CTextProgressCtrl *pCtrl=
      (CTextProgressCtrl*)AFExtractExSynchronizer_pWindow->GetDlgItem(ID_PROGRESS);
   pCtrl->StepIt();
   if (sFile[0]==AF_SPLIT_INDICATOR) return TRUE;
   //int nPos=pCtrl->GetPos();
   //int nLower,nUpper;
   //pCtrl->GetRange(nLower,nUpper);
   AFExtractExSynchronizer_nStart++;
   CString sMessage;
   sMessage.Format("%s => %d%%",sFile,
      (int)(AFExtractExSynchronizer_nStart*100/(AFExtractExSynchronizer_nEnd)));
   pCtrl->SetWindowText(sMessage);
   return TRUE;

}
void CExecute::OnExecuteGargamel() 
{
	// TODO: Add your control notification handler code here
   char *pPatterns,*pFiles,***string2d,buf32[32];
   AFLIST *pList;
   int nResult;
   int nPos,nCount,nCountOfSplitFile,nrl,nrh,ncl,nch;
   CString lfsPattern,lfsSplit,string;

   CExecute::MyUpdateDataTrue();
   GetDataFromPages(&pPatterns,&pFiles);
   if (!pPatterns||!pFiles) {
      MessageBox(
         "Error, your setting is not completed.\n"
         "Fill'em up properly ..",
         NULL,MB_ICONWARNING);
      return;
   }
   lfsPattern=pPatterns;delete pPatterns;
   lfsSplit=pFiles;    delete pFiles;

   m_lfsPattern=lfsPattern;
   m_lfsSplit=lfsSplit;

   if (m_AFlist) {
      m_pApp->m_pAnyfind->_AFClose(m_AFlist);
      m_AFlist=0;
      m_pApp->m_pAnyfind->_AFReleaseString2D(m_string2d,m_nrl,m_nrh,m_ncl,m_nch);
      m_string2d=0;
      m_nrl=m_nrh=m_ncl=m_nch=0;
   }

   m_pApp->m_pAnyfind->_AFOpen(
      &pList,m_nSearchType,1,m_nPostProcessType,0,m_bComposite);

   //20030209
   CToken Token(lfsPattern,"\n");
   CString sToken;
   switch (m_nSearchType) {
   case AFLIST::AF_ABSOLUTE:
   case AFLIST::AF_SEQUENTIAL:
   case AFLIST::AF_WILD:
      while (Token.IsNext()) {
         sToken=Token.GetNextToken();
         nResult=m_pApp->m_pAnyfind->_AFAddNode(
            pList,m_nSearchType,(LPCTSTR)sToken,0);
         if (!nResult) {
            char *pMessage;
            if (m_pApp->m_pAnyfind->_AFGetErrorMessagePointer(&pMessage)) {
               MessageBox(pMessage,NULL,MB_OK|MB_ICONSTOP);
            }
            m_pApp->m_pAnyfind->_AFClose(pList);
            MessageBox(
               "Error caused by one of followings :\n\n"
               "  1. Selection number is not digit.\n"
               "  2. Selection number is at the case of FirstNo>LastNo.\n"
               "  3. ... \n"
               "  \n"
               "Don't cheat me !",
               NULL,MB_OK|MB_ICONSTOP);
            return;
         }
      }
      break;
   case AFLIST::AF_BLOCK:
      nResult=m_pApp->m_pAnyfind->_AFAddNode(
         pList,m_nSearchType,(LPCTSTR)Token,0);
      if (!nResult) {
         char *pMessage;
         if (m_pApp->m_pAnyfind->_AFGetErrorMessagePointer(&pMessage)) {
            MessageBox(pMessage,NULL,MB_OK|MB_ICONSTOP);
         }
         m_pApp->m_pAnyfind->_AFClose(pList);
         MessageBox(
            "Error caused in the description of pattern for block.\n"
            "Don't make me upset!",
            NULL,MB_OK|MB_ICONSTOP);
         return;
      }
      break;
   }

   nPos=nCount=nCountOfSplitFile=0;
   while ((nPos=lfsSplit.Find('\n',nPos))>=0) {
      nPos++;
      nCount++;
      if (lfsSplit[nPos]!=AF_SPLIT_INDICATOR) nCountOfSplitFile++;
   }
   string2d=0;
   nrl=nrh=ncl=nch=0;
   m_Progress.SetRange(0,nCount);
   AFExtractExSynchronizer_pWindow=this;
   AFExtractExSynchronizer_nStart=1;
   AFExtractExSynchronizer_nEnd=nCountOfSplitFile;
   nResult=m_pApp->m_pAnyfind->_AFExtractEx(
      pList,(LPCTSTR)lfsSplit,&string2d,&nrl,&nrh,&ncl,&nch,
      AFExtractExSynchronizer);
   if (!nResult) {
      char *pMessage;
      if (m_pApp->m_pAnyfind->_AFGetErrorMessagePointer(&pMessage)) {
         MessageBox(pMessage,NULL,MB_OK|MB_ICONSTOP);
      }
      m_pApp->m_pAnyfind->_AFClose(pList);
   } else {
      nCount=m_pApp->m_pAnyfind->_AFGetColumnCountPerBlock(pList);
      if (m_nColumnarMatrixType) {
         int nTemp=nrh-nrl+1;
         m_pApp->m_pAnyfind->_AFExchangeRowColPerBlock(
            &string2d,&nrl,&nrh,&ncl,&nch,nCount,
            m_nColumnarMatrixType);
         nCount=nTemp;
      }
   }
   
   m_AFlist=pList;
   m_string2d=string2d;
   m_nrl=nrl;
   m_nrh=nrh;
   m_ncl=ncl;
   m_nch=nch;
   CString rowColTotal;
   sprintf(buf32,"%d",nrh-nrl+1);rowColTotal+=buf32;rowColTotal+=" x ";
   sprintf(buf32,"%d",nch-ncl+1);rowColTotal+=buf32;rowColTotal+=" = ";
   sprintf(buf32,"%d",(nrh-nrl+1)*(nch-ncl+1));rowColTotal+=buf32;

   m_Progress.SetWindowText(nResult?rowColTotal:"0 x 0 = 0");
   m_Progress.SetPos(0);

   GetDlgItem(ID_EXECUTE_DUMP)->EnableWindow(TRUE);
   GetDlgItem(ID_EXECUTE_DUMPAS)->EnableWindow(TRUE);
   GetDlgItem(ID_EXECUTE_DUMPANDVIEW)->EnableWindow(TRUE);
   GetDlgItem(ID_EXECUTE_VIEW)->EnableWindow(TRUE);
}

void CExecute::OnExecuteLoad() 
{
	// TODO: Add your control notification handler code here

   int nLength;
   char *pStream;
   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      InFileFilter);
   fDialog.m_ofn.lpstrInitialDir=m_sLastDirectory;
   if (fDialog.DoModal()==IDCANCEL) return;
   CString sFile=fDialog.GetPathName();
   if (sFile.IsEmpty()) return;
   CFile File(sFile,CFile::modeRead);
   nLength=File.GetLength();
   pStream=new char[nLength*sizeof(TCHAR)];
   File.ReadHuge(pStream,nLength);
   File.Close();

   int bResult=LoadSettings(pStream);
   delete pStream;
   if (!bResult) return;

   m_sInputFile=sFile;

   GetParentOwner()->SetWindowText((LPCTSTR)m_sInputFile);
   if (!sFile.IsEmpty()) {
      int nPos=sFile.ReverseFind('\\');
      if (nPos!=-1) {
         sFile.Delete(nPos,sFile.GetLength()-nPos);
         m_sLastDirectory=sFile;
      }
   }
}

void CExecute::OnExecuteSave() 
{
	// TODO: Add your control notification handler code here

   if (m_sInputFile.IsEmpty()) return;

   if (m_bSynchronizeOutFileName) {
      UpdateData(TRUE);
      m_sDumpFileName=m_sInputFile;
      CString sTemp=m_sDumpFileName.Right(3);
      if (!sTemp.CompareNoCase(GARGAMEL_FILE_TAIL)) {
         m_sDumpFileName.Delete(m_sDumpFileName.GetLength()-3,3);
      }
      m_sDumpFileName+=".out";
      UpdateData(FALSE);
   }

   CString sAll;
   CExecute::SaveSettings(sAll);
	CFile File(m_sInputFile,CFile::modeCreate|CFile::modeWrite);
   File.WriteHuge(sAll,sAll.GetLength());
   File.Close();
}

void CExecute::OnExecuteSaveAs() 
{
	// TODO: Add your control notification handler code here

   UpdateData(TRUE);

   CString sTemp=_T("");
   if (!m_sInputFile.IsEmpty()) {
      int i=m_sInputFile.ReverseFind('\\');
      //sTemp=m_sInputFile.Left(i);
      //_chdir((LPCTSTR)sTemp);
      sTemp=m_sInputFile.Right(m_sInputFile.GetLength()-i-1);
   }   
   CFileDialogEx fDialog(FALSE,GARGAMEL_FILE_EXT,(LPCTSTR)sTemp,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,
      InFileFilter);
   fDialog.m_ofn.lpstrInitialDir=m_sLastDirectory;
   if (fDialog.DoModal()==IDCANCEL) return;
   CString sFile=fDialog.GetPathName();
   if (sFile.IsEmpty()) return;

   m_sInputFile=sFile;
   CExecute::OnExecuteSave();

   GetParentOwner()->SetWindowText((LPCTSTR)m_sInputFile);
   if (!sFile.IsEmpty()) {
      int nPos=sFile.ReverseFind('\\');
      if (nPos!=-1) {
         sFile.Delete(nPos,sFile.GetLength()-nPos);
         m_sLastDirectory=sFile;
      }
   }
}

void CExecute::OnSynchronizeOutfilename() 
{
	// TODO: Add your control notification handler code here

   CButton *pButton=(CButton*)GetDlgItem(ID_SYNCHRONIZE_OUTFILENAME);
   m_bSynchronizeOutFileName=pButton->GetCheck();
}

void CExecute::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

   CWnd *wnd=GetDlgItem(ID_GARGAMEL_PICTURE);
   CRect rect;
   wnd->GetWindowRect((LPRECT)rect);
   ScreenToClient(&rect);
   if (rect.PtInRect(point)) {
      CWinApp *pApp=AfxGetApp();
      pApp->m_pMainWnd->SendMessage(WM_SYSCOMMAND,IDD_ABOUTBOX);
   }

	CDialog::OnLButtonDblClk(nFlags, point);
}

BOOL CExecute::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   m_pApp=(CGargamelApp*)AfxGetApp();
   m_pTab=(CGargamelTabCtrl*)GetParent();

   SetTimer(ID_TIMER_TEXT,1000,NULL);

   CWinApp *pApp=AfxGetApp();
   if (pApp->m_lpCmdLine[0]!=_T('\0')) {
      CString sFile(pApp->m_lpCmdLine);
      sFile.TrimLeft();
      sFile.TrimRight();
      if (sFile[0]=='\"' && sFile[sFile.GetLength()-1]=='\"') {
         sFile.Delete(0);
         sFile.Delete(sFile.GetLength()-1);
      }
      //if (i!=-1) sFile.Delete(i,sFile.GetLength()-i);
      CFile File;
      int bResult=File.Open((LPCTSTR)sFile,CFile::modeRead);
      if (bResult) {
         int nLength=File.GetLength();
         char *pStream=new char[nLength*sizeof(TCHAR)];
         File.ReadHuge(pStream,nLength);
         File.Close();
         CExecute::LoadSettings(pStream);
         delete pStream;
         if (bResult) {
            m_sInputFile=sFile;
            GetParentOwner()->SetWindowText((LPCTSTR)m_sInputFile);
            if (!sFile.IsEmpty()) {
               int nPos=sFile.ReverseFind('\\');
               if (nPos!=-1) {
                  sFile.Delete(nPos,sFile.GetLength()-nPos);
                  m_sLastDirectory=sFile;
               }
            }
         }
      } else {
         CString message;
         message.Format("Error, <%s> is not opened !",sFile);
         MessageBox((LPCTSTR)message,NULL,MB_ICONERROR);
      }
   }

	SetComboBoxStringsOfNumPostProcess();
   OnSelchangeOptionNumpostprocess();

   m_Progress.SetShowText(TRUE);
   m_Progress.SetPos(0);
   m_Progress.SetStep(1);

   MyUpdateDataFalse();
   GetDlgItem(ID_EXECUTE_DUMP)->EnableWindow(FALSE);
   GetDlgItem(ID_EXECUTE_DUMPAS)->EnableWindow(FALSE);
   GetDlgItem(ID_EXECUTE_DUMPANDVIEW)->EnableWindow(FALSE);
   GetDlgItem(ID_EXECUTE_VIEW)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExecute::SetComboBoxStringsOfNumPostProcess()
{
    int nIndex,nCount=sizeof(qNumericPostProcessStrings)/
       sizeof(qNumericPostProcessStrings[0]);   
    for (nIndex=0;nIndex<nCount;nIndex++) {
       m_PostProcessType.AddString(qNumericPostProcessStrings[nIndex]);
    }
    m_PostProcessType.SetCurSel(0);
}

void CExecute::OnExecuteDump() 
{
	// TODO: Add your control notification handler code here
   
   if (!UpdateData(TRUE)) return;
   if (m_sDumpFileName.IsEmpty()) {
      MessageBox("Dump file name is not set.",NULL,MB_ICONWARNING);
      return;
   }
   if (!m_AFlist) {
      MessageBox("Extracted data is not found.",NULL,MB_ICONWARNING);
      return;
   }

   char *pStream,**ppExHeader;
   int nExHeader;
   nExHeader=0;
   ppExHeader=0;
   switch (m_nColumnarMatrixType) {
   case AF_ROWCOL_EXCHANGE_NONE :
      break;
   case AF_ROWCOL_EXCHANGE_BYPATTERN :
   case AF_ROWCOL_EXCHANGE_BYPATTERN2 :
      m_pApp->m_pAnyfind->_AFGetPatternAliasArrayB1(
         m_AFlist,m_bNumericAlias,
         &ppExHeader,&nExHeader);
      break;
   case AF_ROWCOL_EXCHANGE_BYSPLIT :
      m_pApp->m_pAnyfind->_AFGetSplitAliasArrayB1(
         (LPCTSTR)m_lfsSplit,"\n",m_bNumericAlias,
         &ppExHeader,&nExHeader);
      break;
   }
   if (m_nColumnarMatrixType && !nExHeader) {
      CString sTmp;
      sTmp.Format(
         "Error, Could not create a %s alias array \n"
         "under bNumericAlias=%s",
         m_nColumnarMatrixType==1 ? "PATTERN" : "SPLIT",
         m_bNumericAlias ? "TRUE":"FALSE"
         );
      MessageBox(sTmp,NULL,MB_ICONWARNING);
      return;
   }
   m_pApp->m_pAnyfind->_AFPutItToStream(
      m_AFlist,m_nColumnarMatrixType,nExHeader,ppExHeader,
      m_string2d,m_nrl,m_nrh,m_ncl,m_nch,
      &pStream);
   if (!pStream) {
      MessageBox("Could not make extracted data stream.",NULL,MB_ICONWARNING);
      return;
   }
   m_pApp->m_pAnyfind->_AFReleaseString1D(ppExHeader,1,nExHeader);

   CFile File;
   if (!File.Open(m_sDumpFileName,CFile::modeCreate|CFile::modeWrite)) {
      CString sTemp;
      sTemp=m_sDumpFileName+" \n\ncould not be opend.";
      MessageBox((LPCTSTR)sTemp,NULL,MB_ICONERROR);
      m_pApp->m_pAnyfind->_AFReleaseString(pStream);
      return;
   }
   if (!m_sOutputFileHeader.IsEmpty()) {
      CString string(m_sOutputFileHeader);
      string+=AF_COMMAND_LINE_END;
      string+=pStream;
      File.WriteHuge((LPCTSTR)string,string.GetLength());
   } else
      File.WriteHuge(pStream,strlen(pStream));
   File.Close();
   m_pApp->m_pAnyfind->_AFReleaseString(pStream);
}

void CExecute::OnExecuteDumpAs() 
{
	// TODO: Add your control notification handler code here
	
   char qStream[255+1];
   CWnd::SendDlgItemMessage(ID_DUMPFILENAME,WM_GETTEXT,255,(LPARAM)qStream);
   char *pAddr=strrchr(qStream,'\\');
   if (pAddr) {
      *pAddr=0;
      _chdir(qStream);
   }
   CFileDialogEx fDialog(FALSE,NULL,pAddr+1,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,
      OutFileFilter);
   if (fDialog.DoModal()==IDCANCEL) return;
   CString sFile=fDialog.GetPathName();
   if (sFile.IsEmpty()) return;
   char *endString=".out";
   CString end=sFile.Right(strlen(endString));
   if (end!=endString) sFile+=endString;
   CWnd::SendDlgItemMessage(ID_DUMPFILENAME,WM_SETTEXT,
                            0,(LPARAM)(LPCTSTR)sFile);
   CExecute::OnExecuteDump();
}

void CExecute::OnExecuteDumpAndView() 
{
	// TODO: Add your control notification handler code here

   CExecute::OnExecuteDump();
   CExecute::OnExecuteView();
}

void CExecute::OnExecuteView() 
{
	// TODO: Add your control notification handler code here

   CWinApp *pApp=AfxGetApp();
   CString sValue=pApp->GetProfileString(RegKeySettings,RegKeyTextViewer);
   if (sValue.IsEmpty()) {
      MessageBox("Warning, you should enroll the viewer before.",NULL,MB_ICONEXCLAMATION);
      CFileDialog fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "Exec Files (*.exe;*.com)|*.exe;*.com|All Files (*.*)|*.*||",
      NULL);
      fDialog.m_ofn.lpstrTitle=_T("외부 Editor 실행파일을 선택하세요.");
      fDialog.DoModal();
      sValue=fDialog.GetPathName();
      if (sValue.IsEmpty()) return;
      pApp->WriteProfileString(RegKeySettings,RegKeyTextViewer,(LPCTSTR)sValue);
   }
   UpdateData(TRUE);
   if (m_sDumpFileName.IsEmpty()) return;
   sValue+=" "+m_sDumpFileName;
   WinExec((LPCTSTR)sValue,SW_SHOWDEFAULT);
}

BOOL CExecute::MyUpdateDataTrue()
{
   if (!UpdateData(TRUE)) return FALSE;

   if (m_sDumpFileName.IsEmpty()) {
      m_sDumpFileName=m_sInputFile;
      if (!m_sDumpFileName.IsEmpty()) {
         char *pIn=GARGAMEL_FILE_TAIL,*pOut=".out";
         int nLength=m_sDumpFileName.GetLength();
         int nExt=max(strlen(pIn),strlen(pOut));
         int nPos=m_sDumpFileName.Find(pIn,nLength-nExt);
         if (nPos>=0) {
            m_sDumpFileName.Delete(nPos,nLength-nPos);
         } else {
            nPos=m_sDumpFileName.Find(pOut,nLength-nExt);
            if (nPos>=0) {
               m_sDumpFileName.Delete(nPos,nLength-nPos);
            }
         }
         m_sDumpFileName+=".out";
         UpdateData(FALSE);
      }
   }

   if (((CButton*)GetDlgItem(ID_OPTION_SEARCH_ABSOLUTE))->GetCheck()==1)
      m_nSearchType=AFLIST::AF_ABSOLUTE;
   else if (((CButton*)GetDlgItem(ID_OPTION_SEARCH_SEQUENTIAL))->GetCheck()==1)
      m_nSearchType=AFLIST::AF_SEQUENTIAL;
   else if (((CButton*)GetDlgItem(ID_OPTION_SEARCH_WILD))->GetCheck()==1)
      m_nSearchType=AFLIST::AF_WILD;
   else if (((CButton*)GetDlgItem(ID_OPTION_SEARCH_BLOCK))->GetCheck()==1)
      m_nSearchType=AFLIST::AF_BLOCK;

   if (((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_NO))->GetCheck()==1)
      m_nColumnarMatrixType=AF_ROWCOL_EXCHANGE_NONE;
   else if (((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_BYPATTERN))->GetCheck()==1)
      m_nColumnarMatrixType=AF_ROWCOL_EXCHANGE_BYPATTERN;
   else if (((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_BYPATTERN2))->GetCheck()==1)
      m_nColumnarMatrixType=AF_ROWCOL_EXCHANGE_BYPATTERN2;
   else if (((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_BYSPLIT))->GetCheck()==1)
      m_nColumnarMatrixType=AF_ROWCOL_EXCHANGE_BYSPLIT;

   m_nPostProcessType=m_PostProcessType.GetCurSel();

   return TRUE;
}

BOOL CExecute::MyUpdateDataFalse()
{
   UpdateData(false);

   ((CButton*)GetDlgItem(ID_OPTION_SEARCH_ABSOLUTE))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_OPTION_SEARCH_SEQUENTIAL))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_OPTION_SEARCH_WILD))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_OPTION_SEARCH_BLOCK))->SetCheck(0);
   switch(m_nSearchType) {
   case AFLIST::AF_ABSOLUTE :
      ((CButton*)GetDlgItem(ID_OPTION_SEARCH_ABSOLUTE))->SetCheck(1);break;
   case AFLIST::AF_SEQUENTIAL :
      ((CButton*)GetDlgItem(ID_OPTION_SEARCH_SEQUENTIAL))->SetCheck(1);break;
   case AFLIST::AF_WILD :
      ((CButton*)GetDlgItem(ID_OPTION_SEARCH_WILD))->SetCheck(1);break;
   case AFLIST::AF_BLOCK :
      ((CButton*)GetDlgItem(ID_OPTION_SEARCH_BLOCK))->SetCheck(1);break;
   }

   ((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_NO))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_BYPATTERN))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_BYPATTERN2))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_BYSPLIT))->SetCheck(0);
   switch(m_nColumnarMatrixType) {
   case AF_ROWCOL_EXCHANGE_NONE :
      ((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_NO))->SetCheck(1);break;
   case AF_ROWCOL_EXCHANGE_BYPATTERN :
      ((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_BYPATTERN))->SetCheck(1);break;
   case AF_ROWCOL_EXCHANGE_BYPATTERN2 :
      ((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_BYPATTERN2))->SetCheck(1);break;
   case AF_ROWCOL_EXCHANGE_BYSPLIT :
      ((CButton*)GetDlgItem(ID_OPTION_COLUMNARMTX_BYSPLIT))->SetCheck(1);break;
   }

   m_PostProcessType.SetCurSel(m_nPostProcessType);
   GetDlgItem(ID_OPTION_COMPOSITE)->EnableWindow(m_nPostProcessType);

   OnOptionSearchWays(); //20030209

   return true;
}

int CExecute::LoadSettings(const char *qStream)
{
   CGargamelPatternFrameDialog *pPattern=
      (CGargamelPatternFrameDialog*)m_pTab->GetDialogClassPtr(IDD_GARGAMEL_PATTERN);
   CGargamelPatternForMatrixFrameDialog *pPatternForMatrix=
      (CGargamelPatternForMatrixFrameDialog*)m_pTab->GetDialogClassPtr(IDD_GARGAMEL_PATTERNFORMATRIX);
   CGargamelSplitFrameDialog *pSplit=
      (CGargamelSplitFrameDialog*)m_pTab->GetDialogClassPtr(IDD_GARGAMEL_SPLIT);

   char *sDumpFileName,*lfsPattern,*lfsSplit;
   int nResult=m_pApp->m_pAnyfind->_AFGetParametersFromScript(
      qStream,
      &sDumpFileName,
      &m_nSearchType,&m_nColumnarMatrixType,&m_bNumericAlias,
      &m_nPostProcessType,
      &lfsPattern,&lfsSplit);
   m_sDumpFileName=sDumpFileName;
   if (m_nSearchType==AFLIST::AF_BLOCK) {
      pPatternForMatrix->m_sStream=lfsPattern;
   } else {
      pPattern->m_sStream=lfsPattern;
   }
   pSplit->m_sStream=lfsSplit;
   m_pApp->m_pAnyfind->_AFReleaseString(sDumpFileName);
   m_pApp->m_pAnyfind->_AFReleaseString(lfsPattern);
   m_pApp->m_pAnyfind->_AFReleaseString(lfsSplit);
   if (!nResult) {
      MessageBox("Error, script file is invalid.",NULL,MB_OK|MB_ICONSTOP);
      return FALSE;
   }

   MyUpdateDataFalse();
   return TRUE;
}

void CExecute::SaveSettings(CString &script)
{
   CExecute::MyUpdateDataTrue();

   CGargamelPatternFrameDialog *pPattern=
      (CGargamelPatternFrameDialog*)m_pTab->GetDialogClassPtr(IDD_GARGAMEL_PATTERN);
   CGargamelPatternForMatrixFrameDialog *pPatternForMatrix=
      (CGargamelPatternForMatrixFrameDialog*)m_pTab->GetDialogClassPtr(IDD_GARGAMEL_PATTERNFORMATRIX);
   CGargamelSplitFrameDialog *pSplit=
      (CGargamelSplitFrameDialog*)m_pTab->GetDialogClassPtr(IDD_GARGAMEL_SPLIT);
   LPCTSTR pPatternOrPatternForMatrix=
      (m_pTab->IsActivatedDialogInTabControl(IDD_GARGAMEL_PATTERNFORMATRIX)
      ? pPatternForMatrix->m_sStream:pPattern->m_sStream);
   char *pOutScript;
   m_pApp->m_pAnyfind->_AFPutParametersIntoScript(
      &pOutScript,
      (LPCTSTR)m_sGargamelVersion,(LPCTSTR)m_sDumpFileName,
      m_nSearchType,m_nColumnarMatrixType,m_bNumericAlias,
      m_nPostProcessType,
      (LPCTSTR)pPatternOrPatternForMatrix,
      (LPCTSTR)pSplit->m_sStream);
   script=pOutScript;
   m_pApp->m_pAnyfind->_AFReleaseString(pOutScript);
}

void CExecute::GetDataFromPages(char **ppStrings, char **ppFiles)
{
   CGargamelPatternFrameDialog *pPattern=
      (CGargamelPatternFrameDialog*)m_pTab->GetDialogClassPtr(IDD_GARGAMEL_PATTERN);
   CGargamelPatternForMatrixFrameDialog *pPatternForMatrix=
      (CGargamelPatternForMatrixFrameDialog*)m_pTab->GetDialogClassPtr(IDD_GARGAMEL_PATTERNFORMATRIX);
   CGargamelSplitFrameDialog *pSplit=
      (CGargamelSplitFrameDialog*)m_pTab->GetDialogClassPtr(IDD_GARGAMEL_SPLIT);

   CString sPattern= //Y.Kim,20030208
      m_pTab->IsActivatedDialogInTabControl(IDD_GARGAMEL_PATTERNFORMATRIX)
      ? pPatternForMatrix->m_sStream:pPattern->m_sStream;

   if ( sPattern.IsEmpty()
      ||pSplit->m_sStream.IsEmpty()) {
      *ppStrings=*ppFiles=0;
      return;
   }

   // CPattern
   int nLength=strlen((LPCTSTR)sPattern);
   *ppStrings=new char[nLength+1];
   strcpy(*ppStrings,(LPCTSTR)sPattern);

   // CSplit
   nLength=pSplit->m_sStream.GetLength();
   *ppFiles=new char[nLength+1];
   strcpy(*ppFiles,pSplit->m_sStream.GetBuffer(nLength+1));
   //pSplit->m_sStream.ReleaseBuffer(); 20030208
}


void CExecute::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

   if (nIDEvent==ID_TIMER_TEXT) {
      static char *Week[]={"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};
      CTime Time=CTime::GetCurrentTime();
      CString sText;
      sText.Format("%d.%d.%d (%s) %d:%02d:%02d",
         Time.GetYear()+2333,Time.GetMonth(),Time.GetDay(),
         Week[Time.GetDayOfWeek()-1],
         Time.GetHour(),Time.GetMinute(),Time.GetSecond());
      GetDlgItem(ID_TIMER_TEXT)->SetWindowText(sText);
   }
	
	CDialog::OnTimer(nIDEvent);
}

void CExecute::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

   KillTimer(ID_TIMER_TEXT);
}

void CExecute::OnSelchangeOptionNumpostprocess() 
{
	// TODO: Add your control notification handler code here

   int nSelection=m_PostProcessType.GetCurSel();
   GetDlgItem(ID_OPTION_COMPOSITE)->EnableWindow(nSelection);
}

void CExecute::OnDismiss() 
{
	// TODO: Add your control notification handler code here

	CWnd *pWnd=GetParentOwner();
   ((CDialog*)pWnd)->EndDialog(IDOK);
}

void CExecute::OnExecuteExample() 
{
	// TODO: Add your control notification handler code here

   //2001.0512
   CWinApp *pApp=AfxGetApp();
   CString sValue=pApp->GetProfileString(RegKeySettings,RegKeyExample);
   if (sValue.IsEmpty()) return;
   ShellExecute(NULL,"open",sValue,NULL,NULL,SW_SHOW);
}

void CExecute::OnOptionSearchWays() 
{
	// TODO: Add your control notification handler code here

   CGargamelTabCtrl *pTab=(CGargamelTabCtrl *)GetParent();
   if (((CButton*)GetDlgItem(ID_OPTION_SEARCH_ABSOLUTE))->GetCheck() ||
      ((CButton*)GetDlgItem(ID_OPTION_SEARCH_SEQUENTIAL))->GetCheck() ||
      ((CButton*)GetDlgItem(ID_OPTION_SEARCH_WILD))->GetCheck()) {
      pTab->SetTabArrayItemProperty(IDD_GARGAMEL_PATTERNFORMATRIX,1,false);
      pTab->SetTabArrayItemProperty(IDD_GARGAMEL_PATTERN,1,true);
   } else if (((CButton*)GetDlgItem(ID_OPTION_SEARCH_BLOCK))->GetCheck()) {
      pTab->SetTabArrayItemProperty(IDD_GARGAMEL_PATTERN,1,false);
      pTab->SetTabArrayItemProperty(IDD_GARGAMEL_PATTERNFORMATRIX,1,true);
   }
}

void CExecute::OnGargamelUpdateData(WPARAM wParam, LPARAM lParam)
{
   switch (wParam) {
   case true:  MyUpdateDataTrue();break;
   case false: MyUpdateDataFalse();break;
   }
}

