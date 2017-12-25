// CMyMessageBox.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MyMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define backgroundcolor RGB(255,255,255)
#define headercolor	RGB(76,76,76)

// CMyMessageBox dialog

IMPLEMENT_DYNAMIC(CMyMessageBox, CDialog)

CMyMessageBox::CMyMessageBox(CWnd* pParent /*=NULL*/ , LPCTSTR msg ,DWORD mbType /*= FLAG_OK*/)
	: CDialog(CMyMessageBox::IDD, pParent)
{
	//m_btnFlag = mbType;
	m_strMsg = msg;
	szMaxChar = NULL;
	if(pParent)
		pParent->GetWindowText(m_strTitle);
	else
		m_strTitle = AfxGetAppName();
	borderheight1 = 45;
	borderheight = 60;
	btnCount = 0;
	bCustomButtonString = false;
	/*if(m_btnFlag & FLAG_OK)
	{
		btnCount++;
	}
	if(m_btnFlag & FLAG_YES)
	{
		btnCount++;
	}
	if(m_btnFlag & FLAG_CANCEL)
	{
		btnCount++;
	}
	if(m_btnFlag & FLAG_NO)
	{
		btnCount++;
	}*/

	
	if((mbType & MB_OKCANCEL) == MB_OKCANCEL)
	{
		btnCount = 2;
		m_btnFlag = FLAG_OK | FLAG_CANCEL;
	}
	else if((mbType & MB_YESNO) == MB_YESNO)
	{
		btnCount = 2;
		m_btnFlag = FLAG_YES | FLAG_NO;
	}
	else if((mbType & MB_OK) == MB_OK)
	{
		m_btnFlag = FLAG_OK;
		btnCount = 1;
	}
	else
	{
		//default ok
		m_btnFlag = FLAG_OK;
		btnCount = 1;
	}
	
}

CMyMessageBox::~CMyMessageBox()
{
	if(szMaxChar) delete[] szMaxChar;
}

void CMyMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyMessageBox, CDialog)

	ON_BN_CLICKED(IDC_BUTTON1, &CMyMessageBox::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyMessageBox::OnBnClickedButton2)

	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMyMessageBox message handlers

void CMyMessageBox::SetButtonString(LPCTSTR positiveButton, LPCTSTR negativeButton)
{
	btnCount = 2;
	m_btnFlag = FLAG_OK | FLAG_CANCEL;
	bCustomButtonString = true;
	if(positiveButton != NULL)
		strPositive = positiveButton;
	else
		strPositive = LoadDextroString(L"IDS_Ok");
	if(negativeButton != NULL)
		strNegative = negativeButton;
	else
		strNegative = LoadDextroString(L"IDS_Cancel");
}

