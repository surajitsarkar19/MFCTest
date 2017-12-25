// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the WIN32_DLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// WIN32_DLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef WIN32_DLL_EXPORTS
#define WIN32_DLL_API __declspec(dllexport)
#else
#define WIN32_DLL_API __declspec(dllimport)
#endif

// This class is exported from the WIN32_DLL.dll
class WIN32_DLL_API CWIN32_DLL {
public:
	int m_nValue;
public:
	CWIN32_DLL(void);
	// TODO: add your methods here.
	int Add(int a,int b);
	float Add(float a, float b);
};

extern WIN32_DLL_API int nWIN32_DLL;

WIN32_DLL_API int fnWIN32_DLL(void);
