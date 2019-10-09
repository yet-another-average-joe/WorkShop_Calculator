#pragma once



// CAppDlg : classe de base pour les applications CAppDlg 
// baséees sur une boite de dialogue

// gestion des deux actions standard :
//
// boite de dialogue A propos : CLASSES_ID_MENU_ABOUT
// lancement de WrkShpCalc : CLASSES_ID_MENU_WRKSHPCALC
//
// pour créer une application, il suffit de :
//
// dériver l'application de CAppDlg
//
// créer un dialogue dérivé de CCEDlgAppMainDlg
//
// définir InitInstance()
//
//	BOOL CMyApp::InitInstance()
//	{
//		CAppDlg::InitInstance();
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

class CAppDlg : public CWinApp
{
	DECLARE_DYNCREATE(CAppDlg)

protected:
	CAppDlg();           // constructeur protégé utilisé par la création dynamique
	virtual ~CAppDlg();

public:
	virtual BOOL InitInstance();


protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnWrkShpCalc();
	afx_msg void OnAbout();
};


