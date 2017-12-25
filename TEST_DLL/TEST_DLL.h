// TEST_DLL.h : main header file for the TEST_DLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTEST_DLLApp
// See TEST_DLL.cpp for the implementation of this class
//

class CTEST_DLLApp : public CWinApp
{
public:
	CTEST_DLLApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
