// ParserCalc.cpp : D�finit les comportements de classe pour l'application.
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
	// TODO�: ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CParserCalcApp
CParserCalcApp theApp;

// initialisation de CParserCalcApp

BOOL CParserCalcApp::InitInstance()
{
	// id�e : ajouter param�tres pour calcul, et valeur de retour : permettrait
	// d'utiliser ParserCalc comme calculette appel�e depuis d'autres applications
	CSheetParseCalc dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO�: placez ici le code d�finissant le comportement lorsque la bo�te de dialogue est
		//  ferm�e avec OK
	}

	// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
	//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
	return FALSE;
}
