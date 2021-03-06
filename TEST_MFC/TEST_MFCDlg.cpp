
// TEST_MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TEST_MFC.h"
#include "TEST_MFCDlg.h"
#include "..\\WIN32_DLL\\WIN32_DLL.h"
#include "Base64.h"
#include "UnicodeFile.h"
#include "Setupapi.h"
#include <iostream>
#include "Dialog1.h"

#include "mmsystem.h"

#include "Volume\Volume.h"

#include "Globals.h"
#include "..\\TEST_DLL\\MyClass.h"

#pragma comment(lib,"..\\Debug\\WIN32_DLL.lib") 
#pragma comment(lib,"..\\Debug\\MFC_DLL.lib") 
#pragma comment(lib, "winmm.lib")

#define TIMER_ID 287

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)

END_MESSAGE_MAP()


// CTEST_MFCDlg dialog




CTEST_MFCDlg::CTEST_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDextroDialog(CTEST_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTEST_MFCDlg::~CTEST_MFCDlg()
{
	
}

void CTEST_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_switch);
}

BEGIN_MESSAGE_MAP(CTEST_MFCDlg, CDextroDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CTEST_MFCDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK,IDC_CUSTOM1,&CTEST_MFCDlg::OnSwitchClicked)
	ON_BN_CLICKED(IDC_BUTTON1, &CTEST_MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CTEST_MFCDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CTEST_MFCDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CTEST_MFCDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTEST_MFCDlg message handlers

CTEST_MFCDlg* CTEST_MFCDlg::InitInstance()
{
	CTEST_MFCDlg *dlg = new CTEST_MFCDlg();
	dlg->Create(IDD);
	return dlg;
}



BOOL CTEST_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CWIN32_DLL dll;
	CString str;
	CString output;
	str.Format(L"Add int %d",dll.Add(5,7));
	output+=str+L"\n";
	str.Format(L"Add  Int %f",dll.Add((float)5.6,(float)7.1));
	output+=str+L"\n";
	str.Format(L"Add  Int %d",dll.m_nValue);
	output+=str+L"\n";
	GetDlgItem(IDC_STATIC_OUTPUT)->SetWindowText(output);

	queue.Push(new CString(L"asd"));
	queue.Push(new CString(L"awr"));
	queue.Push(new CString(L"jvu"));

	TRACE(L"\nLength = %d",queue.GetSize());
	DisplayQueue();

	//Base64Encode();
	//AddUnicodeString();
	USBDevice();

	//SetTimer(TIMER_ID,500,NULL);

	//MicrophoneDemo(0);

	


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTEST_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTEST_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTEST_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTEST_MFCDlg::OnSwitchClicked(NMHDR * pNotifyStruct, LRESULT* result)
{
	PNMONOFFCTRL nm = (PNMONOFFCTRL)pNotifyStruct;
	bool val = nm->toggleState;
	TRACE(L"%i",val);
	*result = 0;
}

void CTEST_MFCDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	/*CString *s = queue.Pop();
	delete s;
	DisplayQueue();*/

	//CString ss = L"USBケーブルでスマートフォンを接続し、デバッグモードを有効にしてください。|suraসুরজিৎ";
	//CString ss = L"Surajit|hi";
	//CString ss = L"আমার নাম সুরজিৎ হয়|khgkhhmmm";
	//SendUtfString(ss);


	VolumeInDemo();

	//MfcDllTest();
}

void CTEST_MFCDlg::DisplayQueue()
{
	if(queue.GetCount()>0)
    {
		POSITION pos;
		pos=queue.GetHeadPosition();
		do
		{
		   //display first image.then set timer
		   CString *str = queue.GetNext(pos);
		   TRACE(L"\n%s",str->GetBuffer());
		   str->ReleaseBuffer();
		}while(pos!=NULL);
    }
}

