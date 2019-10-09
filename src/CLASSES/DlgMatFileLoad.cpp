// DlgMatFlieLoad.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DlgMatFileLoad.h"
#include "CLASSES_rc.h"
#include "CEFileFind.h"
#include "Data.h"
#include "CLASSES_rc.h"

// Boîte de dialogue CDlgMatFileLoad

IMPLEMENT_DYNAMIC(CDlgMatFileLoad, CCEDialog)


CDlgMatFileLoad::CDlgMatFileLoad(CWnd* pParent /*=NULL*/)
	: CCEDialog(CLASSES_IDD_MATFILE_LOAD, pParent)
	, m_strFileName(_T(""))
	, m_strFileExt(_T(""))
{
	m_nStyle=CEMB_OKCANCEL;
}

CDlgMatFileLoad::~CDlgMatFileLoad()
{
}

void CDlgMatFileLoad::DoDataExchange(CDataExchange* pDX)
{
	CCEDialog::DoDataExchange(pDX);
	DDX_Control(pDX, CLASSES_IDC_LISTBOX_MATFILE, m_listboxFileName);
}


BEGIN_MESSAGE_MAP(CDlgMatFileLoad, CCEDialog)
	ON_LBN_SELCHANGE(CLASSES_IDC_LISTBOX_MATFILE, &CDlgMatFileLoad::OnLbnSelchangeListboxMatFile)
END_MESSAGE_MAP()


// Gestionnaires de messages de CDlgMatFileLoad

BOOL CDlgMatFileLoad::OnInitDialog()
{
	CCEDialog::OnInitDialog();

	CToolBarCtrl&	tb = m_wndCommandBar.GetToolBarCtrl();
	tb.EnableButton(IDOK, FALSE);

	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strFind = strAppDir + _T("\\*.") + m_strFileExt;

	CCEFileFind ff;
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

	m_listboxFileName.SetCurSel(0);

	// problème : appalle le constructeur du fichier de données
	OnLbnSelchangeListboxMatFile();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CDlgMatFileLoad::OnLbnSelchangeListboxMatFile()
{
	int nCurSel=m_listboxFileName.GetCurSel();
	ASSERT(nCurSel!=LB_ERR);
	m_listboxFileName.GetText(nCurSel, m_strFileName);
	//SetDlgItemText(CLASSES_IDC_EDIT_MATFILE, m_strFileName);

	CData data;
	data.SetFileExt(m_strFileExt);
	data.FileRead(m_strFileName);
	SetDlgItemText(CLASSES_IDC_EDIT_COMMENT, data.m_strComment);

	// activer le bouton ok
	CToolBarCtrl&	tb = m_wndCommandBar.GetToolBarCtrl();
	tb.EnableButton(IDOK, TRUE);
}

