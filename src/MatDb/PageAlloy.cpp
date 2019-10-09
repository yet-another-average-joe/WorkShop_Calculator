// PageAlloy.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MatDb.h"
#include "DataMatDb.h"
#include "PageAlloy.h"

// pour débogage : pas de repositionnement des contrôles
// afin de vérifier les attirbuts visible, lecture seule, etc
// dans les mode édition et lecture seule
#undef NO_REPOSITION

// Boîte de dialogue CPageAlloy

IMPLEMENT_DYNAMIC(CPageAlloy, CPropPageEx)

CPageAlloy::CPageAlloy(CData* pData)
	: CPropPageEx(CPageAlloy::IDD, pData),
		m_listboxAlloy(	IDC_EDIT_ALLOY,
						CLASSES_IDC_BUTTON_NEW,
						CLASSES_IDC_BUTTON_DEL,
						CLASSES_IDC_BUTTON_UP,
						CLASSES_IDC_BUTTON_DOWN)
{
	m_pAlloyNew=NULL;
	m_comboCat.SetFullDrop(TRUE);
	m_fPosSaved=FALSE;
}

CPageAlloy::~CPageAlloy()
{
}

BOOL CPageAlloy::OnInitDialog()
{
	CPropPageEx::OnInitDialog();

	CSize size(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	m_btnNew.SetIconMulti(		CLASSES_IDI_ADD,	CLASSES_IDI_ADD_DISABLED, size);
	m_btnDel.SetIconMulti(		CLASSES_IDI_DEL,	CLASSES_IDI_DEL_DISABLED, size);
	m_btnUp.SetIconMulti(		CLASSES_IDI_UP,		CLASSES_IDI_UP_DISABLED, size);
	m_btnDown.SetIconMulti(		CLASSES_IDI_DOWN,	CLASSES_IDI_DOWN_DISABLED, size);

	// positionnement des boutons
	int cxBtnIcon=::GetSystemMetrics(SM_CXSMICON);
	int cxBtn=cxBtnIcon+cxBtnIcon/2; // boutons 50% plus grand que l'icone (24 pou 16, et 48 pour 32
	int x0=0;
	int y0=0;
	UINT nFlags=SWP_NOZORDER | SWP_NOACTIVATE;
	nFlags|=GetEditMode()?SWP_SHOWWINDOW:SWP_HIDEWINDOW;
	m_btnNew.SetWindowPos(NULL, x0, y0, cxBtn, cxBtn, nFlags);
	m_btnDel.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnUp.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);
	m_btnDown.SetWindowPos(NULL, x0, y0+=cxBtn, cxBtn, cxBtn, nFlags);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPageAlloy::UpdatePage()
{
	SetControlsPos();

	// remplir la Combo avec les données de la listbox

	CListCat* pListCat=((CDataMatDb*)m_pData)->Cat_GetList();
	ASSERT(pListCat!=NULL);
	m_comboCat.SetCatList(pListCat);

	if(m_comboCat.GetCount()>0)
		m_comboCat.SetCurSel(0);

	if(m_comboCat.GetCount()<=0)
	{
		m_listboxAlloy.SetNamedObList(NULL); // désactive les boutons
		m_editAlloy.SetWindowText_NoNotify(_T(""));
		m_btnNew.EnableWindow(FALSE);
	}
	else
	{
		m_comboCat.SetCurSel(0);
		m_btnNew.EnableWindow(TRUE);
		CCat* pCat=Data_Cat_GetCurSel();
		Cat_SetCurSel(pCat);

		CListAlloy* pListAlloy=pCat->Alloy_GetList();
		m_listboxAlloy.SetNamedObList(pListAlloy);
		CAlloy* pAlloy=Data_Alloy_GetCurSel();
		Alloy_SetCurSel(pAlloy);
		m_comboCat.SetFocus();
	}

	CPropPageEx::UpdatePage();
}

void CPageAlloy::UpdateControlsStyles()
{
	if(GetEditMode())
	{
		m_btnNew.ShowWindow(SW_SHOW);
		m_btnDel.ShowWindow(SW_SHOW);
		m_btnUp.ShowWindow(SW_SHOW);
		m_btnDown.ShowWindow(SW_SHOW);
//		m_editAlloy.SetReadOnly(FALSE);
		m_editAlloy.ShowWindow(SW_SHOW);
		m_listboxAlloy.EnableDragAndDrop(TRUE);
	}
	else
	{
		m_btnNew.ShowWindow(SW_HIDE);
		m_btnDel.ShowWindow(SW_HIDE);
		m_btnUp.ShowWindow(SW_HIDE);
		m_btnDown.ShowWindow(SW_HIDE);
		m_listboxAlloy.EnableDragAndDrop(FALSE);
//		m_editAlloy.SetReadOnly(TRUE);
		m_editAlloy.ShowWindow(SW_HIDE);
	}
	
	if(m_pData->IsEmpty())
		m_comboCat.EnableWindow(FALSE);
	else
		m_comboCat.EnableWindow(TRUE);

	if(m_comboCat.GetCount()<=0)
		m_btnNew.EnableWindow(FALSE);
	else
		m_btnNew.EnableWindow(TRUE);
}

void CPageAlloy::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CAT, m_comboCat);
	DDX_Control(pDX, IDC_LIST_ALLOY, m_listboxAlloy);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_DEL, m_btnDel);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_UP, m_btnUp);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_EDIT_ALLOY, m_editAlloy);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_NEW, m_btnNew);
}

