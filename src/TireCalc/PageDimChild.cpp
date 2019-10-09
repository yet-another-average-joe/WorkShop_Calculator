// PageDimChild.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageDimChild.h"


// Boîte de dialogue CPageDimChild

IMPLEMENT_DYNAMIC(CPageDimChild, CDlgScroll)

CPageDimChild::CPageDimChild(UINT nIDTemplate, CWnd* pParentWnd /*= NULL*/)
	: CDlgScroll(nIDTemplate, pParentWnd)
{
	EnableScrollbars(TRUE);
	m_comboAspectRatio.SetFullDrop(TRUE);
	m_comboWidth.SetFullDrop(TRUE);
	m_comboDiam.SetFullDrop(TRUE);
	m_comboCorrect.SetFullDrop(TRUE);
	m_comboRim.SetFullDrop(TRUE);
}

CPageDimChild::~CPageDimChild()
{
}

void CPageDimChild::DoDataExchange(CDataExchange* pDX)
{
	CDlgScroll::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_WIDTH, m_editWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_editHeight);
	DDX_Control(pDX, IDC_EDIT_DIAM, m_editDiam);
	DDX_Control(pDX, IDC_EDIT_DEV, m_editDev);
	DDX_Control(pDX, IDC_COMBO_RIM, m_comboRim);
	DDX_Control(pDX, IDC_COMBO_WIDTH, m_comboWidth);
	DDX_Control(pDX, IDC_COMBO_CORRECT, m_comboCorrect);
	DDX_Control(pDX, IDC_COMBO_ASPECT_RATIO, m_comboAspectRatio);
	DDX_Control(pDX, IDC_COMBO_DIAM, m_comboDiam);
}


BEGIN_MESSAGE_MAP(CPageDimChild, CDlgScroll)
	ON_CBN_SELCHANGE(IDC_COMBO_RIM, &CPageDimChild::OnCbnSelchangeComboRim)
	ON_CBN_SELCHANGE(IDC_COMBO_WIDTH, &CPageDimChild::OnCbnSelchangeComboWidth)
	ON_CBN_SELCHANGE(IDC_COMBO_ASPECT_RATIO, &CPageDimChild::OnCbnSelchangeComboAspectRatio)
	ON_CBN_SELCHANGE(IDC_COMBO_CORRECT, &CPageDimChild::OnCbnSelchangeComboCorrect)
	ON_CBN_SELCHANGE(IDC_COMBO_DIAM, &CPageDimChild::OnCbnSelchangeComboDiam)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageDimChild

BOOL CPageDimChild::OnInitDialog()
{
	CDlgScroll::OnInitDialog();

	for(double i=-10; i<= 10; i+=1)
	{
		CString str;
			str.Format(_T("%+g%%"), i);
		int n=m_comboCorrect.AddString(str);
		m_comboCorrect.SetItemData(n, (int)i);
	}

	m_comboCorrect.SetCurSel(10);

	return TRUE;
}

void CPageDimChild::FillWidthMetric()
{
	for(int i=50; i< 345; i+=5)
	{
		CString str;
		str.Format(_T("%d"), i);
		int n=m_comboWidth.AddString(str);
		m_comboWidth.SetItemData(n, i);
	}
}

void CPageDimChild::FillWidthNumeric()
{
	for(double i=1.00; i<= 12.50; i+=0.5)
	{
		CString str;
		str.Format(_T("%.2f"), i);
		int n=m_comboWidth.AddString(str);
		m_comboWidth.SetItemData(n, (int)(i*100));
	}
}

void CPageDimChild::FillAspectRatio()
{
	for(int i=25; i< 105; i+=5)
	{
		CString str;
		str.Format(_T("%d"), i);
		int n=m_comboAspectRatio.AddString(str);
		m_comboAspectRatio.SetItemData(n, i);
	}
}

void CPageDimChild::FillAspectRatio80()
{
	CString str;
	str.Format(_T("%d"), 80);
	int n=m_comboAspectRatio.AddString(str);
	m_comboAspectRatio.SetItemData(n, 80);
	str.Format(_T("%d"), 82);
	n=m_comboAspectRatio.AddString(str);
	m_comboAspectRatio.SetItemData(n, 82);
}

void CPageDimChild::FillAspectRatioNumeric()
{
	CString str;
	str.Format(_T("%d"), 82);
	int n=m_comboAspectRatio.AddString(str);
	m_comboAspectRatio.SetItemData(n, 80);
	str.Format(_T("%d"), 92);
	n=m_comboAspectRatio.AddString(str);
	m_comboAspectRatio.SetItemData(n, 82);
	str.Format(_T("%d"), 100);
	n=m_comboAspectRatio.AddString(str);
	m_comboAspectRatio.SetItemData(n, 100);
}

void CPageDimChild::FillWidthFlotation()
{
	for(double i=5; i<= 20; i+=0.5)
	{
		CString str;
		str.Format(_T("%g"), i);
		int n=m_comboWidth.AddString(str);
		m_comboWidth.SetItemData(n, (int)(i*100));
	}
}

void CPageDimChild::FillDiamFlotation()
{
	for(double i=20.00; i<= 50; i+=0.5)
	{
		CString str;
		str.Format(_T("%g"), i);
		int n=m_comboDiam.AddString(str);
		m_comboDiam.SetItemData(n, (int)(i*100));
	}
}

void CPageDimChild::FillRimInches()
{
	for(double i=8; i<= 23; i+=0.50)
	{
		CString str;
		str.Format(_T("%g"), i);
		int n=m_comboRim.AddString(str);
		m_comboRim.SetItemData(n, (int)(i*100));
	}
}

