// DrillCalcSheet.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DrillCalc.h"
#include "SheetDrillCalc.h"
#include "PageCondDrill.h"
#include "PageCalcDrill.h"
#include "PageMementoDrill.h"

//void CSheetDrillCalc::LoadData(const CString& strPath)
//{
//	CFile file(strPath, CFile::modeRead); 
//	CArchive ar(&file, CArchive::load);
//	ASSERT(m_pData!=NULL);
//	m_pData->Serialize(ar);
//	file.Close();
//}

// CSheetDrillCalc

IMPLEMENT_DYNAMIC(CSheetDrillCalc, CSheetCutCalc)

CSheetDrillCalc::CSheetDrillCalc(UINT iSelectPage /*= 0*/)
	: CSheetCutCalc(IDS_FILE_EXT, iSelectPage)
{
	// on peut appeler les fonctions virtuelles CreatePageXXX() ici
	// ce sont celles de la classe qui sont appelées (vues
	// comme non virtuelles)
	// ne pas déplacer ce code dans le constructeur d'une
	// classe dérivée !

	if(!m_listToolFileName.IsEmpty())
	{
		// fichier de donnée trouvé : ajouter les 5 pages
		m_pData=new CDataToolDb();
		m_pData->SetFileExt(m_nIdFileExt);
	
		m_pPageToolFile=new CPageToolFile(m_pData);
		m_pPageToolFile->SetToolFileExt(m_nIdFileExt);
		AddPage(m_pPageToolFile);
	
		m_pPageTool=new CPageTool(m_pData);
		AddPage(m_pPageTool);

		m_pPageCond=CreatePageCond(m_pData);
		AddPage(m_pPageCond);

		m_pPageCalc=CreatePageCalc(m_pData);
		AddPage(m_pPageCalc);

		m_pPageMemento=CreatePageMemento(m_pData);
		AddPage(m_pPageMemento);
	}
	else
	{
		// fichier de données non trouvé : ajouter Calc et Memento

		m_pData=NULL;

		m_pPageCalc=new CPageCalcDrill(m_pData);//CreatePageCalc(m_pData);
		AddPage(m_pPageCalc);

		m_pPageMemento=new CPageMementoDrill(m_pData);//CreatePageCond(m_pData);
		AddPage(m_pPageMemento);
	}
}

CSheetDrillCalc::~CSheetDrillCalc()
{
}

BEGIN_MESSAGE_MAP(CSheetDrillCalc, CSheetCutCalc)
END_MESSAGE_MAP()

CPageCondBase* CSheetDrillCalc::CreatePageCond(CData* pData)
{
	return new CPageCondDrill(pData);
}
CPageCalcBase* CSheetDrillCalc::CreatePageCalc(CData* pData)
{
	return new CPageCalcDrill(pData);
}

CPropPageEx* CSheetDrillCalc::CreatePageMemento(CData* pData)
{
	return new CPageMementoDrill(pData);
}

// Gestionnaires de messages de CSheetDrillCalc

