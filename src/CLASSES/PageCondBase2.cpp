// PageCond.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "PageCondBase2.h"
#include "CLASSES_rc.h"

// les champs vides sont cachés ou simplement désacivés

// Boîte de dialogue CPageCondBase2

IMPLEMENT_DYNAMIC(CPageCondBase2, CPageCondBase)

CPageCondBase2::CPageCondBase2(UINT nIDTemplate, CData* pData)
	: CPageCondBase(nIDTemplate, pData)
{
	// il faut toujours être en mode scrollbars puisque la hauteur est fixée
	// par le nombre de champs, même s'ils ne sont pas tous visibles
	// pour éviter l'équivoque, voir ce que ça donne
	// en désactivant plutôt qu'en cachant les controles inutilisés
	EnableScrollbars(TRUE);

	for(int i=0; i<GRID_LINES; i++)
	{
		m_editD[i].m_bNoGray=TRUE;
		m_editFmin[i].m_bNoGray=TRUE;
		m_editFmax[i].m_bNoGray=TRUE;
	}
}

CPageCondBase2::~CPageCondBase2()
{
}

void CPageCondBase2::DoDataExchange(CDataExchange* pDX)
{
	CPageCondBase::DoDataExchange(pDX);

	for(int i=0; i<GRID_LINES; i++)
	{
		DDX_Control(pDX, CLASSES_IDC_STATIC_A1+i, m_staticA[i]);
		DDX_Control(pDX, CLASSES_IDC_EDIT_D1+i, m_editD[i]);
		DDX_Control(pDX, CLASSES_IDC_EDIT_FMIN1+i, m_editFmin[i]);
		DDX_Control(pDX, CLASSES_IDC_EDIT_FMAX1+i, m_editFmax[i]);
	}
	DDX_Control(pDX, CLASSES_IDC_STATIC_D, m_staticDiam);
	DDX_Control(pDX, CLASSES_IDC_STATIC_FEED, m_staticFeed);
}


