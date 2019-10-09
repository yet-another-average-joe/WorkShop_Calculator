// PageRatings.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "PageRatings.h"

typedef struct SpeedRating
{
	TCHAR szIndex[4];
	TCHAR szKPH[10];
} t_SpeedRating;

t_SpeedRating speedRatingArray[]=
{
	{ _T("A1"), _T("5 km/h") },
	{ _T("A2"), _T("10 km/h") },
	{ _T("A3"), _T("15 km/h") },
	{ _T("A4"), _T("20 km/h") },
	{ _T("A5"), _T("25 km/h") },
	{ _T("A6"), _T("30 km/h") },
	{ _T("A7"), _T("35 km/h") },
	{ _T("A8"), _T("40 km/h") },
	{ _T("B"), _T("50 km/h") },
	{ _T("C"), _T("60 km/h") },
	{ _T("D"), _T("65 km/h") },
	{ _T("E"), _T("70 km/h") },
	{ _T("F"), _T("80 km/h") },
	{ _T("G"), _T("90 km/h") },
	{ _T("J"), _T("100 km/h") },
	{ _T("K"), _T("110 km/h") },
	{ _T("L"), _T("120 km/h") },
	{ _T("M"), _T("130 km/h") },
	{ _T("N"), _T("140 km/h") },
	{ _T("P"), _T("150 km/h") },
	{ _T("Q"), _T("160 km/h") },
	{ _T("R"), _T("170 km/h") },
	{ _T("S"), _T("180 km/h") },
	{ _T("T"), _T("190 km/h") },
	{ _T("U"), _T("200 km/h") },
	{ _T("H"), _T("210 km/h") },
	{ _T("V"), _T("240 km/h") },
	{ _T("W"), _T("270 km/h") },
	{ _T("Y"), _T("300 km/h") },
	{ _T("(Y)"), _T(">300 km/h") }
};

typedef struct LoadIndex
{
	int nIndex;
	TCHAR szKg[8];
} t_LoadIndex;

t_LoadIndex loadIndexArray[]=
{
	{ 20, _T("80 kg") },
	{ 22, _T("85 kg") },
	{ 24, _T("85 kg") },
	{ 26, _T("90 kg") },
	{ 28, _T("100 kg") },
	{ 30, _T("106 kg") },
	{ 31, _T("109 kg") },
	{ 33, _T("115 kg") },
	{ 35, _T("121 kg") },
	{ 37, _T("128 kg") },
	{ 40, _T("136 kg") },
	{ 41, _T("145 kg") },
	{ 42, _T("150 kg") },
	{ 44, _T("160 kg") },
	{ 46, _T("170 kg") },
	{ 47, _T("175 kg") },
	{ 48, _T("180 kg") },
	{ 50, _T("190 kg") },
	{ 51, _T("195 kg") },
	{ 52, _T("200 kg") },
	{ 53, _T("206 kg") },
	{ 54, _T("212 kg") },
	{ 55, _T("218 kg") },
	{ 58, _T("236 kg") },
	{ 59, _T("243 kg") },
	{ 60, _T("250 kg") },
	{ 61, _T("257 kg") },
	{ 62, _T("265 kg") },
	{ 63, _T("272 kg") },
	{ 64, _T("280 kg") },
	{ 65, _T("290 kg") },
	{ 66, _T("300 kg") },
	{ 67, _T("307 kg") },
	{ 68, _T("315 kg") },
	{ 69, _T("325 kg") },
	{ 70, _T("335 kg") },
	{ 71, _T("345 kg") },
	{ 72, _T("355 kg") },
	{ 73, _T("365 kg") },
	{ 74, _T("375 kg") },
	{ 75, _T("387 kg") },
	{ 76, _T("400 kg") },
	{ 77, _T("412 kg") },
	{ 78, _T("425 kg") },
	{ 79, _T("437 kg") },
	{ 80, _T("450 kg") },
	{ 81, _T("462 kg") },
	{ 82, _T("475 kg") },
	{ 83, _T("487 kg") },
	{ 84, _T("500 kg") },
	{ 85, _T("515 kg") },
	{ 86, _T("530 kg") },
	{ 87, _T("545 kg") },
	{ 88, _T("560 kg") },
	{ 89, _T("580 kg") },
	{ 90, _T("600 kg") },
	{ 91, _T("615 kg") },
	{ 92, _T("630 kg") },
	{ 93, _T("650 kg") },
	{ 94, _T("670 kg") },
	{ 95, _T("690 kg") },
	{ 96, _T("710 kg") },
	{ 97, _T("730 kg") },
	{ 98, _T("750 kg") },
	{ 99, _T("775 kg") },
	{ 100, _T("800 kg") },
	{ 101, _T("825 kg") },
	{ 102, _T("850 kg") },
	{ 103, _T("875 kg") },
	{ 104, _T("900 kg") },
	{ 105, _T("925 kg") },
	{ 106, _T("950 kg") },
	{ 107, _T("975 kg") },
	{ 108, _T("1000 kg") },
	{ 109, _T("1030 kg") },
	{ 110, _T("1060 kg") },
	{ 111, _T("1060 kg") },
	{ 112, _T("1120 kg") },
	{ 113, _T("1150 kg") },
	{ 114, _T("1180 kg") },
	{ 115, _T("1215 kg") },
	{ 116, _T("1250 kg") },
	{ 117, _T("1285 kg") },
	{ 118, _T("1320 kg") },
	{ 119, _T("1360 kg") },
	{ 120, _T("1400 ") }

};

