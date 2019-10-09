// TireCalc.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "TireCalc.h"
#include "SheetTireCalc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTireCalcApp

BEGIN_MESSAGE_MAP(CTireCalcApp, CAppDlg)
END_MESSAGE_MAP()


// construction CTireCalcApp
CTireCalcApp::CTireCalcApp()
	: CAppDlg()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CTireCalcApp
CTireCalcApp theApp;

// initialisation de CTireCalcApp

BOOL CTireCalcApp::InitInstance()
{
/*
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
    // SHInitExtraControls doit être appelé une fois lors de l'initialisation de votre application afin d'initialiser
    // l'un des contrôles spécifiques à Windows Mobile, tels que CAPEDIT et SIPPREF.
    SHInitExtraControls();
#endif // WIN32_PLATFORM_PSPC || WIN32_PLATFORM_WFSP

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
	// de votre exécutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation spécifiques dont vous n'avez pas besoin.
	// Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
	// TODO : modifiez cette chaîne avec des informations appropriées,
	// telles que le nom de votre société ou organisation
	SetRegistryKey(_T("Applications locales générées par AppWizard"));
*/
	CSheetTireCalc dlg;
	m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO : placez ici le code définissant le comportement lorsque la boîte de dialogue est
	//	//  fermée avec OK
	//}

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}
