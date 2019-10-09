// SheetTapCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "SheetCutCalc.h"
#include "DlgMatFileLoad.h"
#include "DlgNoToolFile.h"
#include "DlgNoMatFile.h"
#include "PageCondBase.h"
#include "PageCalcBase.h"
#include "CEFileFind.h"

#define IDS_FILE_EXT 133

// #define USE_MOVEWINDOW SetWindowPos obligatoire pour placer le slider au dessus du reste !


void CSheetCutCalc::LoadData(const CString& strPath)
{
	CFile file(strPath, CFile::modeRead); 
	CArchive ar(&file, CArchive::load);
	ASSERT(m_pData!=NULL);
	m_pData->Serialize(ar);
	file.Close();

}

// CSheetCutCalc

IMPLEMENT_DYNAMIC(CSheetCutCalc, CPropSheetEx)

CSheetCutCalc::CSheetCutCalc(UINT m_nIdFileExt, UINT iSelectPage /*= 0*/):
	CPropSheetEx(iSelectPage),
		m_nIdFileExt(m_nIdFileExt)
{
	// établir la liste des noms de fichiers d'outils valides
	ListValidToolFiles();

	if(m_listToolFileName.IsEmpty())
	{
		// fichier de données non trouvé : ajouter Calc et Memento
		CDlgNoToolFile dlg;
		dlg.DoModal();
	}

	m_pData=NULL;

	m_pPageToolFile=NULL;
	m_pPageTool=NULL;
	m_pPageCond=NULL;
	m_pPageCalc=NULL;
	m_pPageMemento=NULL;
}

void CSheetCutCalc::ListValidToolFiles()
{
	CWaitCursor wait;

	// remplir la listbox avec les noms de fichiers outils présents dans le dossier de l'application
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strFileExt;
	strFileExt.LoadString(m_nIdFileExt);
	CString strFind = strAppDir + _T("\\*.") + strFileExt;

	TRACE(_T("CSheetCutCalc::ListValidToolFiles(%s)\n"), strFind);


	CFileFind ff;

	if (!ff.FindFile(strFind)) 
		return;

	BOOL bNext;

	// vider m_listToolFileName
	m_listToolFileName.RemoveAll();

	do 
	{
		// n'ajouter le fichier à la liste que s'il est valide
		bNext=ff.FindNextFile();
		CString strFileName = ff.GetFileName();

		CString strPathName = strAppDir+_T("\\")+strFileName;
		// nom sans extension
		strFileName = strFileName.Left(strFileName.ReverseFind('.'));

		// tenter de lire le fichier
		CDataToolDb* pData=new CDataToolDb;
		pData->SetFileExt(strFileExt);

		if(pData->FileRead(strFileName))
		{
			m_listToolFileName.AddTail(strFileName);
		}

		delete pData;

		//int j=m_comboToolFile.AddString(strFileName);
		//ASSERT(j!=CB_ERR);
		//strFileName.ReleaseBuffer();
	} while (bNext);
}

CSheetCutCalc::~CSheetCutCalc()
{
	if(m_pPageToolFile!=NULL)
		delete m_pPageToolFile;
	if(m_pPageTool!=NULL)
		delete m_pPageTool;
	if(m_pPageCond!=NULL)
		delete m_pPageCond;
	if(m_pPageCalc!=NULL)
		delete m_pPageCalc;
	if(m_pPageMemento!=NULL)
		delete m_pPageMemento;
	if(m_pData!=NULL)
		delete m_pData;
}

BEGIN_MESSAGE_MAP(CSheetCutCalc, CPropSheetEx)
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// Gestionnaires de messages de CSheetCutCalc