void CTEST_MFCDlg::Base64Encode()
{
	char *buff=0;
	int length = load_file("C:\\Users\\Dextrosoft\\Desktop\\adb\\AdbWinApi.dll",&buff);
	int encoded_length = base64_encode_get_length(length);
	char *output = (char*)malloc(encoded_length* sizeof(char));
	int status = base64_encode((unsigned char*)buff,length,output);
	store_file(output,"C:\\Users\\Dextrosoft\\Desktop\\adb\\base64.txt");
	free(buff);
	free(output);
}

void CTEST_MFCDlg::AddUnicodeString(void)
{
	CString file = L"C:\\Users\\Dextrosoft\\Desktop\\test.txt";
	CUnicodeFile f(file,CUnicodeFile::modeReadWrite | CUnicodeFile::modeNoTruncate);
	BOOL ret  = f.Open();
	f.SeekToEnd();
	f.WriteString(L"USBケーブルでスマートフォンを接続し、デバッグモードを有効にしてください。");
	f.Close();
}

int CTEST_MFCDlg::USBDevice(void)
{


	// Program
    cout << "USB Device Lister." << endl;
 
    // Get Number Of Devices
    UINT nDevices = 0;
    GetRawInputDeviceList( NULL, &nDevices, sizeof( RAWINPUTDEVICELIST ) );
 
    // Got Any?
    if( nDevices < 1 )
    {
        // Exit
        cout << "ERR: 0 Devices?";
        cin.get();
        return 0;
    }
     
    // Allocate Memory For Device List
    PRAWINPUTDEVICELIST pRawInputDeviceList;
    pRawInputDeviceList = new RAWINPUTDEVICELIST[ sizeof( RAWINPUTDEVICELIST ) * nDevices ];
 
    // Got Memory?
    if( pRawInputDeviceList == NULL )
    {
        // Error
        cout << "ERR: Could not allocate memory for Device List.";
        cin.get();
        return 0;
    }
     
    // Fill Device List Buffer
    int nResult;
    nResult = GetRawInputDeviceList( pRawInputDeviceList, &nDevices, sizeof( RAWINPUTDEVICELIST ) );
 
    // Got Device List?
    if( nResult < 0 )
    {
        // Clean Up
        delete [] pRawInputDeviceList;
 
        // Error
        cout << "ERR: Could not get device list.";
        cin.get();
        return 0;
    }
 
    // Loop Through Device List
    for( UINT i = 0; i < nDevices; i++ )
    {
        // Get Character Count For Device Name
        UINT nBufferSize = 0;
        nResult = GetRawInputDeviceInfo( pRawInputDeviceList[i].hDevice, // Device
                                         RIDI_DEVICENAME,                // Get Device Name
                                         NULL,                           // NO Buff, Want Count!
                                         &nBufferSize );                 // Char Count Here!
 
        // Got Device Name?
        if( nResult < 0 )
        {
            // Error
            cout << "ERR: Unable to get Device Name character count.. Moving to next device." << endl << endl;
 
            // Next
            continue;
        }
 
        // Allocate Memory For Device Name
        WCHAR* wcDeviceName = new WCHAR[ nBufferSize + 1 ];
         
        // Got Memory
        if( wcDeviceName == NULL )
        {
            // Error
            cout << "ERR: Unable to allocate memory for Device Name.. Moving to next device." << endl << endl;
 
            // Next
            continue;
        }
 
        // Get Name
        nResult = GetRawInputDeviceInfo( pRawInputDeviceList[i].hDevice, // Device
                                         RIDI_DEVICENAME,                // Get Device Name
                                         wcDeviceName,                   // Get Name!
                                         &nBufferSize );                 // Char Count
 
        // Got Device Name?
        if( nResult < 0 )
        {
            // Error
            cout << "ERR: Unable to get Device Name.. Moving to next device." << endl << endl;
 
            // Clean Up
            delete [] wcDeviceName;
 
            // Next
            continue;
        }
 
        // Set Device Info & Buffer Size
        RID_DEVICE_INFO rdiDeviceInfo;
        rdiDeviceInfo.cbSize = sizeof( RID_DEVICE_INFO );
        nBufferSize = rdiDeviceInfo.cbSize;
 
        // Get Device Info
        nResult = GetRawInputDeviceInfo( pRawInputDeviceList[i].hDevice,
                                         RIDI_DEVICEINFO,
                                         &rdiDeviceInfo,
                                         &nBufferSize );
 
        // Got All Buffer?
        if( nResult < 0 )
        {
            // Error
            cout << "ERR: Unable to read Device Info.. Moving to next device." << endl << endl;
 
            // Next
            continue;
        }
 
        // Mouse
        if( rdiDeviceInfo.dwType == RIM_TYPEMOUSE )
        {
            // Current Device
            cout << endl << "Displaying device " << i+1 << " information. (MOUSE)" << endl;
            wcout << L"Device Name: " << wcDeviceName << endl;
            cout << "Mouse ID: " << rdiDeviceInfo.mouse.dwId << endl;
            cout << "Mouse buttons: " << rdiDeviceInfo.mouse.dwNumberOfButtons << endl;
            cout << "Mouse sample rate (Data Points): " << rdiDeviceInfo.mouse.dwSampleRate << endl;
            if( rdiDeviceInfo.mouse.fHasHorizontalWheel )
            {
                cout << "Mouse has horizontal wheel" << endl;
            }
            else
            {
                cout << "Mouse does not have horizontal wheel" << endl;
            }
        }
 
        // Keyboard
        else if( rdiDeviceInfo.dwType == RIM_TYPEKEYBOARD )
        {
            // Current Device
            cout << endl << "Displaying device " << i+1 << " information. (KEYBOARD)" << endl;
            wcout << L"Device Name: " << wcDeviceName << endl;
            cout << "Keyboard mode: " << rdiDeviceInfo.keyboard.dwKeyboardMode << endl;
            cout << "Number of function keys: " << rdiDeviceInfo.keyboard.dwNumberOfFunctionKeys << endl;
            cout << "Number of indicators: " << rdiDeviceInfo.keyboard.dwNumberOfIndicators << endl;
            cout << "Number of keys total: " << rdiDeviceInfo.keyboard.dwNumberOfKeysTotal << endl;
            cout << "Type of the keyboard: " << rdiDeviceInfo.keyboard.dwType << endl;
            cout << "Subtype of the keyboard: " << rdiDeviceInfo.keyboard.dwSubType << endl;
        }
 
        // Some HID
        else // (rdi.dwType == RIM_TYPEHID)
        {
            // Current Device
            cout << endl << "Displaying device " << i+1 << " information. (HID)" << endl;
            wcout << L"Device Name: " << wcDeviceName << endl;
            cout << "Vendor Id:" << rdiDeviceInfo.hid.dwVendorId << endl;
            cout << "Product Id:" << rdiDeviceInfo.hid.dwProductId << endl;
            cout << "Version No:" << rdiDeviceInfo.hid.dwVersionNumber << endl;
            cout << "Usage for the device: " << rdiDeviceInfo.hid.usUsage << endl;
            cout << "Usage Page for the device: " << rdiDeviceInfo.hid.usUsagePage << endl;
        }
 
        // Delete Name Memory!
        delete [] wcDeviceName;
    }
 
    // Clean Up - Free Memory
    delete [] pRawInputDeviceList;
 
    // Exit
    cout << endl << "Finnished.";
    cin.get();
    return 0;
}

