// CEDlgApp.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "AppSheet.h"
#include "CLASSES_rc.h"
#include "DlgAbout.h"
#include "CLASSES.h"

// CAppSheet

IMPLEMENT_DYNCREATE(CAppSheet, CWinApp)

CAppSheet::CAppSheet()
{
}

CAppSheet::~CAppSheet()
{
}

BOOL CAppSheet::InitInstance()
{
    // SHInitExtraControls doit être appelé une fois lors de l'initialisation de votre application afin d'initialiser
    // l'un des contrôles spécifiques à Windows Mobile, tels que CAPEDIT et SIPPREF.
    SHInitExtraControls();

	// si appelée, problèmes !... (en horizontal)
	//if(!IsOldCE2003())
	//	AfxEnableDRA(TRUE); // resolution aware

	return FALSE;
}

BEGIN_MESSAGE_MAP(CAppSheet, CWinApp)
	ON_COMMAND(CLASSES_IDM_WRKSHPCALC, &CAppSheet::OnWrkShpCalc)
	ON_COMMAND(CLASSES_IDM_ABOUT, &CAppSheet::OnAbout)
END_MESSAGE_MAP()

// Gestionnaires de messages de CAppSheet

void CAppSheet::OnWrkShpCalc()
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strApp = strAppDir + _T("\\") + _T("WrkShpCalc.exe"); // pas besoin de placer en resource : invariable


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
	{
		AfxMessageBox(CLASSES_IDS_ERROR_WRKSHPCALC, MB_OK|MB_ICONSTOP);
	}
}

void CAppSheet::OnAbout()
{
	CDlgAbout aboutDlg;
	aboutDlg.DoModal();
}

