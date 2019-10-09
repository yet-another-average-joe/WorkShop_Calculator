// TapCalc.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "TapCalc.h"
#include "SheetTapCalc.h"
#include "PageCalcTap.h"
#include "PageMementoTap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CTapCalcApp, CAppSheet)

// CTapCalcApp

BEGIN_MESSAGE_MAP(CTapCalcApp, CAppSheet)
END_MESSAGE_MAP()

// construction CTapCalcApp
CTapCalcApp::CTapCalcApp()
	: CAppSheet()
{
}

// Seul et unique objet CTapCalcApp
CTapCalcApp theApp;

// initialisation de CTapCalcApp

BOOL CTapCalcApp::InitInstance()
{
	CAppSheet::InitInstance();

	CSheetTapCalc dlg;
	m_pMainWnd = &dlg;


	dlg.DoModal();

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}

/*

à faire

ajouter une boite de dialogue options avec 
- les diamètres apparaissant dans la page calcul
- le nombre de Vc dans la combo
- le fichier d'outils par défaut à l'ouverture

*/

