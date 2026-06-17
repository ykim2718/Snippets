// GrPlotWizard.cpp : implementation file
//

#include "stdafx.h"
#include "Grapher.h"
#include "GrPlotWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include <direct.h>
#include <math.h>
#include "GrapherDoc.h"
#include "GrapherView.h"
#include "FileDialogEx.h"

#include "plotse.h"
#include "AnyfindClient.h" // 2001.0411
#include "Token.h"

extern "C" {

char *rskipwhite(char **p);
char *skipblack(char **p);
char *rskipblack(char **p);
char *strcommon(const char* first,const char* second,int nStart);

}

CString GargamelMessageBoxText(_T(""));
void GargamelMessageBox()
{
   if (GargamelMessageBoxText.IsEmpty()) return;
   AfxMessageBox((LPCTSTR)GargamelMessageBoxText,MB_ICONINFORMATION);
}

static char *qMessageBoxCaption="Gr (Plot) Wizard";

/////////////////////////////////////////////////////////////////////////////
// CGrPlotWizard dialog

CGrPlotWizard::CGrPlotWizard(CWnd* pParent /*=NULL*/)
	: CDialog(CGrPlotWizard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrPlotWizard)
	m_sMapFile = _T("");
	m_bCompositeMap = FALSE;
	//}}AFX_DATA_INIT
   CWinApp* pApp=AfxGetApp();

   m_sPatternFile=_T("");
   m_sSplitFile=_T("");
   m_sMapFile=pApp->GetProfileString(RegKeySettings,RegKeyPlotWizardMapFile);
   m_bPlotSeries=FALSE;
   m_nPlotSeries=0;
   m_bPlotScatter=FALSE;
   m_nPlotScatter=0;
   m_bPlotMap=FALSE;
   m_nPlotMap=0;
   m_nSearchType=0;
   m_nColumnarMatrixType=0;
   m_bNumericAlias=0;
   m_nPostProcessType=0;
   m_bCompositeMap=FALSE;
   m_sGargamelTemporaryFile=_T("");
}

CGrPlotWizard::~CGrPlotWizard()
{
   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileString(RegKeySettings,RegKeyPlotWizardMapFile,
      m_sMapFile);
}

void CGrPlotWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrPlotWizard)
	DDX_Control(pDX, ID_GRPLOTWIZARD_SPLITFILE, m_SplitFile);
	DDX_Control(pDX, ID_GRPLOTWIZARD_PATTERNFILE, m_PatternFile);
	DDX_Control(pDX, ID_GRPLOTWIZARD_POSTPROCESSTYPE, m_PostProcessType);
	DDX_Text(pDX, ID_GRPLOTWIZARD_MAP01_EDIT, m_sMapFile);
	DDV_MaxChars(pDX, m_sMapFile, 128);
	DDX_Check(pDX, ID_GRPLOTWIZARD_MAP_COMPOSITE, m_bCompositeMap);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrPlotWizard, CDialog)
	//{{AFX_MSG_MAP(CGrPlotWizard)
	ON_BN_CLICKED(ID_GRPLOTWIZARD_READPATTERN, OnGrplotwizardReadPattern)
	ON_BN_CLICKED(ID_GRPLOTWIZARD_DRAW, OnGrplotwizardDraw)
	ON_BN_CLICKED(ID_GRPLOTWIZARD_READSPLIT, OnGrplotwizardReadsplit)
	ON_CBN_SELCHANGE(ID_GRPLOTWIZARD_PATTERNFILE, OnChangeGrplotwizardPatternfile)
	ON_CBN_SELCHANGE(ID_GRPLOTWIZARD_SPLITFILE, OnChangeGrplotwizardSplitfile)
	ON_BN_CLICKED(ID_GRPLOTWIZARD_EXECPATTERN, OnGrplotwizardExecpattern)
	ON_BN_CLICKED(ID_GRPLOTWIZARD_EXECSPLIT, OnGrplotwizardExecsplit)
	ON_BN_CLICKED(ID_GRPLOTWIZARD_MAP01_READ, OnGrplotwizardMap01Read)
	ON_CBN_EDITCHANGE(ID_GRPLOTWIZARD_PATTERNFILE, OnEditchangeGrplotwizardPatternfile)
	ON_CBN_EDITCHANGE(ID_GRPLOTWIZARD_SPLITFILE, OnEditchangeGrplotwizardSplitfile)
	ON_BN_CLICKED(ID_GRPLOTWIZARD_MAP01_CREATE, OnGrplotwizardMap01Create)
	ON_BN_CLICKED(ID_GRPLOTWIZARD_WRITESCRIPT, OnGrplotwizardWritescript)
	ON_CBN_DROPDOWN(ID_GRPLOTWIZARD_SPLITFILE, OnDropdownGrplotwizardSplitfile)
	ON_CBN_DROPDOWN(ID_GRPLOTWIZARD_PATTERNFILE, OnDropdownGrplotwizardPatternfile)
	ON_BN_CLICKED(ID_GRPLOTWIZARD_MAP_COMPOSITE, OnGrplotwizardMapComposite)
	//}}AFX_MSG_MAP
   ON_CONTROL_RANGE(BN_CLICKED,ID_GRPLOTWIZARD_XSERIES,ID_GRPLOTWIZARD_MAP02,
                    OnGrplotwizardRadioButtonHandler)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrPlotWizard message handlers

void CGrPlotWizard::ComboBoxSetDroppedWidth(CComboBox *pBox)
{
   int nCount=pBox->GetCount();
   if (nCount<=0) return;
   CString sLongest,sReturn;
   pBox->GetLBText(0,sLongest);
   for (int nIndex=1;nIndex<nCount;nIndex++) {
      pBox->GetLBText(nIndex,sReturn);
      if (sReturn.GetLength()>sLongest.GetLength()) sLongest=sReturn;
   }
   CDC *pDC=pBox->GetWindowDC();
   CSize Size=pDC->GetTextExtent(sLongest);
   int nNewWidth=(int)Size.cx; // -GetSystemMetrics(SM_CXVSCROLL);
   int nDroppedWidth=pBox->GetDroppedWidth();
   pBox->SetDroppedWidth(max(nNewWidth,nDroppedWidth));
}

void CGrPlotWizard::ComboBoxAddString(CComboBox *pBox, const CString &String)
{
   int nFound;
   nFound=pBox->FindString(-1,String);
   while (nFound!=CB_ERR) {
      nFound=pBox->FindString(-1,String);
      pBox->DeleteString(nFound);
   }
   pBox->AddString(String);
}

void CGrPlotWizard::OnDropdownGrplotwizardPatternfile() 
{
	// TODO: Add your control notification handler code here

   CGrPlotWizard::ComboBoxSetDroppedWidth(&m_PatternFile);
}

void CGrPlotWizard::OnDropdownGrplotwizardSplitfile() 
{
	// TODO: Add your control notification handler code here

   CGrPlotWizard::ComboBoxSetDroppedWidth(&m_SplitFile);
}

BOOL CGrPlotWizard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   MyUpdateDataFalse();
   CGrPlotWizard::SetCheckButtons();
   CGrPlotWizard::ResetViewportCount();

   int nTable;
   char **pTable;
   GargamelGetPostProcessType(&pTable,&nTable);
   for (int nIndex=0;nIndex<nTable;nIndex++) {
      m_PostProcessType.AddString(pTable[nIndex]);
   }
   m_PostProcessType.SetCurSel(0);

   if (m_PatternFile.GetCount()>0) {
      m_PatternFile.SetCurSel(0);
      m_PatternFile.GetLBText(0,m_sPatternFile);
   }
   if (m_SplitFile.GetCount()>0) {
      m_SplitFile.SetCurSel(0);
      m_SplitFile.GetLBText(0,m_sSplitFile);
   }

   //
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CGrPlotWizard::GetGrTemporaryFileName( int nFileType )
// nFileType=0 (=FIELTYPE_GR)   <- *.gr  <- default
// nFileType=1 (=FIELTYPE_GRXY) <- *.grxy
// nFileType=2 (=FIELTYPE_DAT)  <- *.dat
{
   #define GARGAMEL_TEMPORARY_GR_FILE "grTemporary%d.gr"
   CString sGrTemporary,sTitle;
   int nGrTemporary,nGrWizardJobID=1;

   sGrTemporary=GARGAMEL_TEMPORARY_GR_FILE;
   nGrTemporary=sGrTemporary.ReverseFind('%');
   sGrTemporary.Delete(nGrTemporary,sGrTemporary.GetLength()-nGrTemporary);
   CMDIFrameWnd *pFrame=(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
   CMDIChildWnd *pChildFrame=(CMDIChildWnd*)pFrame->GetActiveFrame();
   CDocument *pDoc=pChildFrame->GetActiveDocument();
   if (pDoc) {
      CDocTemplate* pDocTemplate=pDoc->GetDocTemplate();
      POSITION xPosition=pDocTemplate->GetFirstDocPosition();
      while (xPosition &&(pDoc=pDocTemplate->GetNextDoc(xPosition))) {
         POSITION xPos=pDoc->GetFirstViewPosition();
         CGrapherView* pView=(CGrapherView*)pDoc->GetNextView(xPos);
         sTitle=pDoc->GetTitle();
         if (!sGrTemporary.Compare(sTitle.Left(nGrTemporary))) {
            sTitle.Delete(0,nGrTemporary);
            nGrWizardJobID=max(nGrWizardJobID,atoi(sTitle)+1);
         }
      }
   }

   const int nBufferLength=1024;
   char qBuffer[nBufferLength];
   GetTempPath(nBufferLength,qBuffer);

   sGrTemporary.Format(GARGAMEL_TEMPORARY_GR_FILE,nGrWizardJobID);
   sGrTemporary.Insert(0,qBuffer);

   int nPos;
   switch (nFileType) { //2001.0405
   case FILETYPE_EXT_GR : break;
   case FILETYPE_EXT_GRXY :
      sGrTemporary.MakeReverse();
      nPos=sGrTemporary.Find('.');
      sGrTemporary.Delete(0,nPos+1);
      sGrTemporary.MakeReverse();
      sGrTemporary+=".grxy";
      break;
   case FILETYPE_EXT_DAT :
      sGrTemporary.MakeReverse();
      nPos=sGrTemporary.Find('.');
      sGrTemporary.Delete(0,nPos+1);
      sGrTemporary.MakeReverse();
      sGrTemporary+="-001.dat"; // This must coincide with
      break;                    // GetTemporaryDataFileName() in plot.c.
   }

   return sGrTemporary;
}

void CGrPlotWizard::OnGrplotwizardExecpattern() 
{
	// TODO: Add your control notification handler code here
   CGrapherApp *pApp=(CGrapherApp*)AfxGetApp();
	CString sPath=pApp->GetPathOfGargamel();
   if (sPath.IsEmpty()) return;
   CString sFile(_T(""));
   m_PatternFile.GetWindowText(sFile);
   if (sFile.IsEmpty()) {
      WinExec(sPath,SW_SHOWDEFAULT);
      return;
   }
   sPath.Insert(0,"\"");
   sPath+="\"";
   sFile.Insert(0,"\"");
   sFile+="\"";
   WinExec(sPath+" "+sFile,SW_SHOWDEFAULT);
}

void CGrPlotWizard::OnGrplotwizardExecsplit() 
{
	// TODO: Add your control notification handler code here
	CGrapherApp *pApp=(CGrapherApp*)AfxGetApp();
	CString sPath=pApp->GetPathOfGargamel();
   if (sPath.IsEmpty()) return;
   CString sFile(_T(""));
   m_SplitFile.GetWindowText(sFile);
   if (sFile.IsEmpty()) {
      WinExec(sPath,SW_SHOWDEFAULT);
      return;
   }
   //if (!m_SplitFile.GetCount()) return;
   //m_SplitFile.GetLBText(0,sFile);
   sPath.Insert(0,"\"");
   sPath+="\"";
   sFile.Insert(0,"\"");
   sFile+="\"";
   WinExec(sPath+" "+sFile,SW_SHOWDEFAULT);
}

void CGrPlotWizard::OnGrplotwizardReadPattern() 
{
	// TODO: Add your control notification handler code here

   CString sDirectory;
   if (m_PatternFile.GetCurSel()>=0)
      m_PatternFile.GetLBText(0,sDirectory);
   else
      sDirectory.Empty();
   if (!sDirectory.IsEmpty()) {
      int nPos=sDirectory.ReverseFind('\\');
      sDirectory.Delete(nPos,sDirectory.GetLength()-nPos);
   } else {
      char qBuffer[1024+1];
      GetCurrentDirectory(1024,qBuffer);
      sDirectory=qBuffer;
   }
	char qFilter[]=
      "Gargamel Script (Input) Files (*.in)|*.in|"
      "Script Files (*.scr;*.txt)|*.scr;*.txt|"
      "All Files (*.*)|*.*||";
   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      qFilter,NULL);
   fDialog.m_ofn.lpstrInitialDir=(LPCTSTR)sDirectory;
   int nResponse=fDialog.DoModal();
	if (nResponse!=IDOK) return;
   CString sFile=fDialog.GetPathName();
   m_PatternFile.SetWindowText(sFile);
   CGrPlotWizard::OnChangeGrplotwizardPatternfile();
}