BEGIN_MESSAGE_MAP(CPageAlloy, CPropPageEx)
	ON_CBN_SELCHANGE(IDC_COMBO_CAT, &CPageAlloy::OnCbnSelchangeComboCat)
	ON_EN_CHANGE(IDC_EDIT_ALLOY, &CPageAlloy::OnEnChangeEditAlloy)
	ON_LBN_SELCHANGE(IDC_LIST_ALLOY, &CPageAlloy::OnLbnSelchangeListAlloy)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_DEL, &CPageAlloy::OnBnClickedButtonDel)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_UP, &CPageAlloy::OnBnClickedButtonUp)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_DOWN, &CPageAlloy::OnBnClickedButtonDown)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_NEW, &CPageAlloy::OnBnClickedButtonNew)
	// message envoyé par la listbox quadn réorganisée par drag and drop
	ON_MESSAGE(WMU_LBUPDOWN_DRAGGED, OnDragAndDrop)
END_MESSAGE_MAP()

static int s_nIdNewAlloy=1;

void CPageAlloy::OnBnClickedButtonNew()
{
	// créer une nouvelle nuance
	CCat* pCat=Data_Cat_GetCurSel();
	ASSERT_VALID(pCat);
	CString str;
	TRACE(_T("CPageAlloy::OnBnClickedButtonNew() - chaine à placer en resource\n"));
	str.Format(_T("<nouvelle nuance %d-%d>"), pCat->m_nID, s_nIdNewAlloy);
	CAlloy* pAlloyNew = new CAlloy();
	ASSERT_VALID(pCat);
	pAlloyNew->m_strName=str;	
	pAlloyNew->m_pCat=pCat;
	m_editAlloy.SetWindowText_NoNotify(str);

	CAlloy* pAlloy = (CAlloy*)m_listboxAlloy.OnBnClickedAdd(pAlloyNew);
	ASSERT(pAlloy==pAlloyNew);
	s_nIdNewAlloy++;

	// focus sur l'edit et sélection du texte
//	m_editAlloy.SetReadOnly(FALSE);
//	m_editAlloy.SetFocus();
//	m_editAlloy.SetSel(0, -1);

	// le document est modifié
	Data_SetModifiedFlag(TRUE);
	Data_Alloy_SetCurSel(pAlloy);
}


