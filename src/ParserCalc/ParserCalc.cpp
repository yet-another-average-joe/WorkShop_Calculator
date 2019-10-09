// ParserCalc.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "ParserCalc.h"
#include "SheetParseCalc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CParserCalcApp

BEGIN_MESSAGE_MAP(CParserCalcApp, CAppSheet)
END_MESSAGE_MAP()


// construction CParserCalcApp
CParserCalcApp::CParserCalcApp()
	: CAppSheet()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CParserCalcApp
CParserCalcApp theApp;

// initialisation de CParserCalcApp

BOOL CParserCalcApp::InitInstance()
{
	// idée : ajouter paramètres pour calcul, et valeur de retour : permettrait
	// d'utiliser ParserCalc comme calculette appelée depuis d'autres applications
	CSheetParseCalc dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO : placez ici le code définissant le comportement lorsque la boîte de dialogue est
		//  fermée avec OK
	}

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}