void CGrPlotWizard::OnGrplotwizardReadsplit() 
{
	// TODO: Add your control notification handler code here

   CString sDirectory;
   if (m_SplitFile.GetCurSel()>=0)
      m_SplitFile.GetLBText(0,sDirectory);
   else
      sDirectory.Empty();
   if (sDirectory) {
      int nPos=sDirectory.ReverseFind('\\');
      sDirectory.Delete(nPos,sDirectory.GetLength()-nPos);
   } else {
      char qBuffer[1024+1];
      GetCurrentDirectory(1024,qBuffer);
      sDirectory=qBuffer;
   }
	char qFilter[]=
      "Gargamel Script (Input) Files (*.in)|*.in|"
      "Script Files (*.scr;*.txt)|*.scr;*.txt|"
      "All Files (*.*)|*.*||";
   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      qFilter,NULL);
   fDialog.m_ofn.lpstrInitialDir=(LPCTSTR)sDirectory;
   int nResponse=fDialog.DoModal();
	if (nResponse!=IDOK) return;
   CString sFile=fDialog.GetPathName();
   m_SplitFile.SetWindowText(sFile);
   CGrPlotWizard::OnChangeGrplotwizardSplitfile();
}

void CGrPlotWizard::OnGrplotwizardWritescript() 
{
	// TODO: Add your control notification handler code here

   MessageBox("Don't be trying. Under constrution !");
}

void CGrPlotWizard::OnGrplotwizardMap01Read() 
{
	// TODO: Add your control notification handler code here
   char qFilter[]=
      "XY Files (*.grxy)|*.grxy|"
      "All Files (*.*)|*.*||";
   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      qFilter,NULL);
   CString sPath=m_sMapFile;
   if (!sPath.IsEmpty()) {
      int nPos=sPath.ReverseFind('\\');
      if (nPos!=-1) {
         //fDialog.m_ofn.lpstrFile=(LPCTSTR)(sPath.Mid(nPos));
         sPath.Delete(nPos,sPath.GetLength()-nPos);
         fDialog.m_ofn.lpstrInitialDir=(LPCTSTR)sPath;
      }
   }
   int nResponse=fDialog.DoModal();
	if (nResponse!=IDOK) return;
   CString sFile=fDialog.GetPathName();
   m_sMapFile=sFile;
   UpdateData(FALSE);
}

void CGrPlotWizard::OnGrplotwizardMap01Create() 
{
	// TODO: Add your control notification handler code here
   CString sDirectory;
   if (m_PatternFile.GetCurSel()>=0)
      m_PatternFile.GetLBText(0,sDirectory);
   else
      sDirectory.Empty();
   if (!sDirectory.IsEmpty()) {
      int nPos=sDirectory.ReverseFind('\\');
      sDirectory.Delete(nPos,sDirectory.GetLength()-nPos);
   } else {
      char qBuffer[1024+1];
      GetCurrentDirectory(1024,qBuffer);
      sDirectory=qBuffer;
   }
   CFileDialog fOpenDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      "All Files (*.*)|*.*||",NULL);
   fOpenDialog.m_ofn.lpstrInitialDir=(LPCTSTR)sDirectory;
   CString Title;
   Title.Format(" Open ET File ... (%s)",(LPCTSTR)sDirectory);
   fOpenDialog.m_ofn.lpstrTitle=Title;
   int nResponse=fOpenDialog.DoModal();
	if (nResponse!=IDOK) return;
   CString sInFile=fOpenDialog.GetPathName();

   CFileDialog fSaveDialog(FALSE,"grxy",sInFile+".grxy",
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,
      "Grxy Files (*.grxy)|*.grxy||",NULL);
   fOpenDialog.m_ofn.lpstrInitialDir=(LPCTSTR)sDirectory;
   Title.Format(" Save Grxy File As ... (%s)",(LPCTSTR)sDirectory);
   fSaveDialog.m_ofn.lpstrTitle=Title;
   nResponse=fSaveDialog.DoModal();
	if (nResponse!=IDOK) return;
   CString sOutFile=fSaveDialog.GetPathName();

   nResponse=CreateXYFileFromKJTETFormat((LPCTSTR)sInFile,(LPCTSTR)sOutFile);
   if (nResponse) {
      m_sMapFile=sOutFile;
      UpdateData(FALSE);
   }
}

void CGrPlotWizard::OnChangeGrplotwizardPatternfile() 
{
   CString sReturn;
   int nIndex=m_PatternFile.GetCurSel();
   if (nIndex>0) {
      m_PatternFile.GetLBText(nIndex,sReturn);
      m_PatternFile.DeleteString(nIndex);
      m_PatternFile.InsertString(0,sReturn);
   } else {
      m_PatternFile.GetWindowText(sReturn);
      if (!sReturn.IsEmpty()) {
         nIndex=m_PatternFile.FindStringExact(-1,sReturn);
         if (nIndex>0) {
            m_PatternFile.DeleteString(nIndex);
            m_PatternFile.InsertString(0,sReturn);
         } else if (nIndex<0) {
            m_PatternFile.InsertString(0,sReturn);
         }
      } else {
         if (!m_PatternFile.GetCount())
            return;
      }
   }
   m_PatternFile.SetCurSel(0);
   m_PatternFile.GetLBText(0,sReturn);
   if (sReturn.Compare(m_sPatternFile)) {
      CGrPlotWizard::OnEditchangeGrplotwizardPatternfile();
   }
}

void CGrPlotWizard::OnChangeGrplotwizardSplitfile() 
{
   CString sReturn;
   int nIndex=m_SplitFile.GetCurSel();
   if (nIndex>0) {
      m_SplitFile.GetLBText(nIndex,sReturn);
      m_SplitFile.DeleteString(nIndex);
      m_SplitFile.InsertString(0,sReturn);
   } else {
      m_SplitFile.GetWindowText(sReturn);
      if (!sReturn.IsEmpty()) {
         nIndex=m_SplitFile.FindStringExact(-1,sReturn);
         if (nIndex>0) {
            m_SplitFile.DeleteString(nIndex);
            m_SplitFile.InsertString(0,sReturn);
         } else if (nIndex<0) {
            m_SplitFile.InsertString(0,sReturn);
         }
      } else {
         if (!m_SplitFile.GetCount())
            return;
      }
   }
   m_SplitFile.SetCurSel(0);
   m_SplitFile.GetLBText(0,sReturn);
   if (sReturn.Compare(m_sSplitFile)) {
      CGrPlotWizard::OnEditchangeGrplotwizardSplitfile();
   }
}

void CGrPlotWizard::OnEditchangeGrplotwizardPatternfile() 
{
	// TODO: Add your control notification handler code here
	m_nPlotSeries=m_nPlotScatter=m_nPlotMap=0;
   CGrPlotWizard::SetCheckButtons();
	CGrPlotWizard::ResetViewportCount();
}

void CGrPlotWizard::OnEditchangeGrplotwizardSplitfile() 
{
	// TODO: Add your control notification handler code here
	CGrPlotWizard::OnEditchangeGrplotwizardPatternfile();
}


void CGrPlotWizard::OnGrplotwizardMapComposite() 
{
	// TODO: Add your control notification handler code here
	
   int bCheck=((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP_COMPOSITE))->GetCheck();
   if (bCheck) {
      if (!m_PostProcessType.GetCurSel()) {
         MessageBox(
            "Warning, a composite map is not compatible with no After-Searching-Process !",
            qMessageBoxCaption,MB_ICONWARNING);
      }
   }
}

void CGrPlotWizard::SetCheckButtons()
{
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSERIES))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSERIES01))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSERIES02))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER01))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER02))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER03))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER04))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER05))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER06))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER07))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP01))->SetCheck(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP02))->SetCheck(0);
   if (m_bPlotSeries) {
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSERIES))->SetCheck(1);
      if (m_nPlotSeries) ((CButton*)GetDlgItem(m_nPlotSeries))->SetCheck(1);
   } else if (m_bPlotScatter) {
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER))->SetCheck(1);
      if (m_nPlotScatter) ((CButton*)GetDlgItem(m_nPlotScatter))->SetCheck(1);
   } else if (m_bPlotMap) {
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP))->SetCheck(1);
      if (m_nPlotMap) ((CButton*)GetDlgItem(m_nPlotMap))->SetCheck(1);
   }
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSERIES01))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSERIES02))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER01))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER02))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER03))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER04))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER05))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER06))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER07))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP_COMPOSITE))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP01))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP01_EDIT))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP01_CREATE))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP01_READ))->EnableWindow(0);
   ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP02))->EnableWindow(0);
   if (m_bPlotSeries) {
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSERIES01))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSERIES02))->EnableWindow(1);
   } else if (m_bPlotScatter) {
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER01))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER02))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER03))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER04))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER05))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER06))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_XSCATTER07))->EnableWindow(1);
   } else if (m_bPlotMap) {
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP_COMPOSITE))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP01))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP01_EDIT))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP01_CREATE))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP01_READ))->EnableWindow(1);
      ((CButton*)GetDlgItem(ID_GRPLOTWIZARD_MAP02))->EnableWindow(1);
   }
}

