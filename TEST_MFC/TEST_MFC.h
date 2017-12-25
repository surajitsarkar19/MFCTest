
// TEST_MFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "DextroDialog.h"

#define LOG	ATLTRACE; \
	TRACE0(L"\n")
// CTEST_MFCApp:
// See TEST_MFC.cpp for the implementation of this class
//

extern CString AppPATH;

class CTEST_MFCApp : public CWinAppEx
{
public:
	CTEST_MFCApp();


	CDextroDialog *m_dlg;
	CDextroDialog *m_dummyDlg;

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
public:
	void ExitApplication();
	void SetCurrentWindow(CDextroDialog *dlg);
};

extern CTEST_MFCApp theApp;