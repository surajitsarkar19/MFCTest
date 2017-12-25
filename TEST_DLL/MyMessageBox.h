/***
This class needs the following part to be addred in .rc file

IDD_MYMESSAGEBOX DIALOG  0, 0, 320, 200
STYLE DS_SETFONT | DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Dialog"
FONT 8, "MS Shell Dlg"
BEGIN
    DEFPUSHBUTTON   "OK",IDOK,209,179,50,14
    PUSHBUTTON      "Cancel",IDCANCEL,263,179,50,14
END


***/



#ifndef MYMESSAGEBOX_H__58888D1C_E7EF_43FF_822B_680E1AB2363B__INCLUDED_
#define MYMESSAGEBOX_H__58888D1C_E7EF_43FF_822B_680E1AB2363B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyButton.h"
#include "resource.h"

#define FLAG_DEF	0x0000 //default button flag
#define FLAG_OK		0x0001 //OK button flag
#define FLAG_CANCEL	0x0002 //Cancel button flag
#define FLAG_YES	0x0004 //Yes button flag
#define FLAG_NO		0x0008 //No button flag

#define MYMSG_OK	FLAG_OK
#define MYMSG_CANCEL	FLAG_CANCEL
#define MYMSG_YES	FLAG_YES
#define MYMSG_NO	FLAG_NO


// CMyMessageBox dialog

class CMyMessageBox : public CDialog
{
	DECLARE_DYNAMIC(CMyMessageBox)

public:
	//CMyMessageBox(CWnd* pParent = NULL);   // standard constructor
	CMyMessageBox(CWnd* pParent = NULL, LPCTSTR msg=L"", DWORD mbType = FLAG_OK);
	virtual ~CMyMessageBox();
	INT_PTR Show();
	int GetLineCount(LPTSTR msg);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

// Dialog Data
	enum { IDD = IDD_MYMESSAGEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HICON m_hIcon;

public:
	int borderheight1;
	int borderheight;

private:
	CMyButton m_button1;
	CMyButton m_button2;
	CStatic m_msgCtrl;
	DWORD m_btnFlag;
	CString m_strMsg;
	CString m_strTitle;
	CSize m_sDialogUnit;
	int cxChar, cyChar; //dialog text metric
	int width, heigth; //dialog size
	int maxCharWidth; //Maximum char width in a line
	LPTSTR szMaxChar; // max char pointer in a line
	int btnCount;

	bool bCustomButtonString;
	CString strPositive,strNegative;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void SetButtonString(LPCTSTR positiveButton, LPCTSTR negativeButton);
	CString LoadDextroString(CString str);
};

#endif