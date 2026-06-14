// ShellExecute.h: interface for the CShellExecute class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHELLEXECUTE_H__1F5DCB22_44A9_11D5_9E85_0000E8C3064A__INCLUDED_)
#define AFX_SHELLEXECUTE_H__1F5DCB22_44A9_11D5_9E85_0000E8C3064A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShellExecute  
{
public:
	BOOL m_bShowWindow;
	HANDLE m_hProcess;
   virtual void OnProcessStderr(const char *qMessage) {};
   virtual void OnProcessStdout(const char *qMessage) {};
   virtual void OnProcessEnd(const char *qMessage) {};
   virtual void OnProcessBegin(const char *qMessage) {};
   void ResetCommand() { m_aCommand.RemoveAll(); };
   void SetCommand(const char *qCommand) { m_aCommand.Add(qCommand); };
	void KillProcess();
	void Commence();

	CStringArray m_aCommand;

	CShellExecute();
	virtual ~CShellExecute();
protected:
	BOOL CreateProcess();
};

#endif // !defined(AFX_SHELLEXECUTE_H__1F5DCB22_44A9_11D5_9E85_0000E8C3064A__INCLUDED_)