BOOL CMyMessageBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO:  Add extra initialization here

	SetWindowText(m_strTitle);
	//SetWindowText(gAppTitle);

	int btnWidth,btnHeight;
	int msgWidth,msgHeight;
	int xPos,yPos;
	int msgSize; // max length of char per line

	try
	{
		CWnd* wnd = NULL;
		wnd = GetDlgItem(IDCANCEL);
		if(wnd)
		{
			wnd->DestroyWindow();
		}
		wnd = GetDlgItem(IDOK);
		if(wnd)
		{
			wnd->DestroyWindow();
		}
	}
	catch(...){}

	int titlebarHeight = ::GetSystemMetrics(SM_CYCAPTION); 
	int borderHeight = ::GetSystemMetrics(SM_CXSIZEFRAME);  
	/*if(titlebarHeight == 0)
		titlebarHeight = GetSystemMetrics(SM_CYSMCAPTION )*/

	cxChar = LOWORD (GetDialogBaseUnits ()) ;
    cyChar = HIWORD (GetDialogBaseUnits ()) ;

	int lineCount = GetLineCount((LPTSTR)(LPCTSTR)m_strMsg);
	msgSize = maxCharWidth;


	int yGap = 1 * cyChar;
	int xGap = 1 * cxChar;

	CClientDC dc(this);
	//CFont* font = m_msgCtrl.GetFont();
	//dc.SelectObject(font);
	CString csText(szMaxChar);
	CSize sz = dc.GetTextExtent( csText, csText.GetLength());

	//calculation of message width and height
	//msgWidth = cxChar * (msgSize +2);
	//msgHeight = cyChar*(lineCount +1);
	msgHeight = sz.cy*lineCount;
	msgWidth = sz.cx;

	//calculation of button width and height
	//btnWidth = 12*cxChar;
	//btnHeight = 5 * cyChar/3;
	btnWidth = 138;
	btnHeight = 30;

	if(btnCount == 1)
		btnCount = 2; // only for SSTA


	width = max(msgWidth,btnCount * btnWidth) + 4*xGap + (btnCount-1)*2*xGap;
	//heigth = msgHeight + btnHeight + 4*yGap;
	heigth = msgHeight + borderheight + 4*yGap;


	//set dialog size
	SetWindowPos(NULL, -1, -1, width, heigth, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	CRect wndRect;
	GetClientRect(&wndRect);
	width = wndRect.Width();
	heigth = wndRect.Height();

	//create text control
	xPos = (width / 2) - (msgWidth / 2);
	yPos = yGap;
	CRect msgRect(xPos, yPos, xPos + msgWidth, yPos + msgHeight);
	m_msgCtrl.Create(m_strMsg,WS_CHILD | WS_VISIBLE , msgRect, this, IDC_STATIC);
	yPos += yGap + msgHeight;

	/*CFont m_font;
	m_font.CreateFont(15,7,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,0,0,0,0,L"Couriar New");
	m_msgCtrl.SetFont(&m_font);
	m_font.Detach();*/


	//create button control
	if(m_btnFlag & FLAG_OK && m_btnFlag & FLAG_CANCEL)
	{
		//ok button
		//xPos = (width / 2) - (btnWidth * btnCount )/2 - 2*xGap;
		xPos = (width / 2) - ( (btnWidth*btnCount) + ((btnCount-1)*2*xGap) )/2; //in total there willbe 2.xGap between two buttons


		//yPos = msgHeight + yGap*1.5;
		//yPos = msgHeight + yGap*1.8;
		yPos = (heigth-borderheight)  +(borderheight/2)-(btnHeight/2);
		CRect btnRect(xPos,yPos,xPos+ btnWidth,yPos+btnHeight); //CRect orientation left,top,right,bottom
		if(bCustomButtonString)
			m_button1.Create(strPositive,WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,btnRect,this,IDC_BUTTON1);
		else
			m_button1.Create(LoadDextroString(L"IDS_Ok"),WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,btnRect,this,IDC_BUTTON1);

		//cancel button
		//xPos = xPos + btnWidth + 3*xGap; //in total there willbe 4.xGap between two buttons
		xPos = xPos + btnWidth + 2*xGap; //in total there willbe 2.xGap between two buttons
		//yPos = msgHeight + yGap*1.5;
		//yPos = msgHeight + yGap*1.8;
		CRect btnRect1(xPos,yPos,xPos+ btnWidth,yPos+btnHeight); //CRect orientation left,top,right,bottom
		if(bCustomButtonString)
			m_button2.Create(strNegative,WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,btnRect1,this,IDC_BUTTON2);
		else
			m_button2.Create(LoadDextroString(L"IDS_Cancel"),WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,btnRect1,this,IDC_BUTTON2);
		m_button2.SetFocus();

	}
	else if(m_btnFlag & FLAG_YES && m_btnFlag & FLAG_NO)
	{
		//yes button
		//xPos = (width / 2) - (btnWidth * btnCount )/2 - 2*xGap;
		xPos = (width / 2) - ( (btnWidth*btnCount) + ((btnCount-1)*2*xGap) )/2; //in total there willbe 2.xGap between two buttons

		//yPos = msgHeight + yGap*1.5;
		//yPos = msgHeight + yGap*1.8;
		yPos = (heigth-borderheight)  +(borderheight/2)-(btnHeight/2);
		CRect btnRect(xPos,yPos,xPos+ btnWidth,yPos+btnHeight); //CRect orientation left,top,right,bottom
		m_button1.Create(LoadDextroString(L"IDS_Yes"),WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,btnRect,this,IDC_BUTTON1);

		//no button
		//xPos = xPos + btnWidth + 3*xGap; //in total there willbe 4.xGap between two buttons
		xPos = xPos + btnWidth + 2*xGap; //in total there willbe 2.xGap between two buttons
		//yPos = msgHeight + yGap*1.5;
		//yPos = msgHeight + yGap*1.8;
		CRect btnRect1(xPos,yPos,xPos+ btnWidth,yPos+btnHeight); //CRect orientation left,top,right,bottom
		m_button2.Create(LoadDextroString(L"IDS_No"),WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,btnRect1,this,IDC_BUTTON2);
		m_button2.SetFocus();
	}
	else
	{
		//OK button
		xPos = (width / 2) - (btnWidth / 2);
		//yPos = msgHeight + yGap*1.5;
		//yPos = msgHeight + yGap*1.8;
		yPos = (heigth-borderheight)  +(borderheight/2)-(btnHeight/2);
		CRect btnRect(xPos,yPos,xPos+ btnWidth,yPos+btnHeight); //CRect orientation left,top,right,bottom
		m_button1.Create(LoadDextroString(L"IDS_Ok"),WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW,btnRect,this,IDC_BUTTON1);
		//SetDefaultButton(IDC_BUTTON1);
		m_button1.SetFocus();
	}

	//SetDialogFont(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

INT_PTR CMyMessageBox::Show()
{	
	return DoModal();
}

int CMyMessageBox::GetLineCount(LPTSTR msg)
{
	maxCharWidth = 0;
	int ret = 0;
	TCHAR *token;
	int len = _tcslen(msg);
	LPTSTR buff = new TCHAR[len+1];
	_tcscpy(buff,msg);
	token = _tcstok(buff, L"\n");
	while(token != NULL)
	{
		int charLen = _tcslen(token);
		if(charLen > maxCharWidth)
		{
			maxCharWidth = charLen;
			if(szMaxChar != NULL)
				delete[] szMaxChar;
			szMaxChar = new TCHAR[maxCharWidth+1];
			_tcscpy(szMaxChar,token);
		}
		token = _tcstok(NULL, L"\n");
		ret++;
	}
	delete buff;
	return ret;
}

void CMyMessageBox::OnBnClickedButton1()
{
	if(m_btnFlag & FLAG_OK)
	{
		EndDialog(IDOK);
	}
	else
	{
		EndDialog(IDYES);
	}
	
}
void CMyMessageBox::OnBnClickedButton2()
{
	OnClose();
}

void CMyMessageBox::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	if(m_btnFlag & FLAG_CANCEL)
	{
		EndDialog(IDCANCEL);
	}
	else if(m_btnFlag & FLAG_NO)
	{
		EndDialog(IDNO);
	}
	else
	{
		EndDialog(IDCANCEL);
	}

	CDialog::OnClose();
}

