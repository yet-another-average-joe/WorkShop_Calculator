// PageDimMetric80.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageDimMetric80.h"


// Boîte de dialogue CPageDimMetric80

IMPLEMENT_DYNAMIC(CPageDimMetric80, CPageDimChild)

CPageDimMetric80::CPageDimMetric80(CWnd* pParent /*=NULL*/)
	: CPageDimChild(CPageDimMetric80::IDD, pParent)
{

}

CPageDimMetric80::~CPageDimMetric80()
{
}

void CPageDimMetric80::Calculate()
{
	CalculateMetric();
}

void CPageDimMetric80::DoDataExchange(CDataExchange* pDX)
{
	CPageDimChild::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageDimMetric80, CPageDimChild)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageDimMetric80

BOOL CPageDimMetric80::OnInitDialog()
{
	CPageDimChild::OnInitDialog();

	FillWidthMetric();
	m_comboWidth.SetCurSel(31);

	FillRimInches();
	m_comboRim.SetCurSel(16);

	FillAspectRatio80();
	m_comboAspectRatio.SetCurSel(0);

	Calculate();

	return TRUE;
}