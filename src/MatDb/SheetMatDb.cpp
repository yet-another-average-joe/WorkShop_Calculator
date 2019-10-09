// MatDbSheet.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MatDb.h"
#include "SheetMatDb.h"

// Boîte de dialogue CSheetMatDb

IMPLEMENT_DYNAMIC(CSheetMatDb, CPropSheetEx)


// retourne l'extension de fichier
void CSheetMatDb::GetDataFileExt(CString& strExt)
{
	strExt.LoadString(IDS_FILE_EXT);
}


CSheetMatDb::CSheetMatDb(UINT iSelectPage /*= 0*/)
	: CPropSheetEx(iSelectPage)
{
	// dossier des fichiers de donnes = dossier de l'application
	CString strFolder;
	::GetModuleFileName(NULL, strFolder.GetBuffer(_MAX_PATH), _MAX_PATH);
	strFolder.ReleaseBuffer();
	strFolder = strFolder.Left(strFolder.ReverseFind('\\'));

	// extension de fichier = "mtl"
	CString strFileExt;
	strFileExt.LoadString(IDS_FILE_EXT);

	m_pData = new CDataMatDb;

	//m_pData->m_strFolder=strFolder;
	//m_pData->m_strFileExt=strFileExt;

	m_pPageData = new CPageData(m_pData);
	m_pPageCat = new CPageCat(m_pData);
	m_pPageAlloy = new CPageAlloy(m_pData);
	m_pPageSearch = new CPageSearch(m_pData);

	AddPage(m_pPageData);
	AddPage(m_pPageCat);
	AddPage(m_pPageAlloy);
	AddPage(m_pPageSearch);

	SetEditMode(FALSE);
}

CSheetMatDb::~CSheetMatDb()
{
	delete m_pPageData;
	delete m_pPageCat;
	delete m_pPageAlloy;
	delete m_pPageSearch;
	delete m_pData;
}

BEGIN_MESSAGE_MAP(CSheetMatDb, CPropSheetEx)
END_MESSAGE_MAP()
