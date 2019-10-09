// TapCalc.cpp : D�finit les comportements de classe pour l'application.
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

	// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
	//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
	return FALSE;
}

/*

� faire

ajouter une boite de dialogue options avec 
- les diam�tres apparaissant dans la page calcul
- le nombre de Vc dans la combo
- le fichier d'outils par d�faut � l'ouverture

*/

