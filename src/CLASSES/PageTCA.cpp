// PageTCA.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "PageTCA.h"
#include "CLASSES_rc.h"

// ID du pad magique ; doit être incrémenté à chaque appel de 
// Create pour éviter d'en avoir deux avec le même ID !
static int s_nScrollPad=3333;

// en cas d'absence de fichier d'outils, cacher :
// - le scrollpad
// - les 3 combos

// Boîte de dialogue CPageTCA

IMPLEMENT_DYNAMIC(CPageTCA, CPropertyPage)

CPageTCA::CPageTCA(UINT nIDTemplate, CData* pData):
	CPropPageEx(nIDTemplate, pData)
{
	m_comboTool.SetFullDrop(TRUE);
	m_comboCat.SetFullDrop(TRUE);
	m_comboAlloy.SetFullDrop(TRUE);
	m_fNoHintCondChanged=TRUE;
}

CPageTCA::~CPageTCA()
{
}

CCut* CPageTCA::Data_Cut_GetCurSel()
{
	CCat* pCat=Data_Cat_GetCurSel();
	if(pCat==NULL)
	{
		// cas où le fichier de matières est vide
		return NULL;
	}

	CTool* pTool=Data_Tool_GetCurSel();

	if(pTool==NULL) // fichier vide
		return NULL;

	return pTool->MapCatCut_GetAt(pCat->m_nID);
}

void CPageTCA::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);

	DDX_Control(pDX, CLASSES_IDC_COMBO_TOOL, m_comboTool);
	DDX_Control(pDX, CLASSES_IDC_COMBO_CAT, m_comboCat);
	DDX_Control(pDX, CLASSES_IDC_STATIC_ALLOY, m_staticAlloy);
	DDX_Control(pDX, CLASSES_IDC_COMBO_ALLOY, m_comboAlloy);
}

BEGIN_MESSAGE_MAP(CPageTCA, CPropPageEx)
	ON_CBN_SELCHANGE(CLASSES_IDC_COMBO_TOOL, &CPageTCA::OnCbnSelChangeTool)
	ON_CBN_SELCHANGE(CLASSES_IDC_COMBO_CAT, &CPageTCA::OnCbnSelChangeCat)
	ON_CBN_SELCHANGE(CLASSES_IDC_COMBO_ALLOY, &CPageTCA::OnCbnSelChangeAlloy)
END_MESSAGE_MAP()

// Gestionnaires de messages de CPageTCA


void CPageTCA::OnCbnSelChangeTool()
{
	CTool* pTool=Combo_Tool_GetCurSel();

	if(pTool==NULL)
	{
		ASSERT(0);
		return;
	}

	Data_Tool_SetCurSel(pTool);

	// remplir la combo des catégories associées à l'outil sélectionné
	FillComboCat();
	CCat* pCurSelCat=Data_Cat_GetCurSel();
	Combo_Cat_SetCurSel(pCurSelCat);

	// remplir la combo des nuances associées à l'outil sélectionné
	FillComboAlloy();
	CAlloy* pCurSelAlloy=Data_Alloy_GetCurSel();
	Combo_Alloy_SetCurSel(pCurSelAlloy);

	if(!GetEditMode())
	{
		// vérifier que la matière sélectionnée dans la combo
		// est valide pour l'outil courant
		POSITION posCatId=pTool->CatId_GetHeadPosition();
		while(posCatId)
		{
			int nCatId=pTool->CatId_GetNext(posCatId);

			if(pCurSelCat!=NULL && pCurSelCat->m_nID==nCatId)
			{
				// en mode lecture, seules sont placées dans la combo
				// les matières pour lesquelles Vcmin ou Vcmax est définie
				CCut* pCut=pTool->MapCatCut_GetAt(nCatId);
				ASSERT(pCut!=NULL);
				if(pCut->nVcmin==0 /*&& pCut->nVcmax==0*/) // invalide
				{
					// sélectionner le premier item de la combo, si présent
					if(m_comboCat.GetCount())
					{
						m_comboCat.SetCurSel(0);
						CCat* pCat=Combo_Cat_GetCurSel();
						ASSERT((int)pCat!=CB_ERR);
						Data_Cat_SetCurSel(pCat);
					}
					else
					{
						m_comboCat.SetCurSel(-1);
						Data_Cat_SetCurSel(NULL);
					}
				}
			}
		}
	}

	OnChangeTWPair();
}

