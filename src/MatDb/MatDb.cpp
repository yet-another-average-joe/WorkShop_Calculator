// MatDb.cpp�: D�finit les comportements de classe pour l'application.
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
	// TODO�: ajoutez ici du code de construction,
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

	// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
	//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
	return FALSE;
}

