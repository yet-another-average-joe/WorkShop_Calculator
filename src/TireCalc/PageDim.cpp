// TireCalcDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageDim.h"
#include "NumPadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// hauteur à donner à la page : 151

// Boîte de dialogue CPageDim

CPageDim::CPageDim()
	: CPropPageEx(CPageDim::IDD, NULL)
{
	EnableScrollbars(FALSE);
}

void CPageDim::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_NORM, m_comboNorm);
	DDX_Control(pDX, IDC_STATIC_PLACEHOLDER, m_staticPlaceHolder);
}

BEGIN_MESSAGE_MAP(CPageDim, CPropPageEx)
//#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
//	ON_WM_SIZE()
//#endif
	ON_CBN_SELCHANGE(IDC_COMBO_NORM, &CPageDim::OnCbnSelchangeComboNorm)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Gestionnaires de messages pour CPageDim

BOOL CPageDim::OnInitDialog()
{
	CPropPageEx::OnInitDialog();

	m_pageFlotation.Create(IDD_CHILD_DIM_FLOTATION, this);
	m_pageMetric.Create(IDD_CHILD_DIM_METRIC, this);
	m_pageMetric80.Create(IDD_CHILD_DIM_METRIC80, this);
	m_pageMillimetric.Create(IDD_CHILD_DIM_MILLIMETRIC, this);
	m_pageNumeric.Create(IDD_CHILD_DIM_NUMERIC, this);

	m_strArrayNorm.SetSize(5);
	m_strArrayNorm[0]=_T("Metric: ex. 235/85R16");
	m_strArrayNorm[1]=_T("Metric \"série 80\" : ex. 205R16");
	m_strArrayNorm[2]=_T("Millimetric : ex. 165/80R365");
	m_strArrayNorm[3]=_T("Numeric: ex. 7.50R16");
	m_strArrayNorm[4]=_T("Flotation: ex. 30.5x11.5R16");

	m_comboNorm.AddString(m_strArrayNorm[0]);
	m_comboNorm.AddString(m_strArrayNorm[1]);
	m_comboNorm.AddString(m_strArrayNorm[2]);
	m_comboNorm.AddString(m_strArrayNorm[3]);
	m_comboNorm.AddString(m_strArrayNorm[4]);
	m_comboNorm.SetFullDrop(TRUE);
	m_comboNorm.SetCurSel(0);

	OnCbnSelchangeComboNorm();

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

//#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
//void CPageDim::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
//{
//	if (AfxIsDRAEnabled())
//	{
//		DRA::RelayoutDialog(
//			AfxGetResourceHandle(), 
//			this->m_hWnd, 
//			DRA::GetDisplayMode() != DRA::Portrait ? 
//			MAKEINTRESOURCE(IDD_TIRECALC_DIALOG_WIDE) : 
//			MAKEINTRESOURCE(IDD_TIRECALC_DIALOG));
//	}
//}
//#endif


void CPageDim::OnCbnSelchangeComboNorm()
{
	switch(m_comboNorm.GetCurSel())
	{
	case NORM_METRIC:
		m_pageFlotation.ShowWindow(SW_HIDE);
		m_pageMetric.ShowWindow(SW_SHOW);
		m_pageMetric80.ShowWindow(SW_HIDE);
		m_pageMillimetric.ShowWindow(SW_HIDE);
		m_pageNumeric.ShowWindow(SW_HIDE);
		break;

	case NORM_METRIC80:
		m_pageFlotation.ShowWindow(SW_HIDE);
		m_pageMetric.ShowWindow(SW_HIDE);
		m_pageMetric80.ShowWindow(SW_SHOW);
		m_pageMillimetric.ShowWindow(SW_HIDE);
		m_pageNumeric.ShowWindow(SW_HIDE);
		break;

	case NORM_NUMERIC:
		m_pageFlotation.ShowWindow(SW_HIDE);
		m_pageMetric.ShowWindow(SW_HIDE);
		m_pageMetric80.ShowWindow(SW_HIDE);
		m_pageMillimetric.ShowWindow(SW_HIDE);
		m_pageNumeric.ShowWindow(SW_SHOW);
		break;

	case NORM_FLOT:
		m_pageFlotation.ShowWindow(SW_SHOW);
		m_pageMetric.ShowWindow(SW_HIDE);
		m_pageMetric80.ShowWindow(SW_HIDE);
		m_pageMillimetric.ShowWindow(SW_HIDE);
		m_pageNumeric.ShowWindow(SW_HIDE);
		break;

	case NORM_MILLIMETRIC:
		m_pageFlotation.ShowWindow(SW_HIDE);
		m_pageMetric.ShowWindow(SW_HIDE);
		m_pageMetric80.ShowWindow(SW_HIDE);
		m_pageMillimetric.ShowWindow(SW_SHOW);
		m_pageNumeric.ShowWindow(SW_HIDE);
		break;

	default:
		ASSERT(0);
		break;
	}

	//Calculate();
}


void CPageDim::OnSize(UINT nType, int cx, int cy)
{
	CPropPageEx::OnSize(nType, cx, cy);

	if(!m_pageFlotation.m_hWnd)
		return;

	CRect rc;
	m_staticPlaceHolder.GetWindowRect(rc);
	ScreenToClient(rc);
	CRect rcClient;
	GetClientRect(rcClient);
	m_pageFlotation.SetWindowPos(NULL, rc.left, rc.top, rcClient.right-rc.left, rcClient.bottom-rc.top, SWP_NOZORDER);
	m_pageMetric.SetWindowPos(NULL, rc.left, rc.top, rcClient.right-rc.left, rcClient.bottom-rc.top, SWP_NOZORDER);
	m_pageMetric80.SetWindowPos(NULL, rc.left, rc.top, rcClient.right-rc.left, rcClient.bottom-rc.top, SWP_NOZORDER);
	m_pageMillimetric.SetWindowPos(NULL, rc.left, rc.top, rcClient.right-rc.left, rcClient.bottom-rc.top, SWP_NOZORDER);
	m_pageNumeric.SetWindowPos(NULL, rc.left, rc.top, rcClient.right-rc.left, rcClient.bottom-rc.top, SWP_NOZORDER);
}
