// GrLogDialog.cpp : implementation file
//

#define OEMRESOURCE 1 // for OBM_SIZE in <WINDOWS.H>
                      // should be here. 2001.0817

#include "stdafx.h"
#include "Grapher.h"
#include "GrLogDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// shik96@samsung.co.kr

#include "GrapherDoc.h"
#include "GrapherView.h"

/////////////////////////////////////////////////////////////////////////////
// CGrLogDialog dialog


CGrLogDialog::CGrLogDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGrLogDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrLogDialog)
	m_sLog = _T("");
	//}}AFX_DATA_INIT
}


void CGrLogDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrLogDialog)
	DDX_Control(pDX, ID_BITMAP_GRIPPER, m_Gripper);
	DDX_Text(pDX, ID_GRLOG_EDIT, m_sLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGrLogDialog, CDialog)
	//{{AFX_MSG_MAP(CGrLogDialog)
	ON_BN_CLICKED(ID_SCRIPT_DIALOG_SAVEAS, OnScriptDialogSaveas)
	ON_BN_CLICKED(ID_SCRIPT_DIALOG_CLEAR, OnScriptDialogClear)
	ON_WM_SIZE()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(ID_SCRIPT_DIALOG_PRINT, OnScriptDialogPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrLogDialog message handlers

void CGrLogDialog::OnScriptDialogSaveas() 
{
	// TODO: Add your control notification handler code here

   UpdateData(TRUE);
   if (m_sLog.IsEmpty()) return;
   //
   char initialFileName[]={"Grapher"};
   CFileDialog fDialog(FALSE,".log",initialFileName,
      OFN_LONGNAMES|OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,
      "Log Files (*.log)|*.log|Text Files (*.txt)|*.txt|Data Files (*.dat)|*.dat|"
      "All Files (*.*)|*.*||");
   if (fDialog.DoModal()==IDCANCEL) return;
   CString fName=fDialog.GetPathName();
   CFile fHandle(fName,CFile::modeCreate|CFile::modeWrite);
   fHandle.WriteHuge((LPCTSTR)m_sLog,m_sLog.GetLength());
   fHandle.Close();
}

void CGrLogDialog::OnScriptDialogClear() 
{
	// TODO: Add your control notification handler code here

	m_sLog.Empty();
   UpdateData(FALSE);
}

void CGrLogDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

   CRect Rect;
   if (!GetDlgItem(ID_GRLOG_EDIT)) {
      GetWindowRect(&Rect);
      m_nWidth=Rect.Width();
      m_nHeight=Rect.Height();
      return;
   }

   CRect RLog,RSaveas,RClear,RPrint,RCancel,RBitmap;
   GetDlgItem(ID_GRLOG_EDIT)->GetWindowRect(&RLog);
   GetDlgItem(ID_SCRIPT_DIALOG_SAVEAS)->GetWindowRect(&RSaveas);
   GetDlgItem(ID_SCRIPT_DIALOG_CLEAR)->GetWindowRect(&RClear);
   GetDlgItem(ID_SCRIPT_DIALOG_PRINT)->GetWindowRect(&RPrint);
   GetDlgItem(IDCANCEL)->GetWindowRect(&RCancel);
   GetDlgItem(ID_BITMAP_GRIPPER)->GetWindowRect(&RBitmap);
   ScreenToClient(&RLog);
   ScreenToClient(&RSaveas);
   ScreenToClient(&RClear);
   ScreenToClient(&RPrint);
   ScreenToClient(&RCancel);
   ScreenToClient(&RBitmap);

   int nMargin=RLog.left;
   int nMinWidth,nMinHeight,nWidth,nHeight;

   nMinWidth=0;
   nMinWidth+=(nWidth=RSaveas.Width());
   RSaveas.left=nMargin;
   RSaveas.right=RSaveas.left+nWidth;
   nMinWidth+=(nWidth=RClear.Width());
   RClear.left=RSaveas.right+(nMargin>>1);
   RClear.right=RClear.left+nWidth;
   nMinWidth+=(nWidth=RPrint.Width());
   RPrint.left=RClear.right+(nMargin>>1);
   RPrint.right=RPrint.left+nWidth;
   nMinWidth+=(nWidth=RCancel.Width());
   RCancel.right=cx-nMargin;
   RCancel.left=RCancel.right-nWidth;
   RLog.left=RSaveas.left;
   RLog.right=RCancel.right;
   nMinWidth+=(int)(nMargin*1.5);

   nMinHeight=nMargin*5;
   nHeight=RSaveas.Height();
   RSaveas.bottom=RClear.bottom=RPrint.bottom=RCancel.bottom=cy-nMargin;
   RSaveas.top=RClear.top=RPrint.top=RCancel.top=RSaveas.bottom-nHeight;
   RLog.bottom=RSaveas.top-nMargin;
   RLog.top=nMargin;

   nWidth=RBitmap.Width();
   nHeight=RBitmap.Height();
   RBitmap.right=cx;
   RBitmap.left=cx-nWidth;
   RBitmap.top=cy-nHeight;
   RBitmap.bottom=cy;

   if (RLog.Width()<nMinWidth || RLog.Height()<nMinHeight) {
      CRect Rect;
      GetWindowRect(&Rect);
      Rect.right=Rect.left+m_nWidth;
      Rect.bottom=Rect.top+m_nHeight;
      MoveWindow(Rect);
      return;
   }

   GetDlgItem(ID_GRLOG_EDIT)->MoveWindow(RLog);
   GetDlgItem(ID_SCRIPT_DIALOG_SAVEAS)->MoveWindow(RSaveas);
   GetDlgItem(ID_SCRIPT_DIALOG_CLEAR)->MoveWindow(RClear);
   GetDlgItem(ID_SCRIPT_DIALOG_PRINT)->MoveWindow(RPrint);
   GetDlgItem(IDCANCEL)->MoveWindow(RCancel);
   GetDlgItem(ID_BITMAP_GRIPPER)->MoveWindow(RBitmap);

   GetWindowRect(&Rect);
   m_nWidth=Rect.Width();
   m_nHeight=Rect.Height();
}

