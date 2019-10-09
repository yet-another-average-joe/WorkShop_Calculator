// PageDimNumeric.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageDimNumeric.h"


// Boîte de dialogue CPageDimNumeric

IMPLEMENT_DYNAMIC(CPageDimNumeric, CPageDimChild)

CPageDimNumeric::CPageDimNumeric(CWnd* pParent /*=NULL*/)
	: CPageDimChild(CPageDimNumeric::IDD, pParent)
{

}

CPageDimNumeric::~CPageDimNumeric()
{
}

void CPageDimNumeric::Calculate()
{
	CalculateNumeric();
}

void CPageDimNumeric::DoDataExchange(CDataExchange* pDX)
{
	CPageDimChild::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageDimNumeric, CPageDimChild)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageDimNumeric

BOOL CPageDimNumeric::OnInitDialog()
{
	CPageDimChild::OnInitDialog();

	FillWidthNumeric();
	m_comboWidth.SetCurSel(13);

	FillRimInches();
	m_comboRim.SetCurSel(16);

	FillRimInches();
	m_comboRim.SetCurSel(16);

	FillAspectRatioNumeric();
	m_comboAspectRatio.SetCurSel(1);

	Calculate();

	return TRUE;
}