BOOL CMyMessageBox::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnEraseBkgnd(pDC);

	CRect rect;
    GetClientRect(&rect);
	BOOL bRes;

	//paint dialog background
	CBrush myBrush0(backgroundcolor);    // dialog background color
    CBrush *pOld = pDC->SelectObject(&myBrush0);
    bRes  = pDC->PatBlt(0, 0, rect.Width(),rect.Height(), PATCOPY);
	pDC->SelectObject(pOld); 

	CBrush myBrush(backgroundcolor);
	CBrush myBrush1(headercolor);

	pOld = pDC->SelectObject(&myBrush1);
    //bRes  = pDC->PatBlt(0, 0, rect.Width(),borderheight1, PATCOPY);
    bRes  = pDC->PatBlt(0, rect.Height()-borderheight, rect.Width(),borderheight, PATCOPY);

   
	/*pDC->SelectObject(&myBrush);
    bRes  = pDC->PatBlt(0, borderheight1, rect.Width(), 2, PATCOPY);
    bRes  = pDC->PatBlt(0, rect.Height()-borderheight1, rect.Width(),2, PATCOPY);*/
	
 

	pDC->SelectObject(pOld);    // restore old brush

	myBrush.Detach();
	myBrush0.Detach();
	myBrush1.Detach();

    return bRes;

}

HBRUSH CMyMessageBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	if(pWnd->GetDlgCtrlID() == IDC_STATIC)  
	{  
		hbr = (HBRUSH)GetStockObject(WHITE_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
	} 

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

//dummy function
CString CMyMessageBox::LoadDextroString(CString str)
{
	if(str == L"IDS_Ok")
		return L"Ok";
	else if(str == L"IDS_Cancel")
		return L"Cancel";
	else if(str == L"IDS_Yes")
		return L"Yes";
	else if(str == L"IDS_No")
		return L"No";
	else
		return str;
}
