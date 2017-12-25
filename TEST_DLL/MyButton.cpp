// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "MyButton.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
	isHovered=false;
	bmp_idle.LoadBitmapW(IDB_BUTTON);
	bmp_clicked.LoadBitmapW(IDB_BUTTON_CLICK);
	bmp_hovered.LoadBitmapW(IDB_BUTTON_MOUSEHOVER);
	bmp_disabled.LoadBitmapW(IDB_BUTTON_DISABLE);

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//ON_WM_MOUSEHOVER()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CMyButton message handlers



void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{


	CDC dc;
	CDC dcMemory;
	BITMAP bm;
	CBitmap bmp;
  dc.Attach(lpDrawItemStruct->hDC);     //Get device context object
  CRect rt;
  rt = lpDrawItemStruct->rcItem;        //Get button rect


 
  //dc.FillSolidRect(rt, RGB(0, 0, 255)); //Fill button with blue color
  dcMemory.CreateCompatibleDC(&dc);

  UINT state = lpDrawItemStruct->itemState; //Get state of the button
  
  if ( (state & ODS_SELECTED) )            // If it is pressed
  {
	//dc.DrawEdge(rt,EDGE_SUNKEN,BF_RECT);    // Draw a sunken face
	  
	  bmp_clicked.GetBitmap(&bm);
	  CBitmap *oldBitmap=(CBitmap*)dcMemory.SelectObject(&bmp_clicked);
	  dc.StretchBlt(0,0,rt.Width(),rt.Height(),&dcMemory,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	  dcMemory.SelectObject(oldBitmap);

  }
  else if((state & ODS_DISABLED)) //if the button is disabled
  {
	  /*bmp_disabled.GetBitmap(&bm);
	  CBitmap *oldBitmap=(CBitmap*)dcMemory.SelectObject(&bmp_disabled);
	  dc.StretchBlt(0,0,rt.Width(),rt.Height(),&dcMemory,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	  dcMemory.SelectObject(oldBitmap);*/

	  bmp_idle.GetBitmap(&bm); //for normal
	  CBitmap *oldBitmap=(CBitmap*)dcMemory.SelectObject(&bmp_idle);
	  dc.StretchBlt(0,0,rt.Width(),rt.Height(),&dcMemory,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	  dcMemory.SelectObject(oldBitmap);

  }
  else if(isHovered)
  {
	  //isHovered=false;
	  bmp_hovered.GetBitmap(&bm);
	  CBitmap *oldBitmap=(CBitmap*)dcMemory.SelectObject(&bmp_hovered);
	  dc.StretchBlt(0,0,rt.Width(),rt.Height(),&dcMemory,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	  dcMemory.SelectObject(oldBitmap);
  }
  else
  {
	//dc.DrawEdge(rt,EDGE_RAISED,BF_RECT);    // Draw a raised face
	  bmp_idle.GetBitmap(&bm); //for normal
	  CBitmap *oldBitmap=(CBitmap*)dcMemory.SelectObject(&bmp_idle);
	  dc.StretchBlt(0,0,rt.Width(),rt.Height(),&dcMemory,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	  dcMemory.SelectObject(oldBitmap);
  }
 
  //set button text

  if((state & ODS_DISABLED))
	  dc.SetTextColor(RGB(0,0,0));
  else
	dc.SetTextColor(RGB(255,255,255));
  dc.SetBkMode(TRANSPARENT);
  CString strTemp;
  GetWindowText(strTemp); 
						// Get the caption which have been set
  dc.DrawText(strTemp,rt,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
							  // Draw out the caption
  
  if ( (state & ODS_FOCUS ) )       // If the button is focused
  {
	// Draw a focus rect which indicates the user 
	// that the button is focused
	int iChange = 3;
	rt.top += iChange;
	rt.left += iChange;
	rt.right -= iChange;
	rt.bottom -= iChange;
	dc.DrawFocusRect(rt);
  }
  //dcMemory.DeleteDC();
  dc.Detach();

	// TODO:  Add your code to draw the specified item
}

void CMyButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//TRACE(_T("Mouse Hover ( x = %d, y = %d)\n"), point.x,point.y);


	TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_HOVER | TME_LEAVE;
    tme.hwndTrack = m_hWnd;
    tme.dwHoverTime = HOVER_DEFAULT;
    ::TrackMouseEvent(&tme);
	CButton::OnMouseHover(nFlags, point);
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(!isHovered)
    {
        //TRACE(_T("Mouse enter\n"));
        isHovered=true;
		Invalidate(); //refresh window
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.hwndTrack = m_hWnd;
        tme.dwHoverTime = HOVER_DEFAULT;
        ::TrackMouseEvent(&tme);
    }
	CButton::OnMouseMove(nFlags, point);
}

void CMyButton::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	isHovered=false;
	Invalidate();
	CButton::OnMouseLeave();
}

bool CMyButton::IsMouseHover()
{
	return isHovered;
}
