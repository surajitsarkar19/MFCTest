// Dialog1.cpp : implementation file
//

#include "stdafx.h"
#include "TEST_MFC.h"
#include "Dialog1.h"
#include "TEST_MFCDlg.h"

// CDialog1 dialog

IMPLEMENT_DYNAMIC(CDialog1, CDextroDialog)

CDialog1::CDialog1(CWnd* pParent /*=NULL*/)
	: CDextroDialog(CDialog1::IDD, pParent)
{

}

CDialog1::~CDialog1()
{
}

void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog1, CDextroDialog)
	ON_BN_CLICKED(IDCANCEL, &CDialog1::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog1::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialog1 message handlers

void CDialog1::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	theApp.ExitApplication();
}

void CDialog1::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	theApp.SetCurrentWindow(CTEST_MFCDlg::InitInstance());
}

CDialog1* CDialog1::InitInstance()
{
	CDialog1 *dlg = new CDialog1();
	dlg->Create(IDD);
	return dlg;
}