void CTEST_MFCDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//OnCancel();
	KillTimer(TIMER_ID);
	theApp.ExitApplication();
}
void CTEST_MFCDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
	KillTimer(TIMER_ID);
	DestroyWindow();
}

void CTEST_MFCDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	theApp.SetCurrentWindow(CDialog1::InitInstance());
	//dlg->ShowWindow(SW_SHOW);
	//DestroyWindow();
}

void CTEST_MFCDlg::MicrophoneDemo(int deviceId)
{
	MMRESULT rc;              // Return code.
    HMIXER hMixer;            // Mixer handle used in mixer API calls.
    MIXERCONTROL mxc;         // Holds the mixer control data.
    MIXERLINE mxl;            // Holds the mixer line data.
    MIXERLINECONTROLS mxlc;   // Obtains the mixer control.

    // Open the mixer. This opens the mixer with a deviceID of 0. If you
    // have a single sound card/mixer, then this will open it. If you have
    // multiple sound cards/mixers, the deviceIDs will be 0, 1, 2, and
    // so on.
    rc = mixerOpen(&hMixer, deviceId,0,0,0);
    if (MMSYSERR_NOERROR != rc) {
        // Couldn't open the mixer.
		TRACE(L"Couldn't open the mixer.\n");
    }

    // Initialize MIXERLINE structure.
    ZeroMemory(&mxl,sizeof(mxl));
    mxl.cbStruct = sizeof(mxl);

    // Specify the line you want to get. You are getting the input line
    // here. If you want to get the output line, you need to use
    // MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT.
    mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;

    rc = mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl,
                           MIXER_GETLINEINFOF_COMPONENTTYPE);
    if (MMSYSERR_NOERROR == rc) {
        // Couldn't get the mixer line.
		TRACE(L"Couldn't get the mixer line.\n");
    }

    // Get the control.
    ZeroMemory(&mxlc, sizeof(mxlc));
    mxlc.cbStruct = sizeof(mxlc);
    mxlc.dwLineID = mxl.dwLineID;
    mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_PEAKMETER;
    mxlc.cControls = 1;
    mxlc.cbmxctrl = sizeof(mxc);
    mxlc.pamxctrl = &mxc;
    ZeroMemory(&mxc, sizeof(mxc));
    mxc.cbStruct = sizeof(mxc);
    rc = mixerGetLineControls((HMIXEROBJ)hMixer,&mxlc,
                               MIXER_GETLINECONTROLSF_ONEBYTYPE);
    if (MMSYSERR_NOERROR != rc) {
        // Couldn't get the control.
		TRACE(L"Couldn't get the control.\n");
    }

    // After successfully getting the peakmeter control, the volume range
    // will be specified by mxc.Bounds.lMinimum to mxc.Bounds.lMaximum.

    MIXERCONTROLDETAILS mxcd;             // Gets the control values.
    MIXERCONTROLDETAILS_SIGNED volStruct; // Gets the control values.
    long volume;                          // Holds the final volume value.

    // Initialize the MIXERCONTROLDETAILS structure
    ZeroMemory(&mxcd, sizeof(mxcd));
    mxcd.cbStruct = sizeof(mxcd);
    mxcd.cbDetails = sizeof(volStruct);
    mxcd.dwControlID = mxc.dwControlID;
    mxcd.paDetails = &volStruct;
    mxcd.cChannels = 1;

    // Get the current value of the peakmeter control. Typically, you
    // would set a timer in your program to query the volume every 10th
    // of a second or so.
    rc = mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd,
                                 MIXER_GETCONTROLDETAILSF_VALUE);
    if (MMSYSERR_NOERROR == rc) {
        // Couldn't get the current volume.
		TRACE(L"Couldn't get the current volume.\n");
    }
    volume = volStruct.lValue;

    // Get the absolute value of the volume.
    if (volume < 0)
        volume = -volume;

	TRACE(L"Volume = %d\n",volume);
}


