// CEDlgAppMainDlg.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "DlgMain.h"
#include "CLASSES_rc.h"
#include "CLASSES.h"

// Bo�te de dialogue CDlgMain

#define ID_MENU	128
#define ID_ICON	128

IMPLEMENT_DYNAMIC(CDlgMain, CDlgScroll)

CDlgMain::CDlgMain(	UINT nIDTemplate,		// template du dialogue
									BOOL fHideSHDoneBtn /*=FALSE*/,	// si TRUE, le bouton "ok" est remplac� par "X"
									CWnd* pParent /*= NULL*/)
	: CDlgScroll(nIDTemplate, pParent)
{
	m_fHideSHDoneBtn=fHideSHDoneBtn;
	m_fHideSHDoneBtn=FALSE;	// si TRUE, le bouton "ok" est remplac� par "X"
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

	// D�finir l'ic�ne de cette bo�te de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fen�tre principale de l'application n'est pas une bo�te de dialogue
	HICON hIcon=AfxGetApp()->LoadIcon(ID_ICON);
	SetIcon(hIcon, TRUE);			// D�finir une grande ic�ne
	SetIcon(hIcon, FALSE);		// D�finir une petite ic�ne

	// bouton OK ou X
	::SHDoneButton(m_hWnd, m_fHideSHDoneBtn==TRUE?SHDB_HIDE:SHDB_SHOW);

	// command bar control
	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(ID_MENU) ||
	    !m_wndCommandBar.AddAdornments(0))
	{
		TRACE0("Impossible de cr�er CommandBar\n");
		return -1;      // �chec de la cr�ation
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);

	// bouton WrkShpCalc actif seulement si le programme est pr�sent
	EnableWrkShpCalcBtn(m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION�: les pages de propri�t�s OCX devraient retourner FALSE
}

