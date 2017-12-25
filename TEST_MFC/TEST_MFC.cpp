
// TEST_MFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TEST_MFC.h"
#include "TEST_MFCDlg.h"
#include "MainWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString AppPATH;


// CTEST_MFCApp

BEGIN_MESSAGE_MAP(CTEST_MFCApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTEST_MFCApp construction

CTEST_MFCApp::CTEST_MFCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTEST_MFCApp object

CTEST_MFCApp theApp;


// CTEST_MFCApp initialization

BOOL CTEST_MFCApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	//CTEST_MFCDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with OK
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with Cancel
	//}

	m_dummyDlg = new CDextroDialog(IDD_DEXTRODIALOG);
	m_dummyDlg->Create(IDD_DEXTRODIALOG);
	m_pMainWnd = m_dummyDlg;
	m_pMainWnd->ShowWindow(SW_HIDE);
	SetCurrentWindow(CTEST_MFCDlg::InitInstance());
	//dlg->ShowWindow(SW_SHOW);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return TRUE;


	/*m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow ( m_nCmdShow) ;
	m_pMainWnd->UpdateWindow ( ) ;
	return TRUE;*/
}

int CTEST_MFCApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinAppEx::ExitInstance();
}

void CTEST_MFCApp::ExitApplication()
{
	if(m_dlg)
	{
		m_dlg->DestroyWindow();
		m_dlg = NULL;
	}
	if(m_pMainWnd)
	{
		m_pMainWnd->DestroyWindow();
		m_pMainWnd = NULL;
	}
}

void CTEST_MFCApp::SetCurrentWindow(CDextroDialog *dlg)
{
	if(m_dlg)
	{
		CDextroDialog *tmpDlg = m_dlg;
		m_dlg = dlg;
		m_dlg->ShowWindow(SW_SHOW);
		tmpDlg->DestroyWindow();
		//m_dlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_dlg = dlg;
		m_dlg->ShowWindow(SW_SHOW);
	}
}
