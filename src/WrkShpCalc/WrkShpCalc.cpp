// WrkShpCalc.cpp : D�finit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "WrkShpCalc.h"
#include "WrkShpCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWrkShpCalcApp

BEGIN_MESSAGE_MAP(CWrkShpCalcApp, CAppDlg)
END_MESSAGE_MAP()


// construction CWrkShpCalcApp
CWrkShpCalcApp::CWrkShpCalcApp()
	: CAppDlg()
{
	// TODO�: ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CWrkShpCalcApp
CWrkShpCalcApp theApp;

// initialisation de CWrkShpCalcApp

BOOL CWrkShpCalcApp::InitInstance()
{
	CAppDlg::InitInstance();

	CWrkShpCalcDlg dlg;
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
