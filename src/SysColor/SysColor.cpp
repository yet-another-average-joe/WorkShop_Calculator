// SysColor.cpp : D�finit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "SysColor.h"
#include "SysColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSysColorApp

BEGIN_MESSAGE_MAP(CSysColorApp, CAppDlg)
END_MESSAGE_MAP()


// construction CSysColorApp
CSysColorApp::CSysColorApp()
	: CAppDlg()
{
}


// Seul et unique objet CSysColorApp
CSysColorApp theApp;

// initialisation de CSysColorApp

BOOL CSysColorApp::InitInstance()
{
	CAppDlg::InitInstance();

	CSysColorDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
	//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
	return FALSE;
}
