// PageCalcTurning.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "CLASSES_rc.h"
#include "PageCalcBase.h"
#include "SheetCutCalc.h"

// donner une valeur par défaut au diamètre

#define DIAM_INC		0.25
#define VC_INC			0.5
#define N_INC			50

// test des valeurs :
//
// D :
// si m_fDmin == m_fDmax
// ou m_fDmax
// pas de contrôle du diamètre
// normalement, on devrait dans ce cas avoir fDmin=m_fDmax
// revoir la saisie
//
// pour Vcmin et Vcmax, laisser une tolérance sur la valeur calculée 
// si on ne peut pas avoir fVcmax = 0 ; dans ce cas, fVcmax=fVcmin
// à partir de N
//
// gérer le mode calcul simple (pData=NULL)
// diamètre par défaut : 10 mm, Vc par défaut 10m/mn

#define VC_TOL	(10/100.0)
#define DIAM_DEFAULT	10
#define VC_DEFAULT		10

// Boîte de dialogue CPageCalcBase

IMPLEMENT_DYNAMIC(CPageCalcBase, CPageTCA)

CPageCalcBase::CPageCalcBase(UINT nIDTemplate, CData* pData)
	: CPageTCA(nIDTemplate, pData)
{
	m_editD.m_bFrameFocus=TRUE;
	m_editVc.m_bFrameFocus=TRUE;
	m_editN.m_bFrameFocus=TRUE;

	m_editD.m_bNoCaret=TRUE;
	m_editVc.m_bNoCaret=TRUE;
	m_editN.m_bNoCaret=TRUE;

	EnableScrollbars(TRUE);
}

CPageCalcBase::~CPageCalcBase()
{
}

void CPageCalcBase::DoDataExchange(CDataExchange* pDX)
{
	CPageTCA::DoDataExchange(pDX);
	
	DDX_Control(pDX, CLASSES_IDC_STATIC_D, m_staticD);
	DDX_Control(pDX, CLASSES_IDC_STATIC_VC, m_staticVc);
	DDX_Control(pDX, CLASSES_IDC_STATIC_N, m_staticN);

	DDX_Control(pDX, CLASSES_IDC_EDIT_D, m_editD);
	DDX_Control(pDX, CLASSES_IDC_EDIT_VC, m_editVc);
	DDX_Control(pDX, CLASSES_IDC_EDIT_N, m_editN);
}

BEGIN_MESSAGE_MAP(CPageCalcBase, CPageTCA)
	ON_WM_DESTROY()
	ON_EN_CHANGE(CLASSES_IDC_EDIT_D, &CPageCalcBase::OnEnChangeEditD)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_VC, &CPageCalcBase::OnEnChangeEditVc)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_N, &CPageCalcBase::OnEnChangeEditN)
END_MESSAGE_MAP()

// Gestionnaires de messages de CPageCalcBase

