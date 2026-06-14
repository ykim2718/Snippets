// WriteFileListToSynchronize.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// shik96

#include "GargamelSplitDialog.h"

#include "FileDialogEx.h"
#include "WriteFileListToSynchronize.h"

/*
 * from "c shell" source code
 */
int strweq( const char *str,const char *filter )
{
#define TRIM 0177
   register char *s=(char*)str, *p=(char*)filter;
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
// CWriteFileListToSynchronize dialog


CWriteFileListToSynchronize::CWriteFileListToSynchronize(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteFileListToSynchronize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWriteFileListToSynchronize)
	m_sFilter = _T("*.in");
	//}}AFX_DATA_INIT
   m_pParent=pParent;

   CWinApp* pApp=AfxGetApp();
   m_sLastDirectory=pApp->GetProfileString(RegKeySettings,RegKeyLastScriptDirectoryAtSplit);
}

CWriteFileListToSynchronize::~CWriteFileListToSynchronize()
{
   CWinApp* pApp=AfxGetApp();
   pApp->WriteProfileString(RegKeySettings,RegKeyLastScriptDirectoryAtSplit,m_sLastDirectory);
}

void CWriteFileListToSynchronize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWriteFileListToSynchronize)
	DDX_Control(pDX, ID_GARGAMEL_ETCETRA_LIST, m_fList);
	DDX_Text(pDX, ID_GARGAMEL_WRITEFILELIST_FILTER_STRING, m_sFilter);
	DDV_MaxChars(pDX, m_sFilter, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWriteFileListToSynchronize, CDialog)
	//{{AFX_MSG_MAP(CWriteFileListToSynchronize)
	ON_BN_CLICKED(ID_GARGAMEL_WRITEFILELIST_ADD, OnGargamelWriteFileListAdd)
	ON_BN_CLICKED(ID_GARGAMEL_WRITEFILELIST_CLEAR, OnGargamelWriteFileListClear)
	ON_BN_CLICKED(ID_GARGAMEL_WRITEFILELIST_REPLACE, OnGargamelWriteFileListReplace)
	ON_BN_CLICKED(ID_GARGAMEL_WRITEFILELIST_FILTER, OnGargamelWritefilelistFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriteFileListToSynchronize message handlers

void CWriteFileListToSynchronize::OnGargamelWriteFileListAdd() 
{
	// TODO: Add your control notification handler code here

   CFileDialogEx fDialog(TRUE,NULL,NULL,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT,
      "Input Files (*.in)|*.in|All Files (*.*)|*.*||");
   fDialog.m_ofn.lpstrInitialDir=(LPCTSTR)m_sLastDirectory;
   if (fDialog.DoModal()==IDCANCEL) return;
   CString sFile;
   POSITION p=fDialog.GetStartPosition();
   int index=m_fList.GetCount();
   while (p) {
      sFile=fDialog.GetNextPathName(p);
      if (sFile.IsEmpty()) return;
      switch (m_fList.CheckBeforeAdd((LPCTSTR)sFile)) {
      case IDYES : m_fList.InsertString(index,(LPCTSTR)sFile);break;
      case IDNO : return;
      }
   }
   if (!sFile.IsEmpty()) {
      int nPos=sFile.ReverseFind('\\');
      if (nPos!=-1) {
         sFile.Delete(nPos,sFile.GetLength()-nPos);
         m_sLastDirectory=sFile;
      }
   }
   return;
}

void CWriteFileListToSynchronize::OnGargamelWriteFileListClear() 
{
	// TODO: Add your control notification handler code here
	m_fList.ResetContent();
}

void CWriteFileListToSynchronize::OnGargamelWriteFileListReplace() 
{
	// TODO: Add your control notification handler code here

   int nTotal=m_fList.GetCount();
   if (!nTotal) {
      MessageBox("Warning, You did not enroll any file to be changed !",NULL,MB_ICONWARNING);
      return;
   }

   CGargamelSplitDialog *pParent=(CGargamelSplitDialog*)m_pParent;
   int bResult;
   CString sReturn;
   for (int nIndex=0;nIndex<nTotal;nIndex++) {
      m_fList.GetText(nIndex,sReturn);
      sReturn.TrimLeft();
      if (sReturn[0]=='<') continue;
      bResult=pParent->WriteCurrentListToAFile(sReturn);
      if (!bResult) break;
   }

   EndDialog(IDOK);
}

void CWriteFileListToSynchronize::OnGargamelWritefilelistFilter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
   int nTotal,nIndex,nResult;
   nTotal=m_fList.GetCount();
   CString sReturn;
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      m_fList.GetText(nIndex,sReturn);
      nResult=strweq((LPCTSTR)sReturn,(LPCTSTR)m_sFilter);
      if (!nResult) {
         m_fList.DeleteString(nIndex);
         nIndex--;
         nTotal--;
      }
   }
}