BOOL CPageCondBase2::OnInitDialog()
{
	CPageCondBase::OnInitDialog();

	PositionFeedsGrid();

	// pour les controles supplémentaires
	//OnChangeTWPair();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

BEGIN_MESSAGE_MAP(CPageCondBase2, CPageCondBase)
	ON_CONTROL_RANGE(EN_CHANGE, CLASSES_IDC_EDIT_D1, CLASSES_IDC_EDIT_D1+GRID_LINES, &CPageCondBase2::OnEnChangeEditD)
	ON_CONTROL_RANGE(EN_CHANGE, CLASSES_IDC_EDIT_FMIN1, CLASSES_IDC_EDIT_FMIN1+GRID_LINES, &CPageCondBase2::OnEnChangeEditFmin)
	ON_CONTROL_RANGE(EN_CHANGE, CLASSES_IDC_EDIT_FMAX1, CLASSES_IDC_EDIT_FMAX1+GRID_LINES, &CPageCondBase2::OnEnChangeEditFmax)
END_MESSAGE_MAP()

// Gestionnaires de messages de CPageCondBase2
void CPageCondBase2::OnEnChangeEditD(UINT nID)
{
	ASSERT(GetEditMode());

	double newValue=GetDlgItemValue(nID);

	UINT i=nID-CLASSES_IDC_EDIT_D1;
	if(ReadD(i)!=newValue)
	{
		if(WriteD(i, newValue))
			m_pData->SetModifiedFlag(TRUE);
	}
}

void CPageCondBase2::OnEnChangeEditFmin(UINT nID)
{
	ASSERT(GetEditMode());

	double newValue=GetDlgItemValue(nID);

	UINT i=nID-CLASSES_IDC_EDIT_FMIN1;
	if(ReadFmin(i)!=newValue)
	{
		if(WriteFmin(i, newValue))
			m_pData->SetModifiedFlag(TRUE);

		//if(!m_fNoHintCondChanged)
		//	UpdateAllOtherPages(HINT_COND_CHANGED);
	}
}

void CPageCondBase2::OnEnChangeEditFmax(UINT nID)
{
	ASSERT(GetEditMode());

	double newValue=GetDlgItemValue(nID);

	UINT i=nID-CLASSES_IDC_EDIT_FMAX1;
	if(ReadFmax(i)!=newValue)
	{
		if(WriteFmax(i, newValue))
			m_pData->SetModifiedFlag(TRUE);
	}
}

void CPageCondBase2::Clear()
{
	CPageCondBase::Clear();

	m_fNoHintCondChanged=TRUE;

	for(int i=0; i<GRID_LINES; i++)
	{
		ClearD(i);
		ClearFmin(i);
		ClearFmax(i);
	}

	m_fNoHintCondChanged=FALSE;
}

//PAS BON : MELANGE ENTRE DONNEES ET STYLES
void CPageCondBase2::OnChangeTWPair()
{
	CTool* pTool=Data_Tool_GetCurSel();

	if(pTool==NULL) // fichier vide
	{
		Clear();
		// appeler à la fin pour validité des données 
		// lors de l'appel à UpdateControlsStyles();
		CPageTCA::OnChangeTWPair();
		return;
	}

	CCat* pCat=Data_Cat_GetCurSel();

	if(pCat==NULL)
	{
		// cas où le fichier de matières est vide
		TRACE(_T("CPageCondBase2::UpdatePage() : pCat = NULL\n"));
		// appeler à la fin pour validité des données 
		// lors de l'appel à UpdateControlsStyles();
		CPageTCA::OnChangeTWPair();
		return;
	}

	m_fNoHintCondChanged=TRUE;

	if(GetEditMode())
	{
		for(int i=0; i<GRID_LINES; i++)
		{
			SetD(i, ReadD(i));
			SetFmin(i, ReadFmin(i));
			SetFmax(i, ReadFmax(i));
		}
	}
	else
	{
		// commencer par vider ; ensuite, remplir 
		// jusqu'à trouver une ligne invalide...
		for(int i=0; i<GRID_LINES; i++)
		{
			ClearD(i);
			ClearFmin(i);
			ClearFmax(i);
		}

		for(int i=0; i<GRID_LINES; i++)
		{
			// affichage de la ligne si diamètre défini ET avance définie
			double D=ReadD(i);
			double fmin=ReadFmin(i);

			if(D>0 && fmin>0)
			{
				SetD(i, D);
				SetFmin(i, fmin);
				SetFmax(i, ReadFmax(i));
			}
			else
				break; // les suivantes sont déjà vides
		}
	}
	m_fNoHintCondChanged=FALSE;

	// appeler à la fin pour validité des données 
	// lors de l'appel à UpdateControlsStyles();
	CPageCondBase::OnChangeTWPair();}

void CPageCondBase2::PositionFeedsGrid()
{
	// récupérer les positions des controles de référence
	CRect rcD1;
	CRect rcVcmin;
	CRect rcVcmax;
	CRect rcA0;
	CRect rcA1;
	CRect rcClient;
	CRect rcVc;

	m_staticVc.GetWindowRect(rcVc);
	m_editD[0].GetWindowRect(rcD1);
	m_editVcmin.GetWindowRect(rcVcmin);
	m_staticA0.GetWindowRect(rcA0);
	m_editVcmax.GetWindowRect(rcVcmax);
	m_staticA[0].GetWindowRect(rcA1);
	GetClientRect(rcClient);


	ScreenToClient(rcVc);
	ScreenToClient(rcD1);
	ScreenToClient(rcVcmin);
	ScreenToClient(rcVcmax);
	ScreenToClient(rcA0);
	ScreenToClient(rcA1);

	int cx=rcClient.Width()-2*::GetSystemMetrics(SM_CXEDGE);

	int xD = rcD1.left;			// position d'alignement left des static D
	int xVc = rcVc.left;			// position d'alignement left des static D
	int yD = rcD1.top;			// position d'alignement top du premier static D
	int cxD = rcD1.Width();		// largeur des static D
	int xVcmin = rcVcmin.left;	// position d'alignement left des edit Vcmin et fmin
	int xVcmax = rcVcmax.left;	// position d'alignement left des edit Vcmax et fmax
	int cxVc = rcVcmin.Width();	// largeur des edit Vc, f
	int cyVc = rcVcmin.Height();// hauteur des edit
	int cxA = rcA0.Width();		// largeur des static "à"
	int cyA = rcA0.Width();		// hauteur des static "à"
	int xA = rcA0.left;			// position d'alignement left des static "à"
	int yA1 = rcA1.top;			// position y du premier static "à" des f
	
	int dy = cyVc-::GetSystemMetrics(SM_CYBORDER);			// décalage en hauteur des edit D et f du tableau

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER/*|SWP_NOREDRAW*/;

	CRect rc;

	m_staticDiam.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticDiam.SetWindowPos(NULL, xVc, rc.top, rc.Width(), rc.Height(), uFlags);

	for(int i=0; i<GRID_LINES; i++)
	{
		// positionner les edit D
		m_editD[i].SetWindowPos(NULL, xVc, yD+dy*i, cxD, cyVc, uFlags);

		// aligner les edit fmin avec l'edit Vcmin
		m_editFmin[i].SetWindowPos(NULL, xVcmin, yD+dy*i, cxVc, cyVc, uFlags);

		// aligner les edit "à" avec celui des Vc
		m_staticA[i].SetWindowPos(NULL, xA, yA1+dy*i, cxA, cyA, uFlags);

		// aligner les edit fmax avec l'edit Vcmax
		m_editFmax[i].SetWindowPos(NULL, xVcmax, yD+dy*i, cxVc, cyVc, uFlags);
	}
}

void CPageCondBase2::UpdateControlsStyles()
{
	CPageCondBase::UpdateControlsStyles();

	BOOL bEditMode=GetEditMode();

	if(bEditMode)
	{
		// afficher tout
		m_staticDiam.ShowWindow(SW_SHOW);
		m_staticFeed.ShowWindow(SW_SHOW);

		for(int i=0; i<GRID_LINES; i++)
		{
			m_editD[i].ShowWindow(SW_SHOW);
			m_editD[i].EnableWindow(TRUE);
			m_editD[i].SetReadOnly(FALSE);

			m_editFmin[i].ShowWindow(SW_SHOW);
			m_editFmin[i].EnableWindow(TRUE);
			m_editFmin[i].SetReadOnly(FALSE);

			m_staticA[i].ShowWindow(SW_SHOW);

			m_editFmax[i].ShowWindow(SW_SHOW);
			m_editFmax[i].EnableWindow(TRUE);
			m_editFmax[i].SetReadOnly(FALSE);
		}
	}
	else
	{
		// tous désactivés, read only et caché
		m_staticDiam.ShowWindow(SW_HIDE);
		m_staticFeed.ShowWindow(SW_HIDE);

		for(int i=0; i<GRID_LINES; i++)
		{
			m_editD[i].EnableWindow(FALSE);
			m_editFmin[i].EnableWindow(FALSE);
			m_editFmax[i].EnableWindow(FALSE);

			m_editD[i].SetReadOnly(TRUE);
			m_editFmin[i].SetReadOnly(TRUE);
			m_editFmax[i].SetReadOnly(TRUE);

			m_editD[i].ShowWindow(SW_HIDE);
			m_editFmin[i].ShowWindow(SW_HIDE);
			m_staticA[i].ShowWindow(SW_HIDE);
			m_editFmax[i].ShowWindow(SW_HIDE);
		}

		// n'afficher que les données valides
		for(int i=0; i<GRID_LINES; i++)
		{
			// affichage de la ligne si diamètre défini ET avance définie
			if(ReadD(i) && ReadFmin(i))
			{
				if(i==0) // 1 ligne valide suffit...
				{
					m_staticDiam.ShowWindow(SW_SHOW);
					m_staticFeed.ShowWindow(SW_SHOW);
				}

				m_editD[i].ShowWindow(SW_SHOW);
				m_editFmin[i].ShowWindow(SW_SHOW);
				if(ReadFmax(i))
				{
					m_staticA[i].ShowWindow(SW_SHOW);
					m_editFmax[i].ShowWindow(SW_SHOW);
				}
				else
				{
					// pas de fmax : ne pas afficher
					m_staticA[i].ShowWindow(SW_HIDE);
					m_editFmax[i].ShowWindow(SW_HIDE);
				}
			}
			else // les suivantes sont déjà cachées
				break;
		}
	}
}
