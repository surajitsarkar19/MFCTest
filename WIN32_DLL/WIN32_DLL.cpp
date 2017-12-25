// WIN32_DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "WIN32_DLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is an example of an exported variable
WIN32_DLL_API int nWIN32_DLL=1;

// This is an example of an exported function.
WIN32_DLL_API int fnWIN32_DLL(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see WIN32_DLL.h for the class definition
CWIN32_DLL::CWIN32_DLL()
{
	m_nValue = 10;
	return;
}

int CWIN32_DLL::Add(int a, int b)
{
	return a+b;
}

float CWIN32_DLL::Add(float a, float b)
{
	return a+b;
}
