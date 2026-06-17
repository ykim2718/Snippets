// GargamelPatternForMatrixDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GargamelPatternForMatrix.h"
#include "GargamelPatternForMatrixDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Y.Kim,20030208

#include "Token.h"
#include "../myC/anyfind_def.h"

static const char *qBEGINNING=AF_OPT_BEGINNING;
static const char *qENDING=AF_OPT_ENDING;
static const char *qBLOCKSELECTIONS=AF_OPT_BLOCKSELECTIONS;
static const char *qBLOCKSELECTIONALL=AF_OPT_BLOCKSELECTIONALL;
static const char *qFIRSTCOLUMN=AF_OPT_FIRSTCOLUMN;
static const char *qOTHERCOLUMNS=AF_OPT_OTHERCOLUMNS;
static const char *qFORMAT=AF_OPT_FORMAT;
static const char *qEQUATION=AF_OPT_EQUATION;
static const char *qCUTLOW=AF_OPT_CUTLOW;
static const char *qCUTHIGH=AF_OPT_CUTHIGH;

static const char *qDataFormatString[]={"%s","%.0f","%.3f","%.3e","%.3z"};

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixDialog dialog


CGargamelPatternForMatrixDialog::CGargamelPatternForMatrixDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGargamelPatternForMatrixDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGargamelPatternForMatrixDialog)
	m_sBeginning = _T("");
	m_sEnding = _T("");
	m_sBlockSelections = _T("1");
	m_bBlockSelectionAll = FALSE;
	m_n1stColumn = 1;
	m_sOtherColumns = _T("2");
	m_sFormat = _T("%.2e");
	m_sEquation = _T("");
	m_sCutHigh = _T("");
	m_sCutLow = _T("");
	//}}AFX_DATA_INIT
}


void CGargamelPatternForMatrixDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGargamelPatternForMatrixDialog)
	DDX_Text(pDX, ID_BEGINNING_TEXT, m_sBeginning);
	DDX_Text(pDX, ID_ENDING_TEXT, m_sEnding);
	DDX_Text(pDX, ID_BLOCK_SELECTION, m_sBlockSelections);
	DDX_Check(pDX, ID_BLOCK_SELECTION_ALL, m_bBlockSelectionAll);
	DDX_Text(pDX, ID_1ST_COLUMN, m_n1stColumn);
	DDV_MinMaxInt(pDX, m_n1stColumn, 1, 99);
	DDX_Text(pDX, ID_OTHER_COLUMNS, m_sOtherColumns);
	DDX_CBString(pDX, ID_FORMAT, m_sFormat);
	DDX_Text(pDX, ID_EQUATION, m_sEquation);
	DDX_Text(pDX, ID_CUTHIGH, m_sCutHigh);
	DDX_Text(pDX, ID_CUTLOW, m_sCutLow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGargamelPatternForMatrixDialog, CDialog)
	//{{AFX_MSG_MAP(CGargamelPatternForMatrixDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_FORMAT_HELP, OnFormatHelp)
	ON_BN_CLICKED(ID_BLOCK_SELECTION_ALL, OnBlockSelectionAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternForMatrixDialog message handlers

void CGargamelPatternForMatrixDialog::SetScriptToDialog(const CString &sScript)
{
   if (sScript.Find(qBEGINNING)<0) return;
   if (sScript.Find(qENDING)<0) return;
   if (sScript.Find(qBLOCKSELECTIONS)<0) return;
   if (sScript.Find(qBLOCKSELECTIONALL)<0) return;
   if (sScript.Find(qFIRSTCOLUMN)<0) return;
   if (sScript.Find(qOTHERCOLUMNS)<0) return;
   if (sScript.Find(qFORMAT)<0) return;
   if (sScript.Find(qEQUATION)<0) return;
   if (sScript.Find(qCUTLOW)<0) return;
   if (sScript.Find(qCUTHIGH)<0) return;

   int nFirst,nLast;
   nFirst=sScript.Find(qBEGINNING)+strlen(qBEGINNING);
   nLast=sScript.Find("\n",nFirst);
   m_sBeginning=nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst);
   nFirst=sScript.Find(qENDING)+strlen(qENDING);
   nLast=sScript.Find("\n",nFirst);
   m_sEnding=nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst);
   nFirst=sScript.Find(qBLOCKSELECTIONS)+strlen(qBLOCKSELECTIONS);
   nLast=sScript.Find("\n",nFirst);
   m_sBlockSelections=nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst);
   nFirst=sScript.Find(qBLOCKSELECTIONALL)+strlen(qBLOCKSELECTIONALL);
   nLast=sScript.Find("\n",nFirst);
   m_bBlockSelectionAll=atoi(nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst));
   nFirst=sScript.Find(qFIRSTCOLUMN)+strlen(qFIRSTCOLUMN);
   nLast=sScript.Find("\n",nFirst);
   m_n1stColumn=atoi(nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst));
   nFirst=sScript.Find(qOTHERCOLUMNS)+strlen(qOTHERCOLUMNS);
   nLast=sScript.Find("\n",nFirst);
   m_sOtherColumns=nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst);
   nFirst=sScript.Find(qFORMAT)+strlen(qFORMAT);
   nLast=sScript.Find("\n",nFirst);
   m_sFormat=nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst);
   nFirst=sScript.Find(qEQUATION)+strlen(qEQUATION);
   nLast=sScript.Find("\n",nFirst);
   m_sEquation=nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst);
   nFirst=sScript.Find(qCUTLOW)+strlen(qCUTLOW);
   nLast=sScript.Find("\n",nFirst);
   m_sCutLow=nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst);
   nFirst=sScript.Find(qCUTHIGH)+strlen(qCUTHIGH);
   nLast=sScript.Find("\n",nFirst);
   m_sCutHigh=nLast>=0 ? sScript.Mid(nFirst,nLast-nFirst+1):sScript.Mid(nFirst);

   TrimLeftRight(m_sBeginning);
	TrimLeftRight(m_sEnding);
	TrimLeftRight(m_sBlockSelections);
	TrimLeftRight(m_sOtherColumns);
	TrimLeftRight(m_sFormat);
	TrimLeftRight(m_sEquation);
	TrimLeftRight(m_sCutLow);
	TrimLeftRight(m_sCutHigh);

   UpdateData(false);
}

