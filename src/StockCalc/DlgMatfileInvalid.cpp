// DlgMatfileInvalid.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "StockCalc.h"
#include "DlgMatfileInvalid.h"


// Boîte de dialogue CDlgMatfileInvalid

IMPLEMENT_DYNAMIC(CDlgMatfileInvalid, CCEDialog)

CDlgMatfileInvalid::CDlgMatfileInvalid(CWnd* pParent /*=NULL*/)
	: CCEDialog(CDlgMatfileInvalid::IDD, pParent)
{

}

CDlgMatfileInvalid::~CDlgMatfileInvalid()
{
}

void CDlgMatfileInvalid::DoDataExchange(CDataExchange* pDX)
{
	CCEDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMatfileInvalid, CCEDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Gestionnaires de messages de CDlgMatfileInvalid

void CDlgMatfileInvalid::OnSize(UINT nType, int cx, int cy)
{
	UINT nIdResource;
	switch(DRA::GetDisplayMode())
	{
	case DRA::Portrait:
	case DRA::Square:
		nIdResource=IDD_MATFILE_INVALID_PORTRAIT;
		break;
	case DRA::Landscape:
		nIdResource=IDD_MATFILE_INVALID_LANSCAPE;
		break;
	default:
		ASSERT(0);
		break;
	}

	DRA::RelayoutDialog(AfxGetResourceHandle(), this->m_hWnd, MAKEINTRESOURCE(nIdResource));
}
