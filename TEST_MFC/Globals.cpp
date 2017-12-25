#include "StdAfx.h"
#include "Globals.h"

#define MAX_CMD_PATH 1024

char* CSTRtoCHAR(CString& orig){
	char *ret = NULL;
	TCHAR *ptr = NULL;
	ptr = orig.GetBuffer(orig.GetLength());
	orig.ReleaseBuffer();
	int len=orig.GetLength();
	ret=new char[len+1];
	memset(ret,0,len+1);
	int i=wcstombs(ret,ptr,len);
	ret[len]='\0';
	return ret;
}

CString ExecCmd( LPTSTR pCmdArg, DWORD& errorCode, LPCTSTR pCurrentDirectory)
{
   // Handle Inheritance - to pipe child's stdout via pipes to parent, handles must be inherited.
   //   SECURITY_ATTRIBUTES.bInheritHandle must be TRUE
   //   CreateProcess parameter bInheritHandles must be TRUE;
   //   STARTUPINFO.dwFlags must have STARTF_USESTDHANDLES set.
 
   CString strResult=L""; // Contains result of cmdArg.
   HANDLE hChildStdoutRd; // Read-side, used in calls to ReadFile() to get child's stdout output.
   HANDLE hChildStdoutWr; // Write-side, given to child process using si struct.
   errorCode=0; //no error
 
   BOOL fSuccess;

   TCHAR currentDirectory[MAX_PATH];
   memset(currentDirectory,0,sizeof(currentDirectory));
   if(pCurrentDirectory!=NULL)
   {
	   wcscpy(currentDirectory,pCurrentDirectory);
   }
 
   BOOL ret=FALSE;
   wchar_t cmd[]=L"cmd.exe";
   wchar_t cmdline[ MAX_CMD_PATH ];
   swprintf_s( cmdline, L"%s /C %s", cmd, pCmdArg );
   // Create security attributes to create pipe.
   SECURITY_ATTRIBUTES saAttr = {0} ;
   saAttr.nLength			   = sizeof(saAttr);
   saAttr.bInheritHandle       = TRUE; // Set the bInheritHandle flag so pipe handles are inherited by child process. Required.
   saAttr.lpSecurityDescriptor = NULL;
 
   // Create a pipe to get results from child's stdout.
   // I'll create only 1 because I don't need to pipe to the child's stdin.
   if ( !CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0) )
   {
      ret=FALSE;
	  DWORD error=::GetLastError();
      return strResult;
   }
 
   STARTUPINFO si = {0}; // specifies startup parameters for child process.
   memset(&si,0,sizeof(si));
   si.cb          = sizeof(si);
   si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES; // STARTF_USESTDHANDLES is Required.
   si.hStdOutput  = hChildStdoutWr; // Requires STARTF_USESTDHANDLES in dwFlags.
   si.hStdError   = hChildStdoutWr; // Requires STARTF_USESTDHANDLES in dwFlags.
   si.hStdInput   = NULL;
   si.wShowWindow = SW_HIDE; // Prevents cmd window from flashing. Requires STARTF_USESHOWWINDOW in dwFlags.
 
   PROCESS_INFORMATION pi  = { 0 };
   memset(&pi,0,sizeof(pi));
 
   if(pCurrentDirectory == NULL)
   {
	   // Create the child process.
	   fSuccess = CreateProcess(
		  NULL,
		  cmdline,            // command line
		  NULL,               // process security attributes
		  NULL,               // primary thread security attributes
		  TRUE,               // TRUE=handles are inherited. Required.
		  NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW, // creation flags
		  NULL,               // use parent's environment
		  NULL,               // use parent's current directory
		  &si,                // __in, STARTUPINFO pointer
		  &pi);               // __out, receives PROCESS_INFORMATION
   }
   else
   {
	   // Create the child process.
	   fSuccess = CreateProcess(
		  NULL,
		  cmdline,            // command line
		  NULL,               // process security attributes
		  NULL,               // primary thread security attributes
		  TRUE,               // TRUE=handles are inherited. Required.
		  NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW, // creation flags
		  NULL,               // use parent's environment
		  currentDirectory,               // set current directory
		  &si,                // __in, STARTUPINFO pointer
		  &pi);               // __out, receives PROCESS_INFORMATION
   }
 
   if (! fSuccess)
   {
      // CreateProcess() failed
      // Get the error from the system
		
	  ret=FALSE;
	  errorCode=GetLastError();

   }
   else
   {
	  
	   // Wait until child processes exit. Don't wait forever.
	   WaitForSingleObject( pi.hProcess, 2000 );
	   
	   DWORD exitCode;
	   BOOL result = GetExitCodeProcess(pi.hProcess, &exitCode);

	   if (!result)
	   {
		 // Could not get exit code.
		 errorCode=GetLastError();
		 TRACE(_T("Executed command but couldn't get exit code.\nCommand=%s\n"), pCmdArg);
		 ret=FALSE;
	   }
	   else{
		  // We succeeded.
		  ret=TRUE;
	   } 

	   TerminateProcess( pi.hProcess, 0 ); //unconditionally cause a process and all of its associate threades to exit
	 
	   // Close process and thread handles.
	   CloseHandle( pi.hProcess );
	   CloseHandle( pi.hThread );

	   // Close the write end of the pipe before reading from the read end of the pipe.
	   if (!CloseHandle(hChildStdoutWr))
	   {
		  errorCode=GetLastError();
		  return strResult;
	   }

	   // Read output from the child process.
	   for (;;)
	   {
		  DWORD dwRead;
		  CHAR chBuf[4096];
		  ZeroMemory(chBuf,sizeof(chBuf));
		  // Read from pipe that is the standard output for child process.
		  bool done = !ReadFile( hChildStdoutRd, chBuf, 4096, &dwRead, NULL) || dwRead == 0;
		  if( done )
		  {
			 //errorCode=ErrorMessage(L"CreateProcess");
			 break;
		  }
	 
		  // Append result to string.
		  CString result(chBuf, dwRead);
		  result.Replace(L"\r\r\n",L"\r\n");
		  //CString result(str_replace(chBuf,"<DIR>","<>"));
		  //char *opr=str_replace(chBuf,"\r\r\n","\r\n");
		  //CString result(opr);
		  
		  strResult = strResult + result;
		
		  //free(opr);
		  result.Empty();
	   }

	   ret=TRUE;

	   // Close the pipe handle
	   CloseHandle( hChildStdoutRd );   
	 
   }
 //TRACE("\n%S",pCmdArg);
   return strResult;
 
}
