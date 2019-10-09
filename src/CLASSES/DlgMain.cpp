// CEDlgAppMainDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DlgMain.h"
#include "CLASSES_rc.h"
#include "CLASSES.h"

// Boîte de dialogue CDlgMain

#define ID_MENU	128
#define ID_ICON	128

IMPLEMENT_DYNAMIC(CDlgMain, CDlgScroll)

CDlgMain::CDlgMain(	UINT nIDTemplate,		// template du dialogue
									BOOL fHideSHDoneBtn /*=FALSE*/,	// si TRUE, le bouton "ok" est remplacé par "X"
									CWnd* pParent /*= NULL*/)
	: CDlgScroll(nIDTemplate, pParent)
{
	m_fHideSHDoneBtn=fHideSHDoneBtn;
	m_fHideSHDoneBtn=FALSE;	// si TRUE, le bouton "ok" est remplacé par "X"
}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDlgScroll::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMain, CDlgScroll)
END_MESSAGE_MAP()


// Gestionnaires de messages de CDlgMain

BOOL CDlgMain::OnInitDialog()
{
	CDlgScroll::OnInitDialog();

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	HICON hIcon=AfxGetApp()->LoadIcon(ID_ICON);
	SetIcon(hIcon, TRUE);			// Définir une grande icône
	SetIcon(hIcon, FALSE);		// Définir une petite icône

	// bouton OK ou X
	::SHDoneButton(m_hWnd, m_fHideSHDoneBtn==TRUE?SHDB_HIDE:SHDB_SHOW);

	// command bar control
	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(ID_MENU) ||
	    !m_wndCommandBar.AddAdornments(0))
	{
		TRACE0("Impossible de créer CommandBar\n");
		return -1;      // échec de la création
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);

	// bouton WrkShpCalc actif seulement si le programme est présent
	EnableWrkShpCalcBtn(m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