CString CGargamelPatternForMatrixDialog::GetScriptFromDialog()
{
   UpdateData(true);

   TrimLeftRight(m_sBeginning);
	TrimLeftRight(m_sEnding);
	TrimLeftRight(m_sBlockSelections);
	TrimLeftRight(m_sOtherColumns);
	TrimLeftRight(m_sFormat);
	TrimLeftRight(m_sEquation);
	TrimLeftRight(m_sCutLow);
	TrimLeftRight(m_sCutHigh);

   const char *qLineEnd=AF_COMMAND_LINE_END;
   CString sScript,sWhite(" "),sNo;
   char qNo[128]; //? 20030208
   sScript=qBEGINNING+sWhite+m_sBeginning+qLineEnd;
   sScript+=qENDING+sWhite+m_sEnding+qLineEnd;
   sScript+=qBLOCKSELECTIONS+sWhite+m_sBlockSelections+qLineEnd;
   sNo=_itoa(m_bBlockSelectionAll,qNo,10);
   sScript+=qBLOCKSELECTIONALL+sWhite+sNo+qLineEnd;
   sNo=_itoa(m_n1stColumn,qNo,10);
   sScript+=qFIRSTCOLUMN+sWhite+sNo+qLineEnd;
   sScript+=qOTHERCOLUMNS+sWhite+m_sOtherColumns+qLineEnd;
   sScript+=qFORMAT+sWhite+m_sFormat+qLineEnd;
   sScript+=qEQUATION+sWhite+m_sEquation+qLineEnd;
   sScript+=qCUTLOW+sWhite+m_sCutLow+qLineEnd;
   sScript+=qCUTHIGH+sWhite+m_sCutHigh+qLineEnd;

   sScript.TrimLeft();
   sScript.TrimRight();
   return sScript;
}

void CGargamelPatternForMatrixDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	m_sLastScriptOnDestory=GetScriptFromDialog();
}

BOOL CGargamelPatternForMatrixDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   int nCount,nIndex;

   LOGFONT LogFont;
   GetFont()->GetLogFont(&LogFont);
   LogFont.lfUnderline=TRUE;
   m_MyFont.CreateFontIndirect(&LogFont);
   GetDlgItem(ID_BLOCK_SELECTION_TAG)->SetFont(&m_MyFont);
   GetDlgItem(ID_1ST_COLUMN_TAG)->SetFont(&m_MyFont);
   GetDlgItem(ID_OTHER_COLUMNS_TAG)->SetFont(&m_MyFont);
	
   //????
   CComboBox *pBox=(CComboBox*)GetDlgItem(ID_FORMAT_HELP);
   nCount=sizeof(qDataFormatString)/sizeof(qDataFormatString[0]);
   for (nIndex=0;nIndex<nCount;nIndex++)
      pBox->AddString((LPCTSTR)qDataFormatString[nIndex]);
   pBox->SetCurSel(3);

   //
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGargamelPatternForMatrixDialog::OnFormatHelp() 
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

void CGargamelPatternForMatrixDialog::OnBlockSelectionAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
   GetDlgItem(ID_BLOCK_SELECTION)->EnableWindow(!m_bBlockSelectionAll);
}

void CGargamelPatternForMatrixDialog::TrimLeftRight(CString &sStuff)
{
    sStuff.TrimLeft();
    sStuff.TrimRight();
}
