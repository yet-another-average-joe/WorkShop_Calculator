// LatheCalc.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "LatheCalc.h"
#include "SheetLatheCalc.h"
#include "PageCalcLathe.h"
#include "PageMementoLathe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CLatheCalcApp, CAppSheet)

// CLatheCalcApp

BEGIN_MESSAGE_MAP(CLatheCalcApp, CAppSheet)
END_MESSAGE_MAP()

// construction CLatheCalcApp
CLatheCalcApp::CLatheCalcApp()
	: CAppSheet()
{
}

// Seul et unique objet CLatheCalcApp
CLatheCalcApp theApp;

// initialisation de CLatheCalcApp

BOOL CLatheCalcApp::InitInstance()
{
	CAppSheet::InitInstance();

	CSheetLatheCalc dlg;
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

