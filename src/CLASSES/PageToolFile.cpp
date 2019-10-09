// PageData.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "PageToolFile.h"
#include "CEFileFind.h"
#include "DataToolDb.h"
#include "DlgCatMissing.h"
#include "SheetCutCalc.h"

// Boîte de dialogue CPageToolFile

IMPLEMENT_DYNCREATE(CPageToolFile, CPropPageEx)

CPageToolFile::CPageToolFile()
	: CPropPageEx(CPageToolFile::IDD, NULL)
{
	EnableScrollbars(TRUE);
	m_comboToolFile.SetFullDrop(TRUE);
	m_editToolFileComment.m_bNoGray=TRUE;
	m_editMatFile.m_bNoGray=TRUE;
	m_editMatFileComment.m_bNoGray=TRUE;
}

CPageToolFile::CPageToolFile(CData* pData)
	: CPropPageEx(CPageToolFile::IDD, pData)
{
	EnableScrollbars(TRUE);
	m_comboToolFile.SetFullDrop(TRUE);
	m_editToolFileComment.m_bNoGray=TRUE;
	m_editMatFile.m_bNoGray=TRUE;
	m_editMatFileComment.m_bNoGray=TRUE;
}

CPageToolFile::~CPageToolFile()
{
}

void CPageToolFile::ResetPage()
{
	if(!m_fDoneDDE)
		return;

	m_comboToolFile.ResetContent();
	m_comboToolFile.SetFocus(); // semble ne pas fonctionner !
	m_comboToolFile.SetCurSel(-1);
	UpdateFileList();
	CString str;
	m_pData->GetFileName(str);
	if(!str.IsEmpty())
		Combo_SelectFileName(str);

	if(m_comboToolFile.GetCount()>0)
	{
		m_comboToolFile.SetCurSel(0);
		OnCbnSelchangeComboToolFile();
	}

	SetDlgItemText(CLASSES_IDC_EDIT_TOOLFILE_COMMENT, m_pData->m_strComment);
}

void CPageToolFile::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
	DDX_Control(pDX, CLASSES_IDC_STATIC_TOOLFILE, m_staticToolFile);
	DDX_Control(pDX, CLASSES_IDC_COMBO_TOOLFILE, m_comboToolFile);
	DDX_Control(pDX, CLASSES_IDC_STATIC_TOOLFILE_COMMENT, m_staticToolFileComment);
	DDX_Control(pDX, CLASSES_IDC_EDIT_TOOLFILE_COMMENT, m_editToolFileComment);
	DDX_Control(pDX, CLASSES_IDC_STATIC_MATFILE, m_staticMatFile);
	DDX_Control(pDX, CLASSES_IDC_EDIT_MATFILE, m_editMatFile);
	DDX_Control(pDX, CLASSES_IDC_STATIC_MATFILE_COMMENT, m_staticMatFileComment);
	DDX_Control(pDX, CLASSES_IDC_EDIT_MATFILE_COMMENT, m_editMatFileComment);
}