void CSheetCutCalc::OnFileNew()
{
	// vérifier présence d'un fichier d'outils
	// message d'erreur s'il n'y en a pas

	// s'il n'y a pas de fichier de matières : abandon
	if(!FindFile(CLASSES_IDS_MATFILE_EXT))
	{
		CDlgNoMatFile dlg(this);
		dlg.DoModal();
		return;
	}

	// charger un fichier de matières
	CDlgMatFileLoad dlg(this);
	dlg.m_strFileExt.LoadStringW(CLASSES_IDS_MATFILE_EXT);

	if(dlg.DoModal()==IDCANCEL)
		return;

	if(m_pData==NULL) // création d'un fichier à partir du mode "minimum"
	{
		// à ce stade, on a 2 pages : Calcul et Memento
		// on ne peut pas se contenter de Remove() / Add()
		// parce que les fenêtre n'existent plus après un Remove()
		// il faut donc les recréer

		// créer le fichier de données
		m_pData=new CDataToolDb();
		m_pData->SetFileExt(m_nIdFileExt);
		m_pData->New();
		((CDataToolDb*)m_pData)->LoadMaterials(dlg.m_strFileName);

		// créer et ajouter les 3 premières  pages
		
		m_fEditMode=TRUE;

		// page Fichier
		ASSERT(m_pPageToolFile==NULL);
		m_pPageToolFile=new CPageToolFile(m_pData);
		ASSERT(m_pPageToolFile!=NULL);
		AddPage(m_pPageToolFile);

		// page Outils
		ASSERT(m_pPageTool==NULL);
		m_pPageTool=new CPageTool(m_pData);
		ASSERT(m_pPageTool!=NULL);
		AddPage(m_pPageTool);

		// page Cond
		ASSERT(m_pPageCond==NULL);
		m_pPageCond=CreatePageCond(m_pData);
		ASSERT(m_pPageCond!=NULL);
		AddPage(m_pPageCond);

		// les deux pages suivantes sont toujours au début
		// donc les supprimer

		// supprimer la page Calc
		ASSERT(m_pPageCalc!=NULL);
		RemovePage(m_pPageCalc);
		delete m_pPageCalc;
		m_pPageCalc=NULL;

		// supprimer la page Memento
		ASSERT(m_pPageMemento!=NULL);
		RemovePage(m_pPageMemento);
		delete m_pPageMemento;
		m_pPageMemento=NULL;

		// créer une nouvelle page Calc, et la placer à la suite
		ASSERT(m_pPageCalc==NULL);
		m_pPageCalc=CreatePageCalc(m_pData);
		ASSERT(m_pPageCalc!=NULL);
		AddPage(m_pPageCalc);

		// créer une nouvelle page Memento, et la placer à la suite
		ASSERT(m_pPageMemento==NULL);
		m_pPageMemento=CreatePageMemento(m_pData);
		ASSERT(m_pPageMemento!=NULL);
		AddPage(m_pPageMemento);
	}
	else
	{
		m_fEditMode=TRUE;

		m_pData->New();
		((CDataToolDb*)m_pData)->LoadMaterials(dlg.m_strFileName);

		// toutes les pages existent déjà

		m_pPageToolFile->SetToolFileExt(IDS_FILE_EXT);
	}

	ASSERT(m_pPageToolFile!=NULL);
	m_pPageToolFile->OnFileNew();
}


void CSheetCutCalc::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CPropSheetEx::OnVScroll(nSBCode, nPos, pScrollBar);

	// renvoyer vers CPageCalcMill si elle est active

	CPropertyPage* pPage=GetActivePage();
	if(pPage==m_pPageCalc)
		m_pPageCalc->OnSlider(nSBCode, nPos);
	if(pPage==m_pPageCond)
		m_pPageCond->OnSlider(nSBCode, nPos);
}

void CSheetCutCalc::OnFileSave()
{
	CPropSheetEx::OnFileSave();
	ASSERT(m_pPageToolFile!=NULL);
	m_pPageToolFile->OnFileSave();
}

void CSheetCutCalc::OnFileSaveAs()
{
	CPropSheetEx::OnFileSaveAs();
	ASSERT(m_pPageToolFile!=NULL);
	m_pPageToolFile->OnFileSaveAs();
}

void CSheetCutCalc::OnFileSaveCopyAs()
{
	CPropSheetEx::OnFileSaveCopyAs();
	ASSERT(m_pPageToolFile!=NULL);
	m_pPageToolFile->OnFileSaveCopyAs();
}

