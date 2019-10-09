// NewtonCalc.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "NewtonCalc.h"
#include "NewtonCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewtonCalcApp

BEGIN_MESSAGE_MAP(CNewtonCalcApp, CAppDlg)
END_MESSAGE_MAP()


// construction CNewtonCalcApp
CNewtonCalcApp::CNewtonCalcApp()
	: CAppDlg()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CNewtonCalcApp
CNewtonCalcApp theApp;

// initialisation de CNewtonCalcApp

BOOL CNewtonCalcApp::InitInstance()
{
	CAppDlg::InitInstance();

	CNewtonCalcDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}
