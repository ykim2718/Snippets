#include <stdio.h> 
#include <afxwin.h> // MFC core and standard components
#include <afxext.h> // MFC extensions

#define BUFSIZE 4096

// http://tcl.apache.org/sources/tcl/win/nmakehlp.c.html
// 20030423

typedef struct {
    HANDLE pipe;
    char buffer[1000];
} pipeinfo;

pipeinfo Out = {INVALID_HANDLE_VALUE, '\0'};
pipeinfo Err = {INVALID_HANDLE_VALUE, '\0'};

DWORD WINAPI
ReadFromPipe (LPVOID args)
{
    pipeinfo *pi = (pipeinfo *) args;
    char *lastBuf = pi->buffer;
    DWORD dwRead;
    BOOL ok;

again:
    ok = ReadFile(pi->pipe, lastBuf, 25, &dwRead, 0L);
    if (!ok || dwRead == 0) {
	CloseHandle(pi->pipe);
	return 0;
    }
    lastBuf += dwRead;
    goto again;

    return 0;  /* makes the compiler happy */
}

void CreateProcessWithRedirectedIO2(
   const char *qCommand,
   CString &sReturn,
   int bWindowless
   )
{
    sReturn.Empty();

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;
    DWORD threadID;
    BOOL ok;
    HANDLE hProcess, h, pipeThreads[2];

    hProcess = GetCurrentProcess();

    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags   = STARTF_USESTDHANDLES;
    si.hStdInput = INVALID_HANDLE_VALUE;

    ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    /* create a non-inheritible pipe. */
    CreatePipe(&Out.pipe, &h, &sa, 0);

    /* dupe the write side, make it inheritible, and close the original. */
    DuplicateHandle(hProcess, h, hProcess, &si.hStdOutput, 
	    0, TRUE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE);

    /* Same as above, but for the error side. */
    CreatePipe(&Err.pipe, &h, &sa, 0);
    DuplicateHandle(hProcess, h, hProcess, &si.hStdError, 
	    0, TRUE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE);


    ok = CreateProcess(
	    NULL,	    /* Module name. */
	    (char*)qCommand,	    /* Command line. */
	    NULL,	    /* Process handle not inheritable. */
	    NULL,	    /* Thread handle not inheritable. */
	    TRUE,	    /* yes, inherit handles. */
	    DETACHED_PROCESS, /* No console for you. */
	    NULL,	    /* Use parent's environment block. */
	    NULL,	    /* Use parent's starting directory. */
	    &si,	    /* Pointer to STARTUPINFO structure. */
	    &pi);	    /* Pointer to PROCESS_INFORMATION structure. */

    if (!ok) {
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
          sReturn=szMsgBuf;
       return;
    }

    /* close our references to the write handles that have now been inherited. */
    CloseHandle(si.hStdOutput);
    CloseHandle(si.hStdError);

    WaitForInputIdle(pi.hProcess, 5000);
    CloseHandle(pi.hThread);

    /* start the pipe reader threads. */
    pipeThreads[0] = CreateThread(NULL, 0, ReadFromPipe, &Out, 0, &threadID);
    pipeThreads[1] = CreateThread(NULL, 0, ReadFromPipe, &Err, 0, &threadID);

    /* block waiting for the process to end. */
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);

    /* wait for our pipe to get done reading, should it be a little slow. */
    WaitForMultipleObjects(2, pipeThreads, TRUE, 500);
    CloseHandle(pipeThreads[0]);
    CloseHandle(pipeThreads[1]);

    /* Get the output */
    sReturn=Out.buffer;

}
