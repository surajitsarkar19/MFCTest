
// TEST_MFCDlg.h : header file
//

#pragma once
#include "onoffctrl.h"
#include "Queue.h"


// CTEST_MFCDlg dialog
class CTEST_MFCDlg : public CDextroDialog
{
// Construction
public:
	//static GUID GUID_DEVINTERFACE_USB_DEVICE = { 0xA5DCBF10L, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } };
	CTEST_MFCDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CTEST_MFCDlg();

// Dialog Data
	enum { IDD = IDD_TEST_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	COnOffCtrl m_switch;
	CQueue<CString> queue;
	void DisplayQueue();
	afx_msg void OnBnClickedOk();
	afx_msg void OnSwitchClicked(NMHDR * pNotifyStruct, LRESULT* result);
	afx_msg void OnBnClickedButton1();
	void Base64Encode();
	void AddUnicodeString(void);
	int USBDevice(void);
	static CTEST_MFCDlg* InitInstance();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	void MicrophoneDemo(int deviceId);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SendUtfString(CString strData);

	static bool CALLBACK EnumInputLineProc( UINT uLineIndex,MIXERLINE* pLineInfo, DWORD dwUserValue );
	int VolumeInDemo(void);
	static void CALLBACK OnMicVolumeChange( DWORD dwCurrentVolume, DWORD dwUserValue );
	void MfcDllTest(void);
	afx_msg void OnBnClickedButton3();
};