BOOL CGrLogDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   LOGFONT LogFont;
   GetFont()->GetLogFont(&LogFont);
   m_MyFont.CreateFont(
      LogFont.lfHeight,0,0,0,
      FW_NORMAL,FALSE,FALSE,
      FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,0x40,
      DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE,"Courier New");
   GetDlgItem(ID_GRLOG_EDIT)->SetFont(&m_MyFont);

   m_bmpGripper.LoadOEMBitmap(OBM_SIZE);
   m_Gripper.SetBitmap(m_bmpGripper);
   
   CRect Rect;
   GetWindowRect(&Rect);
   m_nWidth=Rect.Width();
   m_nHeight=Rect.Height();
   
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CGrLogDialog::OnNcHitTest(CPoint point) //2001.0803
{
	// TODO: Add your message handler code here and/or call default
	
	UINT nResult=CDialog::OnNcHitTest(point);

   CRect Rect;
   GetDlgItem(ID_BITMAP_GRIPPER)->GetWindowRect(Rect);
   if (Rect.PtInRect(point)) {
      nResult=HTBOTTOMRIGHT;
	}

   return nResult;
}

extern void MYorkPrintTextFast(
   const char *qText,const char *qPrinterName,const char *qJobName);
void CGrLogDialog::OnScriptDialogPrint() //20030506
{
	// TODO: Add your control notification handler code here

	UpdateData(true);

   CPrintDialog Dialog(false);
   if (Dialog.DoModal() == IDCANCEL) return;
   CString sPrinter=Dialog.GetDeviceName();
   CString sFile;GetWindowText(sFile);
   MYorkPrintTextFast(m_sLog,sPrinter,sFile);
}
