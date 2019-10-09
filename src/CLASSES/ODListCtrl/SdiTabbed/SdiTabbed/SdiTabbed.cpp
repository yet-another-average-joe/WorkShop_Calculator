// SdiTabbed.cpp�: D�finit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "SdiTabbed.h"
#include "MainFrm.h"

#include "SdiTabbedDoc.h"
#include "SdiTabbedView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdiTabbedApp

BEGIN_MESSAGE_MAP(CSdiTabbedApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSdiTabbedApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()



// construction CSdiTabbedApp
CSdiTabbedApp::CSdiTabbedApp()
	: CWinApp()
{
	// TODO�: ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CSdiTabbedApp
CSdiTabbedApp theApp;

// initialisation de CSdiTabbedApp

BOOL CSdiTabbedApp::InitInstance()
{
    // SHInitExtraControls doit �tre appel� une fois lors de l'initialisation de votre application afin d'initialiser
    // l'un des contr�les sp�cifiques � Windows Mobile, tels que CAPEDIT et SIPPREF.
    SHInitExtraControls();

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalit�s et que vous souhaitez r�duire la taille
	// de votre ex�cutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation sp�cifiques dont vous n'avez pas besoin.
	
	// Changez la cl� de Registre sous laquelle nos param�tres sont enregistr�s
	// TODO : modifiez cette cha�ne avec des informations appropri�es,
	// telles que le nom de votre soci�t� ou organisation
	SetRegistryKey(_T("Applications locales g�n�r�es par AppWizard"));
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSdiTabbedDoc),
		RUNTIME_CLASS(CMainFrame),       // fen�tre frame SDI principale
		RUNTIME_CLASS(CSdiTabbedView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Analyser la ligne de commande pour les commandes shell standard, DDE, ouverture de fichiers
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Commandes de dispatch sp�cifi�es sur la ligne de commande. Retournent FALSE si
	// l'application a �t� lanc�e avec /RegServer, /Register, /Unregserver ou /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// La seule fen�tre a �t� initialis�e et peut donc �tre affich�e et mise � jour
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


// bo�te de dialogue CAboutDlg utilis�e pour la bo�te de dialogue '� propos de' pour votre application
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Impl�mentation
protected:
#ifdef _DEVICE_RESOLUTION_AWARE
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;	// retourne TRUE sauf si vous avez d�fini le focus sur un contr�le
			// EXCEPTION�: les pages de propri�t�s OCX devraient retourner FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
#ifdef _DEVICE_RESOLUTION_AWARE
	ON_WM_SIZE()
#endif
END_MESSAGE_MAP()

#ifdef _DEVICE_RESOLUTION_AWARE
void CAboutDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
    	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? MAKEINTRESOURCE(IDD_ABOUTBOX_WIDE) : MAKEINTRESOURCE(IDD_ABOUTBOX));
	}
}
#endif

// Commande App pour ex�cuter la bo�te de dialogue
void CSdiTabbedApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
