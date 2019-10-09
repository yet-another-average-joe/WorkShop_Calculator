// PageCat.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MatDb.h"
#include "PageCat.h"
#include "SheetMatDb.h"

// pour débogage : pas de repositionnement des contrôles
// afin de vérifier les attirbuts visible, lecture seule, etc
// dans les mode édition et lecture seule
#undef NO_REPOSITION

// Boîte de dialogue CPageCat

IMPLEMENT_DYNAMIC(CPageCat, CPropPageEx)

CPageCat::CPageCat(CData* pData)
	: CPropPageEx(CPageCat::IDD, pData),
		m_listboxCat(	IDC_EDIT_CAT,
						CLASSES_IDC_BUTTON_NEW,
						CLASSES_IDC_BUTTON_DEL,
						CLASSES_IDC_BUTTON_UP,
						CLASSES_IDC_BUTTON_DOWN)
{
	m_pCatNew=NULL;
	m_fPosSaved=FALSE;
}

CPageCat::~CPageCat()
{
}

BOOL CPageCat::OnInitDialog()
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

void CPageCat::UpdatePage()
{
	// forcer le repositionnement des contrôles en mode edition
	SetControlsPos();

	CNamedObList* pList=Data_Cat_GetList();
	m_listboxCat.SetNamedObList(pList);
	CCat* pCat=Data_Cat_GetCurSel();
	SetCurSel(pCat);
	SetDlgItemInt(IDC_EDIT_ID, Data_GetNextID());

	CPropPageEx::UpdatePage();
}

void CPageCat::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CAT, m_listboxCat);
	DDX_Control(pDX, IDC_EDIT_CAT, m_editCat);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_DEL, m_btnDel);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_UP, m_btnUp);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_DOWN, m_btnDown);
	DDX_Control(pDX, CLASSES_IDC_BUTTON_NEW, m_btnNew);
	DDX_Control(pDX, IDC_EDIT_ID, m_editId);
	DDX_Control(pDX, IDC_STATIC_ID, m_staticId);
}

BEGIN_MESSAGE_MAP(CPageCat, CPropPageEx)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_DEL, &CPageCat::OnBnClickedButtonDel)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_UP, &CPageCat::OnBnClickedButtonUp)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_DOWN, &CPageCat::OnBnClickedButtonDown)
	ON_EN_CHANGE(IDC_EDIT_CAT, &CPageCat::OnEnChangeEditName)
	ON_LBN_SELCHANGE(IDC_LIST_CAT, &CPageCat::OnLbnSelchangeListCat)
	ON_BN_CLICKED(CLASSES_IDC_BUTTON_NEW, &CPageCat::OnBnClickedButtonNew)
	// message envoyé par la listbox quadn réorganisée par drag and drop
	ON_MESSAGE(WMU_LBUPDOWN_DRAGGED, OnDragAndDrop)
END_MESSAGE_MAP()

void CPageCat::OnBnClickedButtonNew()
{
	// créer une nouvelle catégorie
	CString str;
	str.Format(_T("<nouvelle catégorie %d>"), Data_GetNextID());
	CCat* pCatNew = new CCat();
	pCatNew->m_strName=str;
	pCatNew->m_nID=Data_GetNextID();
	m_editCat.SetWindowText_NoNotify(str);

	// CListboxUpDown3::.OnBnClickedAdd() se charge d'ajouter le nouvel élmément à la liste
	CCat* pCat = (CCat*)m_listboxCat.OnBnClickedAdd(pCatNew);
	ASSERT(pCat==pCatNew);
	SetDlgItemInt(IDC_EDIT_ID, pCat->m_nID);

	// focus sur l'edit et sélection du texte
//	m_editCat.SetReadOnly(FALSE);
//	m_editCat.SetSel(0, -1);
//	m_editCat.SetFocus();

	Data_IncNextID();

	// le document est modifié
	Data_SetModifiedFlag(TRUE);
	Data_Cat_SetCurSel(pCat);
}

void CPageCat::OnBnClickedButtonDel()
{
	m_listboxCat.OnBnClickedDel();

	int nCurSel=m_listboxCat.GetCurSel();
	CCat* pCat=NULL;

	if(nCurSel!=LB_ERR)
		pCat = (CCat*)m_listboxCat.Listbox_Get(nCurSel);
	//else
	//	m_editCat.SetReadOnly(TRUE); // vide

	// le document est modifié
	Data_SetModifiedFlag(TRUE);
	Data_Cat_SetCurSel(pCat);

	OnLbnSelchangeListCat();
}

void CPageCat::OnBnClickedButtonUp()
{
	m_listboxCat.OnBnClickedUp();
	Data_SetModifiedFlag(TRUE);
}

void CPageCat::OnBnClickedButtonDown()
{
	m_listboxCat.OnBnClickedDown();
	Data_SetModifiedFlag(TRUE);
}

