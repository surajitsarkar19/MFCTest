#include "StdAfx.h"
#include "MyClass.h"
#include "TEST_DLL.h"
#include "MyMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OURMESSAGEBOX

INT_PTR OurMessageBox(CWnd* wnd,LPCTSTR msg,DWORD flag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ASSERT(msg != NULL);
#ifdef OURMESSAGEBOX
	CMyMessageBox dlgs(wnd,msg,flag);
	return dlgs.Show();
#else
	if(wnd == NULL)
	{
		return MessageBox(NULL,msg,AfxGetAppName(),flag);
	}
	else
	{
		return MessageBox(wnd->m_hWnd,msg,AfxGetAppName(),flag);
	}
#endif
}

CMyClass::CMyClass(void)
{
}

CMyClass::~CMyClass(void)
{
}

LPCTSTR CMyClass::SayHello (LPCTSTR strName)
{
	tmp = _T("Hello ");
    tmp += strName;
    return (LPCTSTR)tmp; 
}
