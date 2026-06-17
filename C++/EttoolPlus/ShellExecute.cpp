// ShellExecute.cpp: implementation of the CShellExecute class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShellExecute.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShellExecute::CShellExecute()
{
   m_hProcess=0;
   m_bShowWindow=FALSE;
}

CShellExecute::~CShellExecute()
{

}

CStringArray &aCommandOfCommenceThread;
void CommenceThread()
{
}

void CShellExecute::Commence()
{
   HANDLE hProcess = ::GetCurrentProcess();

	PROCESS_INFORMATION pi;

	STARTUPINFO si;
	::ZeroMemory(&si,sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
	si.hStdOutput = hStdOut;
	si.hStdInput  = hStdIn;
	si.hStdError  = hStdErr;
	si.wShowWindow = m_bShowWindow ? SW_SHOW: SW_HIDE;
	LPVOID lpSD = NULL;
	LPSECURITY_ATTRIBUTES lpSA = NULL;
	BOOL bResult=::CreateProcess(
      NULL,
      (char*)lpszCmdLine,
      lpSA,
      NULL,
      TRUE,
      CREATE_NEW_CONSOLE,
      NULL,
      NULL,
      &si,
      &pi);
	if (lpSA != NULL)
		::GlobalFree(lpSA);
	if (lpSD != NULL)
		::GlobalFree(lpSD);

   if (bResult) {
      VERIFY(::CloseHandle(pi.hThread));
      m_hProcess=pi.hProcess;
   } else
      m_hProcess=0;
   //Wait above process
}

void CShellExecute::KillProcess()
{

}

BOOL CShellExecute::CreateProcess()
{

}