void CPageCat::OnEnChangeEditName()
{
	// ne prendre en compte que si mode édition
	if(GetEditMode())
	{
		// récupérer le texte de l'edit
		CString str;
		GetDlgItemText(IDC_EDIT_CAT, str);
		CCat* pCat=Data_Cat_GetCurSel();
		ASSERT_VALID(pCat);

		if(pCat->m_strName==str)
			return;
		
		// modifier le texte dans la listbox
		int nCurSel=m_listboxCat.GetCurSel();
		
		if(nCurSel==LB_ERR)
		{
			//ASSERT(0);
			return;
		}
		
		pCat=(CCat*)m_listboxCat.GetItemDataPtr(nCurSel);
		ASSERT_VALID(pCat);
		pCat->m_strName=str;
		m_listboxCat.DeleteString(nCurSel);
		m_listboxCat.InsertString(nCurSel, str);
		m_listboxCat.SetItemDataPtr(nCurSel, pCat);
		m_listboxCat.SetCurSel(nCurSel);

		Data_SetModifiedFlag(TRUE);
	}
}

void CPageCat::OnLbnSelchangeListCat()
{
	m_listboxCat.OnLbnSelchange();
	CCat* pCat=Listbox_Cat_GetCurSel();
	Data_Cat_SetCurSel(pCat);

	if(pCat==NULL) // fichier vide
	{
		//m_editCat.SetReadOnly(TRUE);
		m_editId.SetWindowText_NoNotify(_T(""));
	}
	else
	{
		ASSERT_VALID(pCat);
		//m_editCat.SetReadOnly(FALSE);
		SetDlgItemInt(IDC_EDIT_ID, pCat->m_nID);
	}
}

void CPageCat::SetControlsPos()
{
#ifdef NO_REPOSITION
	return;
#endif
	// sauvegarder la position de la listbox définie par la resource
	if(!m_fPosSaved)
	{
		CRect rc;
		m_listboxCat.GetWindowRect(rc);
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

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER;

	if(!GetEditMode()) // mode lecture seule
	{
		// dans ce cas la listbox occupe toute la largeur
		// et elle recouvre l'edit
		int cxMax = cxClient-2*cxMargin;

		m_editCat.GetWindowRect(rc);
		ScreenToClient(rc);
		m_editCat.SetWindowPos(NULL, cxMargin, rc.top, cxMax,rc.Height(), uFlags);

		int yEdit=rc.top;

		m_listboxCat.GetWindowRect(rc);
		ScreenToClient(rc);
		m_listboxCat.SetWindowPos(NULL, cxMargin, yEdit, cxMax, cyClient-yEdit-cyMargin, uFlags);
	}
	else
	{
		m_editCat.GetWindowRect(rc);
		ScreenToClient(rc);
		m_editCat.SetWindowPos(NULL, cxBtn, rc.top, cxClient-cxBtn-cxMargin,rc.Height(), uFlags);

		// mettre la listbox dans la position définie dans la resource
		m_listboxCat.GetWindowRect(rc);
		ScreenToClient(rc);
		m_listboxCat.SetWindowPos(NULL, cxBtn, m_yListbox, cxClient-cxBtn-cxMargin, cyClient-m_yListbox-cyMargin, uFlags);
	}
}

BOOL CPageCat::CanChangePage()
{
	return TRUE;
}

int CPageCat::SetCurSel(CCat* pCat)
{
	int nCount=m_listboxCat.GetCount();
	int n=0;
	while(n<nCount)
	{
		if(pCat==(CCat*)m_listboxCat.GetItemDataPtr(n))
		{
			ASSERT_VALID(pCat);
			m_editCat.SetWindowText_NoNotify(pCat->m_strName);
			SetDlgItemInt(IDC_EDIT_ID, pCat->m_nID);
			return m_listboxCat.SetCurSel(n);
		}
		n++;
	}

	return CB_ERR;
}

CCat* CPageCat::Listbox_Cat_GetCurSel()
{
	int nCurSel=m_listboxCat.GetCurSel();
	if(nCurSel==LB_ERR)
		return NULL;
	else
		return (CCat*)m_listboxCat.Listbox_Get(nCurSel);
}

LRESULT CPageCat::OnDragAndDrop(WPARAM, LPARAM)
{
	Data_SetModifiedFlag(TRUE);
	return 0;
}

void CPageCat::UpdateControlsStyles()
{
	if(GetEditMode())
	{
		m_btnNew.ShowWindow(SW_SHOW);
		m_btnDel.ShowWindow(SW_SHOW);
		m_btnUp.ShowWindow(SW_SHOW);
		m_btnDown.ShowWindow(SW_SHOW);
		m_listboxCat.EnableDragAndDrop(TRUE);
		m_editCat.ShowWindow(SW_SHOW);
		m_staticId.ShowWindow(SW_SHOW);
		m_editId.ShowWindow(SW_SHOW);
	}
	else
	{
		m_btnNew.ShowWindow(SW_HIDE);
		m_btnDel.ShowWindow(SW_HIDE);
		m_btnUp.ShowWindow(SW_HIDE);
		m_btnDown.ShowWindow(SW_HIDE);
		m_listboxCat.EnableDragAndDrop(FALSE);
		m_editCat.ShowWindow(SW_HIDE);
		m_staticId.ShowWindow(SW_HIDE);
		m_editId.ShowWindow(SW_HIDE);
	}
}