BYTE* stringToBytesUTF(CString str,int *dataLength){
	int length = str.GetLength();
	TCHAR *buffer = str.GetBuffer();
	int utfLength = length << 1;//allocate double buffer
	*dataLength = utfLength;
	byte *b = new byte[utfLength];
	for(int i = 0; i < length; i++) {
		int bpos = i << 1;
		b[bpos] = (byte) ((buffer[i]&0xFF00)>>8);
		b[bpos + 1] = (byte) (buffer[i]&0x00FF);
	}
	str.ReleaseBuffer();
	return b;
}

void CTEST_MFCDlg::SendUtfString(CString strData)
{
	CString str;
	//str.Format(L"Resources\\ADB\\adb.exe -s "+gDeviceSerial+L" forward tcp:%d tcp:%d",38345,38345);
	str.Format(L"Resources\\ADB\\adb.exe forward tcp:%d tcp:%d",38345,38345);
	CString output;
	DWORD err;
	output = ExecCmd(str.GetBuffer(),err,NULL);
	str.ReleaseBuffer();
	int bootCount = 0;
	CSocket sock;
	BOOL bSuccess = sock.Create();
	if(bSuccess)
	{
		bSuccess = sock.Connect(L"127.0.0.1",38345);
		if(bSuccess)
		{
			int cmdLength = 4;
			
			int argLength = 0;
			byte *b = stringToBytesUTF(strData,&argLength);
			

			int totalDataLength = cmdLength+4+argLength;
			
			char *cmd = "CASE";
			//BYTE *data = new BYTE[totalDataLength];
			char *data = new char[totalDataLength];
			memset(data,0,totalDataLength);
			memcpy(data,cmd,4);
			CString argsize;
			argsize.Format(L"%04X",argLength);
			char *size = CSTRtoCHAR(argsize);
			memcpy(data+4,size,4);
			delete[] size;

			memcpy(data+8,b,argLength);//copy the argument

			BYTE bb[200];
			memset(bb,0,sizeof(bb));
			memcpy(bb,data,totalDataLength);


			bSuccess = sock.Send(data,totalDataLength);
			delete[] data;
			delete[] b;
		}
		sock.Close();
	}
}

