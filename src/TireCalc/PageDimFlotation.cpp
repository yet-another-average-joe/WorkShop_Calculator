// PageDimFlotation.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageDimFlotation.h"


// Boîte de dialogue CPageDimFlotation

IMPLEMENT_DYNAMIC(CPageDimFlotation, CPageDimChild)

CPageDimFlotation::CPageDimFlotation(CWnd* pParent /*=NULL*/)
	: CPageDimChild(CPageDimFlotation::IDD, pParent)
{

}

CPageDimFlotation::~CPageDimFlotation()
{
}

void CPageDimFlotation::Calculate()
{
	CalculateFlotation();
	CalculateAspectRatio();
}

void CPageDimFlotation::DoDataExchange(CDataExchange* pDX)
{
	CPageDimChild::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ASPECT_RATIO, m_editAspectratio);
}


BEGIN_MESSAGE_MAP(CPageDimFlotation, CPageDimChild)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageDimFlotation

BOOL CPageDimFlotation::OnInitDialog()
{
	CPageDimChild::OnInitDialog();

	FillWidthFlotation();
	m_comboWidth.SetCurSel(13);

	FillDiamFlotation();
	m_comboDiam.SetCurSel(21);

	FillRimInches();
	m_comboRim.SetCurSel(16);

	Calculate();

	return TRUE;
}

void CPageDimFlotation::CalculateAspectRatio()
{
	double dWidth=0;
	m_editWidth.GetDecimalValue(dWidth);

	if(dWidth==0)
	{
		m_editAspectratio.SetWindowText_NoNotify(_T(""));
		return;
	}

	double dHeight=0;
	m_editHeight.GetDecimalValue(dHeight);

	if(dHeight==0)
	{
		m_editAspectratio.SetWindowText_NoNotify(_T(""));
		return;
	}


	m_editAspectratio.SetDecimalValue(dHeight/dWidth, 3);
}