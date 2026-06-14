// GargamelSplitFrameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Gargamel.h"
#include "GargamelSplitFrameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Y.Kim,20020206

#include "GargamelTabCtrl.h"

static char qThisClassName[]="CGargamelSplitFrameDialog";

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitFrameDialog dialog

CGargamelSplitFrameDialog::CGargamelSplitFrameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGargamelSplitFrameDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGargamelSplitFrameDialog)
	//}}AFX_DATA_INIT

   /* m_pIDGargamel=NULL; */
   m_sStream.Empty();
}


void CGargamelSplitFrameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGargamelSplitFrameDialog)
	DDX_Control(pDX, ID_GARGAMEL_SPLIT_OCX, m_GargamelSplitOcx);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGargamelSplitFrameDialog, CDialog)
	//{{AFX_MSG_MAP(CGargamelSplitFrameDialog)
	//}}AFX_MSG_MAP

   //Y.Kim,20030206
   ON_REGISTERED_MESSAGE(GargamelUpdateDataMessage,OnGargamelUpdateData)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGargamelSplitFrameDialog message handlers

BOOL CGargamelSplitFrameDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   /*
   IUnknown *pIUnknown;
   HRESULT hResult=::CoCreateInstance(
      CLSID_GargamelSplit,NULL,CLSCTX_INPROC_SERVER,
      //IID_IUnknown,(void**)&pIUnknown);
      IID_IDispatch,(void**)&m_pIDGargamel);
   if (FAILED(hResult)) {
      MessageBox(
         "Error, ::CoCreateInstance() for CLSID_GargamelSplit:IID_IDispatch",
         qThisClassName,MB_ICONWARNING);
      return FALSE;
   }
   */

   GetDlgItem(ID_PROVERB)->SetWindowText(_T("ŒNŽqŽ©‹­•s‘§"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGargamelSplitFrameDialog::SetScript(const CString &sForwarding)
{
   m_GargamelSplitOcx.SetSplitScript(sForwarding);
   /*
   HRESULT hResult=NOERROR;    
   OLECHAR *qFunction=L"SplitScript";
   DISPID nDispid;
   hResult=m_pIDGargamel->GetIDsOfNames(
      IID_NULL,&qFunction,1,GetUserDefaultLCID(),&nDispid);
   if (FAILED(hResult)) {
      CString Message="pIDispatch->GetIDsOfNames() Error : \n\n";
      switch (hResult) {
      case E_OUTOFMEMORY :
         Message+="Out of memory.";
         break;
      case DISP_E_UNKNOWNNAME :
         Message+="One or more of the names were not known.\n"
                  "The returned array of DISPIDs contains DISPID_UNKNOWN\n"
                  "for each entry that corresponds to an unknown name.";
         break;
      case DISP_E_UNKNOWNLCID :
         Message+="The locale identifier (LCID) was not recognized.";
         break;
      }
      AfxMessageBox(Message,MB_ICONSTOP);
      m_pIDGargamel->Release();
      return;
   }

   VARIANTARG varg[1];
   varg[0].vt=VT_BSTR;
   varg[0].bstrVal=sForwarding.AllocSysString();
   DISPPARAMS param={varg,NULL,1,0};

   hResult=m_pIDGargamel->Invoke(
      nDispid,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,
      &param,NULL,NULL,NULL);
   if (FAILED(hResult)) {
      CString Message="m_pIDGargamel->Invoke() Error : \n\n";
      switch (hResult) {
      case DISP_E_BADPARAMCOUNT :    Message+="DISP_E_BADPARAMCOUNT";break;
      case DISP_E_BADVARTYPE :       Message+="DISP_E_BADVARTYPE";break;
      case DISP_E_EXCEPTION :        Message+="DISP_E_EXCEPTION";break;
      case DISP_E_MEMBERNOTFOUND :   Message+="DISP_E_MEMBERNOTFOUND";break;
      case DISP_E_NONAMEDARGS :      Message+="DISP_E_NONAMEDARGS";break;
      case DISP_E_OVERFLOW :         Message+="DISP_E_OVERFLOW";break;
      case DISP_E_PARAMNOTFOUND :    Message+="DISP_E_PARAMNOTFOUND";break;
      case DISP_E_TYPEMISMATCH :     Message+="DISP_E_TYPEMISMATCH";break;
      case DISP_E_UNKNOWNINTERFACE : Message+="DISP_E_UNKNOWNINTERFACE";break;
      case DISP_E_UNKNOWNLCID :      Message+="DISP_E_UNKNOWNLCID";break;
      case DISP_E_PARAMNOTOPTIONAL : Message+="DISP_E_PARAMNOTOPTIONAL";break;
      }
      AfxMessageBox(Message,MB_ICONSTOP);
      m_pIDGargamel->Release();
   }
   ::SysFreeString(varg[0].bstrVal);
   */
}

void CGargamelSplitFrameDialog::GetScript(CString &sReturn)
{
   sReturn=m_GargamelSplitOcx.GetSplitScript();
   /*
   HRESULT hResult=NOERROR;    
   OLECHAR *qFunction=L"SplitScript";
   DISPID nDispid;
   hResult=m_pIDGargamel->GetIDsOfNames(
      IID_NULL,&qFunction,1,GetUserDefaultLCID(),&nDispid);
   if (FAILED(hResult)) {
      CString Message="pIDispatch->GetIDsOfNames() Error : \n\n";
      switch (hResult) {
      case E_OUTOFMEMORY :
         Message+="Out of memory.";
         break;
      case DISP_E_UNKNOWNNAME :
         Message+="One or more of the names were not known.\n"
                  "The returned array of DISPIDs contains DISPID_UNKNOWN\n"
                  "for each entry that corresponds to an unknown name.";
         break;
      case DISP_E_UNKNOWNLCID :
         Message+="The locale identifier (LCID) was not recognized.";
         break;
      }
      AfxMessageBox(Message,MB_ICONSTOP);
      m_pIDGargamel->Release();
      return;
   }

   DISPPARAMS param={NULL,NULL,0,0};
   VARIANT VarResult;

   hResult=m_pIDGargamel->Invoke(
      nDispid,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,
      &param,&VarResult,NULL,NULL);
   if (FAILED(hResult)) {
      CString Message="m_pIDGargamel->Invoke() Error : \n\n";
      switch (hResult) {
      case DISP_E_BADPARAMCOUNT :    Message+="DISP_E_BADPARAMCOUNT";break;
      case DISP_E_BADVARTYPE :       Message+="DISP_E_BADVARTYPE";break;
      case DISP_E_EXCEPTION :        Message+="DISP_E_EXCEPTION";break;
      case DISP_E_MEMBERNOTFOUND :   Message+="DISP_E_MEMBERNOTFOUND";break;
      case DISP_E_NONAMEDARGS :      Message+="DISP_E_NONAMEDARGS";break;
      case DISP_E_OVERFLOW :         Message+="DISP_E_OVERFLOW";break;
      case DISP_E_PARAMNOTFOUND :    Message+="DISP_E_PARAMNOTFOUND";break;
      case DISP_E_TYPEMISMATCH :     Message+="DISP_E_TYPEMISMATCH";break;
      case DISP_E_UNKNOWNINTERFACE : Message+="DISP_E_UNKNOWNINTERFACE";break;
      case DISP_E_UNKNOWNLCID :      Message+="DISP_E_UNKNOWNLCID";break;
      case DISP_E_PARAMNOTOPTIONAL : Message+="DISP_E_PARAMNOTOPTIONAL";break;
      }
      AfxMessageBox(Message,MB_ICONSTOP);
      m_pIDGargamel->Release();
      return;
   }

   if (VarResult.vt!=VT_BSTR) return;
   sReturn=VarResult.bstrVal;
   ::SysFreeString(VarResult.bstrVal);
   */
}

void CGargamelSplitFrameDialog::OnOK()
{
   m_GargamelSplitOcx.NotifyFlagrantDialogOk();
   /*
   HRESULT hResult=NOERROR;
   OLECHAR *qFunction=L"NotifyFlagrantDialogOk";
   DISPID nDispid;
   hResult=m_pIDGargamel->GetIDsOfNames(
      IID_NULL,&qFunction,1,GetUserDefaultLCID(),&nDispid);
   DISPPARAMS param={NULL,NULL,0,0};
   hResult=m_pIDGargamel->Invoke(
      nDispid,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,
      &param,NULL,NULL,NULL);
   */
}

void CGargamelSplitFrameDialog::OnCancel()
{
   m_GargamelSplitOcx.NotifyFlagrantDialogCancel();
   /*
   HRESULT hResult=NOERROR;
   OLECHAR *qFunction=L"NotifyFlagrantDialogCancel";
   DISPID nDispid;
   hResult=m_pIDGargamel->GetIDsOfNames(
      IID_NULL,&qFunction,1,GetUserDefaultLCID(),&nDispid);
   DISPPARAMS param={NULL,NULL,0,0};
   hResult=m_pIDGargamel->Invoke(
      nDispid,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,
      &param,NULL,NULL,NULL);
   */
}

void CGargamelSplitFrameDialog::OnGargamelUpdateData(WPARAM wParam, LPARAM lParam)
{
   switch (wParam) {
   case true:  GetScript(m_sStream);break; // MyUpdateDataTrue
   case false: SetScript(m_sStream);break; // MyUpdateDataFalse
   }
}
