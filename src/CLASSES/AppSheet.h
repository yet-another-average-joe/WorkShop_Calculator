#pragma once



// CAppSheet : classe de base pour les applications CAppSheet 
// bas�ees sur une boite de dialogue

// gestion des deux actions standard :
//
// boite de dialogue A propos : CLASSES_ID_MENU_ABOUT
// lancement de WrkShpCalc : CLASSES_ID_MENU_WRKSHPCALC
//
// pour cr�er une application, il suffit de :
//
// d�river l'application de CAppSheet
//
// cr�er un dialogue d�riv� de CDlgMain
//
// d�finir InitInstance()
//
//	BOOL CMyApp::InitInstance()
//	{
//		CAppSheet::InitInstance();
//	
//		CMyDlg dlg;
//		m_pMainWnd = &dlg;
//		dlg.DoModal();
//	
//		// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
//		//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
//		return FALSE;
//	}
//
//	Les ID de menu et d'ic�ne doivent �tre �gaux � 128 (valeur donn�e
//	par d�faut par Visual Studio � IDR_MAINFRAME
//
//

class CAppSheet : public CWinApp
{
	DECLARE_DYNCREATE(CAppSheet)

protected:
	CAppSheet();           // constructeur prot�g� utilis� par la cr�ation dynamique
	virtual ~CAppSheet();

public:
	virtual BOOL InitInstance();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnWrkShpCalc();
	afx_msg void OnAbout();
};


