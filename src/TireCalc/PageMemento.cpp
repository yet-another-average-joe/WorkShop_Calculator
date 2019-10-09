// PageMemento.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageMemento.h"

// Boîte de dialogue CPageMemento

IMPLEMENT_DYNAMIC(CPageMemento, CPropPageEx)

CPageMemento::CPageMemento()
	: CPropPageEx(CPageMemento::IDD, NULL)
{
	//EnableScrollbars(TRUE);
	m_comboChapter.SetFullDrop(TRUE);
	pDlg1=NULL;
}

CPageMemento::~CPageMemento()
{
	if(pDlg1!=NULL && IsWindow(pDlg1->GetSafeHwnd()))
	{
		pDlg1->DestroyWindow();
		delete pDlg1;
	}

	if(pDlg1!=NULL)
	{
		delete pDlg1;
	}
}

void CPageMemento::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PLACEHOLDER, m_staticPlaceHolder);
	DDX_Control(pDX, IDC_COMBO_CHAPTER, m_comboChapter);
}


BEGIN_MESSAGE_MAP(CPageMemento, CPropPageEx)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_CHAPTER, &CPageMemento::OnCbnSelchangeComboChapter)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageMemento

BOOL CPageMemento::OnInitDialog()
{
	CPropPageEx::OnInitDialog();

	int n;
	CString str;
	str.LoadStringW(IDS_SIZING_SYSTEM_NUMERIC);
	n=m_comboChapter.AddString(str);
	m_comboChapter.SetItemData(n, IDS_SIZING_SYSTEM_NUMERIC);

	str.LoadStringW(IDS_SIZING_SYSTEM_ALPHA_NUMERIC);
	n=m_comboChapter.AddString(str);
	m_comboChapter.SetItemData(n, IDS_SIZING_SYSTEM_ALPHA_NUMERIC);

	str.LoadStringW(IDS_SIZING_SYSTEM_METRIC);
	n=m_comboChapter.AddString(str);
	m_comboChapter.SetItemData(n, IDS_SIZING_SYSTEM_METRIC);

	str.LoadStringW(IDS_SIZING_SYSTEM_MILLIMETRIC);
	n=m_comboChapter.AddString(str);
	m_comboChapter.SetItemData(n, IDS_SIZING_SYSTEM_MILLIMETRIC);

	str.LoadStringW(IDS_SIZING_SYSTEM_FLOTATION);
	n=m_comboChapter.AddString(str);
	m_comboChapter.SetItemData(n, IDS_SIZING_SYSTEM_FLOTATION);
	
	str.LoadStringW(IDS_REGULATIONS);
	n=m_comboChapter.AddString(str);
	m_comboChapter.SetItemData(n, IDS_REGULATIONS);

	str.LoadStringW(IDS_DOT_AGE_CODE);
	n=m_comboChapter.AddString(str);
	m_comboChapter.SetItemData(n, IDS_DOT_AGE_CODE);

	str.LoadStringW(IDS_CE_HOMOLOGATION);
	n=m_comboChapter.AddString(str);
	m_comboChapter.SetItemData(n, IDS_CE_HOMOLOGATION);

	m_comboChapter.SetCurSel(0);
	OnCbnSelchangeComboChapter();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPageMemento::OnSize(UINT nType, int cx, int cy)
{
	CPropPageEx::OnSize(nType, cx, cy);


	if(pDlg1!=NULL && IsWindow(pDlg1->GetSafeHwnd()))
	{
		CRect rc;
		m_staticPlaceHolder.GetWindowRect(rc);
		ScreenToClient(rc);

		CRect rcClient;
		GetClientRect(rcClient);

		//pDlg1=new CDlgChildNumericSizing;
		//VERIFY(pDlg1->Create(IDD_CHILD_NUMERIC_SIZING, this));
		pDlg1->SetWindowPos(NULL, rc.left, rc.top, rcClient.right-rc.left, rcClient.bottom-rc.top, SWP_NOMOVE|SWP_NOZORDER);
	}
}

void CPageMemento::OnCbnSelchangeComboChapter()
{
	if(pDlg1!=NULL && IsWindow(pDlg1->GetSafeHwnd()))
	{
		pDlg1->DestroyWindow();
		delete pDlg1;
	}

	CRect rc;
	m_staticPlaceHolder.GetWindowRect(rc);
	ScreenToClient(rc);

	CRect rcClient;
	GetClientRect(rcClient);

	int n=m_comboChapter.GetCurSel();
	ASSERT(n!=CB_ERR);
	n=m_comboChapter.GetItemData(n);

	UINT nID;

	switch(n)
	{
		case IDS_SIZING_SYSTEM_NUMERIC:
			nID=IDD_CHILD_SIZING_SYSTEM_NUMERIC;
			break;
		case IDS_SIZING_SYSTEM_ALPHA_NUMERIC:
			nID=IDD_CHILD_SIZING_SYSTEM_ALPHA_NUMERIC;
			break;
		case IDS_SIZING_SYSTEM_METRIC:
			nID=IDD_CHILD_SIZING_SYSTEM_METRIC;
			break;
		case IDS_SIZING_SYSTEM_MILLIMETRIC:
			nID=IDD_CHILD_SIZING_SYSTEM_MILLIMETRIC;
			break;
		case IDS_SIZING_SYSTEM_FLOTATION:
			nID=IDD_CHILD_SIZING_SYSTEM_FLOTATION;
			break;
		case IDS_REGULATIONS:
			nID=IDD_CHILD_REGULATIONS;
			break;
		case IDS_DOT_AGE_CODE:
			nID=IDD_CHILD_DOT_AGE_CODE;
			break;
		case IDS_CE_HOMOLOGATION:
			nID=IDD_CHILD_CE_HOMOLOGATION;
			break;
		default:
			ASSERT(0);
			break;
	}

	pDlg1=new CDlgScroll(nID, this);
	VERIFY(pDlg1->Create(nID, this));
	pDlg1->SetWindowPos(NULL, rc.left, rc.top, rcClient.right-rc.left, rcClient.bottom-rc.top, SWP_NOZORDER|SWP_SHOWWINDOW);
}
