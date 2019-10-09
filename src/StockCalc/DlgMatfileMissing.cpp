// DlgMatfileMissing.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "StockCalc.h"
#include "DlgMatfileMissing.h"


// Boîte de dialogue CDlgMatfileMissing

IMPLEMENT_DYNAMIC(CDlgMatfileMissing, CCEDialog)

CDlgMatfileMissing::CDlgMatfileMissing(CWnd* pParent /*=NULL*/)
	: CCEDialog(CDlgMatfileMissing::IDD, pParent)
{

}

CDlgMatfileMissing::~CDlgMatfileMissing()
{
}

void CDlgMatfileMissing::DoDataExchange(CDataExchange* pDX)
{
	CCEDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMatfileMissing, CCEDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Gestionnaires de messages de CDlgMatfileMissing

void CDlgMatfileMissing::OnSize(UINT nType, int cx, int cy)
{
	UINT nIdResource;
	switch(DRA::GetDisplayMode())
	{
	case DRA::Portrait:
	case DRA::Square:
		nIdResource=IDD_MATFILE_MISSING_PORTRAIT;
		break;
	case DRA::Landscape:
		nIdResource=IDD_MATFILE_MISSING_LANSCAPE;
		break;
	default:
		ASSERT(0);
		break;
	}

	DRA::RelayoutDialog(AfxGetResourceHandle(), this->m_hWnd, MAKEINTRESOURCE(nIdResource));
}
