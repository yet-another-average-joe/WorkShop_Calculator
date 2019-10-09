// DlgSave.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DlgSave.h"
#include "CEFileFind.h"
#include "CLASSES_rc.h"
#include "Data.h"

//à revoir :
//
//aligner sur titre
//commentaire : en lecture sur sélection de la listbox pour "enregistrer sous", éditable pour "enregistrer copie sous"
//			  obligation de gérer les 3 cas : portrait / landscape, et suqre (pb avec square...)
//			  pour square : commentaire en lecture seule est la seule solution si pas de scrolling des contrôles

// Boîte de dialogue CDlgSave

IMPLEMENT_DYNAMIC(CDlgSave, CCEDialog)

CDlgSave::CDlgSave(CWnd* pParent /*=NULL*/)
	: CCEDialog(CLASSES_IDD_FILE_SAVE_PORTRAIT, pParent)
	, m_strFileName(_T(""))
	, m_strFileExt(_T(""))
	, m_nIDTitle(0)
{
}

CDlgSave::~CDlgSave()
{
}

void CDlgSave::DoDataExchange(CDataExchange* pDX)
{
	CCEDialog::DoDataExchange(pDX);
	DDX_Control(pDX, CLASSES_IDC_LISTBOX_DATAFILE, m_listboxFileName);
	DDX_Text(pDX, CLASSES_IDC_EDIT_FILENAME, m_strFileName);
	DDX_Control(pDX, CLASSES_IDC_EDIT_FILENAME, m_editFileName);
}

BEGIN_MESSAGE_MAP(CDlgSave, CCEDialog)
	ON_LBN_SELCHANGE(CLASSES_IDC_LISTBOX_DATAFILE, &CDlgSave::OnLbnSelchangeListboxDatafile)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_FILENAME, &CDlgSave::OnEnChangeIdcEditFilename)
END_MESSAGE_MAP()


// Gestionnaires de messages de CDlgSave

BOOL CDlgSave::OnInitDialog()
{
	CCEDialog::OnInitDialog();

	// Create the command bar control
	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(CLASSES_IDR_MENU_OKCANCEL) ||
	    !m_wndCommandBar.AddAdornments(0))
	{
		TRACE0("Impossible de créer CommandBar\n");
		return -1;      // échec de la création
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);

	CToolBarCtrl&	tb = m_wndCommandBar.GetToolBarCtrl();
	if(m_strFileName.IsEmpty())
		tb.EnableButton(IDOK, FALSE);
	else
		tb.EnableButton(IDOK, TRUE);

	ModifyStyle(0, WS_NONAVDONEBUTTON, SWP_NOSIZE); 
	::SHDoneButton(m_hWnd, SHDB_HIDE);

	// désactiver le bouton Ok tant qu'un fichier n'est aps sélectionné
	//CToolBarCtrl&	tb = m_wndCommandBar.GetToolBarCtrl();
	//tb.EnableButton(IDOK, FALSE);

	//CString strTitle;
	//strTitle.LoadString(m_nIDTitle);
	//SetWindowText(strTitle);
	m_strHeader.LoadString(m_nIDTitle);

	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strFind = strAppDir + _T("\\*.") + m_strFileExt;

	CFileFind ff;
	if (!ff.FindFile(strFind)) 
		return 0;
	BOOL bNext;

	do 
	{
		bNext=ff.FindNextFile();
		CString strFileName = ff.GetFileName();

		CString strPathName = strAppDir+_T("\\")+strFileName;
		// nom sans extention
		strFileName = strFileName.Left(strFileName.ReverseFind('.'));

		int j=m_listboxFileName.AddString(strFileName);
		ASSERT(j!=CB_ERR);
		CString* pStr=new CString(strPathName);
		m_listboxFileName.SetItemDataPtr(j, (void*)pStr);
		strFileName.ReleaseBuffer();
	} while (bNext);

	m_editFileName.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CDlgSave::OnLbnSelchangeListboxDatafile()
{
	int nCurSel=m_listboxFileName.GetCurSel();
	ASSERT(nCurSel!=LB_ERR);
	m_listboxFileName.GetText(nCurSel, m_strFileName);
	SetDlgItemText(CLASSES_IDC_EDIT_FILENAME, m_strFileName);

	// problème de place sur affichage carré
	//CData data;
	//data.SetFileExt(m_strFileExt);
	//data.FileRead(m_strFileName);
	//SetDlgItemText(CLASSES_IDC_EDIT_COMMENT, data.m_strComment);

	// activer le bouton ok
	//CToolBarCtrl&	tb = m_wndCommandBar.GetToolBarCtrl();
	//tb.EnableButton(IDOK, TRUE);
}

BOOL CDlgSave::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if(wParam==IDOK)
	{
		CString str;
		GetDlgItemText(CLASSES_IDC_EDIT_FILENAME, str);
		if(str.IsEmpty())
		{
			MessageBeep(0);
			return FALSE;
		}
	}
	// TODO : ajoutez ici votre code spécialisé et/ou l'appel de la classe de base

	return CCEDialog::OnCommand(wParam, lParam);
}

void CDlgSave::OnEnChangeIdcEditFilename()
{
	CString strFileName;
	LPTSTR lpszText=strFileName.GetBuffer(_MAX_FNAME);
	GetDlgItemText(CLASSES_IDC_EDIT_FILENAME, lpszText, _MAX_FNAME);
	strFileName.ReleaseBuffer();
	CToolBarCtrl&	tb = m_wndCommandBar.GetToolBarCtrl();
	if(strFileName.IsEmpty())
		tb.EnableButton(IDOK, FALSE);
	else
		tb.EnableButton(IDOK, TRUE);
}
