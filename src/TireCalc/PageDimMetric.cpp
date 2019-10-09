// PageDimMetric.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageDimMetric.h"


// Boîte de dialogue CPageDimMetric

IMPLEMENT_DYNAMIC(CPageDimMetric, CPageDimChild)

CPageDimMetric::CPageDimMetric(CWnd* pParent /*=NULL*/)
	: CPageDimChild(CPageDimMetric::IDD, pParent)
{

}

CPageDimMetric::~CPageDimMetric()
{
}

void CPageDimMetric::Calculate()
{
	CalculateMetric();
}

void CPageDimMetric::DoDataExchange(CDataExchange* pDX)
{
	CPageDimChild::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageDimMetric, CPageDimChild)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageDimMetric

BOOL CPageDimMetric::OnInitDialog()
{
	CPageDimChild::OnInitDialog();

	FillWidthMetric();
	m_comboWidth.SetCurSel(37);

	FillAspectRatio();
	m_comboAspectRatio.SetCurSel(12);

	FillRimInches();
	m_comboRim.SetCurSel(16);

	Calculate();

	return TRUE;
}