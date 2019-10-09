// PageCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MillCalc.h"
#include "PageCalcMill.h"
#include "CLASSES_rc.h"
#include "CLASSES.h"


#define Z_DEFAULT	2

// Boîte de dialogue CPageCalcMill

IMPLEMENT_DYNAMIC(CPageCalcMill, CPageCalcBase2)

CPageCalcMill::CPageCalcMill(CData* pData)
	: CPageCalcBase2(CPageCalcMill::IDD, pData)
{
	m_editAp.m_bNoGray=TRUE;
	m_editAe.m_bNoGray=TRUE;
	m_editAp.m_bNoGray=TRUE;
	m_editAe.m_bNoGray=TRUE;

	m_editZ.m_bFrameFocus=TRUE;
	m_editZ.m_bNoCaret=TRUE;
}

CPageCalcMill::~CPageCalcMill()
{
}

void CPageCalcMill::DoDataExchange(CDataExchange* pDX)
{
	CPageCalcBase2::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Z, m_staticZ);
	DDX_Control(pDX, IDC_EDIT_Z, m_editZ);
	DDX_Control(pDX, IDC_STATIC_AP, m_staticAp);
	DDX_Control(pDX, IDC_STATIC_AE, m_staticAe);
	DDX_Control(pDX, IDC_EDIT_AP, m_editAp);
	DDX_Control(pDX, IDC_EDIT_AE, m_editAe);
}

BEGIN_MESSAGE_MAP(CPageCalcMill, CPageCalcBase2)
	ON_EN_CHANGE(IDC_EDIT_Z, &CPageCalcMill::OnEnChangeEditZ)
END_MESSAGE_MAP()

BOOL CPageCalcMill::OnInitDialog()
{
	CPageCalcBase2::OnInitDialog();

	SetDlgItemInt(IDC_EDIT_Z, Z_DEFAULT);
	UpdateApAe();
	OnChangeTWPair();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPageCalcMill::OnEnChangeEditZ()
{
	OnChangeZ();
}

void CPageCalcMill::OnChangeZ()
{
	CalcAndUpdateVf();
}

void CPageCalcMill::UpdateApAe()
{
	if(m_pData==NULL) // pas de fichier
		return;

	CTool* pTool=Data_Tool_GetCurSel();
	
	if(pTool!=NULL)
	{
		double D=GetD();

		if(pTool->m_ap!=0)
		//if(pTool->m_ap>0.01)
		{
			m_staticAp.ShowWindow(SW_SHOW);
			m_editAp.ShowWindow(SW_SHOW);
			SetAp(pTool->m_ap*D/100.0);
		}
		else
		{
			m_staticAp.ShowWindow(SW_HIDE);
			m_editAp.ShowWindow(SW_HIDE);
			ClearAp();
		}

		if(pTool->m_ae!=0)
		//if(pTool->m_ae>=0.01)
		{
			m_staticAe.ShowWindow(SW_SHOW);
			m_editAe.ShowWindow(SW_SHOW);
			SetAe(pTool->m_ae*D/100.0);
		}
		else
		{
			m_staticAe.ShowWindow(SW_HIDE);
			m_editAe.ShowWindow(SW_HIDE);
			ClearAe();
		}
	}
}

void CPageCalcMill::OnSlider(int nTBCode, UINT nPos)
{
	CPageCalcBase2::OnSlider(nTBCode, nPos);

	CWnd* pwndFocus=GetFocus();
	int nID=pwndFocus->GetDlgCtrlID();

	switch(nID)
	{
	case IDC_EDIT_Z: 
		{
			UINT z=GetZ();
			switch(nTBCode)
			{
			case SB_LINEUP:
				z++;
				break;
			case SB_LINEDOWN:
				if(z>1)
					z--;
				break;
			default:
				ASSERT(0);
				break;
			}
			SetZ(z);
			OnChangeZ();
		}
		break;

	default:
		return;
	}
}

void CPageCalcMill::OnChangeTWPair()
{
	CPageCalcBase2::OnChangeTWPair(); // D est inchangé, Vc est moyenné, N est calculé
	UpdateApAe();
}

void CPageCalcMill::Clear() // appelée pour vider les champs
{
	CPageCalcBase::Clear();

	ClearZ();
	ClearAp();
	ClearAe();
}

// calcule et met à jour Vf en fonction de f et N
void CPageCalcMill::CalcAndUpdateVf()
{
	// Vf = z*fz*N
	SetVf( GetZ() * GetF() * GetN() );
}

// calcule et met à jour f en fonction de Vf et N
void CPageCalcMill::CalcAndUpdateF()
{
	// fz = Vf / (z*N)
	double N=GetN();
	UINT Z=GetZ();

	if(N!=0 && Z!=0)
		SetF( GetVf() / N / Z );
	else
		ClearF(); // div / 0
}

