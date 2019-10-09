// PageDimMillimetric.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageDimMillimetric.h"


// Boîte de dialogue CPageDimMillimetric

IMPLEMENT_DYNAMIC(CPageDimMillimetric, CPageDimChild)

CPageDimMillimetric::CPageDimMillimetric(CWnd* pParent /*=NULL*/)
	: CPageDimChild(CPageDimMillimetric::IDD, pParent)
{

}

CPageDimMillimetric::~CPageDimMillimetric()
{
}

void CPageDimMillimetric::Calculate()
{
	CalculateMillimetric();
}

void CPageDimMillimetric::DoDataExchange(CDataExchange* pDX)
{
	CPageDimChild::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageDimMillimetric, CPageDimChild)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageDimMillimetric

BOOL CPageDimMillimetric::OnInitDialog()
{
	CPageDimChild::OnInitDialog();

	FillWidthMetric();
	m_comboWidth.SetCurSel(23);

	FillAspectRatio();
	m_comboAspectRatio.SetCurSel(11);

	FillRimMillimetric();
	m_comboRim.SetCurSel(0);

	Calculate();

	return TRUE;
}