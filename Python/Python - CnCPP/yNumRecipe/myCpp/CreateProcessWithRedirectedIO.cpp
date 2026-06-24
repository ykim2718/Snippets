#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

//#include "stdafx.h" //2001.0620
#include <afxwin.h> // MFC core and standard components
#include <afxext.h> // MFC extensions

#define BUFSIZE 4096

static CString GetLastErrorMessage() //20030421
{
   TCHAR szMsgBuf[BUFSIZE];
   FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,                          // ignored
      GetLastError(),                // message id
      MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),// message language    
      szMsgBuf,                      // address of buffer pointer
      BUFSIZE,                       // minimum buffer size
      NULL                           // no other arguments
      );
   return szMsgBuf;
}

// MSDN Library Visual Studio 6.0 : HELP
// CreatePipe 검색결과에서
// Creating a Child Process with Redirected Input and Output
void CreateProcessWithRedirectedIO(
   const char *qCommand,
   CString &sReturn,
   int bWindowless
   )
{
   sReturn.Empty();
   
   SECURITY_ATTRIBUTES sa;
	::ZeroMemory(&sa,sizeof(SECURITY_ATTRIBUTES));
	sa.nLength=sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor=NULL;
	sa.bInheritHandle=TRUE;

   HANDLE hChildStdinRd,hChildStdinWr,hChildStdinWrDup,
          hChildStdoutRd,hChildStdoutWr,hChildStdoutRdDup,
          hChildStderrRd,hChildStderrWr,hChildStderrRdDup,
          hSaveStdin,hSaveStdout,hSaveStderr;
   BOOL bResult;

   hSaveStdin=GetStdHandle(STD_INPUT_HANDLE);
   // Create a pipe for the child process's STDIN.
   if (!CreatePipe(&hChildStdinRd,&hChildStdinWr,&sa,0)) return;
   // Set a read handle to the pipe to be STDIN.
   if (!SetStdHandle(STD_INPUT_HANDLE,hChildStdinRd)) return;
   // Duplicate the write handle to the pipe so it is not inherited.
   bResult=DuplicateHandle(
      GetCurrentProcess(),hChildStdinWr,
      GetCurrentProcess(),&hChildStdinWrDup,
      0,FALSE,DUPLICATE_SAME_ACCESS);
   if (!bResult) return;
   CloseHandle(hChildStdinWr); //shik96

   hSaveStdout=GetStdHandle(STD_OUTPUT_HANDLE);
   VERIFY(CreatePipe(&hChildStdoutRd,&hChildStdoutWr,&sa,0));
   VERIFY(SetStdHandle(STD_OUTPUT_HANDLE,hChildStdoutWr));
   VERIFY(DuplicateHandle(
      GetCurrentProcess(),hChildStdoutRd,
      GetCurrentProcess(),&hChildStdoutRdDup,
      0,FALSE,DUPLICATE_SAME_ACCESS));
   CloseHandle(hChildStdoutRd);

   hSaveStderr=GetStdHandle(STD_ERROR_HANDLE);
   VERIFY(CreatePipe(&hChildStderrRd,&hChildStderrWr,&sa,0));
   VERIFY(SetStdHandle(STD_ERROR_HANDLE,hChildStderrWr));
   VERIFY(DuplicateHandle(
      GetCurrentProcess(),hChildStderrRd,
      GetCurrentProcess(),&hChildStderrRdDup,
      0,FALSE,DUPLICATE_SAME_ACCESS));
   CloseHandle(hChildStderrRd);

   HCURSOR hCursor=AfxGetApp()->LoadStandardCursor(IDC_WAIT);
   ::SetCursor(hCursor);

   STARTUPINFO si;
   ::ZeroMemory(&si,sizeof(STARTUPINFO));
   si.cb=sizeof(STARTUPINFO);
   si.dwFlags=STARTF_USESHOWWINDOW; //|STARTF_USESTDHANDLES;
   si.wShowWindow =bWindowless ? SW_HIDE:SW_SHOW;
   PROCESS_INFORMATION pi;
   ::ZeroMemory(&pi,sizeof(PROCESS_INFORMATION));
   bResult=CreateProcess(
      NULL,             // pointer to name of executable module
      (char*)qCommand,  // pointer to command line string
      &sa,              // process security attributes
      &sa,              // thread security attributes
      TRUE,             // handle inheritance flag
      CREATE_DEFAULT_ERROR_MODE,// creation flags
      NULL,             // pointer to new environment block
      NULL,             // pointer to current directory name
      &si,              // pointer to STARTUPINFO         -> input
      &pi               // pointer to PROCESS_INFORMATION -> ouput
   );
   if (bResult) {
      bResult=WaitForSingleObject(pi.hProcess,INFINITE);
      bResult=bResult==WAIT_FAILED ? FALSE:TRUE;
      CloseHandle(pi.hProcess);//20030422
      CloseHandle(pi.hThread); //20030422
   }

   hCursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
   ::SetCursor(hCursor);
   
   // After process creation, restore the saved STDIN and STDOUT.
   VERIFY(SetStdHandle(STD_INPUT_HANDLE,hSaveStdin));
   VERIFY(SetStdHandle(STD_OUTPUT_HANDLE,hSaveStdout));
   VERIFY(SetStdHandle(STD_ERROR_HANDLE,hSaveStderr));

   DWORD dwRead; 
   CHAR chBuf[BUFSIZE];
   
   // Close the write end of the pipe before reading from the
   // read end of the pipe.
   VERIFY(CloseHandle(hChildStdoutWr));
   for (;;) {
      if (!ReadFile(hChildStdoutRdDup,chBuf,BUFSIZE,&dwRead,NULL) ||
         dwRead==0) break;
      chBuf[dwRead]=0;
      sReturn+=chBuf;
   }
   VERIFY(CloseHandle(hChildStderrWr));
   for (;;) {
      if (!ReadFile(hChildStderrRdDup,chBuf,BUFSIZE,&dwRead,NULL) ||
         dwRead==0) break;
      chBuf[dwRead]=0;
      sReturn+=chBuf;
   }

   VERIFY(CloseHandle(hChildStdinWrDup));
   VERIFY(CloseHandle(hChildStdoutRdDup));
   VERIFY(CloseHandle(hChildStderrRdDup));

   if (sReturn.IsEmpty()) {
      sReturn="CreateProcessWithRedirectedIO() :\n";
      sReturn+=GetLastErrorMessage();
   }
}