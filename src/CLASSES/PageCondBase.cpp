// PageCondTurning.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "CLASSES_rc.h"
#include "PageCondBase.h"

#define VC_INC	1 // Vc = entier

// les champs vides sont cachés ou simplement désacivés

// Boîte de dialogue CPageCondBase

// A FAIRE :
// mmm
//
// conditions pour les boutons :
// del : il faut des données : m_pData ! =NULL
// copy : idem
// paste : clipboard !=NULL
// mettre à jour dans OnChangeTWPair()

IMPLEMENT_DYNAMIC(CPageCondBase, CPageTCA)

CPageCondBase::CPageCondBase(UINT nIDTemplate, CData* pData)
	: CPageTCA(nIDTemplate, pData)
{
	EnableScrollbars(FALSE);
	m_pClipboard=NULL;
	// pour texte noir sur edit désactivé
	m_editVcmin.m_bNoGray=TRUE;
	m_editVcmax.m_bNoGray=TRUE;
}

CPageCondBase::~CPageCondBase()
{
}

void CPageCondBase::DoDataExchange(CDataExchange* pDX)
{
	CPageTCA::DoDataExchange(pDX);

	DDX_Control(pDX, CLASSES_IDC_STATIC_A0, m_staticA0);
	DDX_Control(pDX, CLASSES_IDC_EDIT_VCMIN, m_editVcmin);
	DDX_Control(pDX, CLASSES_IDC_EDIT_VCMAX, m_editVcmax);
	DDX_Control(pDX, CLASSES_IDC_STATIC_VC, m_staticVc);
//	DDX_Control(pDX, CLASSES_IDC_BUTTON_DEL, m_btnDel);
//	DDX_Control(pDX, CLASSES_IDC_BUTTON_COPY, m_btnCopy);
//	DDX_Control(pDX, CLASSES_IDC_BUTTON_PASTE, m_btnPaste);
}

BEGIN_MESSAGE_MAP(CPageCondBase, CPageTCA)
//	ON_BN_CLICKED(CLASSES_IDC_BUTTON_DEL, &CPageCondBase::OnBnClickedDel)
//	ON_BN_CLICKED(CLASSES_IDC_BUTTON_COPY, &CPageCondBase::OnBnClickedCopy)
//	ON_BN_CLICKED(CLASSES_IDC_BUTTON_PASTE, &CPageCondBase::OnBnClickedPaste)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_VCMIN, &CPageCondBase::OnEnChangeVcmin)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_VCMAX, &CPageCondBase::OnEnChangeVcmax)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CPageCondBase::OnEnChangeVcmin()
{
	// mises à jour sans notification
	// donc pas d'appel possible en mode lecture
	ASSERT(GetEditMode()); 

	int nValue=ReadVcmin();
	int newValue=GetVcmin();
	if(newValue!=nValue)
	{
		if(!WriteVcmin(newValue))
			return;
		m_pData->SetModifiedFlag(TRUE);
		InitializeTCACombos(); // mise à jour du statut "paramétré" dans les combos
	}
}

void CPageCondBase::OnEnChangeVcmax()
{
	// mises à jour sans notification
	// donc pas d'appel possible en mode lecture
	ASSERT(GetEditMode()); 

	int nValue=ReadVcmax();
	int newValue=GetVcmax();
	if(newValue!=nValue)
	{
		if(!WriteVcmax(newValue))
			return;
		m_pData->SetModifiedFlag(TRUE);
		InitializeTCACombos(); // mise à jour du statut "paramétré" dans les combos
	}
}

// ne fait que mettre à zéro les conditions de coupe
//void CPageCondBase::OnBnClickedDel()
//{
//	Clear(); 
//
//	CCut* pCut=Data_Cut_GetCurSel();
//	ASSERT(pCut!=NULL);
//	pCut->Clear();
//
//	FillComboCat();
//	CCat* pCat=Data_Cat_GetCurSel();
//	Combo_Cat_SetCurSel(pCat);
//	FillComboAlloy();
//	CAlloy* pAlloy=Data_Alloy_GetCurSel();
//	Combo_Alloy_SetCurSel(pAlloy);
//	m_pData->SetModifiedFlag(TRUE);
//
////	if(!m_fNoHintCondChanged)
//		UpdateAllOtherPages(HINT_COND_CHANGED);
//}

