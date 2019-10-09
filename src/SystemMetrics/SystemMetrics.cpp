// SystemMetrics.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "SystemMetrics.h"
#include "SystemMetricsDlg.h"
//#include "AboutDlg.h"
//#include "CLASSES_rc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSystemMetricsApp

BEGIN_MESSAGE_MAP(CSystemMetricsApp, CAppDlg)
END_MESSAGE_MAP()


// construction CSystemMetricsApp
CSystemMetricsApp::CSystemMetricsApp()
	: CAppDlg()
{
}


// Seul et unique objet CSystemMetricsApp
CSystemMetricsApp theApp;

// initialisation de CSystemMetricsApp

BOOL CSystemMetricsApp::InitInstance()
{
	CAppDlg::InitInstance();

	CSystemMetricsDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}

