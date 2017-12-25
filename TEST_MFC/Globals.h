#pragma once

char* CSTRtoCHAR(CString& orig);
CString ExecCmd( LPTSTR pCmdArg, DWORD& errorCode, LPCTSTR pCurrentDirectory);
