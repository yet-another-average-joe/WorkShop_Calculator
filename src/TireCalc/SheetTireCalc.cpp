// SheetTireCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "SheetTireCalc.h"
#include "Data.h"
#include "DlgOdometer.h"
#include "PageDim.h"
#include "PageMisc.h"
#include "PageMemento.h"
#include "PageRatings.h"


// CSheetTireCalc

IMPLEMENT_DYNAMIC(CSheetTireCalc, CPropSheetEx)

CSheetTireCalc::CSheetTireCalc(UINT iSelectPage/*= 0*/)
	:CPropSheetEx(iSelectPage)
{
	m_pPageDim = new CPageDim;
	m_pPageRatings = new CPageRatings;
	m_pPageMisc = new CPageMisc;
	m_pPageMemento = new CPageMemento;

	AddPage(m_pPageDim);
	AddPage(m_pPageRatings);
	AddPage(m_pPageMisc);
	AddPage(m_pPageMemento);
}

CSheetTireCalc::~CSheetTireCalc()
{
	delete m_pPageDim;
	delete m_pPageRatings;
	delete m_pPageMisc;
	delete m_pPageMemento;
}

BEGIN_MESSAGE_MAP(CSheetTireCalc, CPropSheetEx)
	ON_COMMAND(ID_MENU_ODOMETER, &CSheetTireCalc::OnMenuOdometer)
END_MESSAGE_MAP()


// Gestionnaires de messages de CSheetTireCalc

void CSheetTireCalc::OnMenuOdometer()
{
	CDlgOdometer dlg;
	dlg.DoModal();
}
