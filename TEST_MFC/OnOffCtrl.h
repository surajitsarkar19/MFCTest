#if !defined(AFX_ONOFF_H__2D796573_56E0_4b68_978D_387680DA1C23__INCLUDED_)
#define AFX_ONOFF_H__2D796573_56E0_4b68_978D_387680DA1C23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


// COnOffCtrl

#define ONOFFWND_CLASSNAME    _T("MFCOnOffCtrl")  // Window class name

typedef struct nmonoffctrl
{
	NMHDR nmh;
	bool toggleState;
}NMONOFFCTRL,*PNMONOFFCTRL;

class COnOffCtrl : public CWnd
{
	DECLARE_DYNAMIC(COnOffCtrl)

public:
	COnOffCtrl();
	virtual ~COnOffCtrl();
private:
	bool m_bButtonState;
	CString m_strOn,m_strOff;
	CBrush *m_pBrushOn;
	CBrush *m_pBrushOff;
	CBrush *m_pBrushBackground;
	COLORREF m_textColor;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	BOOL RegisterWindowClass();
	void toggleState();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#endif