BOOL CPageCalcBase::OnInitDialog()
{
	CPageTCA::OnInitDialog();

	// initialisation par défaut
	SetD(DIAM_DEFAULT);
	SetVc(VC_DEFAULT);
	//OnChangeTWPair();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageCalcBase::Clear() // appelée pour vider les champs
{
	ClearD();
	ClearVc();
	ClearN();
}

// mise à jour de D et Vc à partir du couple outil/matière
// calcul et mise à jour de N
void CPageCalcBase::OnChangeTWPair()
{
	// ces intervalles ne changent qu'en cas de changement de couple outil matière
	m_editD.m_fLower=ReadDmin();
	m_editD.m_fUpper=ReadDmax();
	// conserver la valeur courante
	
	// forcer la prise en compte de l'intervalle
	m_editD.RedrawWindow();

	m_editVc.m_fLower=ReadVcmin();
	m_editVc.m_fUpper=ReadVcmax();

	// moyenner la Vc
	SetMeanVc();
	
	CalcAndUpdateN();

	// appeler à la fin pour validité des données 
	// lors de l'appel à UpdateControlsStyles();
	CPageTCA::OnChangeTWPair();
}

void CPageCalcBase::SetMeanVc() // recadre la Vc à la moyenne
{
	// recadrer la Vc

	if(m_editVc.m_fLower<m_editVc.m_fUpper)
		SetVc((m_editVc.m_fUpper+m_editVc.m_fLower)/2);
	else
		SetVc(m_editVc.m_fLower);
	
	// forcer la prise en compte de l'intervalle
	m_editVc.RedrawWindow();
}

// calcule et met à jour N en fonction de D et Vc
// m_editN = f(D, Vc);
void CPageCalcBase::CalcAndUpdateN()
{
	double D=GetD();
	
	if(D!=0)
		SetN( 1000.0 * GetVc() / (3.14159 * D) );
	else
		ClearN(); // div / 0
}

// calcule et met à jour Vc en fonction de D et N
void CPageCalcBase::CalcAndUpdateVc()
{
	// m_editVc = f(D, N);

	if(m_pData!=NULL)
	{
		m_editVc.m_fLower=ReadVcmin();
		m_editVc.m_fUpper=ReadVcmax();
	}

	SetVc( 3.14159 * GetD() * GetN() / 1000.0 );
}

void CPageCalcBase::OnEnChangeEditD()
{
	OnChangeD();
}

void CPageCalcBase::OnEnChangeEditVc()
{
	OnChangeVc();
}

void CPageCalcBase::OnEnChangeEditN()
{
	OnChangeN();
}

// afficher N en fonction de D et Vc
void CPageCalcBase::OnChangeD()
{
	CalcAndUpdateN();
}


// afficher N en fonction de D et Vc
void CPageCalcBase::OnChangeVc()
{
	CalcAndUpdateN();
}

// afficher Vc en fonction de D et N
void CPageCalcBase::OnChangeN()
{
	CalcAndUpdateVc();
}

void CPageCalcBase::OnSlider(int nTBCode, UINT nPos)
{
	CPageTCA::OnSlider(nTBCode, nPos);

	CWnd* pwndFocus=GetFocus();
	int nID=pwndFocus->GetDlgCtrlID();

	switch(nID)
	{
	case CLASSES_IDC_EDIT_D: 
		{
			double D=GetD();
			switch(nTBCode)
			{
			case SB_LINEUP:
				D+=DIAM_INC;
				break;
			case SB_LINEDOWN:
				if(D>DIAM_INC)
					D-=DIAM_INC;
				break;
			default:
				// message parasite : ne rien faire
				ASSERT(0);
				break;
			}
			SetD(D);
			OnChangeD();
		}
		break;

	case CLASSES_IDC_EDIT_VC:
		{
			int iVc=(int)(GetVc()*10);
			int iInc=(int)(10*VC_INC);

			switch(nTBCode)
			{
			case SB_LINEUP:
				// arrondi
				iVc=iInc*(iVc/iInc);
				iVc+=iInc;
				break;
			case SB_LINEDOWN:
				// arrondi
				iVc=iInc*(iVc/iInc);
				if(iVc>iInc)
					iVc-=iInc;
				break;
			default:
				ASSERT(0);
				break;
			}

			SetVc((double)iVc/10);
			OnChangeVc();
		}
		break;

	case CLASSES_IDC_EDIT_N:
		{
			// incrément :
			// > 2000		: 100
			// 1000 -> 2000	: 50
			// 100 -> 1000	: 25
			// 50 -> 100	: 10
			// 0 -> 50		: 5

			int N=(int)GetN();
			int nInc=1000000; // détecteur de bug

			switch(nTBCode)
			{
			case SB_LINEUP:
				{
					if(N<50)
						nInc=5;
					else if(N<100)
						nInc=10;
					else if(N<1000)
						nInc=25;
					else if(N<2000)
						nInc=50;
					else
						nInc=100;

					N=nInc*(N/nInc);
					N+=nInc;
				}
				break;
			case SB_LINEDOWN:
				{
					if(N>2000)
						nInc=100;
					else if(N>1000)
						nInc=50;
					else if(N>100)
						nInc=25;
					else if(N>50)
						nInc=10;
					else
						nInc=5;

					// arrondi
					N=nInc*(N/nInc);

					// N=0 interdit
					if(N>nInc)
						N-=nInc;
				}
				break;
			default:
				ASSERT(0);
				break;
			}
			SetN(N);
			OnChangeN();
		}
		break;
	default:
		return;
	}
}