void CGrPlotWizard::OnGrplotwizardRadioButtonHandler(UINT nID)
{
   switch (nID) {
   case ID_GRPLOTWIZARD_XSERIES :
      m_bPlotSeries=TRUE;
      m_bPlotScatter=FALSE;
      m_bPlotMap=FALSE;
      break;
   case ID_GRPLOTWIZARD_XSCATTER :
      m_bPlotSeries=FALSE;
	   m_bPlotScatter=TRUE;
      m_bPlotMap=FALSE;
      break;
   case ID_GRPLOTWIZARD_MAP :
      m_bPlotSeries=FALSE;
	   m_bPlotScatter=FALSE;
      m_bPlotMap=TRUE;
      break;
   case ID_GRPLOTWIZARD_XSERIES01 :
   case ID_GRPLOTWIZARD_XSERIES02 :
      m_nPlotSeries=nID;
      break;
   case ID_GRPLOTWIZARD_XSCATTER01 :
   case ID_GRPLOTWIZARD_XSCATTER02 :
   case ID_GRPLOTWIZARD_XSCATTER03 :
   case ID_GRPLOTWIZARD_XSCATTER04 :
   case ID_GRPLOTWIZARD_XSCATTER05 :
   case ID_GRPLOTWIZARD_XSCATTER06 :
   case ID_GRPLOTWIZARD_XSCATTER07 :
      switch (nID) {
      case ID_GRPLOTWIZARD_XSCATTER01 :
      case ID_GRPLOTWIZARD_XSCATTER02 :
      case ID_GRPLOTWIZARD_XSCATTER05 :
      case ID_GRPLOTWIZARD_XSCATTER06 :
      case ID_GRPLOTWIZARD_XSCATTER07 :
         m_PostProcessType.SetCurSel(m_nPostProcessType=0);
         break;
      }
      m_nPlotScatter=nID;
      break;
   case ID_GRPLOTWIZARD_MAP01 :
   case ID_GRPLOTWIZARD_MAP02 :
      m_nPlotMap=nID;
      break;
      break;
   }

   CGrPlotWizard::SetCheckButtons();
}

