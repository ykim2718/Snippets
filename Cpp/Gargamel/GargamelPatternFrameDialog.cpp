// GargamelPatternFrameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "gargamel.h"
#include "GargamelPatternFrameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Y.Kim,20020206

#include "GargamelTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternFrameDialog dialog


CGargamelPatternFrameDialog::CGargamelPatternFrameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGargamelPatternFrameDialog::IDD, pParent),
   m_pPropertyPage(NULL)
{
	//{{AFX_DATA_INIT(CGargamelPatternFrameDialog)
	//}}AFX_DATA_INIT

   m_pIDGargamel=NULL;
   m_pPropertyPage=NULL;
	m_pWndControl=NULL;
   
   m_sStream.Empty();
}


void CGargamelPatternFrameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGargamelPatternFrameDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGargamelPatternFrameDialog, CDialog)
	//{{AFX_MSG_MAP(CGargamelPatternFrameDialog)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP

   //Y.Kim,20030206
   ON_REGISTERED_MESSAGE(GargamelUpdateDataMessage,OnGargamelUpdateData)

END_MESSAGE_MAP()

//shik96@samsung.co.kr(
BEGIN_INTERFACE_MAP(CGargamelPatternFrameDialog,CDialog)
   INTERFACE_PART(CGargamelPatternFrameDialog,IID_IPropertyPageSite,PropertyPageSite)
END_INTERFACE_MAP()
//)

/////////////////////////////////////////////////////////////////////////////
// CGargamelPatternFrameDialog message handlers

STDMETHODIMP_( ULONG ) CGargamelPatternFrameDialog::XPropertyPageSite::AddRef()
{
   METHOD_PROLOGUE(CGargamelPatternFrameDialog,PropertyPageSite)
	return pThis->ExternalAddRef();
}
STDMETHODIMP_( ULONG ) CGargamelPatternFrameDialog::XPropertyPageSite::Release()
{
   METHOD_PROLOGUE(CGargamelPatternFrameDialog,PropertyPageSite)
	return pThis->ExternalRelease();
}
STDMETHODIMP CGargamelPatternFrameDialog::XPropertyPageSite::QueryInterface( REFIID iid, void FAR* FAR* ppvObj)
{
   METHOD_PROLOGUE(CGargamelPatternFrameDialog,PropertyPageSite)
   return (HRESULT)pThis->ExternalQueryInterface(&iid,ppvObj);
}
STDMETHODIMP CGargamelPatternFrameDialog::XPropertyPageSite::OnStatusChange( DWORD dwFlags )
{
   METHOD_PROLOGUE(CGargamelPatternFrameDialog,PropertyPageSite)
	return NOERROR;
}
STDMETHODIMP CGargamelPatternFrameDialog::XPropertyPageSite::GetLocaleID( LCID *pLocaleID )
{
   METHOD_PROLOGUE(CGargamelPatternFrameDialog,PropertyPageSite)
	*pLocaleID=GetThreadLocale();
	return NOERROR;
}
STDMETHODIMP CGargamelPatternFrameDialog::XPropertyPageSite::GetPageContainer( IUnknown **ppUnk )
{
   METHOD_PROLOGUE(CGargamelPatternFrameDialog,PropertyPageSite)
	return E_FAIL;
}
STDMETHODIMP CGargamelPatternFrameDialog::XPropertyPageSite::TranslateAccelerator( MSG *pMsg )
{
   METHOD_PROLOGUE(CGargamelPatternFrameDialog,PropertyPageSite)
	return pThis->PreTranslateMessage(pMsg) ? S_OK:S_FALSE;
}

BOOL CGargamelPatternFrameDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   m_pWndControl=new CWnd();
   m_pWndControl->CreateControl(
      CLSID_GargamelPattern,NULL,0,CRect(0,0,0,0),this,-1);

   CRect Rect;
   /* CStatic m_Page
	m_Page.GetWindowRect(&Rect);
	ScreenToClient(&Rect);
   */
   GetClientRect(&Rect);
   Rect.OffsetRect(10,10);

   IUnknown *pIUnknown=m_pWndControl->GetControlUnknown();	
   HRESULT hResult=NOERROR;

   try {
      ISpecifyPropertyPagesPtr pSpecifyPropertyPages=pIUnknown;
		CAUUID nPage;
      hResult=pSpecifyPropertyPages->GetPages(&nPage);
		if (FAILED(hResult)) throw _com_error(hResult);

		ASSERT(nPage.cElems>0 && nPage.pElems!=NULL);

		IPropertyPagePtr pPropPage;

		hResult=CoCreateInstance(
         nPage.pElems[0],NULL,CLSCTX_INPROC,IID_IPropertyPage,(void**)&pPropPage);
		if (FAILED(hResult))
         throw _com_error(hResult);
		hResult=pPropPage->SetPageSite((IPropertyPageSite*)GetInterface(&IID_IPropertyPageSite));
		if (FAILED(hResult))
         throw _com_error(hResult);
		hResult=pPropPage->SetObjects(1,&pIUnknown);
		if (FAILED(hResult))
         throw _com_error(hResult);
		hResult=pPropPage->Activate(GetSafeHwnd(),Rect,TRUE);
		if (FAILED(hResult))
         throw _com_error(hResult);
		hResult=pPropPage->Show(SW_SHOW);
		if (FAILED(hResult))
         throw _com_error(hResult);
      m_pPropertyPage=pPropPage;

   } catch(_com_error &e) {
		hResult=e.Error();
		ASSERT(SUCCEEDED(hResult));
      return TRUE;
	}

   hResult=pIUnknown->QueryInterface(IID_IDispatch,(void**)&m_pIDGargamel);
   if (FAILED(hResult)) {
      AfxMessageBox(
         "pIUnknown->QueryInterface(IID_IDispatch,(void**)&m_pIDGargamel)",
         MB_ICONSTOP);
      //pIUnknown->Release();
      return TRUE;
   }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGargamelPatternFrameDialog::SetScript(CString String)
{
   HRESULT hResult=NOERROR;    
   OLECHAR *qFunction=L"PatternScript";
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
   varg[0].bstrVal=String.AllocSysString();
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
}

void CGargamelPatternFrameDialog::GetScript(CString &sReturn)
{
   HRESULT hResult=NOERROR;    
   OLECHAR *qFunction=L"PatternScript";
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
}

void CGargamelPatternFrameDialog::OnGargamelUpdateData(WPARAM wParam, LPARAM lParam)
{
   switch (wParam) {
   case true:  GetScript(m_sStream);break; // MyUpdateDataTrue
   case false: SetScript(m_sStream);break; // MyUpdateDataFalse
   }
}

void CGargamelPatternFrameDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	delete m_pWndControl; //Y.Kim,20030215 TLT
}