void CTEST_MFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if(nIDEvent == TIMER_ID)
	{
		MicrophoneDemo(0);
	}
	CDextroDialog::OnTimer(nIDEvent);
}


bool CALLBACK CTEST_MFCDlg::EnumInputLineProc( UINT uLineIndex,MIXERLINE* pLineInfo, DWORD dwUserValue )
{
    if ( pLineInfo->dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE )
    {
        *((UINT*)dwUserValue) = uLineIndex;
        return false;
    }
    return true;
}

void CTEST_MFCDlg::OnMicVolumeChange( DWORD dwCurrentVolume, DWORD dwUserValue )
{
	TRACE(L"OnMicVolumeChange(%ld,%ld)\n",dwCurrentVolume,dwUserValue);
}

int CTEST_MFCDlg::VolumeInDemo(void)
{
	UINT uMicrophoneLineIndex = (UINT)-1;
	if ( !CVolumeInXXX::EnumerateInputLines( EnumInputLineProc, 
							   (DWORD)&uMicrophoneLineIndex ) )
	{
	   // handle error
	}
	if ( uMicrophoneLineIndex == (UINT)-1 )
	{
		// Error: mic volume'ing is not available.
	}
	IVolume* pMicrophoneVolume = (IVolume*)new CVolumeInXXX( uMicrophoneLineIndex );
	if ( !pMicrophoneVolume || !pMicrophoneVolume->IsAvailable() )
	{
		// handle error
	   TRACE(L"Microphone is not availble\n");
	}
	
	TRACE(L"Using microphone device %d\n",uMicrophoneLineIndex);

	pMicrophoneVolume->RegisterNotificationSink(OnMicVolumeChange,2);

	//delete pMicrophoneVolume;
	return 0;
}

void CTEST_MFCDlg::MfcDllTest(void)
{
	OurMessageBox(NULL,L"hello",MB_OK);
}

void CTEST_MFCDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CMyClass cls;
	CString str = cls.SayHello(L"srs");
	INT_PTR ret = OurMessageBox(this,str,MB_OK);
	TRACE(L"\%ld",ret);
}