void CPageAlloy::OnBnClickedButtonDel()
{
	m_listboxAlloy.OnBnClickedDel();

	int nCurSel=m_listboxAlloy.GetCurSel();
	CAlloy* pAlloy=NULL;

	if(nCurSel!=LB_ERR)
		pAlloy = (CAlloy*)m_listboxAlloy.Listbox_Get(nCurSel);
//	else
//		m_editAlloy.SetReadOnly(TRUE); // vide

	// le document est modifié
	Data_SetModifiedFlag(TRUE);
	Data_Alloy_SetCurSel(pAlloy);
}

void CPageAlloy::OnBnClickedButtonUp()
{
	m_listboxAlloy.OnBnClickedUp();
	m_pData->SetModifiedFlag(TRUE);
}

void CPageAlloy::OnBnClickedButtonDown()
{
	m_listboxAlloy.OnBnClickedDown();
	m_pData->SetModifiedFlag(TRUE);
}

void CPageAlloy::OnCbnSelchangeComboCat()
{
	CCat* pCat=Combo_Cat_GetCurSel();

	if(pCat==NULL)
	{
		m_editAlloy.SetWindowText_NoNotify(_T(""));
	}
	else
	{
		CListAlloy* pListAlloy = pCat->Alloy_GetList();
		m_listboxAlloy.SetNamedObList(pListAlloy);
	}

	// la base n'est pas modifiée
	Data_Cat_SetCurSel(pCat);
	Data_Alloy_SetCurSel(pCat->Alloy_GetHead());

	if(m_listboxAlloy.GetCount()>0)
		m_listboxAlloy.EnableWindow(TRUE);
	else
		m_listboxAlloy.EnableWindow(FALSE);
}

void CPageAlloy::OnEnChangeEditAlloy()
{
	// ne prendre en compte que si mode édition
	if(GetEditMode())
	{
		// récupérer le texte de l'edit
		CString str;
		GetDlgItemText(IDC_EDIT_ALLOY, str);
		CAlloy* pAlloy=Data_Alloy_GetCurSel();
		ASSERT_VALID(pAlloy);

		if(pAlloy->m_strName==str)
			return;
		
		// modifier le texte dans la listbox
		int nCurSel=m_listboxAlloy.GetCurSel();
		
		if(nCurSel==LB_ERR)
		{
			//ASSERT(0);
			return;
		}
		
		pAlloy=(CAlloy*)m_listboxAlloy.GetItemDataPtr(nCurSel);
		ASSERT_VALID(pAlloy);
		pAlloy->m_strName=str;
		m_listboxAlloy.DeleteString(nCurSel);
		m_listboxAlloy.InsertString(nCurSel, str);
		m_listboxAlloy.SetItemDataPtr(nCurSel, pAlloy);
		m_listboxAlloy.SetCurSel(nCurSel);

		Data_SetModifiedFlag(TRUE);
	}
}

void CPageAlloy::OnLbnSelchangeListAlloy()
{
	m_listboxAlloy.OnLbnSelchange();
	CAlloy* pAlloy=Listbox_Alloy_GetCurSel();
	Data_Alloy_SetCurSel(pAlloy);

//	if(pAlloy==NULL) // liste vide
//	{
//		m_editAlloy.SetReadOnly(TRUE);
//	}
//	else
//	{
//		ASSERT_VALID(pAlloy);
//		m_editAlloy.SetReadOnly(FALSE);
//	}

}

