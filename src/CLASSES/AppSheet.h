#pragma once



// CAppSheet : classe de base pour les applications CAppSheet 
// baséees sur une boite de dialogue

// gestion des deux actions standard :
//
// boite de dialogue A propos : CLASSES_ID_MENU_ABOUT
// lancement de WrkShpCalc : CLASSES_ID_MENU_WRKSHPCALC
//
// pour créer une application, il suffit de :
//
// dériver l'application de CAppSheet
//
// créer un dialogue dérivé de CDlgMain
//
// définir InitInstance()
//
//	BOOL CMyApp::InitInstance()
//	{
//		CAppSheet::InitInstance();
//	
//		CMyDlg dlg;
//		m_pMainWnd = &dlg;
//		dlg.DoModal();
//	
//		// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
//		//  l'application, plutôt que de démarrer la pompe de messages de l'application.
//		return FALSE;
//	}
//
//	Les ID de menu et d'icône doivent être égaux à 128 (valeur donnée
//	par défaut par Visual Studio à IDR_MAINFRAME
//
//

class CAppSheet : public CWinApp
{
	DECLARE_DYNCREATE(CAppSheet)

protected:
	CAppSheet();           // constructeur protégé utilisé par la création dynamique
	virtual ~CAppSheet();

public:
	virtual BOOL InitInstance();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnWrkShpCalc();
	afx_msg void OnAbout();
};


