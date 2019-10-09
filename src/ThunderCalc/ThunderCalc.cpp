// ThunderCalc.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "ThunderCalc.h"
#include "ThunderCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CThunderCalcApp

BEGIN_MESSAGE_MAP(CThunderCalcApp, CAppDlg)
END_MESSAGE_MAP()


// construction CThunderCalcApp
CThunderCalcApp::CThunderCalcApp()
	: CAppDlg()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CThunderCalcApp
CThunderCalcApp theApp;

// initialisation de CThunderCalcApp

BOOL CThunderCalcApp::InitInstance()
{
	CAppDlg::InitInstance();

	CThunderCalcDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}