void CPageDimChild::FillRimMillimetric()
{
	CString str;
	str.Format(_T("%d"), 365);
	int n=m_comboRim.AddString(str);
	m_comboRim.SetItemData(n, 365);
	str.Format(_T("%d"), 390);
	n=m_comboRim.AddString(str);
	m_comboRim.SetItemData(n, 390);
	str.Format(_T("%d"), 400);
	n=m_comboRim.AddString(str);
	m_comboRim.SetItemData(n, 400);
	str.Format(_T("%d"), 415);
	n=m_comboRim.AddString(str);
	m_comboRim.SetItemData(n, 415);
}

void CPageDimChild::OnCbnSelchangeComboRim()
{
	Calculate();
}

void CPageDimChild::OnCbnSelchangeComboWidth()
{
	Calculate();
}

void CPageDimChild::OnCbnSelchangeComboAspectRatio()
{
	Calculate();
}

void CPageDimChild::OnCbnSelchangeComboCorrect()
{
	Calculate();
}

void CPageDimChild::OnCbnSelchangeComboDiam()
{
	Calculate();
}

void CPageDimChild::CalculateMetric()
{
	int nSel=m_comboRim.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	double fRim_in=((double)m_comboRim.GetItemData(nSel))/100;

	double fRatio=0;
	double fWidth_mm=0;
	double fWidth_m=0;
	double fHeight_m=0;
	double fDiam_m=0;
	double fDev_m=0;

	nSel=m_comboWidth.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	fWidth_mm=m_comboWidth.GetItemData(nSel);

	nSel=m_comboAspectRatio.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	fRatio=m_comboAspectRatio.GetItemData(nSel);
	
	fWidth_m = fWidth_mm / 1000;
	fHeight_m = fWidth_m * fRatio / 100 * GetCorrect();
	fDiam_m = (0.0254 * fRim_in + (2 * fHeight_m));
	fDev_m = 3.14159 * fDiam_m;

	m_editDev.SetDecimalValue(fDev_m, 4);
	m_editDiam.SetDecimalValue(fDiam_m, 3);
	m_editWidth.SetDecimalValue(fWidth_m, 3);
	m_editHeight.SetDecimalValue(fHeight_m, 3);
}

void CPageDimChild::CalculateMillimetric()
{
	int nSel=m_comboRim.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	double fRim_mm=(double)m_comboRim.GetItemData(nSel);

	double fRatio=0;
	double fWidth_mm=0;
	double fWidth_m=0;
	double fHeight_m=0;
	double fDiam_m=0;
	double fDev_m=0;

	nSel=m_comboWidth.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	fWidth_mm=m_comboWidth.GetItemData(nSel);

	nSel=m_comboAspectRatio.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	fRatio=m_comboAspectRatio.GetItemData(nSel);
	
	fWidth_m = fWidth_mm / 1000;
	fHeight_m = fWidth_m * fRatio / 100 * GetCorrect();
	fDiam_m = (0.001 * fRim_mm + (2 * fHeight_m));
	fDev_m = 3.14159 * fDiam_m;

	m_editDev.SetDecimalValue(fDev_m, 4);
	m_editDiam.SetDecimalValue(fDiam_m, 3);
	m_editWidth.SetDecimalValue(fWidth_m, 3);
	m_editHeight.SetDecimalValue(fHeight_m, 3);
}

void CPageDimChild::CalculateNumeric()
{
	int nSel=m_comboRim.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	double fRim_in=((double)m_comboRim.GetItemData(nSel))/100;

	double fRatio=0;
	double fWidth_m=0;
	double fHeight_m=0;
	double fDiam_m=0;
	double fDev_m=0;
	double fSize_in=0;

	nSel=m_comboAspectRatio.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	fRatio=m_comboAspectRatio.GetItemData(nSel);
	
	nSel=m_comboWidth.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	fSize_in=((double)m_comboWidth.GetItemData(nSel))/100;
	fWidth_m = 0.0254 * fSize_in;
	fHeight_m = 0.0254 * fSize_in*GetCorrect() * fRatio/100;
	fDiam_m = 2 * fHeight_m + 0.0254 * fRim_in;
	fDev_m = 3.14159 * fDiam_m;

	m_editDev.SetDecimalValue(fDev_m, 4);
	m_editDiam.SetDecimalValue(fDiam_m, 3);
	m_editWidth.SetDecimalValue(fWidth_m, 3);
	m_editHeight.SetDecimalValue(fHeight_m, 3);
}

void CPageDimChild::CalculateFlotation()
{
	int nSel=m_comboRim.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	double fRim_in=((double)m_comboRim.GetItemData(nSel))/100;

	double fWidth_m=0;
	double fHeight_m=0;
	double fDiam_m=0;
	double fDev_m=0;
	double fDiam_in=0;
	double fWidth_in=0;

	nSel=m_comboDiam.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	fDiam_in=((double)m_comboDiam.GetItemData(nSel))/100;
	nSel=m_comboWidth.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	fWidth_in=((double)m_comboWidth.GetItemData(nSel))/100;
	fDiam_m = fDiam_in * 0.0254 * GetCorrect();
	fWidth_m = fWidth_in * 0.0254;
	fDev_m = 3.14159 * fDiam_m;
	fHeight_m = (fDiam_m - 0.0254 * fRim_in)/2;

	m_editDev.SetDecimalValue(fDev_m, 4);
	m_editDiam.SetDecimalValue(fDiam_m, 3);
	m_editWidth.SetDecimalValue(fWidth_m, 3);
	m_editHeight.SetDecimalValue(fHeight_m, 3);
}

