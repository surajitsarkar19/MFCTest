// DextroDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TEST_MFC.h"
#include "DextroDialog.h"


// CDextroDialog dialog

IMPLEMENT_DYNAMIC(CDextroDialog, CDialog)

CDextroDialog::CDextroDialog(UINT id, CWnd* pParent /*=NULL*/)
	: CDialog(id, pParent)
{

}

CDextroDialog::~CDextroDialog()
{
}

void CDextroDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDextroDialog, CDialog)

END_MESSAGE_MAP()


// CDextroDialog message handlers

void CDextroDialog::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}