// Boîte de dialogue CPageRatings

IMPLEMENT_DYNAMIC(CPageRatings, CPropertyPage)

CPageRatings::CPageRatings()
	: CPropPageEx(CPageRatings::IDD, NULL)
{
	m_comboSpeedRating.SetFullDrop(TRUE);
	m_comboLoadIndex.SetFullDrop(TRUE);
	EnableScrollbars(TRUE);
}

CPageRatings::~CPageRatings()
{
}

void CPageRatings::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_SPEED_RATING, m_comboSpeedRating);
	DDX_Control(pDX, IDC_COMBO_LOAD_INDEX, m_comboLoadIndex);
	DDX_Control(pDX, IDC_EDIT_SPEED, m_editSpeed);
	DDX_Control(pDX, IDC_EDIT_LOAD, m_editLoad);
}


BEGIN_MESSAGE_MAP(CPageRatings, CPropPageEx)
	ON_CBN_SELCHANGE(IDC_COMBO_LOAD_INDEX, &CPageRatings::OnCbnSelchangeComboLoadIndex)
	ON_CBN_SELCHANGE(IDC_COMBO_SPEED_RATING, &CPageRatings::OnCbnSelchangeComboSpeedRating)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageRatings

BOOL CPageRatings::OnInitDialog()
{
	CPropPageEx::OnInitDialog();

	VERIFY(ModifyStyle(0, WS_TABSTOP));

	for(int i=0; i < sizeof(speedRatingArray)/sizeof(t_SpeedRating); i++)
	{
		CString str;
		str.Format(_T("%s"), speedRatingArray[i].szIndex);
		int n=m_comboSpeedRating.AddString(str);
		m_comboSpeedRating.SetItemDataPtr(n, speedRatingArray[i].szKPH);
		if(str==_T("S"))
			m_comboSpeedRating.SetCurSel(n);
	}

	for(int i=0; i < sizeof(loadIndexArray)/sizeof(t_LoadIndex); i++)
	{
		CString str;
		str.Format(_T("%d"), loadIndexArray[i].nIndex);
		int n=m_comboLoadIndex.AddString(str);
		m_comboLoadIndex.SetItemDataPtr(n, loadIndexArray[i].szKg);
		if(loadIndexArray[i].nIndex==100)
			m_comboLoadIndex.SetCurSel(n);
	}

	OnCbnSelchangeComboLoadIndex();
	OnCbnSelchangeComboSpeedRating();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPageRatings::OnCbnSelchangeComboLoadIndex()
{
	int n=m_comboLoadIndex.GetCurSel();
	ASSERT(n!=CB_ERR);
	TCHAR* psz=(TCHAR*)m_comboLoadIndex.GetItemDataPtr(n);
	m_editLoad.SetWindowTextW(psz);
}

void CPageRatings::OnCbnSelchangeComboSpeedRating()
{
	int n=m_comboSpeedRating.GetCurSel();
	ASSERT(n!=CB_ERR);
	TCHAR* psz=(TCHAR*)m_comboSpeedRating.GetItemDataPtr(n);
	m_editSpeed.SetWindowTextW(psz);
}

