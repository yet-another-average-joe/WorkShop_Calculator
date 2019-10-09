// StockCalc.cpp : D�finit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "StockCalc.h"
#include "StockCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStockCalcApp

BEGIN_MESSAGE_MAP(CStockCalcApp, CAppDlg)
END_MESSAGE_MAP()


// construction CStockCalcApp
CStockCalcApp::CStockCalcApp()
	: CAppDlg()
{
	// TODO�: ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CStockCalcApp
CStockCalcApp theApp;

// initialisation de CStockCalcApp

BOOL CStockCalcApp::InitInstance()
{
	CAppDlg::InitInstance();

	CStockCalcDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
	//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
	return FALSE;
}
