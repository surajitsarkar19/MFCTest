// OnOffCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TEST_MFC.h"
#include "OnOffCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// COnOffCtrl

IMPLEMENT_DYNAMIC(COnOffCtrl, CWnd)

COnOffCtrl::COnOffCtrl()
{
	m_bButtonState = true;
	m_strOn = L"ON";
	m_strOff = L"OFF";
	m_pBrushOn = new CBrush(RGB(12,215,237));
	m_pBrushOff = new CBrush(RGB(157,157,157));
	m_pBrushBackground = new CBrush(RGB(255,255,255));
	m_textColor = RGB(255,255,255);
	RegisterWindowClass();
}

COnOffCtrl::~COnOffCtrl()
{
	if(m_pBrushOff!= NULL)
	{
		delete m_pBrushOff;
		m_pBrushOff = NULL;
	}
	if(m_pBrushOn!= NULL)
	{
		delete m_pBrushOn;
		m_pBrushOn = NULL;
	}
	if(m_pBrushBackground)
	{
		delete m_pBrushBackground;
		m_pBrushBackground = NULL;
	}
}


BEGIN_MESSAGE_MAP(COnOffCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// COnOffCtrl message handlers

// Register the window class if it has not already been registered.
BOOL COnOffCtrl::RegisterWindowClass()
{
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, ONOFFWND_CLASSNAME, &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = ONOFFWND_CLASSNAME;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}

void COnOffCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	BOOL bRes;
	CRect rect;
	GetClientRect(&rect);
	
	if(m_bButtonState)
	{
		//on
		CBrush *pOld = dc.SelectObject(m_pBrushOn);
		bRes  = dc.PatBlt(rect.Width()/2, 0, rect.Width(),rect.Height(), PATCOPY);
		dc.SelectObject(pOld);
		CRect focusRect(rect.Width()/2,0,rect.Width(),rect.Height());
		//dc.DrawFocusRect(focusRect);

		//dc.Draw3dRect(focusRect, RGB(255, 0, 0), RGB(0, 255, 0));
		
		dc.DrawEdge(focusRect,EDGE_RAISED,BF_BOTTOM|BF_RIGHT);
		dc.SetTextColor(m_textColor);
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(m_strOn,focusRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
	else
	{
		CBrush *pOld = dc.SelectObject(m_pBrushOff);
		bRes  = dc.PatBlt(0, 0, rect.Width()/2,rect.Height(), PATCOPY);
		dc.SelectObject(pOld);
		CRect focusRect(0,0,rect.Width()/2,rect.Height());
		//dc.DrawFocusRect(focusRect);

		dc.DrawEdge(focusRect,EDGE_RAISED,BF_BOTTOM|BF_LEFT);
		dc.SetTextColor(m_textColor);
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(m_strOff,focusRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}

	// Do not call CWnd::OnPaint() for painting messages
}

void COnOffCtrl::toggleState()
{
	if(m_bButtonState == true)
	{
		m_bButtonState = false;
	}
	else
	{
		m_bButtonState = true;
	}
}

BOOL COnOffCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CRect rect;
    GetClientRect(&rect);
	BOOL bRes;

	//paint dialog background
	CBrush myBrush0(RGB(255,255,255));    // dialog background color
    CBrush *pOld = pDC->SelectObject(&myBrush0);
    bRes  = pDC->PatBlt(0, 0, rect.Width(),rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);

	return bRes;
}

void COnOffCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect clientRect;
	GetClientRect(&clientRect);
	//point is always in client quardinate

	UINT_PTR controlId = GetDlgCtrlID();
	NMONOFFCTRL nm;
	nm.nmh.code = NM_CLICK;
	nm.nmh.idFrom = controlId;
	nm.nmh.hwndFrom = m_hWnd;

	if(m_bButtonState)
	{
		CRect rect(clientRect.Width()/2,0,clientRect.Width(),clientRect.Height());
		if(rect.PtInRect(point))
		{
			toggleState();
			Invalidate();
			
			nm.toggleState = m_bButtonState;
			GetParent()->SendMessage(WM_NOTIFY,(WPARAM)controlId,(LPARAM)&nm);
		}
	}
	else
	{
		CRect rect(0,0,clientRect.Width()/2,clientRect.Height());
		if(rect.PtInRect(point))
		{
			toggleState();
			Invalidate();
			
			nm.toggleState = m_bButtonState;
			GetParent()->SendMessage(WM_NOTIFY,(WPARAM)controlId,(LPARAM)&nm);
		}
	}
	
	CWnd::OnLButtonUp(nFlags, point);
}
