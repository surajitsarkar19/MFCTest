#include "stdafx.h" 
#include "circleprogress.h" 
 
///////////////////////////////////////////////////////////////////////////// 
// CCircleProgress 
 
IMPLEMENT_DYNCREATE(CCircleProgress, CWnd) 
 
///////////////////////////////////////////////////////////////////////////// 
// CCircleProgress properties 
 
short CCircleProgress::GetPoschange() 
{ 
	short result; 
	GetProperty(0x1, VT_I2, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetPoschange(short propVal) 
{ 
	SetProperty(0x1, VT_I2, propVal); 
} 
 
long CCircleProgress::GetStartColor() 
{ 
	long result; 
	GetProperty(0x8, VT_I4, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetStartColor(long propVal) 
{ 
	SetProperty(0x8, VT_I4, propVal); 
} 
 
long CCircleProgress::GetEndColor() 
{ 
	long result; 
	GetProperty(0x9, VT_I4, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetEndColor(long propVal) 
{ 
	SetProperty(0x9, VT_I4, propVal); 
} 
 
long CCircleProgress::GetBkColor() 
{ 
	long result; 
	GetProperty(0xa, VT_I4, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetBkColor(long propVal) 
{ 
	SetProperty(0xa, VT_I4, propVal); 
} 
 
double CCircleProgress::GetStartAngle() 
{ 
	double result; 
	GetProperty(0x2, VT_R8, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetStartAngle(double propVal) 
{ 
	SetProperty(0x2, VT_R8, propVal); 
} 
 
short CCircleProgress::GetNums() 
{ 
	short result; 
	GetProperty(0xb, VT_I2, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetNums(short propVal) 
{ 
	SetProperty(0xb, VT_I2, propVal); 
} 
 
double CCircleProgress::GetR2() 
{ 
	double result; 
	GetProperty(0x3, VT_R8, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetR2(double propVal) 
{ 
	SetProperty(0x3, VT_R8, propVal); 
} 
 
short CCircleProgress::GetStyle() 
{ 
	short result; 
	GetProperty(0xc, VT_I2, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetStyle(short propVal) 
{ 
	SetProperty(0xc, VT_I2, propVal); 
} 
 
double CCircleProgress::GetValue() 
{ 
	double result; 
	GetProperty(0xd, VT_R8, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetValue(double propVal) 
{ 
	SetProperty(0xd, VT_R8, propVal); 
} 
 
double CCircleProgress::GetMaxValue() 
{ 
	double result; 
	GetProperty(0xe, VT_R8, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetMaxValue(double propVal) 
{ 
	SetProperty(0xe, VT_R8, propVal); 
} 
 
double CCircleProgress::GetMinValue() 
{ 
	double result; 
	GetProperty(0xf, VT_R8, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetMinValue(double propVal) 
{ 
	SetProperty(0xf, VT_R8, propVal); 
} 
 
double CCircleProgress::GetDsubs() 
{ 
	double result; 
	GetProperty(0x4, VT_R8, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetDsubs(double propVal) 
{ 
	SetProperty(0x4, VT_R8, propVal); 
} 
 
long CCircleProgress::GetTextColor() 
{ 
	long result; 
	GetProperty(0x10, VT_I4, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetTextColor(long propVal) 
{ 
	SetProperty(0x10, VT_I4, propVal); 
} 
 
short CCircleProgress::GetDotNumber() 
{ 
	short result; 
	GetProperty(0x5, VT_I2, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetDotNumber(short propVal) 
{ 
	SetProperty(0x5, VT_I2, propVal); 
} 
 
CString CCircleProgress::GetUnit() 
{ 
	CString result; 
	GetProperty(0x11, VT_BSTR, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetUnit(LPCTSTR propVal) 
{ 
	SetProperty(0x11, VT_BSTR, propVal); 
} 
 
BOOL CCircleProgress::GetBUnit() 
{ 
	BOOL result; 
	GetProperty(0x6, VT_BOOL, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetBUnit(BOOL propVal) 
{ 
	SetProperty(0x6, VT_BOOL, propVal); 
} 
 
BOOL CCircleProgress::GetBMove() 
{ 
	BOOL result; 
	GetProperty(0x7, VT_BOOL, (void*)&result); 
	return result; 
} 
 
void CCircleProgress::SetBMove(BOOL propVal) 
{ 
	SetProperty(0x7, VT_BOOL, propVal); 
} 
 
///////////////////////////////////////////////////////////////////////////// 
// CCircleProgress operations 
 
void CCircleProgress::AboutBox() 
{ 
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL); 
} 