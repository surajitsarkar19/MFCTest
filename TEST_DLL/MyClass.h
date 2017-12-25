#pragma once


#ifdef _USRDLL
#define MFC_DLL_API AFX_CLASS_EXPORT
#else
#define MFC_DLL_API AFX_CLASS_IMPORT
#endif

MFC_DLL_API INT_PTR OurMessageBox(CWnd* wnd,LPCTSTR msg,DWORD flag);

class MFC_DLL_API CMyClass: public CObject
{
public:
	LPCTSTR SayHello (LPCTSTR strName);
	CMyClass();
	virtual ~CMyClass();
private:
	CString tmp;

};