BOOL CGrPlotWizard::SetViewportCount()
{
   if (!m_nRow || !m_nCol) {
      MessageBox(
         "Warning, you should check out the script file first !",
         qMessageBoxCaption,MB_ICONWARNING);
      return FALSE;
   }
   int nID=-1;
   int nCount=0;
   if (m_bPlotSeries) {
      switch (m_nPlotSeries) {
      case ID_GRPLOTWIZARD_XSERIES01 :
         nID=ID_GRPLOTWIZARD_XSERIES01_COUNT;
         nCount=1;
         break;
      case ID_GRPLOTWIZARD_XSERIES02 :
         nID=ID_GRPLOTWIZARD_XSERIES02_COUNT;
         nCount=1;
         break;
      }
   } else if (m_bPlotScatter) {
      switch (m_nPlotScatter) {
      case ID_GRPLOTWIZARD_XSCATTER01 : /*
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            ASSERT(m_nPattern*m_nSplit==m_nCol); */
         if (m_nColumnarMatrixType) {
            MessageBox(
               "Warning, columnar matrix is not matched to Gaussian plot !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_bNumericAlias) {
            MessageBox(
               "Warning, you can not use numeric pattern alias !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nPattern*m_nSplit!=m_nCol) {
            MessageBox(
               "Warning, keep in mind that m_nPattern*m_nSplit==m_nCol !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         }
         nID=ID_GRPLOTWIZARD_XSCATTER01_COUNT;
         nCount=m_nSplit;
         break;
      case ID_GRPLOTWIZARD_XSCATTER02 : /*
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            ASSERT(m_nPattern*m_nSplit==m_nCol); */
         if (m_nColumnarMatrixType) {
            MessageBox(
               "Warning, columnar matrix is not matched to Gaussian plot !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_bNumericAlias) {
            MessageBox(
               "Warning, you can not use numeric pattern alias !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nPattern*m_nSplit!=m_nCol) {
            MessageBox(
               "Warning, be sure that m_nPattern*m_nSplit==m_nCol !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         }
         nID=ID_GRPLOTWIZARD_XSCATTER02_COUNT;
         nCount=m_nPattern;
         break;
      case ID_GRPLOTWIZARD_XSCATTER03 : /*
            ASSERT(m_nColumnarMatrixType==1);
            ASSERT(m_bNumericAlias==TRUE);
            ASSERT(m_nSplit*m_nColCountPerBlock==m_nCol);
            ASSERT(m_nPattern==m_nRow); */
         if (!m_nColumnarMatrixType) {
            MessageBox(
               "Warning, you chose this after you set columnar matrix !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nColumnarMatrixType!=1) {
            MessageBox(
               "Warning, you can not apply "
               "both nScaleScatter=3 and nColumnarMatrixType!=1.",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (!m_bNumericAlias) {
            MessageBox(
               "Warning, pattern alias string is not numeric !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nSplit*m_nColCountPerBlock!=m_nCol) {
            MessageBox(
               "Warning, be sure that m_nSplit*m_nColCountPerBlock==m_nCol !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nPattern!=m_nRow) {
            MessageBox(
               "Warning, be sure that m_nPattern==m_nRow !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         }
         nID=ID_GRPLOTWIZARD_XSCATTER03_COUNT;
         nCount=1;
         break;
      case ID_GRPLOTWIZARD_XSCATTER04 : /*
            ASSERT(m_nColumnarMatrixType==3);
            ASSERT(m_bNumericAlias==TRUE);
            ASSERT(m_nPattern*m_nColCountPerBlock==m_nCol);
            ASSERT(m_nSplit==m_nRow); */
         if (!m_nColumnarMatrixType) {
            MessageBox(
               "Warning, you chose this after you set columnar matrix !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nColumnarMatrixType!=3) {
            MessageBox(
               "Warning, you can not apply "
               "both nScaleScatter=4 and nColumnarMatrixType!=3.",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (!m_bNumericAlias) {
            MessageBox(
               "Warning, split alias string is not numeric !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nPattern*m_nColCountPerBlock!=m_nCol) {
            MessageBox(
               "Warning, bear in mind that m_nPattern*m_nColCountPerBlock==m_nCol !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nSplit!=m_nRow) {
            MessageBox(
               "Warning, keep in mind that m_nSplit==m_nRow !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         }
         nID=ID_GRPLOTWIZARD_XSCATTER04_COUNT;
         nCount=1;
         break;
      case ID_GRPLOTWIZARD_XSCATTER05 : /*
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE); */
         if (m_nColumnarMatrixType) {
            MessageBox(
               "Warning, you can not apply columnar matrix !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_bNumericAlias) {
            MessageBox(
               "Warning, you can not apply numeric pattern alias !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         }
         nID=ID_GRPLOTWIZARD_XSCATTER05_COUNT;
         nCount=m_nSplit;
         break;
      case ID_GRPLOTWIZARD_XSCATTER06 :
      case ID_GRPLOTWIZARD_XSCATTER07 : /*
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            ASSERT(!(m_nPattern%2||m_nCol%2));
            ASSERT(m_nColCountPerBlock==1); */
         if (m_nColumnarMatrixType) {
            MessageBox(
               "Warning, you can not apply columnar matrix !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_bNumericAlias) {
            MessageBox(
               "Warning, you can not apply numeric pattern alias !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nPattern%2 || m_nCol%2) {
            MessageBox(
               "Warning, Odd count of nPattern || Odd count of nColumn !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nPattern%2 || m_nCol%2) {
            MessageBox(
               "Warning, Odd count of nPattern || Odd count of nColumn !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_nColCountPerBlock!=1) {
            MessageBox(
               "Warning, be kept that m_nColCountPerBlock==1 !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         }
         switch (m_nPlotScatter) {
         case ID_GRPLOTWIZARD_XSCATTER06 :
            nID=ID_GRPLOTWIZARD_XSCATTER06_COUNT;
            //nCount=m_nCol/m_nColCountPerBlock*(int)(m_nPattern/2);
            //nCount=m_nSplit; // 2K.0914
            nCount=(int)m_nCol/2; // 2001.0509
            break;
         case ID_GRPLOTWIZARD_XSCATTER07 :
            nID=ID_GRPLOTWIZARD_XSCATTER07_COUNT;
            nCount=m_nSplit;
            break;
         }
      }
   } else if (m_bPlotMap) {
      switch (m_nPlotMap) {
      case ID_GRPLOTWIZARD_MAP01 :
         ASSERT(m_nColumnarMatrixType==0);
         ASSERT(m_bNumericAlias==FALSE);
         // ASSERT(!m_sMapFile.IsEmpty());
         if (m_sMapFile.IsEmpty()) {
            MessageBox(
               "Warning, you ought to enroll a xy information(map) file first !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         } else if (m_bCompositeMap && !m_nPostProcessType) {
            MessageBox(
               "Warning, you could not draw a map under no After-Searching-Process !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         }
         nID=ID_GRPLOTWIZARD_MAP01_COUNT;
         nCount=m_nCol;
         break;
      case ID_GRPLOTWIZARD_MAP02 :
         ASSERT(m_nColumnarMatrixType==0);
         ASSERT(m_bNumericAlias==FALSE);
         // ASSERT(!m_sSplitFile.IsEmpty());
         if (m_bCompositeMap && !m_nPostProcessType) {
            MessageBox(
               "Warning, you could not draw a map under no After-Searching-Process !",
               qMessageBoxCaption,MB_ICONWARNING);
            return FALSE;
         }
         nID=ID_GRPLOTWIZARD_MAP02_COUNT;
         nCount=m_nCol;
         break;
      }
   }
   if (nID==-1) return FALSE;
   CString sCount;
   sCount.Format("%d",nCount);
   GetDlgItem(nID)->SetWindowText((LPCTSTR)sCount);
   return TRUE;
}

void CGrPlotWizard::ResetViewportCount()
{   
   GetDlgItem(ID_GRPLOTWIZARD_XSERIES01_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_XSERIES02_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_XSCATTER01_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_XSCATTER02_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_XSCATTER03_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_XSCATTER04_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_XSCATTER05_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_XSCATTER06_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_XSCATTER07_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_MAP01_COUNT)->SetWindowText(_T("#"));
   GetDlgItem(ID_GRPLOTWIZARD_MAP02_COUNT)->SetWindowText(_T("#"));
}

int CGrPlotWizard::GetViewportCount()
{
   int nID;
   if (m_bPlotSeries) {
      switch (m_nPlotSeries) {
      case ID_GRPLOTWIZARD_XSERIES01 : nID=ID_GRPLOTWIZARD_XSERIES01_COUNT;break;
      case ID_GRPLOTWIZARD_XSERIES02 : nID=ID_GRPLOTWIZARD_XSERIES02_COUNT;break;
      default: nID=-1;
      }
   } else if (m_bPlotScatter) {
      switch (m_nPlotScatter) {
      case ID_GRPLOTWIZARD_XSCATTER01 : nID=ID_GRPLOTWIZARD_XSCATTER01_COUNT;break;
      case ID_GRPLOTWIZARD_XSCATTER02 : nID=ID_GRPLOTWIZARD_XSCATTER02_COUNT;break;
      case ID_GRPLOTWIZARD_XSCATTER03 : nID=ID_GRPLOTWIZARD_XSCATTER03_COUNT;break;
      case ID_GRPLOTWIZARD_XSCATTER04 : nID=ID_GRPLOTWIZARD_XSCATTER04_COUNT;break;
      case ID_GRPLOTWIZARD_XSCATTER05 : nID=ID_GRPLOTWIZARD_XSCATTER05_COUNT;break;
      case ID_GRPLOTWIZARD_XSCATTER06 : nID=ID_GRPLOTWIZARD_XSCATTER06_COUNT;break;
      case ID_GRPLOTWIZARD_XSCATTER07 : nID=ID_GRPLOTWIZARD_XSCATTER07_COUNT;break;
      default: nID=-1;
      }
   } else if (m_bPlotMap) {
      switch (m_nPlotMap) {
      case ID_GRPLOTWIZARD_MAP01 : nID=ID_GRPLOTWIZARD_MAP01_COUNT;break;
      case ID_GRPLOTWIZARD_MAP02 : nID=ID_GRPLOTWIZARD_MAP02_COUNT;break;
      default: nID=-1;
      }
   } else
      nID=-1;
   if (nID==-1) return 0;
   CString sReturn;
   GetDlgItem(nID)->GetWindowText(sReturn);
   return atoi((LPCTSTR)sReturn);
}

/*
void CGrPlotWizard::DoGargamel() 
{
	// TODO: Add your control notification handler code here
   //
   UpdateData(TRUE);
   if (m_sPatternFile.IsEmpty() || m_sSplitFile.IsEmpty()) {
      MessageBox("Error, empty pattern file or split file !",NULL,MB_ICONERROR);
      return;
   }
   //
   CWinApp *pApp=AfxGetApp();
   CString ExecFile=
      pApp->GetProfileString(RegKeySettings,RegKeyGargamelPath);
   if (ExecFile.IsEmpty()) {
      MessageBox("Error, no registered DEFF !",NULL,MB_ICONERROR);
      return;
   }
   //
   char qBuffer[1024];
   int nBufferLength=sizeof(qBuffer);
   GetTempPath(nBufferLength,qBuffer);
   CString TemporaryFile(qBuffer);
   #define GARGAMEL_TEMPORARY_DATA_FILE "grTemporary.dat"
   TemporaryFile+=GARGAMEL_TEMPORARY_DATA_FILE
   remove((LPCTSTR)TemporaryFile);
   CString CommandLine;
   CommandLine.Format(
      "\"%s\" %s %s %s %s",
      (LPCTSTR)ExecFile,
      (LPCTSTR)m_sPatternFile,(LPCTSTR)m_sSplitFile,(LPCTSTR)TemporaryFile,
      (LPCTSTR)CGrPlotWizard::GetCurrentDeffOptions());
   //
   STARTUPINFO StartupInfo;
   PROCESS_INFORMATION ProcessInformation;
   memset(&StartupInfo,0,sizeof(STARTUPINFO));
   StartupInfo.cb=sizeof(STARTUPINFO);
   StartupInfo.dwFlags=STARTF_USESHOWWINDOW;
   StartupInfo.wShowWindow =SW_SHOWDEFAULT;
   strncpy(qBuffer,(LPCTSTR)CommandLine,min(sizeof(qBuffer),CommandLine.GetLength()+1));
   CreateProcess(
      (LPCTSTR)ExecFile,   // pointer to name of executable module
      qBuffer,              // pointer to command line string
      NULL,                // process security attributes
      NULL,                // thread security attributes
      FALSE,               // handle inheritance flag
      CREATE_DEFAULT_ERROR_MODE,  // creation flags
      NULL,                // pointer to new environment block
      NULL,                // pointer to current directory name
      &StartupInfo,        // pointer to STARTUPINFO         -> input
      &ProcessInformation  // pointer to PROCESS_INFORMATION -> ouput
   );
   DWORD nResult=WaitForSingleObject(ProcessInformation.hProcess,INFINITE);
   switch (nResult) {
   case WAIT_ABANDONED :
      MessageBox("Error, EXEC.WAIT_ABANDONED",NULL,MB_ICONERROR);
      return;
   case WAIT_FAILED :
      MessageBox("Error, EXEC.WAIT_FAILED",NULL,MB_ICONERROR);
      return;
   case WAIT_TIMEOUT :
      TerminateProcess(ProcessInformation.hProcess,0);
      MessageBox("Error, EXEC.WAIT_TIMEOUT",NULL,MB_ICONERROR);
      return;
   case WAIT_OBJECT_0 :
      break;
   }
   //
   CString sReturn=_T("");
   HKEY hKey,hKey1,hKey2,hKey3;
   if (RegOpenKeyEx(HKEY_CURRENT_USER,"Software",0,KEY_ALL_ACCESS,&hKey)
      ==ERROR_SUCCESS) {
      if (RegOpenKeyEx(hKey,"shik96",0,KEY_ALL_ACCESS,&hKey1)
         ==ERROR_SUCCESS) {
         if (RegOpenKeyEx(hKey1,"DEFF",0,KEY_ALL_ACCESS,&hKey2)
            ==ERROR_SUCCESS) {
            if (RegOpenKeyEx(hKey2,"Settings",0,KEY_ALL_ACCESS,&hKey3)
               ==ERROR_SUCCESS) {
               unsigned char *qBuffer;
               unsigned long nBuffer=1024,nType;
               qBuffer=new unsigned char[nBuffer];
               RegQueryValueEx(hKey3,"LastWorkWithoutWindow",0,&nType,qBuffer,&nBuffer);
               sReturn=qBuffer;
               delete qBuffer;
               RegCloseKey(hKey3);
            }
            RegCloseKey(hKey2);
         }
         RegCloseKey(hKey1);
      }
      RegCloseKey(hKey);
   }
   //
   CToken Token;
   Token=sReturn;
   Token.SetDelimiter(" ");
   int nCount=Token.GetNextTokenCount();
   if (nCount<=3) {
      sReturn="Error, internal execution of \n";
      sReturn+=qBuffer;
      MessageBox((LPCTSTR)sReturn,NULL,MB_ICONERROR);
      return;
   }
   //
   Token=sReturn;
   Token.SetDelimiter(" ");
   sReturn.Empty();
   int nIndex=1,nPos;
   CString string;
   while (Token.IsNext()) {
      string=Token.GetNextToken();
      nPos=string.Find("=")+1;
      if (nIndex>2&&!nPos) continue;
      switch (nIndex++) {
      case 1 : break; // -> pattern file
      case 2 : break; // -> split file
      case 3 : // nPattern
         m_nPattern=atoi(string.Mid(nPos));
         break;
      case 4 : // nSplit
         m_nSplit=atoi(string.Mid(nPos));
         break;
      case 5 : // nSearchType
         m_nSearchType=atoi(string.Mid(nPos));
         break;
      case 6 : // nColumnarMatrixType
         m_nColumnarMatrixType=atoi(string.Mid(nPos));
         break;
      case 7 : // bNumericAlias
         m_bNumericAlias=atoi(string.Mid(nPos));
         break;
      case 8 : // nNumPostProcessType
         m_nPostProcessType=atoi(string.Mid(nPos));
         break;
      case 9 : // nColCountPerBlock
         m_nColCountPerBlock=atoi(string.Mid(nPos));
         break;
      case 10: // nRow
         m_nRow=atoi(string.Mid(nPos));
         break;
      case 11: // nCol
         m_nCol=atoi(string.Mid(nPos));
         break;
      case 12 : // sPatternAliasArray whose delimiter is '\n'
         m_sPatternAlias=string.Mid(nPos);
         break;
      case 13 : // sSplitAliasArray whose delimiter is '\n'
         m_sSplitAlias=string.Mid(nPos);
         break;
      }
      sReturn+=string+"\n";
   }
   nPos=sReturn.Find("sPatternAlias");
   sReturn.Delete(nPos,sReturn.GetLength()-nPos);
   //
   Token=m_sPatternAlias;
   Token.SetDelimiter("\n");
   string.Format("sPatternAlias=>%d",Token.GetNextTokenCount());
   sReturn+="\n"+string;
   Token=m_sSplitAlias;
   Token.SetDelimiter("\n");
   string.Format("sSplitAlias=>%d",Token.GetNextTokenCount());
   sReturn+="\n"+string;
   //
   switch (m_nColumnarMatrixType) {
   case 0 : // No
      break;
   case 1 : // by Pattern
      if ((m_nSplit*m_nColCountPerBlock)!=m_nCol) {
         sReturn+="\n\n";
         sReturn+="Stupid ! \n";
         sReturn+="nSplit*nColCountPerBlock does not equal nCol under nColumnarMatrixType=1,\n";
         sReturn+="which means number of value from searching pattern at each file is different.\n";
      }
      break;
   case 2 : // by Split
      if (m_nSplit!=m_nRow) {
         sReturn+="\n\n";
         sReturn+="Stupid ! \n";
         sReturn+="nSplit does not equal nCol under nColumnarMatrixType=2.\n";
      }
      break;
   }
	MessageBox((LPCTSTR)sReturn,NULL,MB_ICONINFORMATION);
}
*/

void CGrPlotWizard::DoGargamel() 
{
	// TODO: Add your control notification handler code here

   MyUpdateDataTrue();
   if (m_sPatternFile.IsEmpty() || m_sSplitFile.IsEmpty()) {
      MessageBox("Error, empty pattern file or split file !",qMessageBoxCaption,MB_ICONERROR);
      return;
   }

   m_sGargamelTemporaryFile=GetGrTemporaryFileName(FILETYPE_EXT_DAT);
   remove((LPCTSTR)m_sGargamelTemporaryFile);

   char *pAnyfind,*spMessage;
   GargamelInfo *pInfo;
   int nResult=GargamelOpen(&pAnyfind,&spMessage);
   if (!nResult) return;
   HCURSOR hCursor=AfxGetApp()->LoadStandardCursor(IDC_WAIT);
   ::SetCursor(hCursor);
   nResult=GargamelDoit (
      pAnyfind,
      (LPCTSTR)(m_sPatternFile),
      (LPCTSTR)(m_sSplitFile),
      (LPCTSTR)m_sGargamelTemporaryFile,
      m_nSearchType,m_nColumnarMatrixType,m_nPostProcessType,
      m_bNumericAlias,m_bCompositeMap,  // 2001.0410
      &pInfo
   );
   hCursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
   ::SetCursor(hCursor);
   if (!nResult) {
      MessageBox(pInfo->dpMessage,qMessageBoxCaption,MB_OK|MB_ICONSTOP);
      GargamelClose(pAnyfind,pInfo);
      m_nPattern=0;
      m_nSplit=0;
      m_nColCountPerBlock=0;
      m_nRow=0;
      m_nCol=0;
      m_sPatternAlias.Empty();
      m_sSplitAlias.Empty();
      return;
   }
   m_nPattern=pInfo->nPattern;
   m_nSplit=pInfo->nSplit;
   m_sPatternAlias="";
   for (int nIndex=1;nIndex<=pInfo->nPattern;nIndex++) {
      m_sPatternAlias+=(pInfo->vb1PatternAlias)[nIndex];
      m_sPatternAlias+="\n";
   }
   m_sSplitAlias="";
   for (nIndex=1;nIndex<=pInfo->nSplit;nIndex++) {
      m_sSplitAlias+=(pInfo->vb1SplitAlias)[nIndex];
      m_sSplitAlias+="\n";
   }
   m_nColCountPerBlock=pInfo->nColCountPerBlock;
   m_nRow=pInfo->nRow;
   m_nCol=pInfo->nCol;
   GargamelClose(pAnyfind,pInfo);

   CString sTemp="";
   sTemp.Format(
      "[in] \n\n"
      "m_nSearchType=%d \n"
      "m_nColumnarMatrixType=%d \n"
      "m_nPostProcessType=%d \n"
      "m_bNumericAlias=%d \n"
      "m_bCompositeMap=%d \n"
      "\n"
      "[out] \n\n"
      "nPatternAlias=>%d \n"
      "nSplitAlias=>%d \n"
      "nColCountPerBlock=>%d \n"
      "nRow=>%d \n"
      "nCol=>%d \n",
      m_nSearchType,m_nColumnarMatrixType,m_nPostProcessType,m_bNumericAlias,m_bCompositeMap,
      m_nPattern,m_nSplit,m_nColCountPerBlock,m_nRow,m_nCol);
   switch (m_nColumnarMatrixType) {
   case 0 : // No
      break;
   case 1 : // by Pattern
      if (m_nSplit*m_nColCountPerBlock!=m_nCol
         ||m_nPattern!=m_nRow) {
         sTemp+="\n\n";
         sTemp+="Stupid ! \n";
         sTemp+="nSplit*nColCountPerBlock does not equal nCol or \n"
                "nPattern does not equal nRow \n"
                "under nColumnarMatrixType=1,\n"
                "which means number of value from searching pattern at each file is different.\n";
      }
      break;
   case 2 : // by Split
      if (m_nPattern*m_nColCountPerBlock!=m_nCol
         ||m_nSplit!=m_nRow) {
         sTemp+="\n\n";
         sTemp+="Stupid ! \n";
         sTemp+="nPattern*nColCountPerBlock does not equal nCol or \n"
                "nSplit does not equal nCol \n"
                "under nColumnarMatrixType=2.\n";
      }
      break;
   }

#ifdef _DEBUG //shik96,2001.0209
   GargamelMessageBoxText=sTemp;
   HANDLE hThread;
   DWORD nThreadID;
   hThread = CreateThread(
      (LPSECURITY_ATTRIBUTES)NULL,   // No security attributes.
      (DWORD)0,                      // Use same stack size.
      (LPTHREAD_START_ROUTINE)GargamelMessageBox, // Thread procedure.
      (LPVOID)0,                     // Parameter to pass.
      (DWORD)0,                      // Run immediately.
      &nThreadID);
   if (!hThread) {
      TerminateThread(hThread,0);
   }
#endif
}

void CGrPlotWizard::OnGrplotwizardDraw() 
{
	// TODO: Add your control notification handler code here

   // 2001.0426
   if (!m_bPlotSeries && !m_bPlotScatter && !m_bPlotMap) return;
   if (!m_nPlotSeries && !m_nPlotScatter && !m_nPlotMap) return;

   // 2001.0406
   int nPrevious;
   if (m_bPlotSeries) nPrevious=m_nPlotSeries;
   else if (m_bPlotScatter) nPrevious=m_nPlotScatter;
   else if (m_bPlotMap) nPrevious=m_nPlotMap;
   else nPrevious=0;
   CGrPlotWizard::DoGargamel();
   if (!CGrPlotWizard::SetViewportCount()) {
      if (m_bPlotSeries) m_nPlotSeries=nPrevious;
      else if (m_bPlotScatter) m_nPlotScatter=nPrevious;
      else if (m_bPlotMap) m_nPlotMap=nPrevious;
      return;
   }

   CString sScript=CGrPlotWizard::GetGrPlotScript();
   if (sScript.IsEmpty()) return;

   CString sFile=GetGrTemporaryFileName();
   remove((LPCTSTR)sFile);
   CFile File(sFile,CFile::modeCreate|CFile::modeWrite);
   File.WriteHuge(sScript,sScript.GetLength());
   File.Close();

   this->ShowWindow(SW_HIDE);

   CWinApp *pApp=AfxGetApp();
   pApp->OpenDocumentFile((LPCTSTR)sFile);
}

int CGrPlotWizard::GetGrPlotDefaultSymbol(CString &sDefaultSymbol)
{
   sDefaultSymbol.Empty();

   CWinApp *pApp=AfxGetApp();
   int nCount=0;
   CString sIndex,sReturn("Nothing");
   while (!sReturn.IsEmpty()) {
      sIndex.Format(RegKeyDefaultSymbolFormat,nCount);
      sReturn=pApp->GetProfileString(RegKeyGrAttributes,sIndex);
      sDefaultSymbol+=sReturn+"\n";
      nCount++;
   }
   nCount--;
   sDefaultSymbol.TrimRight();

   if (!nCount) {
      MessageBox(
         "Warning, default symbol data Is EMPTY. COULD NOT WORK!\n\n"
         "Try to click a menu button : Tools/Defaults/Symbol. \n"
         "And then act on instinct of beast ...",
         qMessageBoxCaption,MB_ICONWARNING);
      return 0;
   }
   return nCount;
}

/*                     Serial Scatter
                       1 2    1 2 3 4 5  <- 2K.0609
 bColumnarMatrix       T T    F F T F F
 bNumericPatternAlias  F F    F F T F F
*/

CString CGrPlotWizard::GetGrPlotScript()
{
   MyUpdateDataTrue();

   int nPlotCount=CGrPlotWizard::GetViewportCount();
   int nPlotCountLimit=36;
   if (!nPlotCount) {
      MessageBox(
         "Error, Could not work well since you have not select !",
         qMessageBoxCaption,
         MB_ICONWARNING);
      return _T("");
   } else if (nPlotCount>nPlotCountLimit) {
      CString sTemp;
      sTemp.Format(
         "Warning, too many plots : %d > limit of %d !",
         nPlotCount,nPlotCountLimit);
      MessageBox((LPCTSTR)sTemp,qMessageBoxCaption,MB_ICONWARNING);
      return _T("");
   }

   CString sDefaultSymbol;
   int nDefaultSymbol=GetGrPlotDefaultSymbol(sDefaultSymbol);
   if (!nDefaultSymbol) return _T("");

   const char *qHomePath="~";
   CString sHomePath,sPatternFile,sSplitFile;
   sHomePath=((CGrapherApp*)AfxGetApp())->GetPathOfHome();
   sPatternFile=m_sPatternFile.Mid(0,sHomePath.GetLength());
   sSplitFile=m_sSplitFile.Mid(0,sHomePath.GetLength());;
   sHomePath.MakeLower();
   sPatternFile.MakeLower();
   sSplitFile.MakeLower();
   if (!sHomePath.IsEmpty() && sPatternFile==sHomePath) {
      sPatternFile=m_sPatternFile;
      sPatternFile.Delete(0,sHomePath.GetLength());
      sPatternFile.Insert(0,qHomePath);
   } else {
      sPatternFile=m_sPatternFile;
   }
   if (!sHomePath.IsEmpty() && sSplitFile==sHomePath) {
      sSplitFile=m_sSplitFile;
      sSplitFile.Delete(0,sHomePath.GetLength());
      sSplitFile.Insert(0,qHomePath);
   } else {
      sSplitFile=m_sSplitFile;
   }

   CString sScript,sPlot,sPlotFormat,sTemp;
   sScript=_T("");
   sTemp.Format(
      "%%grBeginning \r\n"
      "\r\n"
      ".glob \r\n"
      " gout portrait \r\n"
      " exec home=\"%s\" bReuseIfExist=1 \r\n"
      "      file=\"%s|%s|-nST=%d -nCMT=%d -nPPT=%d -bNA=%d -bC=%d\" \r\n"
      " gtxt txt=\"%s %s (%d,%d,%d,%d,%d)\" \r\n"
      "      t.size=5 \r\n",
      sHomePath,
      sPatternFile,sSplitFile,
      m_nSearchType,m_nColumnarMatrixType,m_nPostProcessType,
      m_bNumericAlias,m_bCompositeMap,
      sPatternFile,sSplitFile,
      m_nSearchType,m_nColumnarMatrixType,m_nPostProcessType,
      m_bNumericAlias,m_bCompositeMap);
   sScript+=sTemp;
   sScript+="\r\n";

   sPlotFormat=".plot \r\n";
   if (m_bPlotSeries) {
      sPlotFormat+=" attr xseries ylin \r\n"
                   " data type=script \r\n"
                   "      file=00 \r\n";
   } else if (m_bPlotScatter) {
      switch (m_nPlotScatter) {
      case ID_GRPLOTWIZARD_XSCATTER01 :
      case ID_GRPLOTWIZARD_XSCATTER02 :
         sPlotFormat+=" attr xlin ynormal \r\n";
         break;
      default :
         sPlotFormat+=" attr xlin ylin \r\n";
      }
      sPlotFormat+=" data type=script \r\n"
                   "      file=00 \r\n";
   } else if (m_bPlotMap) {
      sTemp.Format(
         " attr flat3d zlin \r\n"
         " data type=script \r\n"
         "      file=00 \r\n"
         "      xyfile=\"%s\" \r\n",
         m_sMapFile);
      sPlotFormat+=sTemp;
   }
   if (m_bPlotSeries || m_bPlotScatter) {
      sPlotFormat+=" slct ____ \r\n"
                   "      xno=%s \r\n"
                   "      yno=%s %s \r\n"
                   " axis type=x loc=lower title=\"%s\" title.size=SZTEXT title.spaceFactor=2.5 \r\n"
                   "             label.format=%%.0z label.size=SZTEXT \r\n"
                   "             label.align=23 \r\n"
                   "             axle.color=navy \r\n"
                   "             gridmajor=on gridmajor.color=green2 gridmajor.dash_list=solid \r\n"
                   "             gridminor=on gridminor.color=green1 gridminor.dash_list=shortdashed \r\n"
                   "      type=x loc=upper label=off \r\n"
                   "             axle.color=navy \r\n"
                   "      type=y loc=lower title=\"%s\" title.spaceFactor=5 title.size=SZTEXT \r\n"
                   "             label.align=32 \r\n";
      sPlotFormat+=
         (m_bPlotScatter &&
         (m_nPlotScatter==ID_GRPLOTWIZARD_XSCATTER01 || m_nPlotScatter==ID_GRPLOTWIZARD_XSCATTER02)) ?
                   "             label.format=%%.2f label.size=SZTEXT \r\n":
                   "             label.format=%%.0z label.size=SZTEXT \r\n";
      sPlotFormat+="             axle.color=navy \r\n"
                   "             gridmajor=on gridmajor.color=green2 gridmajor.dash_list=solid \r\n"
                   "             gridminor=on gridminor.color=green1 gridminor.dash_list=shortdashed \r\n"
                   "      type=y loc=upper label=off \r\n"
                   "             axle.color=navy \r\n"
                   " text type=2 txt=\"%s\" t.size=SZTEXT \r\n";
   } else if (m_bPlotMap) {
      sPlotFormat+=" slct ____ \r\n"
                   "      xno=%s \r\n"
                   "      yno=%s %s \r\n"
                   " axis type=x loc=lower axle=off label=off \r\n"
                   "             tickmajor=off tickmajor.step=1 tickminor=off tickminor.step=1 \r\n"
                   "             title=\"%s\" title.size=SZTEXT \r\n"
                   "      type=y loc=lower axle=off label=off \r\n"
                   "             tickmajor=off tickmajor.step=1 tickminor=off tickminor.step=1 \r\n"
                   "      type=x loc=upper axle=off loc=upper label=off \r\n"
                   "             tickmajor=off tickmajor.step=1 tickminor=off tickminor.step=1 \r\n"
                   "             title=\"%s\" title.size=SZTEXT \r\n"
                   "      type=y loc=upper axle=off label=off \r\n"
                   "             tickmajor=off tickmajor.step=1 tickminor=off tickminor.step=1 \r\n"
                   " text type=2 txt=\"%s\" t.size=SZTEXT \r\n";
   }

#define ABS(a) ((a)>0 ? (a):-(a))
#define TEXTSIZE_FROM_PLOTCOUNT(nCount) ((int)ABS((float)(2-9)/(25-0)*(nCount)+9)+1)
   int szText=TEXTSIZE_FROM_PLOTCOUNT(nPlotCount);
   sTemp.Format("%d",szText);
   sPlotFormat.Replace("SZTEXT",(LPCTSTR)sTemp);
   sTemp.Format("legend.size=%d",szText);
   sDefaultSymbol.Replace("legend.size=10",(LPCTSTR)sTemp);

   CToken Token(NULL,"\n"),TokDefault(NULL,"\n");
   CString xNo,yNo,sLegend,xTitle,yTitle,pTitle;
   char *pAddr;
   xNo=yNo=sLegend=xTitle=yTitle=pTitle=_T("");
   int nColTotal=m_bNumericAlias&&m_nColumnarMatrixType ? 1+m_nCol:m_nCol;
   int i,j,k;
   for (int nPlotIndex=0;nPlotIndex<nPlotCount;nPlotIndex++) {
      if (m_bPlotSeries) {
         ASSERT(m_nColumnarMatrixType);
         ASSERT(m_bNumericAlias==FALSE);
         switch (m_nPlotSeries) {
         case ID_GRPLOTWIZARD_XSERIES01 :
            xNo="0";
            yNo=_T("");
            for (i=0;i<m_nSplit;i++) {
               j=i*m_nColCountPerBlock+1;
               k=j+m_nColCountPerBlock-1;
               sTemp.Format(":%d-%d",j,k);
               yNo+=sTemp;
               ASSERT(k<=nColTotal);
            }
            yNo.Delete(0);
            sLegend=_T("");
            Token=m_sSplitAlias;
            TokDefault=_T("");
            for (i=0;i<m_nSplit;i++) {
               if (!TokDefault.IsNext()) TokDefault=sDefaultSymbol;
               sTemp.Format(TokDefault.GetNextToken(),0,Token.GetTokenByIndex(i));
               sLegend+="\r\n      "+sTemp;
            }
            xTitle="Pattern";
            yTitle="Pattern Value";
            pTitle="Title";
            break;
         case ID_GRPLOTWIZARD_XSERIES02 :
            xNo="0";
            yNo=_T("");
            for (i=0;i<m_nPattern;i++) {
               j=i*m_nColCountPerBlock+1;
               k=j+m_nColCountPerBlock-1;
               sTemp.Format(":%d-%d",j,k);
               yNo+=sTemp;
               ASSERT(k<=nColTotal);
            }
            yNo.Delete(0);
            sLegend=_T("");
            Token=m_sPatternAlias;
            TokDefault=_T("");
            for (i=0;i<m_nPattern;i++) {
               if (!TokDefault.IsNext()) TokDefault=sDefaultSymbol;
               sTemp.Format(TokDefault.GetNextToken(),0,Token.GetTokenByIndex(i));
               sLegend+="\r\n      "+sTemp;
            }
            xTitle="Split";
            yTitle="Pattern Value";
            pTitle="Title";
            break;
         }
      } else if (m_bPlotScatter) {
         switch (m_nPlotScatter) {
         case ID_GRPLOTWIZARD_XSCATTER01 :
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            ASSERT(m_nPattern*m_nSplit==m_nCol);
            xNo="*";
            yNo=_T("");
            i=m_nPattern*nPlotIndex+1;
            for (j=0;j<m_nPattern;j++) {
               sTemp.Format(":%d",k=i+j);
               yNo+=sTemp;
               ASSERT(k<=nColTotal);
            }
            yNo.Delete(0);
            //
            sLegend=_T("");
            Token=m_sPatternAlias;
            TokDefault=_T("");
            for (j=0;j<m_nPattern;j++) {
               if (!TokDefault.IsNext()) TokDefault=sDefaultSymbol;
               sTemp.Format(TokDefault.GetNextToken(),0,Token.GetTokenByIndex(j));
               sLegend+="\r\n      "+sTemp;
            }
            //
            Token=m_sPatternAlias;
            if (m_nColCountPerBlock==1) {
               xTitle="Inv.CDF";
            } else {
               xTitle=strcommon(
                  (LPCTSTR)Token.GetTokenByIndex(0),
                  (LPCTSTR)Token.GetTokenByIndex(1),
                  0);
               xTitle+="***";
            }
            yTitle="CDF";
            //
            Token=m_sSplitAlias;
            pTitle=Token.GetTokenByIndex(nPlotIndex);
            break;
         case ID_GRPLOTWIZARD_XSCATTER02 :
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            ASSERT(m_nPattern*m_nSplit==m_nCol);
            xNo="*";
            yNo=_T("");
            i=nPlotIndex+1;
            for (j=0;j<m_nSplit;j++) {
               k=i+j*m_nPattern;
               sTemp.Format(":%d",k);
               yNo+=sTemp;
               ASSERT(k<=nColTotal);
            }
            yNo.Delete(0);
            //
            sLegend=_T("");
            Token=m_sSplitAlias;
            TokDefault=_T("");
            for (j=0;j<m_nSplit;j++) {
               if (!TokDefault.IsNext()) TokDefault=sDefaultSymbol;
               sTemp.Format(TokDefault.GetNextToken(),0,Token.GetTokenByIndex(j));
               sLegend+="\r\n      "+sTemp;
            }
            //
            xTitle="Inv.CDF";
            yTitle="CDF";
            //
            Token=m_sPatternAlias;
            pTitle=Token.GetTokenByIndex(nPlotIndex);
            break;
         case ID_GRPLOTWIZARD_XSCATTER03 :
            ASSERT(m_nColumnarMatrixType==1);
            ASSERT(m_bNumericAlias==TRUE);
            ASSERT(m_nSplit*m_nColCountPerBlock==m_nCol);
            ASSERT(m_nPattern==m_nRow);
            xNo="1"; // <- numeric alias col.
            yNo=_T("");
            for (i=1;i<=m_nSplit;i++) {
               j=(i-1)*m_nColCountPerBlock+2;
               k=j+m_nColCountPerBlock-1;
               j==k ? sTemp.Format(":%d",j):sTemp.Format(":%d-%d",j,k);
               yNo+=sTemp;
               ASSERT(k<=nColTotal);
            }
            yNo.Delete(0);
            //
            sLegend=_T("");
            Token=m_sSplitAlias;
            TokDefault=_T("");
            for (j=0;j<m_nSplit;j++) {
               if (!TokDefault.IsNext()) TokDefault=sDefaultSymbol;
               sTemp.Format(
                  (LPCTSTR)TokDefault.GetNextToken(),
                  m_nColCountPerBlock-1,
                  Token.GetTokenByIndex(j));
               sLegend+="\r\n      "+sTemp;
            }
            //
            xTitle="Pattern";
            yTitle=m_sPatternAlias;
            if (m_nPattern>1) {
               Token=m_sPatternAlias;
               yTitle=strcommon(
                  (LPCTSTR)yTitle,
                  (LPCTSTR)Token.GetTokenByIndex(2),
                  0);
               yTitle+="***";
            }
            //
            pTitle="Null";
            break;
         case ID_GRPLOTWIZARD_XSCATTER04 :
            ASSERT(m_nColumnarMatrixType==3);
            ASSERT(m_bNumericAlias==TRUE);
            ASSERT(m_nPattern*m_nColCountPerBlock==m_nCol);
            ASSERT(m_nSplit==m_nRow);
            xNo="1"; // <- numeric alias col.
            yNo=_T("");
            for (i=1;i<=m_nPattern;i++) {
               j=(i-1)*m_nColCountPerBlock+2;
               k=j+m_nColCountPerBlock-1;
               j==k ? sTemp.Format(":%d",j):sTemp.Format(":%d-%d",j,k);
               yNo+=sTemp;
               ASSERT(k<=nColTotal);
            }
            yNo.Delete(0);
            //
            sLegend=_T("");
            Token=m_sPatternAlias;
            TokDefault=_T("");
            for (j=0;j<m_nPattern;j++) {
               if (!TokDefault.IsNext()) TokDefault=sDefaultSymbol;
               sTemp.Format(
                  (LPCTSTR)TokDefault.GetNextToken(),
                  m_nColCountPerBlock-1,
                  Token.GetTokenByIndex(j));
               sLegend+="\r\n      "+sTemp;
            }
            //
            xTitle="Split";
            yTitle=m_sSplitAlias;
            if (m_nSplit>1) {
               Token=m_sSplitAlias;
               yTitle=strcommon(
                  (LPCTSTR)yTitle,
                  (LPCTSTR)Token.GetTokenByIndex(2),
                  0);
               yTitle+="***";
            }
            //
            pTitle="Null";
            break;
         case ID_GRPLOTWIZARD_XSCATTER05 :
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            i=1+m_nPattern*nPlotIndex;
            xNo.Format("%d",i);
            yNo=_T("");
            for (j=1;j<m_nPattern;j++) {
               k=i+j;
               sTemp.Format(":%d",k);
               yNo+=sTemp;
               ASSERT(k<=nColTotal);
            }
            yNo.Delete(0);
            //
            sLegend=_T("");
            Token=m_sPatternAlias;
            TokDefault=_T("");
            for (j=1;j<m_nPattern;j++) {
               if (!TokDefault.IsNext()) TokDefault=sDefaultSymbol;
               sTemp.Format(TokDefault.GetNextToken(),0,Token.GetTokenByIndex(j));
               sLegend+="\r\n      "+sTemp;
            }
            //
            Token=m_sPatternAlias;
            xTitle=Token.GetTokenByIndex((i-1)%m_nColCountPerBlock);
            switch (m_nColCountPerBlock) {
            case 2 : yTitle=xTitle;
               break;
            case 3 : yTitle=strcommon(
                        (LPCTSTR)Token.GetTokenByIndex(1),
                        (LPCTSTR)Token.GetTokenByIndex(2),
                        0);
                     yTitle+="***";
               break;
            default: yTitle="Null";
               break;
            }
            //
            Token=m_sSplitAlias;
            pTitle=Token.GetTokenByIndex(nPlotIndex);
            break;
         case ID_GRPLOTWIZARD_XSCATTER06 :
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            ASSERT(!(m_nPattern%2||m_nCol%2));
            ASSERT(m_nColCountPerBlock==1);
            i=nPlotIndex*2+1;
            j=i+1;
            xNo.Format("%d",i);
            yNo.Format("%d",j);
            ASSERT(j<=m_nCol);
            //
            Token=sDefaultSymbol;
            sTemp.Format(Token.GetTokenByIndex(0),0,"");
            sLegend="\r\n      "+sTemp;
            //
            Token=m_sPatternAlias;
            xTitle=Token.GetTokenByIndex((i-1)%m_nPattern);
            yTitle=Token.GetTokenByIndex((j-1)%m_nPattern);
            //
            Token=m_sSplitAlias;
            pTitle=Token.GetTokenByIndex((int)(nPlotIndex/(m_nPattern>>1)));
            break;
         case ID_GRPLOTWIZARD_XSCATTER07 :
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            ASSERT(!(m_nPattern%2||m_nCol%2));
            ASSERT(m_nColCountPerBlock==1);
            i=1+m_nPattern*nPlotIndex;
            xNo=yNo=_T("");
            for (j=0;j<m_nPattern;j++) {
               sTemp.Format(":%d",k=i+j++);
               xNo+=sTemp;
               sTemp.Format(":%d",k=i+j);
               yNo+=sTemp;
            }
            xNo.Delete(0);
            yNo.Delete(0);
            //
            sLegend=_T("");
            Token=m_sPatternAlias;
            TokDefault=_T("");
            for (j=0;j<m_nPattern;j++) {
               if (!(j%2)) continue;
               if (!TokDefault.IsNext()) TokDefault=sDefaultSymbol;
               sTemp.Format(TokDefault.GetNextToken(),0,Token.GetTokenByIndex(j));
               sLegend+="\r\n      "+sTemp;
            }
            //
            Token=m_sPatternAlias;
            xTitle=_T("");
            for (j=0;j<m_nPattern;j++) {
               if (j%2) continue;
               xTitle+=Token.GetTokenByIndex(j);
            }
            if (xTitle.GetLength()>18) {
               xTitle.Delete(18,xTitle.GetLength()-18);
               xTitle+="...";
            }
            Token=m_sPatternAlias;
            yTitle=_T("");
            for (j=0;j<m_nPattern;j++) {
               if (!(j%2)) continue;
               yTitle+=Token.GetTokenByIndex(j);
            }
            if (yTitle.GetLength()>18) {
               yTitle.Delete(18,yTitle.GetLength()-18);
               yTitle+="...";
            }
            //
            Token=m_sSplitAlias;
            pTitle=Token.GetTokenByIndex(nPlotIndex);
            break;
         }
      } else if (m_bPlotMap) {
         if (nPlotIndex==1) {
            i=SEGetOptionPosition(sPlotFormat,
               ".plot",1,"data",1,"type=",1,0);
            pAddr=(char*)(LPCTSTR)sPlotFormat+i;
            if (!strncmp(pAddr,"type=",5)) {
               char *ptr=SEGetNextOptionAddress(pAddr);
               rskipblack(&ptr);
               rskipwhite(&ptr);
               ptr++;
               j=ptr-pAddr;
               sPlotFormat.Delete(i,j);
               sPlotFormat.Insert(i,"type=prev");
            }
         }
         switch (m_nPlotMap) {
         case ID_GRPLOTWIZARD_MAP01 :
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            ASSERT(!m_sMapFile.IsEmpty());
            xNo.Format("%d",m_nCol+1);
            yNo.Format("%d zno=%d",m_nCol+2,nPlotIndex+1);
            sTemp.Format(
               "\r\n"
               "      etc.ColorMin=yellow etc.ColorMax=red etc.ColorTotal=10 \r\n"
               "      etc.Format=%%.0z \r\n"
               "      type=0 legend.symbolsize=%d legend.height=%d \r\n"
               "             solid symbol.color=pink line.color=black",
               TEXTSIZE_FROM_PLOTCOUNT(nPlotCount),
               (int)(TEXTSIZE_FROM_PLOTCOUNT(nPlotCount)*0.5+1)
               );
            sLegend=sTemp;
            xTitle=_T("");
            yTitle=_T("");
            Token=m_sPatternAlias;
            pTitle=Token.GetTokenByIndex(nPlotIndex%m_nPattern);
            pTitle+=" @";
            Token=m_sSplitAlias;
            pTitle+=Token.GetTokenByIndex((int)(nPlotIndex/m_nPattern));
            break;
         case ID_GRPLOTWIZARD_MAP02 :
            ASSERT(m_nColumnarMatrixType==0);
            ASSERT(m_bNumericAlias==FALSE);
            ASSERT(!m_sSplitFile.IsEmpty());
            if (nPlotIndex==0) {
               CString sXYFile;
               sXYFile=GetGrTemporaryFileName(FILETYPE_EXT_GRXY);
               i=SEGetOptionPosition(sPlotFormat,
                  ".plot",1,"data",1,"type=",1,"xyfile=",1,0);
               pAddr=(char*)(LPCTSTR)sPlotFormat+i;
               if (!strncmp(pAddr,"xyfile=",7)) {
                  char *ptr=SEGetNextOptionAddress(pAddr);
                  pAddr+=7;
                  i+=7;
                  rskipblack(&ptr);
                  rskipwhite(&ptr);
                  ptr++;
                  j=ptr-pAddr;
                  sPlotFormat.Delete(i,j);
                  sPlotFormat.Insert(i,"\""+sXYFile+"\"");
               }
               CString sETFile;
               FindFileInScriptFile(m_sSplitFile,sETFile);
               if (!CreateXYFileFromKJTETFormat(sETFile,sXYFile)) {
                  return _T("");
               }
            }
            xNo.Format("%d",m_nCol+1);
            yNo.Format("%d zno=%d",m_nCol+2,nPlotIndex+1);
            sTemp.Format(
               "\r\n"
               "      etc.ColorMin=yellow etc.ColorMax=red etc.ColorTotal=10 \r\n"
               "      etc.Format=%%.0z \r\n"
               "      type=0 legend.symbolsize=%d legend.height=%d \r\n"
               "             solid symbol.color=pink line.color=black",
               TEXTSIZE_FROM_PLOTCOUNT(nPlotCount),
               (int)(TEXTSIZE_FROM_PLOTCOUNT(nPlotCount)*0.5+1)
               );
            sLegend=sTemp;
            xTitle=_T("");
            yTitle=_T("");
            Token=m_sPatternAlias;
            pTitle=Token.GetTokenByIndex(nPlotIndex%m_nPattern);
            pTitle+=" @";
            Token=m_sSplitAlias;
            pTitle+=Token.GetTokenByIndex((int)(nPlotIndex/m_nPattern));
            break;
         }
      }

      sPlot.Format((LPCTSTR)sPlotFormat,xNo,yNo,sLegend,xTitle,yTitle,pTitle);
      sScript+=sPlot;

      double dLeft,dRight,dBottom,dTop;
      SEGetIndexedViewportForGrWizard(nPlotIndex+1,nPlotCount,
         &dLeft,&dRight,&dTop,&dBottom);
      sTemp.Format(
         " view x1=%.3f x2=%.3f y1=%.3f y2=%.3f \r\n",
         dLeft,dRight,dBottom,dTop);
      sScript+=sTemp;

      sScript+=PLOTSCRIPT_LINEEND;
   }

   sScript+="%grEnd";
   sScript+=PLOTSCRIPT_LINEEND;

   /*
   char *pScript;
   SEGetSimpleScript(sScript,&pScript);
   sScript=pScript;
   myFree(pScript);
   */
   char *pScript;
   int nScript=sScript.GetLength()*2;
   pScript=new char[nScript];
   strcpy(pScript,sScript);
   sScript=SEBeautifyScript(pScript,nScript,80) ? pScript:NULL;
   delete pScript;

   return sScript;
}

void CGrPlotWizard::MyUpdateDataTrue()
{
   UpdateData(TRUE);
   m_nSearchType=0; // 1->2001.0213, AF_SEQUENTIAL
                    // 1->2001.0215, AF_ABSOLUTE
   m_nColumnarMatrixType=
   m_bNumericAlias=
   m_nPostProcessType=0;
   if (m_bPlotSeries) {;
      switch (m_nPlotSeries) {
      case ID_GRPLOTWIZARD_XSERIES01 :
         m_nColumnarMatrixType=1;
         break;
      case ID_GRPLOTWIZARD_XSERIES02 :
         m_nColumnarMatrixType=3;
         break;
      }
      m_bNumericAlias=0;
      m_nPostProcessType=m_PostProcessType.GetCurSel();
   } else if (m_bPlotScatter) {
      switch (m_nPlotScatter) {
      case ID_GRPLOTWIZARD_XSCATTER01 :
         m_nColumnarMatrixType=0;
         m_bNumericAlias=0;
         m_nPostProcessType=0;
         break;
      case ID_GRPLOTWIZARD_XSCATTER02 :
         m_nColumnarMatrixType=0;
         m_bNumericAlias=0;
         m_nPostProcessType=0;
         break;
      case ID_GRPLOTWIZARD_XSCATTER03 :
         m_nColumnarMatrixType=1;
         m_bNumericAlias=1;
         m_nPostProcessType=m_PostProcessType.GetCurSel();
         break;
      case ID_GRPLOTWIZARD_XSCATTER04 :
         m_nColumnarMatrixType=3; // 2001.0430
         m_bNumericAlias=1;
         m_nPostProcessType=m_PostProcessType.GetCurSel();
         break;
      case ID_GRPLOTWIZARD_XSCATTER05 :
      case ID_GRPLOTWIZARD_XSCATTER06 :
      case ID_GRPLOTWIZARD_XSCATTER07 :
         m_nColumnarMatrixType=0;
         m_bNumericAlias=0;
         m_nPostProcessType=0;
         break;
      }
   } else if (m_bPlotMap) {
      switch (m_nPlotMap) {
      case ID_GRPLOTWIZARD_MAP01 :
      case ID_GRPLOTWIZARD_MAP02 :
         m_nColumnarMatrixType=0;
         m_bNumericAlias=0;
         //m_nPostProcessType=0; 2001.0410
         m_nPostProcessType=m_bCompositeMap ? m_PostProcessType.GetCurSel():0;
         break;
      }
   }

   m_PatternFile.GetWindowText(m_sPatternFile);
   if (m_sPatternFile.IsEmpty()) {
      if (m_PatternFile.GetCount())
         m_PatternFile.GetLBText(0,m_sPatternFile);
   }
   OnChangeGrplotwizardPatternfile();
   m_SplitFile.GetWindowText(m_sSplitFile);
   if (m_sSplitFile.IsEmpty()) {
      if (m_SplitFile.GetCount())
         m_SplitFile.GetLBText(0,m_sSplitFile);
   }
   OnChangeGrplotwizardSplitfile();

   CWinApp* pApp=AfxGetApp();
   CString sReturn;
   int nCount,nIndex;
   char *pEntry;
   nCount=min(m_PatternFile.GetCount(),10);
   for (nIndex=0;nIndex<nCount && nIndex<10;nIndex++) {
      switch (nIndex) {
      case 0 : pEntry=RegKeyPlotWizardPatternFile0;break;
      case 1 : pEntry=RegKeyPlotWizardPatternFile1;break;
      case 2 : pEntry=RegKeyPlotWizardPatternFile2;break;
      case 3 : pEntry=RegKeyPlotWizardPatternFile3;break;
      case 4 : pEntry=RegKeyPlotWizardPatternFile4;break;
      case 5 : pEntry=RegKeyPlotWizardPatternFile5;break;
      case 6 : pEntry=RegKeyPlotWizardPatternFile6;break;
      case 7 : pEntry=RegKeyPlotWizardPatternFile7;break;
      case 8 : pEntry=RegKeyPlotWizardPatternFile8;break;
      case 9 : pEntry=RegKeyPlotWizardPatternFile9;break;
      }
      m_PatternFile.GetLBText(nIndex,sReturn);
      pApp->WriteProfileString(RegKeySettings,pEntry,sReturn);
   }
   nCount=min(m_SplitFile.GetCount(),10);
   for (nIndex=0;nIndex<nCount && nIndex<10;nIndex++) {
      switch (nIndex) {
      case 0 : pEntry=RegKeyPlotWizardSplitFile0;break;
      case 1 : pEntry=RegKeyPlotWizardSplitFile1;break;
      case 2 : pEntry=RegKeyPlotWizardSplitFile2;break;
      case 3 : pEntry=RegKeyPlotWizardSplitFile3;break;
      case 4 : pEntry=RegKeyPlotWizardSplitFile4;break;
      case 5 : pEntry=RegKeyPlotWizardSplitFile5;break;
      case 6 : pEntry=RegKeyPlotWizardSplitFile6;break;
      case 7 : pEntry=RegKeyPlotWizardSplitFile7;break;
      case 8 : pEntry=RegKeyPlotWizardSplitFile8;break;
      case 9 : pEntry=RegKeyPlotWizardSplitFile9;break;
      }
      m_SplitFile.GetLBText(nIndex,sReturn);
      pApp->WriteProfileString(RegKeySettings,pEntry,sReturn);
   }
}

void CGrPlotWizard::MyUpdateDataFalse()
{
   CWinApp* pApp=AfxGetApp();
   CString sReturn;
   int nCount,nIndex;
   char *pEntry;

   nCount=10;

   for (nIndex=0;nIndex<nCount;nIndex++) {
      switch (nIndex) {
      case 0 : pEntry=RegKeyPlotWizardPatternFile0;break;
      case 1 : pEntry=RegKeyPlotWizardPatternFile1;break;
      case 2 : pEntry=RegKeyPlotWizardPatternFile2;break;
      case 3 : pEntry=RegKeyPlotWizardPatternFile3;break;
      case 4 : pEntry=RegKeyPlotWizardPatternFile4;break;
      case 5 : pEntry=RegKeyPlotWizardPatternFile5;break;
      case 6 : pEntry=RegKeyPlotWizardPatternFile6;break;
      case 7 : pEntry=RegKeyPlotWizardPatternFile7;break;
      case 8 : pEntry=RegKeyPlotWizardPatternFile8;break;
      case 9 : pEntry=RegKeyPlotWizardPatternFile9;break;
      }
      sReturn=pApp->GetProfileString(RegKeySettings,pEntry);
      if (sReturn.IsEmpty()) continue;
      ComboBoxAddString(&m_PatternFile,sReturn);
   }
   for (nIndex=0;nIndex<nCount;nIndex++) {
      switch (nIndex) {
      case 0 : pEntry=RegKeyPlotWizardSplitFile0;break;
      case 1 : pEntry=RegKeyPlotWizardSplitFile1;break;
      case 2 : pEntry=RegKeyPlotWizardSplitFile2;break;
      case 3 : pEntry=RegKeyPlotWizardSplitFile3;break;
      case 4 : pEntry=RegKeyPlotWizardSplitFile4;break;
      case 5 : pEntry=RegKeyPlotWizardSplitFile5;break;
      case 6 : pEntry=RegKeyPlotWizardSplitFile6;break;
      case 7 : pEntry=RegKeyPlotWizardSplitFile7;break;
      case 8 : pEntry=RegKeyPlotWizardSplitFile8;break;
      case 9 : pEntry=RegKeyPlotWizardSplitFile9;break;
      }
      sReturn=pApp->GetProfileString(RegKeySettings,pEntry);
      if (sReturn.IsEmpty()) continue;
      ComboBoxAddString(&m_SplitFile,sReturn);
   }
}

void CGrPlotWizard::FindFileInScriptFile(const char *pScriptFile, CString &rFile)
{
   rFile.Empty();

   CFile File;
   int bResult=File.Open(pScriptFile,CFile::modeRead);
   if (!bResult) return;
   int nBuffer=File.GetLength();
   char *pBuffer=new char[nBuffer];
   File.ReadHuge(pBuffer,nBuffer);
   File.Close();
   CToken Token(pBuffer,"\n");
   delete pBuffer;
   CString sLine;
   while (Token.IsNext()) {
      sLine=Token.GetNextToken();
      if (sLine.Find(':')<0) continue;
      sLine.TrimLeft();
      sLine.TrimRight();
      bResult=File.Open(sLine,CFile::modeRead);
      if (bResult) {
         File.Close();
         rFile=sLine;
         return;
      }
   }
}

BOOL CGrPlotWizard::CreateXYFileFromKJTETFormat(const char *pInFile, const char *pOutFile)
{
   CFile File;
   int bResult=File.Open(pInFile,CFile::modeRead);
   if (!bResult) return FALSE;

   int nBuffer=File.GetLength();
   char *pBuffer=new char[nBuffer];
   File.ReadHuge(pBuffer,nBuffer);
   File.Close();
   CString s2nd,s3rd,s5th;
   s2nd=pBuffer;
   delete pBuffer;

   int nPos1=s2nd.Find('\n');
   int nPos2=s2nd.Find('\n',nPos1+1);
   int nPos3=s2nd.Find('\n',nPos2+1);
   int nPos4=s2nd.Find('\n',nPos3+1);
   int nPos5=s2nd.Find('\n',nPos4+1);
   s3rd=s2nd.Mid(nPos2,nPos3-nPos2);
   s5th=s2nd.Mid(nPos4,nPos5-nPos4);
   s2nd.Delete(nPos2,s2nd.GetLength()-nPos2);
   s2nd.Delete(0,nPos1);
   s2nd.TrimLeft();
   s2nd.TrimRight();
   s3rd.TrimLeft();
   s3rd.TrimRight();
   s5th.TrimLeft();
   s5th.TrimRight();
   CToken Token(s5th,";");
   s5th=Token.GetTokenByIndex(5);
   int nTotal=(int)(s2nd.GetLength()/5);
   if (atoi(s3rd)!=nTotal) {
      CString sTemp;
      sTemp.Format(
         "Error, Invalid U-/RS-Line ET File Format. Could Not Work ! \n\n"
         ".. %s \n",
         pInFile
         );
      MessageBox(sTemp,qMessageBoxCaption,MB_ICONWARNING);
      return FALSE;
   }

   pBuffer=(char*)(LPCTSTR)s2nd;
   int nIndex;
   CString sOut;
   char qBuffer[8];
   qBuffer[3]=' ';
   qBuffer[7]=0;
   sOut=_T("  x   y");
   nIndex=atoi(s5th);
   switch (nIndex) {
   case 0 :
   default :
      qBuffer[0]='+';
      qBuffer[4]='-';
      for (nIndex=0;nIndex<nTotal;nIndex++) {
         nPos1=nIndex*5;
         qBuffer[1]=pBuffer[nPos1+3]; // x
         qBuffer[2]=pBuffer[nPos1+4]; // x
         qBuffer[5]=pBuffer[nPos1+0]; // y
         qBuffer[6]=pBuffer[nPos1+1]; // y
         sOut+="\r\n";
         sOut+=qBuffer;
      }
      break;
   case 90 :
      qBuffer[0]='+';
      qBuffer[4]='+';
      for (nIndex=0;nIndex<nTotal;nIndex++) {
         nPos1=nIndex*5;
         qBuffer[1]=pBuffer[nPos1+0]; // x
         qBuffer[2]=pBuffer[nPos1+1]; // x
         qBuffer[5]=pBuffer[nPos1+3]; // y
         qBuffer[6]=pBuffer[nPos1+4]; // y
         sOut+="\r\n";
         sOut+=qBuffer;
      }
      break;
   case 180 :
      qBuffer[0]='-';
      qBuffer[4]='+';
      for (nIndex=0;nIndex<nTotal;nIndex++) {
         nPos1=nIndex*5;
         qBuffer[1]=pBuffer[nPos1+3]; // x
         qBuffer[2]=pBuffer[nPos1+4]; // x
         qBuffer[5]=pBuffer[nPos1+0]; // y
         qBuffer[6]=pBuffer[nPos1+1]; // y
         sOut+="\r\n";
         sOut+=qBuffer;
      }
      break;
   case 270 :
      qBuffer[0]='-';
      qBuffer[4]='-';
      for (nIndex=0;nIndex<nTotal;nIndex++) {
         nPos1=nIndex*5;
         qBuffer[1]=pBuffer[nPos1+0]; // x
         qBuffer[2]=pBuffer[nPos1+1]; // x
         qBuffer[5]=pBuffer[nPos1+3]; // y
         qBuffer[6]=pBuffer[nPos1+4]; // y
         sOut+="\r\n";
         sOut+=qBuffer;
      }
      break;
   }

   bResult=File.Open(pOutFile,CFile::modeCreate|CFile::modeWrite);
   if (!bResult) {
      CString sTemp;
      sTemp.Format(
         "Error, Could Not Open A Create-/Write-Mode File ! \n\n"
         ".. %s \n",
         pOutFile
         );
      MessageBox(sTemp,qMessageBoxCaption,MB_ICONWARNING);
      return FALSE;
   }
   File.WriteHuge(sOut,sOut.GetLength());
   File.Close();
   return TRUE;
}

