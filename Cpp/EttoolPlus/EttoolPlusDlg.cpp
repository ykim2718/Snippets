// EttoolPlusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EttoolPlus.h"
#include "EttoolPlusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "CreateProcessWithRedirectedIO.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEttoolPlusDlg dialog

CEttoolPlusDlg::CEttoolPlusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEttoolPlusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEttoolPlusDlg)
	m_bFormatDat = FALSE;
	m_bFormatDat2 = FALSE;
	m_bFormatLog = FALSE;
	m_bFormatLot = FALSE;
	m_bFormatLot2 = FALSE;
   m_bFormatLot3 = FALSE;
	m_bFormatLot4 = FALSE;
	m_bFormatMap = FALSE;
	m_bFormatMap2 = FALSE;
	m_bFormatPlt = FALSE;
	m_bFormatRpt = FALSE;
	m_sScriptFolder = _T("");
	m_sAggregation = _T("");
	m_sInputFolder = _T("");
	m_sOutputFolder = _T("");
	m_sInputFolderFileFilter = _T("");
	m_sNumberFormat = _T("");
	m_bFormatSum = FALSE;
	m_sStdout = _T("");
	m_bFormatCvs = FALSE;
	//}}AFX_DATA_INIT

   HRESULT hResult=::CoCreateInstance(
      CLSID_FileFolderTreeSelectionDialog,NULL,CLSCTX_INPROC_SERVER,
      IID_IFileFolderTreeSelectionDialog,(void**)&m_pFileFolderTreeSelectionDialog);
   if (FAILED(hResult)) {
      MessageBox("Error, ::CoCreateInstance().",NULL,MB_ICONWARNING);
      m_pFileFolderTreeSelectionDialog=NULL;
   }

   CWinApp* pApp=AfxGetApp();

   int nCount=pApp->GetProfileInt(RegKeySettings,RegKeyExecCount,0);
   pApp->WriteProfileInt(RegKeySettings,RegKeyExecCount,++nCount);

   m_sScriptFolder=pApp->GetProfileString(RegKeySettings,RegKeyScriptFile);
   m_sInputFolder=pApp->GetProfileString(RegKeySettings,RegKeyInputFolder);
   m_sInputFolderFileFilter=pApp->GetProfileString(RegKeySettings,RegKeyInputFolderFileFilter);
   if (m_sInputFolderFileFilter.IsEmpty()) m_sInputFolderFileFilter="*[0-9][0-9]";
   m_sOutputFolder=pApp->GetProfileString(RegKeySettings,RegKeyOutputFolder);
   m_sNumberFormat=pApp->GetProfileString(RegKeySettings,RegKeyNumberFormat);
   m_bFormatDat=pApp->GetProfileInt(RegKeySettings,RegKeyFormatDat,0);
   m_bFormatDat2=pApp->GetProfileInt(RegKeySettings,RegKeyFormatDat2,0);
   m_bFormatLot=pApp->GetProfileInt(RegKeySettings,RegKeyFormatLot,0);
   m_bFormatLot2=pApp->GetProfileInt(RegKeySettings,RegKeyFormatLot2,0);
   m_bFormatLot3=pApp->GetProfileInt(RegKeySettings,RegKeyFormatLot3,0);
   m_bFormatLot4=pApp->GetProfileInt(RegKeySettings,RegKeyFormatLot4,0);
   m_bFormatMap=pApp->GetProfileInt(RegKeySettings,RegKeyFormatMap,0);
   m_bFormatMap2=pApp->GetProfileInt(RegKeySettings,RegKeyFormatMap2,0);
   m_bFormatPlt=pApp->GetProfileInt(RegKeySettings,RegKeyFormatPlt,0);
   m_bFormatRpt=pApp->GetProfileInt(RegKeySettings,RegKeyFormatRpt,0);
   m_bFormatSum=pApp->GetProfileInt(RegKeySettings,RegKeyFormatSum,0);
   m_bFormatLog=pApp->GetProfileInt(RegKeySettings,RegKeyFormatLog,0);
   m_bFormatCvs=pApp->GetProfileInt(RegKeySettings,RegKeyFormatCvs,0);

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CEttoolPlusDlg::~CEttoolPlusDlg()
{
   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileString(RegKeySettings,RegKeyScriptFile,m_sScriptFolder);
   pApp->WriteProfileString(RegKeySettings,RegKeyInputFolder,m_sInputFolder);
   pApp->WriteProfileString(RegKeySettings,RegKeyInputFolderFileFilter,m_sInputFolderFileFilter);
   pApp->WriteProfileString(RegKeySettings,RegKeyOutputFolder,m_sOutputFolder);
   pApp->WriteProfileString(RegKeySettings,RegKeyNumberFormat,m_sNumberFormat);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatDat,m_bFormatDat);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatDat2,m_bFormatDat2);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatLot,m_bFormatLot);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatLot2,m_bFormatLot2);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatLot3,m_bFormatLot3);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatLot4,m_bFormatLot4);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatMap,m_bFormatMap);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatMap2,m_bFormatMap2);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatPlt,m_bFormatPlt);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatRpt,m_bFormatRpt);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatSum,m_bFormatSum);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatLog,m_bFormatLog);
   pApp->WriteProfileInt(RegKeySettings,RegKeyFormatCvs,m_bFormatCvs);
}

void CEttoolPlusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEttoolPlusDlg)
	DDX_Control(pDX, ID_SPLIT, m_SplitListBox);
	DDX_Check(pDX, ID_CB_DAT, m_bFormatDat);
	DDX_Check(pDX, ID_CB_DAT2, m_bFormatDat2);
	DDX_Check(pDX, ID_CB_LOG, m_bFormatLog);
	DDX_Check(pDX, ID_CB_LOT, m_bFormatLot);
	DDX_Check(pDX, ID_CB_LOT2, m_bFormatLot2);
	DDX_Check(pDX, ID_CB_LOT3, m_bFormatLot3);
	DDX_Check(pDX, ID_CB_LOT4, m_bFormatLot4);
	DDX_Check(pDX, ID_CB_MAP, m_bFormatMap);
	DDX_Check(pDX, ID_CB_MAP2, m_bFormatMap2);
	DDX_Check(pDX, ID_CB_PLT, m_bFormatPlt);
	DDX_Check(pDX, ID_CB_RPT, m_bFormatRpt);
	DDX_Text(pDX, ID_SCRIPTFILE, m_sScriptFolder);
	DDX_CBString(pDX, ID_AGGREGATION, m_sAggregation);
	DDX_Text(pDX, ID_INPUTFOLDER, m_sInputFolder);
	DDX_Text(pDX, ID_OUTPUTFOLDER, m_sOutputFolder);
	DDX_Text(pDX, ID_INPUTFOLDER_FILEFILTER, m_sInputFolderFileFilter);
	DDV_MaxChars(pDX, m_sInputFolderFileFilter, 16);
	DDX_CBString(pDX, ID_NUMBER_FORMAT, m_sNumberFormat);
	DDX_Check(pDX, ID_CB_SUM, m_bFormatSum);
	DDX_Text(pDX, ID_STDOUT, m_sStdout);
	DDX_Check(pDX, ID_CB_CVS, m_bFormatCvs);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEttoolPlusDlg, CDialog)
	//{{AFX_MSG_MAP(CEttoolPlusDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_ENVIRONMENT, OnEnvironment)
	ON_BN_CLICKED(ID_EXECUTE, OnExecute)
	ON_BN_CLICKED(ID_SCRIPTFILE_BROWSER, OnScriptBrowser)
	ON_BN_CLICKED(ID_INPUTFOLDER_BROWSER, OnInputfolderBrowser)
	ON_BN_CLICKED(ID_OUTPUTFOLDER_BROWSER, OnOutputfolderBrowser)
	ON_BN_CLICKED(ID_SCRIPTFILE_EDIT, OnScriptEdit)
	ON_BN_CLICKED(ID_SPLIT_WIZARD, OnSplitWizard)
	ON_CBN_EDITCHANGE(ID_NUMBER_FORMAT, OnEditchangeNumberFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEttoolPlusDlg message handlers

BOOL CEttoolPlusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

   SetGroupNamesInTheOtherScript(m_sScriptFolder);
   m_SplitListBox.AddString("< All");
   m_SplitListBox.AddString("*");

   //((CComboBox*)GetDlgItem(ID_NUMBER_FORMAT))->SetCurSel(0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEttoolPlusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEttoolPlusDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEttoolPlusDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEttoolPlusDlg::OnEnvironment() 
{
	// TODO: Add your control notification handler code here
	CEttoolAmbienceDlg Dlg;
   Dlg.DoModal();
}

void CEttoolPlusDlg::OnExecute() 
{
	// TODO: Add your control notification handler code here

   if (!UpdateData(TRUE)) return;

	CWinApp* pApp=AfxGetApp();
   CString sEttoolPath=pApp->GetProfileString(RegKeySettings,RegKeyEttoolFile);
   CString sM4Path=pApp->GetProfileString(RegKeySettings,RegKeyM4File);

   if (!DoesFileExist(sEttoolPath)) {
      MessageBox("Warning, Enroll a path of ettool.exe properly !",NULL,MB_ICONWARNING);
      CEttoolPlusDlg::OnEnvironment();
      return;
   }
   if (!DoesFileExist(sM4Path)) {
      MessageBox("Warning, Enroll a proper path of M4.exe !",NULL,MB_ICONWARNING);
      CEttoolPlusDlg::OnEnvironment();
      return;
   }
   if (!DoesFileExist(m_sScriptFolder)) {
      MessageBox("Warning, Put down a eligible The-Other-Script !!",NULL,MB_ICONWARNING);
      return;
   }
   if (m_sAggregation.IsEmpty()) {
      MessageBox("Warning, Group of the other script is missed !",NULL,MB_ICONWARNING);
      return;
   }
   if (m_sInputFolder.IsEmpty()) {
      MessageBox("Warning, Input folder is not registered !",NULL,MB_ICONWARNING);
      return;
   }
   if (m_sInputFolderFileFilter.IsEmpty()) {
      m_sInputFolderFileFilter="*";
   }
   if (!m_SplitListBox.GetCount()) {
      MessageBox("Warning, Split list box is empty !",NULL,MB_ICONWARNING);
      return;
   }
   if (m_sOutputFolder.IsEmpty()) {
      MessageBox("Warning, Output folder is not enrolled !",NULL,MB_ICONWARNING);
      return;
   }
   if (m_sNumberFormat.IsEmpty() ||
      m_sNumberFormat[0]!='%') {
      ((CComboBox*)GetDlgItem(ID_NUMBER_FORMAT))->SetCurSel(0);
   }
   if (!(m_bFormatDat|m_bFormatDat2|
         m_bFormatLot|m_bFormatLot2|m_bFormatLot3|m_bFormatLot4|
         m_bFormatMap|m_bFormatMap2|
         m_bFormatPlt|m_bFormatRpt|m_bFormatSum|m_bFormatLog|m_bFormatCvs)) {
      MessageBox(
         "Warning, You are so clumsy that you did not choose output format at all !",
         NULL,MB_ICONWARNING);
      return;
   }
   m_sStdout.Empty();
   
   UpdateData(FALSE);   
   GetDlgItem(ID_STDOUT)->RedrawWindow();

   CString sSplit(""),sReturn,sTemp;
   for (int nIndex=0;nIndex<m_SplitListBox.GetCount();nIndex++) {
      m_SplitListBox.GetText(nIndex,sReturn);
      if (sReturn[0]=='<') {
         sReturn.Delete(0);
         sReturn.TrimLeft();
         sReturn.TrimRight();
         sReturn.Replace(" ","_");
         sSplit+=" +\r\n";
         sTemp.Format("g.split=%s g.wf=",sReturn);
         sSplit+=sTemp;
      } else {
         sSplit+=",";
         sSplit+=sReturn;
      }
   }
   sSplit.Replace("=,","=");
   sSplit.Delete(0,2);
   sSplit.TrimLeft();
   sSplit.TrimRight();

   CString sCheckBoxes("");
   if (m_bFormatDat) sCheckBoxes+="|dat";
   if (m_bFormatDat2) sCheckBoxes+="|dat2";
   if (m_bFormatLot) sCheckBoxes+="|lot";
   if (m_bFormatLot2) sCheckBoxes+="|lot2";
   if (m_bFormatLot3) sCheckBoxes+="|lot3";
   if (m_bFormatLot4) sCheckBoxes+="|lot4";
   if (m_bFormatMap) sCheckBoxes+="|map";
   if (m_bFormatMap2) sCheckBoxes+="|map2";
   if (m_bFormatPlt) sCheckBoxes+="|plt";
   if (m_bFormatRpt) sCheckBoxes+="|rpt";
   if (m_bFormatSum) sCheckBoxes+="|sum2";
   if (m_bFormatLog) sCheckBoxes+="|log";
   if (m_bFormatCvs) sCheckBoxes+="|cvs";
   sCheckBoxes.Delete(0);

   const char *qFormat=
      "# Created by shik96@samsung.co.kr .... 2001.02/L18PA \r\n"
      "# Modified by ... \r\n"
      "# \r\n"
      "include(%s) \r\n"
      "# \r\n"
      "define(WAFER_SPLIT,`` \r\n"
      "%s \r\n"
      "'') \r\n"
      "define(myPrint, `` \r\n"
      "group g.name=$1 g.data=$1 + $2 print p.group=$1 p.mode=$3 p.fmt=%s \r\n"
      "'') \r\n"
      "Pstart \r\n"
      "   open o.name=L18 +\r\n"
      "        o.workdir=%s o.wf=%s +\r\n"
      "        o.outdir=%s \r\n"
      "   myPrint(%s,WAFER_SPLIT,%s) \r\n"
      "Pend";
   CString sScript;
   sScript.Format(
      qFormat,
      m_sScriptFolder,sSplit,m_sNumberFormat,
      m_sInputFolder,m_sInputFolderFileFilter,m_sOutputFolder,
      m_sAggregation,sCheckBoxes);

   CString sTemporaryFile="EttoolPlus.scr";
   char qBuffer[1024];
   int nBufferLength=sizeof(qBuffer);
   GetTempPath(nBufferLength,qBuffer);
   sTemporaryFile.Insert(0,qBuffer);
   remove((LPCTSTR)sTemporaryFile);
   CFile File;
   File.Open(sTemporaryFile,CFile::modeCreate|CFile::modeWrite);
   File.WriteHuge(sScript,sScript.GetLength());
   File.Close();

   CEttoolPlusDlg::Run(sEttoolPath,sTemporaryFile);

   ((CEdit*)GetDlgItem(ID_STDOUT))->SetWindowText(m_sStdout);
}

void CEttoolPlusDlg::OnCancel()
{
	// TODO: Add extra cleanup here

   UpdateData(TRUE);
	CDialog::OnCancel();
}

void CEttoolPlusDlg::OnScriptBrowser() 
{
	// TODO: Add your control notification handler code here

   if (!m_pFileFolderTreeSelectionDialog) return;
   UpdateData(TRUE);
   if (!m_sScriptFolder.IsEmpty()) {
      CString sPath=m_sScriptFolder;
      int nPos=sPath.ReverseFind('\\');
      if (nPos!=-1) {
         sPath.Delete(nPos,sPath.GetLength()-nPos);
         SetCurrentDirectory(sPath);
      }
   }
   m_pFileFolderTreeSelectionDialog->SetFolderSelectionMode(FALSE);
   m_pFileFolderTreeSelectionDialog->DoDialog();
   char *pPath;
   m_pFileFolderTreeSelectionDialog->GetFilePath((unsigned short**)&pPath);
   if (pPath) {
      m_sScriptFolder=pPath;
      ::SysFreeString((unsigned short*)pPath);
   }
	UpdateData(FALSE);

   SetGroupNamesInTheOtherScript(m_sScriptFolder);
}

void CEttoolPlusDlg::OnInputfolderBrowser() 
{
	// TODO: Add your control notification handler code here

   if (!m_pFileFolderTreeSelectionDialog) return;
   UpdateData(TRUE);
   if (!m_sInputFolder.IsEmpty()) {
      SetCurrentDirectory(m_sInputFolder);
   }
   m_pFileFolderTreeSelectionDialog->SetFolderSelectionMode(TRUE);
   m_pFileFolderTreeSelectionDialog->DoDialog();
   char *pPath;
   m_pFileFolderTreeSelectionDialog->GetFolderPath((unsigned short**)&pPath);
   if (pPath) {
      m_sInputFolder=pPath;
      ::SysFreeString((unsigned short*)pPath);
   }
	UpdateData(FALSE);
	
}

void CEttoolPlusDlg::OnOutputfolderBrowser() 
{
	// TODO: Add your control notification handler code here

   if (!m_pFileFolderTreeSelectionDialog) return;
   UpdateData(TRUE);
   if (!m_sOutputFolder.IsEmpty()) {
      SetCurrentDirectory(m_sOutputFolder);
   }
   m_pFileFolderTreeSelectionDialog->SetFolderSelectionMode(TRUE);
   m_pFileFolderTreeSelectionDialog->DoDialog();
   char *pPath;
   m_pFileFolderTreeSelectionDialog->GetFolderPath((unsigned short**)&pPath);
   if (pPath) {
      m_sOutputFolder=pPath;
      ::SysFreeString((unsigned short*)pPath);
   }
	UpdateData(FALSE);
	
}

void CEttoolPlusDlg::OnScriptEdit() 
{
	// TODO: Add your control notification handler code here

   UpdateData(TRUE);
   if (m_sScriptFolder.IsEmpty()) return;
   CWinApp *pApp=AfxGetApp();
   CString sPath=pApp->GetProfileString(RegKeySettings,RegKeyEditorFile);
   if (sPath.IsEmpty()) {
      AfxMessageBox(_T("외부 Editor(Viewer) 실행파일을 먼저 선택하세요."),MB_ICONEXCLAMATION);
      CEttoolPlusDlg::OnEnvironment();
      return;
   }
   sPath+=" \""+m_sScriptFolder+"\"";
   WinExec((LPCTSTR)sPath,SW_SHOWDEFAULT);
}

BOOL CEttoolPlusDlg::DoesFileExist(const char *pFile)
{
   if (!pFile || !strlen(pFile)) return FALSE;
   return (GetFileAttributes(pFile)!=0xFFFFFFFF);
}

void CEttoolPlusDlg::SetGroupNamesInTheOtherScript(const char *pFile)
{   
   CComboBox *pBox=(CComboBox*)GetDlgItem(ID_AGGREGATION);
   pBox->EnableWindow(FALSE);
   if (!DoesFileExist(pFile)) return;

   CFile File;
   File.Open(pFile,CFile::modeRead);
   int nBuffer=File.GetLength();
   char *pBuffer=new char[nBuffer];
   File.ReadHuge(pBuffer,nBuffer);
   File.Close();
   CToken Token(pBuffer,"\n\r");
   delete pBuffer;
   int bFound=FALSE;
   CString String(""),sTemp;
   while (Token.IsNext()) {
      sTemp=Token.GetNextToken();
      sTemp.TrimLeft();
      if (sTemp.IsEmpty()) continue;
      if (sTemp[0]=='#' || sTemp[0]=='!') continue;
      if (!bFound) {
         if (!sTemp.CompareNoCase("Dstart")) {
            bFound=TRUE;
            continue;
         }
      } else {
         if (!sTemp.CompareNoCase("Dend")) break;
         String+=sTemp;
      }
   }
   String.Replace(" ","");
   String.Replace('(','\n');
   String.Replace(')','\n');
   String.Replace('{','\n');
   String.Replace('}','\n');
   Token.operator=(String);
   Token.SetDelimiter("\n");
   pBox->ResetContent();
   while (Token.IsNext()) {
      sTemp=Token.GetNextToken();
      if (sTemp.IsEmpty()) continue;
      if (sTemp[sTemp.GetLength()-1]=='=') {
         sTemp.TrimRight("=");
         pBox->AddString(sTemp);
      }
   }
   pBox->SetCurSel(0);
   pBox->EnableWindow(TRUE);
}

void CEttoolPlusDlg::OnSplitWizard() 
{
	// TODO: Add your control notification handler code here

   CString sList(""),sReturn;

   int nCount=m_SplitListBox.GetCount();
   for (int nIndex=0;nIndex<nCount;nIndex++) {
      m_SplitListBox.GetText(nIndex,sReturn);
      if (sReturn[0]!='<') {
         sList+=m_sInputFolder+"\\";
      }
      sList+=sReturn;
      sList+="\n";
   }

	CGargamelSplitFrameDialog Dialog(this);
   Dialog.m_sStream=sList;
   Dialog.m_sDirectory=m_sInputFolder;
   int nResult=Dialog.DoModal();
   if (nResult!=IDOK) return;

   sReturn=Dialog.m_sStream;
   if (sReturn.IsEmpty()) {
      m_SplitListBox.ResetContent();
      m_SplitListBox.AddString("< All");
      m_SplitListBox.AddString("*");
      return;
   }

   CString sTemp;
   int nFolderLength=m_sInputFolder.GetLength();
   m_SplitListBox.ResetContent();
   CToken Token(sReturn,"\r\n");
   while (Token.IsNext()) {
      sReturn=Token.GetNextToken();
      if (sReturn.IsEmpty()) continue;
      if (sReturn[0]!='<') {
         sTemp=sReturn.Left(nFolderLength);
         if (sTemp.CompareNoCase(m_sInputFolder)) {
            MessageBox(
               "Warning, Your files did not lie in the same input folder !",
               NULL,MB_ICONWARNING);
            return;
         }
         sReturn.Delete(0,nFolderLength+1);
      }
      m_SplitListBox.AddString(sReturn);
   }
}

void CEttoolPlusDlg::OnEditchangeNumberFormat() 
{
	// TODO: Add your control notification handler code here

   ((CComboBox*)GetDlgItem(ID_NUMBER_FORMAT))->GetWindowText(m_sNumberFormat);
}

void CEttoolPlusDlg::Run(const char *qEttoolPath,const char*qScriptPath)
{
   CString sCommand;
   sCommand.Format("\"%s\" \"%s\"",qEttoolPath,qScriptPath);

   CreateProcessWithRedirectedIO(sCommand,m_sStdout,TRUE);
   if (m_sStdout.IsEmpty()) {
      m_sStdout=":< Alert, Error have happened...";
   } else {
      m_sStdout.TrimLeft();
      m_sStdout.Insert(0,":) ");
   }
}

