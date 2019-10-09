// MillCalc.cpp : D�finit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "MillCalc.h"
#include "SheetMillCalc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMillCalcApp, CAppSheet)

// CMillCalcApp

BEGIN_MESSAGE_MAP(CMillCalcApp, CAppSheet)
END_MESSAGE_MAP()

// construction CMillCalcApp
CMillCalcApp::CMillCalcApp()
	: CAppSheet()
{
}

// Seul et unique objet CMillCalcApp
CMillCalcApp theApp;

// initialisation de CMillCalcApp

BOOL CMillCalcApp::InitInstance()
{
	CAppSheet::InitInstance();

	CSheetMillCalc dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
	//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
	return FALSE;
}
