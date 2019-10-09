// PageCalcBase2.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "PageCalcBase2.h"
#include "CLASSES_rc.h"
#include "CLASSES.h"

// donner une valeur par d�faut au diam�tre

#define DIAM_DEFAULT 10
#define F_DEFAULT	0.1
#define F_INC		0.01
#define VF_INC		10

// Bo�te de dialogue CPageCalcBase2

IMPLEMENT_DYNAMIC(CPageCalcBase2, CPageCalcBase)

CPageCalcBase2::CPageCalcBase2(UINT nIDTemplate, CData* pData)
	: CPageCalcBase(nIDTemplate, pData)
{
	m_editF.m_bFrameFocus=TRUE;
	m_editVf.m_bFrameFocus=TRUE;

	m_editF.m_bNoCaret=TRUE;
	m_editVf.m_bNoCaret=TRUE;

	EnableScrollbars(TRUE);
}

CPageCalcBase2::~CPageCalcBase2()
{
}

void CPageCalcBase2::DoDataExchange(CDataExchange* pDX)
{
	CPageCalcBase::DoDataExchange(pDX);
	DDX_Control(pDX, CLASSES_IDC_STATIC_F, m_staticF);
	DDX_Control(pDX, CLASSES_IDC_STATIC_VF, m_staticVf);
	DDX_Control(pDX, CLASSES_IDC_EDIT_F, m_editF);
	DDX_Control(pDX, CLASSES_IDC_EDIT_VF, m_editVf);
}

BEGIN_MESSAGE_MAP(CPageCalcBase2, CPageCalcBase)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_F, &CPageCalcBase2::OnEnChangeEditF)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_VF, &CPageCalcBase2::OnEnChangeEditVf)
END_MESSAGE_MAP()

// Gestionnaires de messages de CPageCalcBase2

BOOL CPageCalcBase2::OnInitDialog()
{
	CPageCalcBase::OnInitDialog();

	// initialisation par d�faut
	SetF(F_DEFAULT);
//	OnChangeTWPair();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION�: les pages de propri�t�s OCX devraient retourner FALSE
}

void CPageCalcBase2::OnChangeTWPair()
{
	// r�cup�rer f, l'afficher (moyenn�) et calculer Vf
	double fmin;
	double fmax;
	
	switch(CalcF(fmin, fmax))
	{
	case 0:
		//ASSERT(0);// � �crire
		//pas d'avance, pas de calcul !
		// appeler � la fin pour validit� des donn�es 
		// lors de l'appel � UpdateControlsStyles();
		CPageCalcBase::OnChangeTWPair();
		return;
	case 1:
		m_editF.m_fLower=fmin;
		m_editF.m_fUpper=fmax;
		SetF((fmin+fmax)/2);
		// appeler � la fin pour validit� des donn�es 
		// lors de l'appel � UpdateControlsStyles();
		CPageCalcBase::OnChangeTWPair();
		break;
	case 2:
		m_editF.m_fLower=fmin;
		m_editF.m_fUpper=fmax;
		SetF((fmin+fmax)/2);
		// appeler � la fin pour validit� des donn�es 
		// lors de l'appel � UpdateControlsStyles();
		CPageCalcBase::OnChangeTWPair();
		break;
	default:
		break;
	}
	
	CalcAndUpdateVf();

	// appeler � la fin pour validit� des donn�es 
	// lors de l'appel � UpdateControlsStyles();
	CPageCalcBase::OnChangeTWPair();
}

void CPageCalcBase2::Clear() // appel�e pour vider les champs
{
	CPageCalcBase::Clear();

	ClearF();
	ClearVf();
}

// mise � jour de D et Vc � partir du couple outil/mati�re
// calcul et mise � jour de N
// r�cup�rer f pour le nouveau D, calculer Vf
void CPageCalcBase2::OnChangeD()
{
	CPageCalcBase::OnChangeD();

	double fmin;
	double fmax;
	
	switch(CalcF(fmin, fmax))
	{
	case 0:
		//ASSERT(0);// � �crire
		//pas d'avance, pas de calcul !
		return;
	case 1:
		ASSERT(fmin==fmax);
		m_editF.m_fLower=fmin;
		m_editF.m_fUpper=fmax;
		SetF((fmin+fmax)/2);
		break;
	case 2:
		m_editF.m_fLower=fmin;
		m_editF.m_fUpper=fmax;
		SetF((fmin+fmax)/2);
		break;
	default:
		break;
	}

	CalcAndUpdateVf();
}

