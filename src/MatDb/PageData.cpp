// PageData.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MatDb.h"
#include "PageData.h"
#include "SheetMatDb.h"
#include "CEFileFind.h"

// Boîte de dialogue CPageData

IMPLEMENT_DYNAMIC(CPageData, CPropPageEx)

CPageData::CPageData(CData* pData)
	: CPropPageEx(CPageData::IDD, pData)
{
	EnableScrollbars(FALSE); // pas de scrolling sur cette page
	m_comboDataFile.SetFullDrop(TRUE);

	m_editComment.m_bNoGray=TRUE;
}

CPageData::~CPageData()
{
}

BOOL CPageData::OnInitDialog()
{
	CPropPageEx::OnInitDialog();

	// sélectionner le premier item ; PostMessage() car OnSetActive() (qui appelle UpdatePage() )
	// est appelée après OnInitDialog ; les messages arrivent plus tard...
	m_comboDataFile.PostMessage(CB_SETCURSEL, 0, 0);
	PostMessage(WM_COMMAND, MAKEWPARAM(IDC_COMBO_DATAFILE, CBN_SELCHANGE), (LPARAM)m_comboDataFile.m_hWnd);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CPageData::UpdatePage()
{
	m_comboDataFile.ResetContent();
	// semble ne pas fonctionner !
	m_comboDataFile.SetFocus();
	UpdateFileList();

	CString strFileName;
	m_pData->GetFileName(strFileName);

	if(!strFileName.IsEmpty())
		Combo_SelectFileName(strFileName);
	else
		m_comboDataFile.SetCurSel(-1);

	m_editComment.SetWindowText_NoNotify(m_pData->m_strComment);

	CPropPageEx::UpdatePage();
}

void CPageData::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMMENT, m_editComment);
	DDX_Control(pDX, IDC_STATIC_COMMENT, m_staticComment);
	DDX_Control(pDX, IDC_COMBO_DATAFILE, m_comboDataFile);
	DDX_Control(pDX, IDC_STATIC_DATAFILE, m_staticDataFile);
}

// ATTENTION : NE GERE PAS LE CAS DES FICHIERS CORROMPUS !
void CPageData::UpdateFileList()
{
	m_comboDataFile.ResetContent();

	// remplir la listbox avec les noms de fichiers mtl présents dnas le dossier de l'application
	
	// récupérer le chemin complet de l'exécutable
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();

	// extraire le dossier
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));

	// composer le filtre de recherche
	CString strFileExt;
	GetPropSheet()->GetDataFileExt(strFileExt);
	strFileExt.LoadString(IDS_FILE_EXT);
	CString strFind = strAppDir + _T("\\*.") + strFileExt;

	CFileFind ff;
	if (!ff.FindFile(strFind)) 
		return;
	BOOL bNext;

	do 
	{
		bNext=ff.FindNextFile();

		// nom du fichier avec extension, sans le chemin 
		CString strFileName = ff.GetFileName();

		// chemin complet du fichier
		//CString strPathName = strAppDir+_T("\\")+strFileName;

		// nom sans extension
		strFileName = strFileName.Left(strFileName.ReverseFind('.'));

		// ajouter le nom sans extension à la combo
		int j=m_comboDataFile.AddString(strFileName);
		ASSERT(j!=CB_ERR);
		strFileName.ReleaseBuffer();
	} while (bNext);
}

BEGIN_MESSAGE_MAP(CPageData, CPropPageEx)
	ON_EN_CHANGE(IDC_EDIT_COMMENT, &CPageData::OnEnChangeEditComment)
	ON_CBN_SELCHANGE(IDC_COMBO_DATAFILE, &CPageData::OnCbnSelchangeComboDatafile)
END_MESSAGE_MAP()

void CPageData::SetControlsPos()
{
	CRect rc;
	GetClientRect(rc);
	int cxClient=rc.Width();
	int cyClient=rc.Height();
	int cxMargin=::GetSystemMetrics(SM_CXEDGE);
	int cxControls=cxClient-2*cxMargin;

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER;

	m_staticDataFile.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticDataFile.SetWindowPos(NULL, cxMargin, rc.top, cxControls, rc.Height(), uFlags);

	m_comboDataFile.GetWindowRect(rc);
	ScreenToClient(rc);
	// fixe la hauteur de la combo déroulée pour qu'elle arrive en bas de la page
	m_comboDataFile.SetWindowPos(NULL, cxMargin, rc.top, cxControls, cyClient-rc.top, uFlags);

	m_staticComment.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticComment.SetWindowPos(NULL, cxMargin, rc.top, cxControls, rc.Height(), uFlags);

	m_editComment.GetWindowRect(rc);
	ScreenToClient(rc);
	m_editComment.SetWindowPos(NULL, cxMargin, rc.top, cxControls, cyClient-rc.top-GetSystemMetrics(SM_CYEDGE), uFlags);
}

void CPageData::OnEnChangeEditComment()
{
	GetDlgItemText(IDC_EDIT_COMMENT, m_pData->m_strComment);
	m_pData->SetModifiedFlag(TRUE);
}

void CPageData::OnCbnSelchangeComboDatafile()
{
	int nCurSel=m_comboDataFile.GetCurSel();
	if(nCurSel==LB_ERR)
		return;

	CString strFileName;
	m_comboDataFile.GetLBText(nCurSel, strFileName);

	CPropSheetEx* pSheet=(CPropSheetEx*)GetParent();

	// crée le path complet
	CString strFolder;
	pSheet->GetDataFolder(strFolder);
	CString strExt;
	pSheet->GetDataFileExt(strExt);
	CString strFilePath=strFolder+_T("\\")+strFileName+_T(".")+strExt;
	pSheet->Data_FileRead(strFilePath);
	
	SetDlgItemText(IDC_EDIT_COMMENT, m_pData->m_strComment);
}

void CPageData::UpdateControlsStyles()
{
	// combo désactivée si pas de données ou si mode édition
	if(m_comboDataFile.GetCount()<1 || GetEditMode())
		m_comboDataFile.EnableWindow(FALSE);
	else
		m_comboDataFile.EnableWindow(TRUE);

	m_editComment.SetReadOnly(!GetEditMode());
	m_editComment.EnableWindow(GetEditMode());
}

