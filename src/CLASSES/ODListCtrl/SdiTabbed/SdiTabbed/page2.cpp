// page2.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "SdiTabbed.h"
#include "page2.h"


// Boîte de dialogue CPage2

IMPLEMENT_DYNAMIC(CPage2, CPage)

CPage2::CPage2()
	: CPage(CPage2::IDD)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage2, CPage)
	ON_WM_SIZE()
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// Gestionnaires de messages de CPage2

BOOL CPage2::OnInitDialog()
{
	CPage::OnInitDialog();

	VERIFY(m_wndList.SubclassDlgItem(IDC_LIST1, this));

    LV_COLUMN lvColumn;
	lvColumn.mask = LVCF_WIDTH;
	lvColumn.cx = 100;
	
	m_wndList.InsertColumn(0, &lvColumn);

//	lvColumn.cx = 20;
//	m_wndList.InsertColumn(1, &lvColumn);

	for(int i=0; i<8; i++)
	{
		//CString str;
		//str.Format(_T("Item n° %d"), i);
		//int nRet=m_wndList.InsertItem(i, str);
		m_strText[i].Format(_T("Item n° %d"), i);
/*
		LVITEM lvi;
		lvi.pszText=(LPWSTR)*m_strText[i];
		lvi.mask=LVIF_PARAM; 
		lvi.iItem=i; 
		lvi.lParam=(LPARAM)&m_strText[i];
		int j =m_wndList.InsertItem(&lvi);
		ASSERT(i==j);
*/
int j=m_wndList.InsertItem(
   LVIF_PARAM,
   i,
   NULL,//LPCTSTR lpszItem,
   0,//UINT nState,
   0,//UINT nStateMask,
   0,//int nImage,
   (LPARAM)&m_strText[i]//LPARAM lParam
);
		ASSERT(i==j);
	}

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
//	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
//	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPage2::OnSize(UINT nType, int cx, int cy)
{
	CPage::OnSize(nType, cx, cy);

	if(!m_wndList.m_hWnd)
		return;

	m_wndList.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER|SWP_SHOWWINDOW);

	// enpêcher l'apparition d'une scrollbar horizontale
	CRect rcClient;
	m_wndList.GetClientRect(rcClient);
	m_wndList.SetColumnWidth(0, rcClient.Width());
}

void CPage2::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMIS)
{
	if(nIDCtl==IDC_LIST1)
		m_wndList.OnMeasureItem(nIDCtl, lpMIS);

//	CPage::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CPage2::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS)
{
	if(nIDCtl==IDC_LIST1)
		m_wndList.OnDrawItem(nIDCtl, lpDIS);

//	CPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