void CPageAlloy::SetControlsPos()
{
#ifdef NO_REPOSITION
	return;
#endif

	// sauvegarder la position de la listbox définie par la resource
	if(!m_fPosSaved)
	{
		CRect rc;
		m_listboxAlloy.GetWindowRect(rc);
		ScreenToClient(rc);
		m_yListbox=rc.top;
		m_fPosSaved=TRUE;
	}

	int cxBtnIcon=::GetSystemMetrics(SM_CXSMICON);
	int cxBtn=cxBtnIcon+cxBtnIcon/2; // boutons 50% plus grand que l'icone (24 pou 16, et 48 pour 32
	CRect rc;
	GetClientRect(rc);
	int cxClient=rc.Width();
	int cyClient=rc.Height();

	int cxMargin=::GetSystemMetrics(SM_CXEDGE);
	int cyMargin=::GetSystemMetrics(SM_CYEDGE);

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER/*|SWP_NOREDRAW*/;

	if(!GetEditMode()) // si lecture seule
	{
		// dans ce cas la listbox occupe toute la largeur
		// et elle recouvre l'edit
		int cxMax = cxClient-2*cxMargin;

		m_comboCat.GetWindowRect(rc);
		ScreenToClient(rc);
		m_comboCat.SetWindowPos(NULL, cxMargin, rc.top, cxMax, rc.Height(), uFlags);

		m_editAlloy.GetWindowRect(rc);
		ScreenToClient(rc);
		int yEdit=rc.top;

		m_listboxAlloy.GetWindowRect(rc);
		ScreenToClient(rc);
		m_listboxAlloy.SetWindowPos(NULL, cxMargin, yEdit, cxMax, cyClient-yEdit-cyMargin, uFlags);
	}
	else
	{
		m_comboCat.GetWindowRect(rc);
		ScreenToClient(rc);
		m_comboCat.SetWindowPos(NULL, cxBtn, rc.top, cxClient-cxBtn-cxMargin,rc.Height(), uFlags);

		m_editAlloy.GetWindowRect(rc);
		ScreenToClient(rc);
		m_editAlloy.SetWindowPos(NULL, cxBtn, rc.top, 
							cxClient-cxBtn-cxMargin, rc.Height(), uFlags);

		m_listboxAlloy.GetWindowRect(rc);
		ScreenToClient(rc);
		m_listboxAlloy.SetWindowPos(NULL, cxBtn, m_yListbox, cxClient-cxBtn-cxMargin, cyClient-m_yListbox-cyMargin, uFlags);
	}
}

BOOL CPageAlloy::CanChangePage()
{
	return TRUE;
}

int CPageAlloy::Cat_SetCurSel(CCat* pCat)
{
	int nCount=m_comboCat.GetCount();
	int n=0;
	while(n<nCount)
	{
		if(pCat==(CCat*)m_comboCat.GetItemDataPtr(n))
			return m_comboCat.SetCurSel(n);
		n++;
	}

	return CB_ERR;
}

int CPageAlloy::Alloy_SetCurSel(CAlloy* pAlloy)
{
	if(pAlloy==NULL)
	{
		m_listboxAlloy.SetCurSel(-1);
		m_editAlloy.SetWindowText_NoNotify(_T(""));
		return CB_ERR;
	}

	int nCount=m_listboxAlloy.GetCount();
	int n=0;
	while(n<nCount)
	{
		if(pAlloy==(CAlloy*)m_listboxAlloy.GetItemDataPtr(n))
		{
			ASSERT_VALID(pAlloy);
			m_editAlloy.SetWindowText_NoNotify(pAlloy->m_strName);
			return m_listboxAlloy.SetCurSel(n);
		}
		n++;
	}

	return CB_ERR;
}

CAlloy* CPageAlloy::Listbox_Alloy_GetCurSel() // renvoie la nuance sélectionnée, ou NULL
{
	int nCurSel=m_listboxAlloy.GetCurSel();
	if(nCurSel>-1)
		return (CAlloy*)m_listboxAlloy.GetItemDataPtr(nCurSel);
	else
		return NULL;
}

CCat* CPageAlloy::Combo_Cat_GetCurSel() // renvoie la catégorie sélectionnée, ou NULL
{
	int nCurSel=m_comboCat.GetCurSel();
	if(nCurSel>-1)
		return (CCat*)m_comboCat.GetItemDataPtr(nCurSel);
	else
		return NULL;
}

LRESULT CPageAlloy::OnDragAndDrop(WPARAM, LPARAM)
{
	Data_SetModifiedFlag(TRUE);
	return 0;
}



