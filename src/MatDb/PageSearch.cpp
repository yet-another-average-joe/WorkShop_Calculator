// PageSearch.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MatDb.h"
#include "PageSearch.h"
#include "DataMatDb.h"

// Boîte de dialogue CPageSearch

IMPLEMENT_DYNAMIC(CPageSearch, CPropPageEx)

CPageSearch::CPageSearch(CData* pData)
	: CPropPageEx(CPageSearch::IDD, pData)
{
	EnableScrollbars(FALSE); // pas de scrolling sur cette page
}

CPageSearch::~CPageSearch()
{
}

void CPageSearch::UpdatePage()
{
	// vider l'EDIT
	m_editCat.SetWindowText_NoNotify(_T(""));
	// vider la LISTBOX
	m_listboxAlloy.ResetContent();

	POSITION posCat = Data_Cat_GetHeadPosition();

	while(posCat)
	{
		CCat* pCat = Data_Cat_GetNext(posCat);
		POSITION posAlloy = pCat->Alloy_GetHeadPosition();

		while(posAlloy)
		{
			CAlloy* pAlloy = pCat->Alloy_GetNext(posAlloy);
			int nItem=m_listboxAlloy.AddString(pAlloy->m_strName);
			m_listboxAlloy.SetItemDataPtr(nItem, pAlloy);
		}
	}

	CAlloy* pAlloy=Data_Alloy_GetCurSel();
	if(pAlloy!=NULL)
	{
		Combo_Alloy_SetCurSel(pAlloy);
		m_editCat.SetWindowText_NoNotify(pAlloy->m_pCat->m_strName);
	}

	CPropPageEx::UpdatePage();
}

void CPageSearch::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CAT, m_editCat);
	DDX_Control(pDX, IDC_LIST_ALLOY, m_listboxAlloy);
	DDX_Control(pDX, IDC_STATIC_CAT, m_staticCat);
	DDX_Control(pDX, IDC_STATIC_ALLOY, m_staticAlloy);
}

BEGIN_MESSAGE_MAP(CPageSearch, CPropPageEx)
	ON_LBN_SELCHANGE(IDC_LIST_ALLOY, &CPageSearch::OnLbnSelchangeListAlloy)
END_MESSAGE_MAP()

// Gestionnaires de messages de CPageSearch

void CPageSearch::OnLbnSelchangeListAlloy()
{
	int nSel = m_listboxAlloy.GetCurSel();
	CAlloy* pAlloy=(CAlloy*)m_listboxAlloy.GetItemDataPtr(nSel);

	// cas où la liste est vide
	if((int)pAlloy==-1)
		return;

	m_editCat.SetWindowText_NoNotify(pAlloy->m_pCat->m_strName);

	// mettre à jour la catégorie sur la page Catégories et la page Normes
	Data_Cat_SetCurSel(pAlloy->m_pCat);
	Data_Alloy_SetCurSel(pAlloy);
}

void CPageSearch::SetControlsPos()
{
	int cxBtnIcon=::GetSystemMetrics(SM_CXSMICON);
	int cxBtn=cxBtnIcon+cxBtnIcon/2; // boutons 50% plus grand que l'icone (24 pou 16, et 48 pour 32
	CRect rc;
	GetClientRect(rc);
	int cxClient=rc.Width();
	int cyClient=rc.Height();

	int cxMargin=::GetSystemMetrics(SM_CXEDGE);
	int cyMargin=::GetSystemMetrics(SM_CYEDGE);
	int cxMax = cxClient-2*cxMargin;

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOREDRAW;

	m_staticCat.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticCat.SetWindowPos(NULL, cxMargin, rc.top, cxMax, rc.Height(), uFlags);

	m_editCat.GetWindowRect(rc);
	ScreenToClient(rc);
	m_editCat.SetWindowPos(NULL, cxMargin, rc.top, cxMax, rc.Height(), uFlags);

	m_staticAlloy.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticAlloy.SetWindowPos(NULL, cxMargin, rc.top, cxMax, rc.Height(), uFlags);

	m_listboxAlloy.GetWindowRect(rc);
	ScreenToClient(rc);
	m_listboxAlloy.SetWindowPos(NULL, cxMargin, rc.top, cxMax, cyClient-rc.top-cyMargin, uFlags);
}

void CPageSearch::UpdateControlsStyles()
{
	POSITION posCat = Data_Cat_GetHeadPosition();

	if(posCat==0) // aucune catégorie de matière = fichier vide
	{
		// désactiver les contrôles
		m_editCat.EnableWindow(FALSE);
		m_listboxAlloy.EnableWindow(FALSE);
	}

	// si aucune nuance, désactiver les contrôles
	if(m_listboxAlloy.GetCount()<1)
	{
		m_editCat.EnableWindow(FALSE);
		m_listboxAlloy.EnableWindow(FALSE);
	}
	else
	{
		m_editCat.EnableWindow(TRUE);
		m_listboxAlloy.EnableWindow(TRUE);
	}
}