// copie les conditions de coupe
//void CPageCondBase::OnBnClickedCopy()
//{
//	if(m_pData!=NULL)
//	{
//		if(m_pClipboard!=NULL)
//			delete m_pClipboard;
//		CCut* pCut=Data_Cut_GetCurSel();
//		if(pCut!=NULL)
//		{
//			m_pClipboard=new CCut(*pCut);
//			m_btnPaste.EnableWindow(TRUE);
//		}
//	}
//}

// remplace les conditions de coupe affichées 
// par celles contenues dans le presse papiers
//void CPageCondBase::OnBnClickedPaste()
//{
//	if(m_pData!=NULL)
//	{
//		ASSERT(m_pClipboard!=NULL);
//		CCut* pCut=Data_Cut_GetCurSel();
//		if(pCut!=NULL)
//		{
//			*pCut=*m_pClipboard;
//			SetVcmin(pCut->nVcmin);
//			SetVcmax(pCut->nVcmax);
//			m_pData->SetModifiedFlag(TRUE);
//			InitializeTCACombos(); // mise à jour du statut "paramétré" dans les combos
//			UpdateAllOtherPages(HINT_COND_CHANGED);
//		}
//	}
//}

void CPageCondBase::Clear()
{
	m_fNoHintCondChanged=TRUE;

	ClearVcmin();
	ClearVcmax();

	m_fNoHintCondChanged=FALSE;
}

BOOL CPageCondBase::OnInitDialog()
{
	CPageTCA::OnInitDialog();

	// Créer les boutons et les cacher
	//CSize size(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	//m_btnDel.SetIconMulti(CLASSES_IDI_DEL, CLASSES_IDI_DEL_DISABLED, size);
	//m_btnCopy.SetIconMulti(CLASSES_IDI_COPY, CLASSES_IDI_COPY_DISABLED, size);
	//m_btnPaste.SetIconMulti(CLASSES_IDI_PASTE, CLASSES_IDI_PASTE_DISABLED, size);

	// pour les controles supplémentaires
	//OnChangeTWPair();

	//m_comboTool.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
}

// en mode lecture, afficher Vcmin, et éventuellement à et Vcmax 
// en mode édition, afficher tout
void CPageCondBase::OnChangeTWPair()
{
	m_fNoHintCondChanged=TRUE;
	int Vcmin=ReadVcmin();
	int Vcmax=ReadVcmax();
	SetVcmin(Vcmin);
	SetVcmax(Vcmax);
	m_fNoHintCondChanged=FALSE;

	// appeler à la fin pour validité des données 
	// lors de l'appel à UpdateControlsStyles();
	CPageTCA::OnChangeTWPair();
}

void CPageCondBase::UpdateControlsStyles()
{
	CPageTCA::UpdateControlsStyles();
	BOOL bEditMode=GetEditMode();

	if(bEditMode)
	{
		CCut* pCut=Data_Cut_GetCurSel();
		if(pCut!=NULL)
		{
			m_editVcmin.EnableWindow(TRUE);
			m_editVcmin.SetReadOnly(FALSE);
			m_editVcmin.ShowWindow(SW_SHOW);

			m_staticA0.ShowWindow(SW_SHOW);

			m_editVcmax.EnableWindow(TRUE);
			m_editVcmax.SetReadOnly(FALSE);
			m_editVcmax.ShowWindow(SW_SHOW);
		}
	}
	else
	{
		// afficher 'à' et  Vcmax seulement si non nul ou != Vcmin
		// cacher les boutons
		//m_btnDel.ShowWindow(SW_HIDE);
		//m_btnCopy.ShowWindow(SW_HIDE);
		//m_btnPaste.ShowWindow(SW_HIDE);

		m_editVcmin.EnableWindow(FALSE);
		m_editVcmin.SetReadOnly(TRUE);

		m_editVcmax.EnableWindow(FALSE);
		m_editVcmax.SetReadOnly(TRUE);

		int Vcmin=ReadVcmin();
		int Vcmax=ReadVcmax();

		if(Vcmin>0)
			m_editVcmin.ShowWindow(SW_SHOW);

		if(Vcmax==0 || Vcmin==Vcmax)
		{
			m_staticA0.ShowWindow(SW_HIDE);
			m_editVcmax.ShowWindow(SW_HIDE);
		}
		else
		{
			m_staticA0.ShowWindow(SW_SHOW);
			m_editVcmax.ShowWindow(SW_SHOW);
		}
	}
}

