#pragma once


// CDextroDialog dialog

class CDextroDialog : public CDialog
{
	DECLARE_DYNAMIC(CDextroDialog)

public:
	CDextroDialog(UINT id, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDextroDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