// calcule les limites de f par interpolation, en fonction de D
int CPageCalcBase2::CalcF(double& fmin, double& fmax)
{
	// r�cup�rer les diam�tres maxi et mini d�finis
	if(m_pData==NULL)
		return 0; // A VOIR : MODE CALCULETTE

	//	int n=pCut->GetDataDim();
	CCat* pCat=Data_Cat_GetCurSel();
	CTool* pTool=Data_Tool_GetCurSel();
	
	// A GERER : MODE CALCULETTE
	ASSERT(pCat!=NULL);
	ASSERT(pTool!=NULL);
	CCut* pCut=Data_Cut_GetCurSel();
	ASSERT(pCut!=NULL);

	double D=GetD();
	int n=pCut->GetDataDim();

	if(pCut->fmin[0]>0 && pCut->fmax[0]>0) // fmin et fmax sont d�finis
	{
		fmin=INTERPOL(pCut->diam, pCut->fmin, n, D);
		fmax=INTERPOL(pCut->diam, pCut->fmax, n, D);
		return 2;
	}
	else
	{
		if(pCut->fmin[0]>0) // une seule valeur d'avance
		{
			fmin=fmax=INTERPOL(pCut->diam, pCut->fmin, n, D);
			return 1;
		}
		else // aucune valeur d'avance
		{
			fmin=fmax=0;
			return 0;
		}
	}
}

void CPageCalcBase2::OnChangeN()
{
	CPageCalcBase::OnChangeN();

	// mettre � jour Vf
	CalcAndUpdateVf();
}

void CPageCalcBase2::OnEnChangeEditF()
{
	OnChangeF();
}

void CPageCalcBase2::OnEnChangeEditVf()
{
	OnChangeVf();
}

void CPageCalcBase2::OnChangeF()
{
	// afficher Vf en fonction de F et N
	CalcAndUpdateVf();
}

void CPageCalcBase2::OnChangeVf()
{
	// afficher F en fonction de Vf et N
	CalcAndUpdateF();
}

// calcule et met � jour Vf en fonction de f et N
void CPageCalcBase2::CalcAndUpdateVf()
{
	// Vf = f*N
	SetVf( GetF() * GetN() );
}

// calcule et met � jour f en fonction de Vf et N
void CPageCalcBase2::CalcAndUpdateF()
{
	// f = Vf / N
	double N=GetN();
	if(N!=0)
		SetF( GetVf() / N);
	else
		ClearF();// div / 0
}

void CPageCalcBase2::OnSlider(int nTBCode, UINT nPos)
{
	CPageCalcBase::OnSlider(nTBCode, nPos);

	CWnd* pwndFocus=GetFocus();
	int nID=pwndFocus->GetDlgCtrlID();

	switch(nID)
	{
	case CLASSES_IDC_EDIT_F: 
		{
			double f=GetF();
			switch(nTBCode)
			{
			case SB_LINEUP:
				f+=F_INC;
				break;
			case SB_LINEDOWN:
				if(f>F_INC)
					f-=F_INC;
				break;
			default:
				ASSERT(0);
				break;
			}
			SetF(f);
			OnChangeF();
		}
		break;
	case CLASSES_IDC_EDIT_VF:
		{
			double Vf=GetVf();
			switch(nTBCode)
			{
			case SB_LINEUP:
				Vf+=VF_INC;
				break;
			case SB_LINEDOWN:
				if(Vf>VF_INC)
					Vf-=VF_INC;
				break;
			default:
				ASSERT(0);
				break;
			}
			SetVf(Vf);
			OnChangeVf();
		}	
		break;
	default:
		return;
	}
}

void CPageCalcBase2::UpdateControlsStyles()
{
	CPageCalcBase::UpdateControlsStyles();
	
	// si pas d'avance d�finie, cacher les contr�les
	double fmin, fmax;
	if(CalcF(fmin, fmax))
	{
		m_staticF.ShowWindow(SW_SHOW);
		m_staticVf.ShowWindow(SW_SHOW);
		m_editF.ShowWindow(SW_SHOW);
		m_editVf.ShowWindow(SW_SHOW);
	}
	else
	{
		m_staticF.ShowWindow(SW_HIDE);
		m_staticVf.ShowWindow(SW_HIDE);
		m_editF.ShowWindow(SW_HIDE);
		m_editVf.ShowWindow(SW_HIDE);
	}
}
