// MatDb.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "MatDb.h"
#include "SheetMatDb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMatDbApp
BEGIN_MESSAGE_MAP(CMatDbApp, CAppSheet)
END_MESSAGE_MAP()

// construction CMatDbApp
CMatDbApp::CMatDbApp():
	CAppSheet()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}

// Seul et unique objet CMatDbApp
CMatDbApp theApp;

// initialisation de CMatDbApp

BOOL CMatDbApp::InitInstance()
{
	CAppSheet::InitInstance();

	CSheetMatDb dlg;
	dlg.DoModal();

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}

