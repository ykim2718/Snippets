// GrHistoryDialog.cpp : implementation file
//

#define OEMRESOURCE 1 // for OBM_SIZE in <WINDOWS.H>
                      // should be here. 2001.0817

#include "stdafx.h"
#include "Grapher.h"
#include "GrHistoryDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrHistoryDialog dialog


CGrHistoryDialog::CGrHistoryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGrHistoryDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrHistoryDialog)
	m_sHistory = _T("");
	//}}AFX_DATA_INIT

   m_sHistory=
   "[Known Bugs]\r\n"
   "1.PS file creation on horizontall mode does not work.\r\n"
   "2.Colors of PS file does not match up to those of the screen.\r\n"
   "3.Full contents are selected from the first in the history dialog.\r\n"
   "\r\n"
   "[Cured Bugs]\r\n"
   "20020913\r\n"
   ".Fixed up EMF generation on Windows 2000 \r\n"
   "20020318\r\n"
   ".Invalid resource error under Windows 2000 is fixed.\r\n"
   "20010824\r\n"
   ".Bug on Gr Mixer is fixed.\r\n"
   "20010817\r\n"
   ".Bug on deleting a plot is fixed at the plot page of property sheet.\r\n"
   "20010815\r\n"
   ".X and Y legend locations are operated separately on the Selection page.\r\n"
   "20010803\r\n"
   ".Gripper of Resiable Log dialog is realized.\r\n"
   ".Text page of GrWizrad dialog is bug-fixed.\r\n"
   "20010605\r\n"
   ".Log dialog is re-sizable.\r\n"
   "20010515\r\n"
   ".Series plot is added.\r\n"
   ".A bug on Mixer is removed.\r\n"
   "20010422\r\n"
   ".Symbol and axis line style (solid,dashed,..) and width can be changed.\r\n"
   "20010419\r\n"
   ".Fixed up a bug of deleting a free-positioned text on the Text page of property sheet.\r\n"
   "20010412\r\n"
   ".Added Count and Range Post-Process Type in GrPlotWizard dialog.\r\n"
   "20010410\r\n"
   ".Composite map is available.\r\n"
   "20010405\r\n"
   ".Added ListCtrl in text property page to position text anywhere.\r\n"
   ".Speeded up Gr-Wizard to reuse data file created by Gargamel.\r\n"
   ".Added Previous/Next buttons for navigating each plot in property page.\r\n"
   "20010402\r\n"
   ".Speeded up to reuse data file just created before.\r\n"
   ".When \"bReuseIfExist=1\", Reuse Gargamel script files and Grapher Temporary Files.\r\n"
   ".Deleted Grapher Temporary Files when exiting a view window.\r\n"
   "20010328\r\n"
   ".Added checking whether the script file is modified.\r\n"
   "20010322\r\n"
   ".Speed up plot displaying speed at the plot page of propery sheet.\r\n"
   "20010321\r\n"
   ".Fixed some bug when deleting a plot while file=previous.\r\n"
   ".Added inflate and deflate buttons in viewport page.\r\n"
   ".Added pre-defined viewport size buttons in viewport page.\r\n"
   "20010319\r\n"
   ".Fixed general symbol displaying at moment box plot.\r\n"
   "20010318\r\n"
   ".Fixed output graphic size when printing without FinePrint.\r\n"
   ".Added moment box plot attribute and symbol.\r\n"
   ".Fixed log scale (tick/grid/label/..) axis bug.\r\n"
   "\r\n"
   "1999.9\r\n"
   "1995.09.27 Big Bang -_-";

}


void CGrHistoryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrHistoryDialog)
	DDX_Control(pDX, ID_BITMAP_GRIPPER, m_Gripper);
	DDX_Text(pDX, ID_GRHISTORY_EDIT, m_sHistory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrHistoryDialog, CDialog)
	//{{AFX_MSG_MAP(CGrHistoryDialog)
	ON_WM_SIZE()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrHistoryDialog message handlers


BOOL CGrHistoryDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   m_bmpGripper.LoadOEMBitmap(OBM_SIZE);
   m_Gripper.SetBitmap(m_bmpGripper);
   
   CEdit *pEdit=(CEdit*)GetDlgItem(ID_GRHISTORY_EDIT);
   //pEdit->SetSel(-1,0); //??
   pEdit->SendMessage(EM_SETSEL,10,15);

   // 20020914
   // By using an idea of Mak (2002/09/06),written on www.codeguru.com
   CFont *pFont=CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
   CWnd *pWnd=GetWindow(GW_CHILD);
   while (pWnd) {
      pWnd->SetFont(pFont); 
      pWnd=pWnd->GetNextWindow();
   }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrHistoryDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
   if (!GetDlgItem(ID_GRHISTORY_EDIT)) return;

   CRect RectHistory,RectBmp;
   GetDlgItem(ID_GRHISTORY_EDIT)->GetWindowRect(&RectHistory);
   GetDlgItem(ID_BITMAP_GRIPPER)->GetWindowRect(&RectBmp);
   ScreenToClient(&RectHistory);
   ScreenToClient(&RectBmp);

   int nMargin=RectHistory.left;
   nMargin=0; // Beats me ! 2001.0817
   RectHistory.right=RectHistory.left+cx-nMargin;
   RectHistory.bottom=RectHistory.top+cy-nMargin;

   int nWidth,nHeight;
   nWidth=RectBmp.Width();
   nHeight=RectBmp.Height();
   RectBmp.right=nWidth;
   RectBmp.left=cx-nWidth;
   RectBmp.top=cy-nHeight;
   RectBmp.bottom=cy;

   GetDlgItem(ID_GRHISTORY_EDIT)->MoveWindow(RectHistory);
   GetDlgItem(ID_BITMAP_GRIPPER)->MoveWindow(RectBmp);
}

UINT CGrHistoryDialog::OnNcHitTest(CPoint point) 
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