void CPageTCA::OnCbnSelChangeCat()
{
	CCat* pCat=Combo_Cat_GetCurSel();
	Data_Cat_SetCurSel(pCat);

	// changement de Catégorie : pas de sélection de nuance
	Data_Alloy_SetCurSel(NULL);
	Combo_Alloy_SetCurSel(NULL);

	OnChangeTWPair();
}

void CPageTCA::OnCbnSelChangeAlloy()
{
	CAlloy* pAlloy=Combo_Alloy_GetCurSel();
	Data_Alloy_SetCurSel(pAlloy);
	
	if(pAlloy!=NULL)
	{
		CCat* pCat=pAlloy->m_pCat;
		Data_Cat_SetCurSel(pCat);

		// sélectionner la catégorie à laquelle appartient la nuance
		Combo_Cat_SetCurSel(pCat);
	}

	OnChangeTWPair();
}

BOOL CPageTCA::OnInitDialog()
{
	CPropPageEx::OnInitDialog();
	
	InitializeTCACombos();
	
	// problèmes si créée dans la Sheet (focus, etc.)
	m_scrollPad.Create(_T(""), WS_CHILD|WS_VISIBLE|WS_BORDER/*|WS_TABSTOP|TBS_VERT|TBS_NOTICKS|TBS_BOTH*/, 
								CRect(0,0,0,0), GetParent(), s_nScrollPad++); 

	// place le scrollpad par dessus touts les fenêtres
	m_scrollPad.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageTCA::InitializeTCACombos()
{
	if(m_pData==NULL) // mode calculette
	{
		// pas de données : désactiver
		//m_comboTool.ShowWindow(SW_HIDE);
		//m_comboCat.ShowWindow(SW_HIDE);
		//m_comboAlloy.ShowWindow(SW_HIDE);
		//m_staticAlloy.ShowWindow(SW_HIDE);
		// vider
		m_comboTool.ResetContent();
		m_comboCat.ResetContent();
		m_comboAlloy.ResetContent();

		return;
	}

	//m_comboTool.ShowWindow(SW_SHOW);
	//m_comboCat.ShowWindow(SW_SHOW);
	//m_comboAlloy.ShowWindow(SW_SHOW);
	//m_staticAlloy.ShowWindow(SW_SHOW);

	if(m_pData->IsEmpty()) // aucun outil
	{
		// montrer les combos, mais les désactiver
		//m_comboTool.EnableWindow(FALSE);
		//m_comboCat.EnableWindow(FALSE);
		//m_comboAlloy.EnableWindow(FALSE);
		m_comboTool.ResetContent();
		m_comboCat.ResetContent();
		m_comboAlloy.ResetContent();
		
		return;
	}

	//m_comboTool.EnableWindow(TRUE);
	//m_comboCat.EnableWindow(TRUE);
	//m_comboAlloy.EnableWindow(TRUE);

	FillComboTool();

	CTool* pTool=Data_Tool_GetCurSel();
	Combo_Tool_SetCurSel(pTool);

	FillComboCat();

	// sélectionner la catégorie
	CCat* pCat=Data_Cat_GetCurSel();
	Combo_Cat_SetCurSel(pCat);

	FillComboAlloy();

	// sélectionner la nuance
	CAlloy* pAlloy=Data_Alloy_GetCurSel();
	Combo_Alloy_SetCurSel(pAlloy);
}

void CPageTCA::FillComboTool()
{
	m_fNoHintCondChanged=TRUE;
	// remplir la combo Tool
	m_comboTool.ResetContent();
	POSITION pos=Data_Tool_GetHeadPosition();
	while(pos)
	{
		CTool* pTool=Data_Tool_GetNext(pos);
		ASSERT_VALID(pTool);
		int nIndex = m_comboTool.AddString(pTool->m_strName);
		ASSERT(nIndex!=-1);
		m_comboTool.SetItemDataPtr(nIndex, pTool);
	}
	m_fNoHintCondChanged=FALSE;
}

void CPageTCA::FillComboCat()
{
	m_comboCat.ResetContent();

	ASSERT(m_pData!=NULL);
	CTool* pTool=Data_Tool_GetCurSel();

	if(pTool==NULL)
		return;

	POSITION posCat=Data_Cat_GetHeadPosition();
	m_fNoHintCondChanged=TRUE;

	while(posCat)  // parcourir la liste des catégories
	{
		CCat* pCat=Data_Cat_GetNext(posCat);
		ASSERT(pCat!=NULL);

		POSITION posCatId=pTool->CatId_GetHeadPosition();
		while(posCatId)
		{
			int nCatId=pTool->CatId_GetNext(posCatId);

			if(pCat->m_nID==nCatId)
			{
				// en mode lecture, ne pas placer les catégories et nuances 
				// pour lesquelles il n'y a pas de conditions valides (non vides)
				CCut* pCut=pTool->MapCatCut_GetAt(nCatId);
				ASSERT(pCut!=NULL);
				if(GetEditMode()==FALSE)
				{
					if(pCut->IsValid())
					{				
						// placer la catégorie dans la combo des catégories
						int n=m_comboCat.AddString(pCat->m_strName);
						ASSERT(n!=-1);
						m_comboCat.SetItemDataPtr(n, pCat);
					}
				}
				else 
				{
					// mode édition : placer toutes les catégories
					// et ajouter une astérisque aux catégories et alliages 
					// ayant des conditions de coupe défiies

					// placer la catégorie dans la combo des catégories
					if(pCut->nVcmin)
					{
						CString str = _T("» ")+pCat->m_strName;
						int n=m_comboCat.AddString(str);
						ASSERT(n!=-1);
						m_comboCat.SetItemDataPtr(n, pCat);
					}
					else
					{
						CString str = _T("   ")+pCat->m_strName;
						int n=m_comboCat.AddString(str);
						ASSERT(n!=-1);
						m_comboCat.SetItemDataPtr(n, pCat);
					}
				}
			}
		}
	}

	m_fNoHintCondChanged=FALSE;
}

void CPageTCA::FillComboAlloy()
{
	m_comboAlloy.ResetContent();

	ASSERT(m_pData!=NULL);
	CTool* pTool=Data_Tool_GetCurSel();

	if(pTool==NULL)
	{
		return;
	}

	POSITION posCat=Data_Cat_GetHeadPosition();
	m_fNoHintCondChanged=TRUE;

	while(posCat)  // parcourir la liste des catégories
	{
		CCat* pCat=Data_Cat_GetNext(posCat);
		ASSERT(pCat!=NULL);

		POSITION posCatId=pTool->CatId_GetHeadPosition();
		while(posCatId)
		{
			int nCatId=pTool->CatId_GetNext(posCatId);

			if(pCat->m_nID==nCatId)
			{
				// en mode lecture, ne pas placer les catégories et nuances 
				// pour lesquelles il n'y a pas de conditions valides (non vides)
				CCut* pCut=pTool->MapCatCut_GetAt(nCatId);
				ASSERT(pCut!=NULL);
				if(GetEditMode()==FALSE)
				{
					if(pCut->IsValid())
					{				
						POSITION posAlloy=pCat->Alloy_GetHeadPosition();

						// placer les nuances dans la combo des nuances
						while(posAlloy)
						{
							CAlloy* pAlloy=pCat->Alloy_GetNext(posAlloy);
							ASSERT(pAlloy!=NULL);
							int n=m_comboAlloy.AddString(pAlloy->m_strName);
							ASSERT(n!=-1);
							// associer la catégorie correspondante
							m_comboAlloy.SetItemDataPtr(n, pAlloy);
						}
					}
				}
				else 
				{
					// mode édition : placer toutes les catégories
					// et ajouter une astérisque aux catégories et alliages 
					// ayant des conditions de coupe défiies

					// placer la catégorie dans la combo des catégories
					if(pCut->nVcmin)
					{
						CString str = _T("» ")+pCat->m_strName;
						POSITION posAlloy=pCat->Alloy_GetHeadPosition();

						// placer les nuances dans la combo des nuances
						while(posAlloy)
						{
							CAlloy* pAlloy=pCat->Alloy_GetNext(posAlloy);
							ASSERT(pAlloy!=NULL);
							str = _T("» ")+pAlloy->m_strName;
							int n=m_comboAlloy.AddString(str);
							ASSERT(n!=-1);
							// associer la catégorie correspondante
							m_comboAlloy.SetItemDataPtr(n, pAlloy);
						}
					}
					else
					{
						CString str = _T("   ")+pCat->m_strName;
						POSITION posAlloy=pCat->Alloy_GetHeadPosition();

						// placer les nuances dans la combo des nuances
						while(posAlloy)
						{
							CAlloy* pAlloy=pCat->Alloy_GetNext(posAlloy);
							ASSERT(pAlloy!=NULL);
							str = _T("   ")+pAlloy->m_strName;
							int n=m_comboAlloy.AddString(str);
							ASSERT(n!=-1);
							// associer la catégorie correspondante
							m_comboAlloy.SetItemDataPtr(n, pAlloy);
						}
					}
				}
			}
		}
	}

	m_fNoHintCondChanged=FALSE;
}


void CPageTCA::OnHintToolSelChanged()
{
	CTool* pTool=Data_Tool_GetCurSel();
	Combo_Tool_SetCurSel(pTool);

	if(pTool==NULL)
	{
		// cas d'un fichier vide
//		ASSERT(0);
		return;
	}

	// remplir la combo des catégories associées à l'outil sélectionné
	FillComboCat();
	CCat* pCurSelCat=Data_Cat_GetCurSel();
	Combo_Cat_SetCurSel(pCurSelCat);

	// remplir la combo des nuances associées à l'outil sélectionné
	FillComboAlloy();
	CAlloy* pCurSelAlloy=Data_Alloy_GetCurSel();
	Combo_Alloy_SetCurSel(pCurSelAlloy);

	if(!GetEditMode())
	{
		// vérifier que la matière sélectionnée dans la combo
		// est valide pour l'outil courant
		POSITION posCatId=pTool->CatId_GetHeadPosition();
		while(posCatId)
		{
			int nCatId=pTool->CatId_GetNext(posCatId);

			if(pCurSelCat!=NULL && pCurSelCat->m_nID==nCatId)
			{
				// en mode lecture, seules sont placées dans la combo
				// les matières pour lesquelles Vcmin ou Vcmax est définie
				CCut* pCut=pTool->MapCatCut_GetAt(nCatId);
				ASSERT(pCut!=NULL);
				if(pCut->nVcmin==0 && pCut->nVcmax==0) // invalide
				{
					// sélectionner le premier item de la combo, si présent
					if(m_comboCat.GetCount())
					{
						m_comboCat.SetCurSel(0);
						CCat* pCat=Combo_Cat_GetCurSel();
						ASSERT((int)pCat!=CB_ERR);
					}
					else
					{
						m_comboCat.SetCurSel(-1);
					}
				}
			}
		}
	}
}

void CPageTCA::OnHintCatSelChanged()
{
	CCat* pCat=Data_Cat_GetCurSel();
	Combo_Cat_SetCurSel(pCat);

	// changement de Catégorie : pas de sélection de nuance
	Combo_Alloy_SetCurSel(NULL);
}

void CPageTCA::OnHintAlloySelChanged()
{
	CAlloy* pAlloy=Data_Alloy_GetCurSel();
	Combo_Alloy_SetCurSel(pAlloy);
	
	if(pAlloy!=NULL)
	{
		CCat* pCat=pAlloy->m_pCat;

		// sélectionner la catégorie à laquelle appartient la nuance
		Combo_Cat_SetCurSel(pCat);
	}
}

int CPageTCA::Combo_Tool_SetCurSel(CTool* pTool)
{
	if(pTool==NULL)
	{
		m_comboTool.SetCurSel(-1);
		return CB_ERR;
	}

	int nCount=m_comboTool.GetCount();
	for(int i=0; i<nCount; i++)
		if(m_comboTool.GetItemDataPtr(i)==pTool)
		{
			m_comboTool.SetCurSel(i);
			return i;
		}

	// non trouvé
	return CB_ERR;
}

int CPageTCA::Combo_Cat_SetCurSel(CCat* pCat)
{
	if(pCat==NULL)
	{
		m_comboCat.SetCurSel(-1);
		return CB_ERR;
	}

	int nCount=m_comboCat.GetCount();
	for(int i=0; i<nCount; i++)
		if(m_comboCat.GetItemDataPtr(i)==pCat)
		{
			m_comboCat.SetCurSel(i);
			return i;
		}

	// non trouvé : cas d'un outil nouveau, ou si sélection d'un outil
	// alors que la matière courante ne figue pas dans sa liste
	return CB_ERR;
}

int CPageTCA::Combo_Alloy_SetCurSel(CAlloy* pAlloy)
{
	if(pAlloy==NULL)
	{
		m_comboAlloy.SetCurSel(-1);
		return CB_ERR;
	}

	ASSERT(pAlloy!=NULL);
	int nCount=m_comboAlloy.GetCount();
	for(int i=0; i<nCount; i++)
	if(m_comboAlloy.GetItemDataPtr(i)==pAlloy)
	{
		m_comboAlloy.SetCurSel(i);
		return i;
	}

	// non trouvé ; se produit quand une matière est sélectionnée, 
	// puis qu'on change d'outil et que cette matière ne fait pas partie
	// de la liste associée à ce nouvel outil
	// sélectionner la première matère et le premier alliage
	return CB_ERR;
}

// cacher et désactiver le slider magique afin de ne pas perturber le fonctionnement
// des autres pages (touches permettant de gérer le passsage d'un controle à l'autre)

BOOL CPageTCA::OnSetActive()
{
	m_scrollPad.ShowWindow(SW_SHOW);
	m_scrollPad.EnableWindow(TRUE);

	InitializeTCACombos();
	OnChangeTWPair();

	return CPropPageEx::OnSetActive();
}

BOOL CPageTCA::OnKillActive()
{
	m_scrollPad.ShowWindow(SW_HIDE);
	m_scrollPad.EnableWindow(FALSE);

	return CPropPageEx::OnKillActive();
}

int CPageTCA::RepositionScrollPad(const CRect& rc)
{
	if(!::IsWindow(m_scrollPad.m_hWnd))
		return 0;

	int cxMargin=0;//::GetSystemMetrics(SM_CXEDGE);

	// rectangle slider fixe en coordonnées écran
	CRect rcSlider;
// ?????	m_scrollPad.GetWindowRect(rcSlider); // INUTILE !!!
	// 21 en 320x240, 38 en VGA
	// 1+1					2+2
	int cxSlider=::GetSystemMetrics(SM_CYVSCROLL);
	rcSlider.left=0;//cxMargin;
	rcSlider.top=0;//::GetSystemMetrics(SM_CYDLGFRAME);
	rcSlider.right=rcSlider.left+cxSlider;
	rcSlider.bottom=rc.Height();//-2*::GetSystemMetrics(SM_CYDLGFRAME);

	m_scrollPad.SetWindowPos(&wndTop, rcSlider.left,
								rcSlider.top,
								rcSlider.Width(), 
								rcSlider.Height(), 
								SWP_NOMOVE);

	// redessiner (dessin custom dépendant de la taille)
	m_scrollPad.Invalidate();
	m_scrollPad.UpdateWindow();

	return rcSlider.right+::GetSystemMetrics(SM_CXEDGE);
}
	
// fonction appelée par la CSheetCutCalc
void CPageTCA::SetControlsPos()
{
	CRect rcClient;
	GetClientRect(rcClient);
	int cxMargin = RepositionScrollPad(rcClient);

	CRect rc;
	int cx=rcClient.Width()-cxMargin-::GetSystemMetrics(SM_CXEDGE);
	int cyClient=rcClient.Height();

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER;

	// combo dérivée de CComboEx : gère la hauteur dans CBN_DROPDOWN
	m_comboTool.GetWindowRect(rc);
	ScreenToClient(rc);
	m_comboTool.SetWindowPos(NULL, cxMargin, rc.top, cx, rc.Height(), uFlags);

	// combo dérivée de CComboEx : gère la hauteur dans CBN_DROPDOWN
	m_comboCat.GetWindowRect(rc);
	ScreenToClient(rc);
	m_comboCat.SetWindowPos(NULL, cxMargin, rc.top, cx, rc.Height(), uFlags);

	m_staticAlloy.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticAlloy.SetWindowPos(NULL, cxMargin, rc.top, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);

	// combo dérivée de CComboEx : gère la hauteur dans CBN_DROPDOWN
	int xRightStaticAlloy=rc.right;
	//m_staticAlloy.GetWindowRect(rcStaticAlloy);
	//ScreenToClient(rcStaticAlloy);
	
	m_comboAlloy.GetWindowRect(rc);
	ScreenToClient(rc);
	m_comboAlloy.SetWindowPos(NULL, xRightStaticAlloy+::GetSystemMetrics(SM_CXEDGE), 
					rc.top, rcClient.Width()-xRightStaticAlloy-2*::GetSystemMetrics(SM_CXEDGE), rc.Height(), uFlags);
}

void CPageTCA::OnSlider(int nTBCode, UINT nPos)
{
	CWnd* pwndFocus=GetFocus();
	int nID=pwndFocus->GetDlgCtrlID();

	switch(nID)
	{
	case CLASSES_IDC_COMBO_TOOL:
		{
			int nCount=m_comboTool.GetCount();
			int nCurSel=m_comboTool.GetCurSel();

			switch(nTBCode)
			{
			case SB_LINEUP:
				if(nCurSel>0)
				{
					int n=m_comboTool.SetCurSel(nCurSel-1);
					ASSERT(n==nCurSel-1);
					OnCbnSelChangeTool();
				}
				break;
			case SB_LINEDOWN:
				if(nCurSel<nCount-1)
				{
					int n=m_comboTool.SetCurSel(nCurSel+1);
					ASSERT(n==nCurSel+1);
					OnCbnSelChangeTool();
				}
				break;
			default:
				ASSERT(0);
				break;
			}
		}
		break;
	case CLASSES_IDC_COMBO_CAT:
		{
			int nCount=m_comboCat.GetCount();
			int nCurSel=m_comboCat.GetCurSel();

			switch(nTBCode)
			{
			case SB_LINEUP:
				if(nCurSel>0)
				{
					int n=m_comboCat.SetCurSel(nCurSel-1);
					ASSERT(n==nCurSel-1);
					OnCbnSelChangeCat();
				}
				break;
			case SB_LINEDOWN:
				if(nCurSel<nCount-1)
				{
					int n=m_comboCat.SetCurSel(nCurSel+1);
					ASSERT(n==nCurSel+1);
					OnCbnSelChangeCat();
				}
				break;
			default:
				ASSERT(0);
				break;
			}
		}
		break;
	case CLASSES_IDC_COMBO_ALLOY:
		{
			int nCount=m_comboAlloy.GetCount();
			int nCurSel=m_comboAlloy.GetCurSel();

			switch(nTBCode)
			{
			case SB_LINEUP:
				if(nCurSel>0)
				{
					int n=m_comboAlloy.SetCurSel(nCurSel-1);
					ASSERT(n==nCurSel-1);
					OnCbnSelChangeAlloy();
				}
				break;
			case SB_LINEDOWN:
				if(nCurSel<nCount-1)
				{
					int n=m_comboAlloy.SetCurSel(nCurSel+1);
					ASSERT(n==nCurSel+1);
					OnCbnSelChangeAlloy();
				}
				break;
			default:
				ASSERT(0);
				break;
			}
		}
		break;
	default:
		return;
	}
}

// lit les données et les place dans les controles, et appelle UpdateControlsStyles()
void CPageTCA::OnChangeTWPair()
{
	UpdateControlsStyles();
}

void CPageTCA::OnChangeEditMode()
{
	InitializeTCACombos();
	CPropPageEx::OnChangeEditMode();

}

void CPageTCA::UpdateControlsStyles()
{
	// fonction vide
	//CPropPageEx::UpdateControlsStyles();

	if(m_pData==NULL) // mode calculette
	{
		// pas de données : désactiver
		m_comboTool.ShowWindow(SW_HIDE);
		m_comboCat.ShowWindow(SW_HIDE);
		m_comboAlloy.ShowWindow(SW_HIDE);
		m_staticAlloy.ShowWindow(SW_HIDE);
		return;
	}

	m_comboTool.ShowWindow(SW_SHOW);
	m_comboCat.ShowWindow(SW_SHOW);
	m_comboAlloy.ShowWindow(SW_SHOW);
	m_staticAlloy.ShowWindow(SW_SHOW);

	if(m_pData->IsEmpty()) // aucun outil
	{
		// montrer les combos, mais les désactiver
		m_comboTool.EnableWindow(FALSE);
		m_comboCat.EnableWindow(FALSE);
		m_comboAlloy.EnableWindow(FALSE);
	}
	else
	{
		m_comboTool.EnableWindow(TRUE);
		m_comboCat.EnableWindow(TRUE);
		m_comboAlloy.EnableWindow(TRUE);
	}
}
