// DrillcalcApp.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "DrillCalc.h"
#include "SheetDrillCalc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CDrillCalcApp, CAppSheet)

// CDrillCalcApp

BEGIN_MESSAGE_MAP(CDrillCalcApp, CAppSheet)
END_MESSAGE_MAP()

// construction CDrillCalcApp
CDrillCalcApp::CDrillCalcApp()
	: CAppSheet()
{
}

// Seul et unique objet CDrillCalcApp
CDrillCalcApp theApp;

// initialisation de CDrillCalcApp

BOOL CDrillCalcApp::InitInstance()
{
	CAppSheet::InitInstance();

	CSheetDrillCalc dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}

