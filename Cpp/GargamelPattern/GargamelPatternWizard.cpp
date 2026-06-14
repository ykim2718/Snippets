// GargamelPatternWizard.cpp : implementation file
//

#include "stdafx.h"
#include "GargamelPatternWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "FileDialogEx.h"
#include "GargamelPatternPpg.h"

/*
 * from "c shell" source code
 */
int strweq( const char *qString, const char *qFilter ) // 2001.0319
{
#define TRIM 0177
   register char *s=(char*)qString, *p=(char*)qFilter;
   register int scc;
   int ok, lc;
   int c, cc;

   for (;;) {
      scc = *s++ & TRIM;
      switch (c = *p++) {
         case '[': ok = 0;
                   lc = 077777;
                   while (cc = *p++) {
                      if (cc == ']') {
                         if (ok)
                            break;
                         return (0);
                      }
                      if (cc == '-') {
                         if (lc <= scc && scc <= *p++)
                            ok++;
                      } else
                         if (scc == (lc = cc))
                            ok++;
                   }
                   if (cc == 0)
                      return (0); /* missing ] */
                   continue;
         case '*': if (!*p)
                      return (1);
                   for (s--; *s; s++)
                      if (strweq(s, p))
                         return (1);
                   return (0);
         case 0:   return (scc == 0);
         default:  if ((c & TRIM) != scc)
                      return (0);
                   continue;
         case '?': if (scc == 0)
                      return (0);
                   continue;
      }
   } 
#undef  TRIM
}

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternWizard dialog


CGargamelPatternWizard::CGargamelPatternWizard(CWnd* pParent /*=NULL*/)
	: CDialog(CGargamelPatternWizard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGargamelPatternWizard)
	m_nFixedWidthNo = 32;
	m_sSpecialString = _T(",;\"");
	m_bSpecialCharOthers = FALSE;
	m_bSpecialCharSpace = TRUE;
	m_bSpecialCharTab = TRUE;
	m_nLineScopeNo = 999;
	m_sFilter = _T("*");
	//}}AFX_DATA_INIT

   CWinApp* pApp=AfxGetApp();
   m_sLastDirectory=pApp->GetProfileString(RegKeySettings,  RegKeyLastDirectoryOfPatternWizard);
}

CGargamelPatternWizard::~CGargamelPatternWizard()
{
   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileString(
      RegKeySettings,RegKeyLastDirectoryOfPatternWizard,m_sLastDirectory);
}

void CGargamelPatternWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGargamelPatternWizard)
	DDX_Control(pDX, ID_GARGAMEL_PATTERNWIZARD_LISTBOX, m_ListBox);
	DDX_Text(pDX, ID_GARGAMEL_PATTERNWIZARD_FIXEDWIDTHNO, m_nFixedWidthNo);
	DDV_MinMaxUInt(pDX, m_nFixedWidthNo, 1, 99);
	DDX_Text(pDX, ID_GARGAMEL_PATTERNWIZARD_SPECIALCHAR_OHTERS_STRING, m_sSpecialString);
	DDV_MaxChars(pDX, m_sSpecialString, 8);
	DDX_Check(pDX, ID_GARGAMEL_PATTERNWIZARD_SPECIALCHAR_OTHERS, m_bSpecialCharOthers);
	DDX_Check(pDX, ID_GARGAMEL_PATTERNWIZARD_SPECIALCHAR_SPACE, m_bSpecialCharSpace);
	DDX_Check(pDX, ID_GARGAMEL_PATTERNWIZARD_SPECIALCHAR_TAB, m_bSpecialCharTab);
	DDX_Text(pDX, ID_GARGAMEL_PATTERNWIZARD_LINESCOPE, m_nLineScopeNo);
	DDV_MinMaxUInt(pDX, m_nLineScopeNo, 1, 99999);
	DDX_Text(pDX, ID_GARGAMEL_PATTERNWIZARD_FILTER, m_sFilter);
	DDV_MaxChars(pDX, m_sFilter, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGargamelPatternWizard, CDialog)
	//{{AFX_MSG_MAP(CGargamelPatternWizard)
	ON_BN_CLICKED(ID_GARGAMEL_PATTERNWIZARD_OPENFILE, OnGargamelPatternWizardOpenfile)
	ON_LBN_DBLCLK(ID_GARGAMEL_PATTERNWIZARD_LISTBOX, OnDblclkGargamelPatternWizardListbox)
	ON_BN_CLICKED(ID_GARGAMEL_PATTERNWIZARD_REOPEN, OnGargamelPatternWizardReopen)
	ON_NOTIFY(UDN_DELTAPOS, ID_GARGAMEL_PATTERNWIZARD_LINESCOPE_SPIN, OnDeltaposGargamelPatternwizardLinescopeSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternWizard message handlers

BOOL CGargamelPatternWizard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   /*
   m_ListBox.ModifyStyle(0,WS_VSCROLL|WS_HSCROLL);
   int i=m_ListBox.GetHorizontalExtent();
   SendDlgItemMessage(ID_GARGAMEL_PATTERNWIZARD_FIXEDWIDTH,BM_SETCHECK,BST_CHECKED);
   */
   ((CButton*)GetDlgItem(ID_GARGAMEL_PATTERNWIZARD_FIXEDWIDTH))->SetCheck(1);
   ((CButton*)GetDlgItem(ID_GARGAMEL_PATTERNWIZARD_SPECIALCHAR))->SetCheck(0);
   ((CSpinButtonCtrl*)GetDlgItem(ID_GARGAMEL_PATTERNWIZARD_FIXEDWIDTHNO_SPIN))->SetRange(1,99);
   ((CSpinButtonCtrl*)GetDlgItem(ID_GARGAMEL_PATTERNWIZARD_LINESCOPE_SPIN))->SetRange(1,99999);
   
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGargamelPatternWizard::OnGargamelPatternWizardOpenfile() 
{
	// TODO: Add your control notification handler code here

   if (!UpdateData(TRUE)) return;

   CFileDialogEx Dialog(
      TRUE,NULL,m_sFile,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
      (LPCTSTR)"All Files (*.*)|*.*|Text Files (*.txt)|*.txt|Data Files (*.dat)|*.dat||");
   Dialog.m_ofn.lpstrInitialDir=m_sLastDirectory;
   Dialog.DoModal();
   m_sFile=Dialog.GetPathName();
   if (m_sFile.IsEmpty()) return;

   OnGargamelPatternWizardReopen();
}

void CGargamelPatternWizard::OnGargamelPatternWizardReopen() 
{
	// TODO: Add your control notification handler code here

   if (!UpdateData(TRUE)) return;
   if (m_sFile.IsEmpty()) return;

   this->SetWindowText((LPCTSTR)m_sFile);

   CFile File(m_sFile,CFile::modeRead);
   int nLength=File.GetLength();
   char *pText=(char*)calloc(nLength,sizeof(TCHAR));
   File.ReadHuge(pText,nLength);
   File.Close();
   CString sText(pText);
   delete pText;

   
   CString sFile(m_sFile);
   int nPos=sFile.ReverseFind('\\');
   if (nPos!=-1) {
      sFile.Delete(nPos,sFile.GetLength()-nPos);
      m_sLastDirectory=sFile;
   }

   if (!m_sFilter.IsEmpty()) { // 2001.0319
      if (m_sFilter[0]!='*' && m_sFilter[0]!='?')
         m_sFilter.Insert(0,'*');
      nLength=m_sFilter.GetLength();
      if (m_sFilter[nLength-1]!='*' && m_sFilter[nLength-1]!='?')
         m_sFilter+="*";
      UpdateData(FALSE);
   }

   int n0=0,n1,nLine=1;
   nLength=0;
   m_ListBox.ResetContent();
   while ((n1=sText.Find('\n',n0))>0) {
      CString sMid=sText.Mid(n0,n1-n0+1);
      //sMid.TrimLeft();
      sMid.TrimRight();
      nLength=max(nLength,sMid.GetLength());
      if (m_sFilter.IsEmpty()) {
         m_ListBox.AddString((LPCTSTR)sMid);
      } else {
         if (strweq(sMid,m_sFilter)) m_ListBox.AddString((LPCTSTR)sMid);
      }
      n0=++n1;
      nLine++;
      if ((unsigned)nLine>m_nLineScopeNo) break;
   }
   CString sEnd=sText.Mid(n0);
   sEnd.TrimLeft();
   sEnd.TrimRight();
   if (!sEnd.IsEmpty()) m_ListBox.AddString((LPCTSTR)sEnd);

   CFont *pFont=m_ListBox.GetFont();
   LOGFONT LogFont;
   pFont->GetLogFont(&LogFont);
   nLength=(int)(nLength*abs(LogFont.lfHeight)/1.7);
   m_ListBox.SetHorizontalExtent(nLength>0 ? nLength:1000);
}

void CGargamelPatternWizard::OnDblclkGargamelPatternWizardListbox() 
{
	// TODO: Add your control notification handler code here
	
   CString sReturn;
   m_ListBox.GetText(m_ListBox.GetCurSel(),sReturn);

   UpdateData(TRUE);
   int i=((CButton*)GetDlgItem(ID_GARGAMEL_PATTERNWIZARD_FIXEDWIDTH))->GetCheck();
   if (i) {
      if ((int)m_nFixedWidthNo<sReturn.GetLength())
         sReturn.SetAt(m_nFixedWidthNo,0);
   } else {      
      CString strDelimit;
      if (m_bSpecialCharSpace) strDelimit+=" ";
      if (m_bSpecialCharTab)   strDelimit+="\t";
      i=sReturn.FindOneOf((LPCTSTR)strDelimit);
      if (i>0) sReturn.SetAt(i,0);
   }
   ((CGargamelPatternPropPage*)m_pParent)->SetRemotely((LPCTSTR)sReturn);
}


void CGargamelPatternWizard::OnDeltaposGargamelPatternwizardLinescopeSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

   if (UpdateData(TRUE)) {
      m_nLineScopeNo+=pNMUpDown->iDelta*-100;
      UpdateData(FALSE);
   }

	*pResult = 0;
}
