// AutoRun.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "AutoRun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define INSTALL_ARGUMENT    TEXT("install")
#define UNINSTALL_ARGUMENT  TEXT("uninstall")

// CAutoRunApp

BEGIN_MESSAGE_MAP(CAutoRunApp, CWinApp)
END_MESSAGE_MAP()


// construction CAutoRunApp
CAutoRunApp::CAutoRunApp()
	: CWinApp()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
	m_bLaunched=FALSE;
}


// Seul et unique objet CAutoRunApp
CAutoRunApp theApp;

// initialisation de CAutoRunApp

BOOL CAutoRunApp::InitInstance()
{

    // See if we've been launched because an MMC card was inserted or removed
    if (0 == lstrcmp(m_lpCmdLine, INSTALL_ARGUMENT)) 
    {
        // MMC card inserted
        //MessageBox( NULL, StringFromResources(IDS_AUTORUN_INSERT), 
        //    StringFromResources(IDS_AUTORUN_TITLE), MB_ICONINFORMATION | MB_OK );
		//AfxMessageBox(_T("carte insérée"));
		TCHAR szAutorunPath[MAX_PATH+1];
		VERIFY(SHGetAutoRunPath(szAutorunPath));

		CString strAppDir=szAutorunPath;
		strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
		// deux fois pour obtenir la racine de la carte
		strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
		strAppDir += _T("\\WrkShpCalc");
		
		CString strApp=strAppDir+_T("\\WrkShpCalc.exe");

		SHELLEXECUTEINFO ExecuteInfo;    
		memset(&ExecuteInfo, 0, sizeof(ExecuteInfo));
		    
		ExecuteInfo.cbSize       = sizeof(ExecuteInfo);
		ExecuteInfo.fMask        = SEE_MASK_FLAG_NO_UI;             
		ExecuteInfo.hwnd         = 0;                
		ExecuteInfo.lpVerb       = _T("open");                      
		ExecuteInfo.lpFile       = strApp;
		ExecuteInfo.lpDirectory  = strAppDir;
		ExecuteInfo.nShow        = SW_SHOW;
		ExecuteInfo.hInstApp     = 0;    

		if(ShellExecuteEx(&ExecuteInfo) == FALSE)
			AfxMessageBox(_T("Erreur lancement WrkShpCalc."), MB_OK|MB_ICONSTOP);
		else
			m_bLaunched=TRUE;
    }
    else if (0 == lstrcmp(m_lpCmdLine, UNINSTALL_ARGUMENT))
    {
        // MMC card removed
		if(m_bLaunched)
			AfxMessageBox(_T("La carte mémoire a été retirée.\n\nRésultats imprévisibles."), MB_OK|MB_ICONSTOP);
    }
    else
    {
        // Unrecognised command-line
		AfxMessageBox(_T("Erreur inconnue."), MB_OK|MB_ICONSTOP);
    }

	return FALSE;
}