void CPageCondBase::OnDestroy()
{
	CPageTCA::OnDestroy();

	if(m_pClipboard!=NULL)
		delete m_pClipboard;
}

// effet "cliquet" entre Vcmin et Vcmax
void CPageCondBase::OnSlider(int nTBCode, UINT nPos)
{
	CPageTCA::OnSlider(nTBCode, nPos);

	if(!GetEditMode())
		return;

	int nVcmin=GetVcmin();
	int nVcmax=GetVcmax();

	CWnd* pwndFocus=GetFocus();
	int nID=pwndFocus->GetDlgCtrlID();

	switch(nID)
	{
	case CLASSES_IDC_EDIT_VCMIN:
		{
			switch(nTBCode)
			{
			case SB_LINEUP:
				nVcmin+=VC_INC;
				SetVcmin(nVcmin);
				OnEnChangeVcmin();
				if(nVcmin>nVcmax)
				{
					nVcmax=nVcmin;
					SetVcmax(nVcmax);
					OnEnChangeVcmax();
				}
				break;
			case SB_LINEDOWN:
				if(nVcmin>VC_INC)
				{
					SetVcmin(nVcmin-VC_INC);
					OnEnChangeVcmin();
				}
				break;
			default:
				ASSERT(0);
				break;
			}
		}
		break;

	case CLASSES_IDC_EDIT_VCMAX:
		{
			switch(nTBCode)
			{
			case SB_LINEUP:
				SetVcmax(nVcmax+1);
				OnEnChangeVcmax();
				break;
			case SB_LINEDOWN:
				if(nVcmax>1)
					nVcmax-=1;
				SetVcmax(nVcmax);
				OnEnChangeVcmax();
				if(nVcmax<nVcmin)
				{
					nVcmin=nVcmax;
					SetVcmin(nVcmin);
					OnEnChangeVcmin();
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

void CPageCondBase::SetControlsPos()
{
	CPageTCA::SetControlsPos();

	//if( !::IsWindow(m_btnDel.GetSafeHwnd()) ||
	//	!::IsWindow(m_btnCopy.GetSafeHwnd()) ||
	//	!::IsWindow(m_btnPaste.GetSafeHwnd()) ||
	//	!::IsWindow(m_scrollPad.GetSafeHwnd()) )
	//	return;
	
	if(!::IsWindow(m_scrollPad.GetSafeHwnd()))
		return; // fenêtre pas encore créées

	// largeur du scrollpad :
	CRect rcScrollPad;
	m_scrollPad.GetWindowRect(rcScrollPad);
	int cxScrollPad=rcScrollPad.Width();
	int cxMargin = cxScrollPad+2*::GetSystemMetrics(SM_CXEDGE);

	//UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER;

	//CRect rc;
	//m_btnDel.GetWindowRect(rc);
	//ScreenToClient(rc);
	//m_btnDel.SetWindowPos(NULL, cxMargin, rc.top, rc.Width(), rc.Height(), uFlags);

	//m_btnCopy.GetWindowRect(rc);
	//ScreenToClient(rc);
	//m_btnCopy.SetWindowPos(NULL, cxMargin, rc.top, rc.Width(), rc.Height(), uFlags);
	//
	//m_btnPaste.GetWindowRect(rc);
	//ScreenToClient(rc);
	//m_btnPaste.SetWindowPos(NULL, cxMargin, rc.top, rc.Width(), rc.Height(), uFlags);
}