BOOL CPageToolFile::OnInitDialog()
{
	CPropPageEx::OnInitDialog();

	m_comboToolFile.EnableWindow(TRUE);
	
	// jamais modifiable
	m_editMatFile.SetReadOnly(TRUE);
	m_editMatFile.EnableWindow(FALSE);

	// jamais modifiable
	m_editMatFileComment.SetReadOnly(TRUE);
	m_editMatFileComment.EnableWindow(FALSE);

	// Au démarrage, charger le premier fichier le la liste
	UpdateFileList();

	m_comboToolFile.SetCurSel(0);
	OnCbnSelchangeComboToolFile();

	CString str;
	Data_GetMatFileName(str);
	m_editMatFile.SetWindowText_NoNotify(str);
	str=_T("");
	Data_GetMatFileComment(str);
	m_editMatFileComment.SetWindowText_NoNotify(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

BEGIN_MESSAGE_MAP(CPageToolFile, CPropPageEx)
	ON_CBN_SELCHANGE(CLASSES_IDC_COMBO_TOOLFILE, &CPageToolFile::OnCbnSelchangeComboToolFile)
	ON_EN_CHANGE(CLASSES_IDC_EDIT_TOOLFILE_COMMENT, &CPageToolFile::OnEnChangeEditCommentToolFile)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageToolFile

void CPageToolFile::UpdateFileList()
{

	m_comboToolFile.ResetContent();

	// remplir la combo avec les noms des fichiers valides

	CSheetCutCalc* pSheet=(CSheetCutCalc*)GetParent();
	pSheet->ListValidToolFiles();
	POSITION pos=pSheet->m_listToolFileName.GetHeadPosition();
	while(pos)
	{
		CString str=pSheet->m_listToolFileName.GetNext(pos);
		m_comboToolFile.AddString(str);
	}
}

void CPageToolFile::OnCbnSelchangeComboToolFile()
{
	ASSERT(m_pData!=NULL);
	int nCurSel=m_comboToolFile.GetCurSel();
	if(nCurSel==LB_ERR) // se produit si nouveau fichier d'outils
	{
		CString str;
		str=_T("");
		Data_GetMatFileName(str); 
		m_editMatFile.SetWindowText_NoNotify(str);
		str=_T("");
		Data_GetMatFileComment(str); // str non renseigné si vide
		m_editMatFileComment.SetWindowText_NoNotify(str);

		Data_Cat_SetCurSel(Data_Cat_GetHead());
	}
	else
	{
		CString strFileName;
		m_comboToolFile.GetLBText(nCurSel, strFileName);

		m_pData->FileRead(strFileName);
		
		CString str;
		m_pData->GetFileName(str);
		m_comboToolFile.SelectString(0, str);
		m_editToolFileComment.SetWindowText_NoNotify(m_pData->m_strComment);
		str=_T("");
		Data_GetMatFileName(str);
		m_editMatFile.SetWindowText_NoNotify(str);
		str=_T("");
		Data_GetMatFileComment(str); // str non renseigné si vide
		m_editMatFileComment.SetWindowText_NoNotify(str);

		//Data_Cat_SetCurSel(Data_Cat_GetHead());
		//Data_Cat_SetCurSel(Data_Cat_GetCurSel());

		if(Data_Cat_GetMissingFlag())
		{
			CDlgCatMissing dlg;
			CString str;
			m_pData->GetFileName(str);
			dlg.m_strFileName=str;
			dlg.DoModal();

			// enregistrer (la base de données a été corrigée lors de la lecture)
			m_pData->FileSave();
			Data_Cat_SetMissingFlag(FALSE);
		}
	}
}

void CPageToolFile::SetControlsPos()
{
	CPropPageEx::SetControlsPos();

	CRect rc;
	GetClientRect(rc);
	int cxClient=rc.Width();
	int cyClient=rc.Height();
	int cxMargin=::GetSystemMetrics(SM_CXEDGE);
	int cxControls=cxClient-2*cxMargin;

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER;

	m_staticToolFile.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticToolFile.SetWindowPos(NULL, cxMargin, rc.top, cxControls,rc.Height(), uFlags);

	m_comboToolFile.GetWindowRect(rc);
	ScreenToClient(rc);
	m_comboToolFile.SetWindowPos(NULL, cxMargin, rc.top, cxControls, rc.Height(), uFlags);

	m_staticToolFileComment.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticToolFileComment.SetWindowPos(NULL, cxMargin, rc.top, cxControls, rc.Height(), uFlags);

	m_editToolFileComment.GetWindowRect(rc);
	ScreenToClient(rc);
	m_editToolFileComment.SetWindowPos(NULL, cxMargin, rc.top, cxControls, rc.Height(), uFlags);

	m_staticMatFile.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticMatFile.SetWindowPos(NULL, cxMargin, rc.top, cxControls, rc.Height(), uFlags);

	m_editMatFile.GetWindowRect(rc);
	ScreenToClient(rc);
	m_editMatFile.SetWindowPos(NULL, cxMargin, rc.top, cxControls, rc.Height(), uFlags);

	m_staticMatFileComment.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticMatFileComment.SetWindowPos(NULL, cxMargin, rc.top, cxControls, rc.Height(), uFlags);

	m_editMatFileComment.GetWindowRect(rc);
	ScreenToClient(rc);
	m_editMatFileComment.SetWindowPos(NULL, cxMargin, rc.top, cxControls, rc.Height(), uFlags);
}

void CPageToolFile::OnEnChangeEditCommentToolFile()
{
	ASSERT(m_pData!=NULL);
	GetDlgItemText(CLASSES_IDC_EDIT_TOOLFILE_COMMENT, m_pData->m_strComment);
	m_pData->SetModifiedFlag(TRUE);
}

void CPageToolFile::UpdateControlsStyles()
{
	m_comboToolFile.EnableWindow(!GetEditMode());
	m_editToolFileComment.SetReadOnly(!GetEditMode());
	m_editToolFileComment.EnableWindow(GetEditMode());
}

void CPageToolFile::OnFileNew()
{
	m_comboToolFile.SetCurSel(-1);
	m_comboToolFile.EnableWindow(FALSE);
	m_editToolFileComment.SetWindowText_NoNotify(_T(""));
	
	// non renseignés ?
	// BUG : fichier de matières pas mis à jour sur page "Fichier"
	// tentative de correction 27/07/2013
	// semble ok
	CString str;
	Data_GetMatFileName(str);
	SetDlgItemText(CLASSES_IDC_EDIT_MATFILE, str);
	str=_T("");
	Data_GetMatFileComment(str);
	m_editMatFileComment.SetWindowText_NoNotify(str);
	// focus sur champ commentaire
	m_editToolFileComment.SetFocus();
}

void CPageToolFile::OnFileSave()
{
	m_editToolFileComment.SetReadOnly(FALSE);
	m_comboToolFile.ResetContent(); // redondant : reset dans UpdateFileList()

	UpdateFileList();

	if(m_comboToolFile.GetCount()!=CB_ERR)
	{
		CString str;
		m_pData->GetFileName(str);
		ASSERT(!str.IsEmpty());
		Combo_SelectFileName(str);
		OnCbnSelchangeComboToolFile();
	}
}

void CPageToolFile::OnFileSaveAs()
{
	OnFileSave();
}

void CPageToolFile::OnFileSaveCopyAs()
{
	OnFileSave();
}

