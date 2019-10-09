// DlgCatMissing.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DlgCatMissing.h"
#include "CLASSES_rc.h"


// Boîte de dialogue CDlgCatMissing

IMPLEMENT_DYNAMIC(CDlgCatMissing, CCEDialog)

CDlgCatMissing::CDlgCatMissing(CWnd* pParent /*=NULL*/)
	: CCEDialog(CLASSES_IDD_CAT_MISSING_PORTRAIT, pParent)
{
}

CDlgCatMissing::~CDlgCatMissing()
{
}

void CDlgCatMissing::DoDataExchange(CDataExchange* pDX)
{
	CCEDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCatMissing, CCEDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Gestionnaires de messages de CDlgCatMissing

void CDlgCatMissing::OnSize(UINT nType, int cx, int cy)
{
	UINT nIdResource;
	switch(DRA::GetDisplayMode())
	{
	case DRA::Portrait:
	case DRA::Square:
		nIdResource=CLASSES_IDD_CAT_MISSING_PORTRAIT;
		break;
	case DRA::Landscape:
		nIdResource=CLASSES_IDD_CAT_MISSING_LANDSCAPE;
		break;
	default:
		ASSERT(0);
		break;
	}

	DRA::RelayoutDialog(AfxGetResourceHandle(), this->m_hWnd, MAKEINTRESOURCE(nIdResource));
	
	CWnd* pWnd=GetDlgItem(CLASSES_IDC_STATIC_FILENAME);
	if(!pWnd)
		return;
		//pWnd->SetWindowText(m_strFileName);
	//pWnd->SetWindowText(_T("essai"));
		pWnd->SetWindowText(m_strFileName);
}

BOOL CDlgCatMissing::OnInitDialog()
{
	CCEDialog::OnInitDialog();

#ifdef _WIN32_WCE
	// supprimer les boutons X et OK
//	::SHDoneButton(m_hWnd, SHDB_HIDE);
//	::SetWindowLong(m_hWnd, GWL_STYLE, WS_VISIBLE| WS_NONAVDONEBUTTON );
#endif _WIN32_WCE

	CWnd* pWnd=GetDlgItem(CLASSES_IDC_STATIC_FILENAME);
		pWnd->SetWindowText(m_strFileName);
	//pWnd->SetWindowText(_T("essai"));
		//pWnd->UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}
