// SheetTapCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TapCalc.h"
#include "SheetTapCalc.h"
#include "PageCondTap.h"
#include "PageCalcTap.h"
#include "PageMementoTap.h"

// CSheetTapCalc

IMPLEMENT_DYNAMIC(CSheetTapCalc, CSheetCutCalc)

CSheetTapCalc::CSheetTapCalc(UINT iSelectPage /*= 0*/):
	CSheetCutCalc(IDS_FILE_EXT, iSelectPage)
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

		m_pPageCalc=new CPageCalcTap(m_pData);
		AddPage(m_pPageCalc);

		m_pPageMemento=new CPageMementoTapping(m_pData);
		AddPage(m_pPageMemento);
	}
}

CSheetTapCalc::~CSheetTapCalc()
{
}

BEGIN_MESSAGE_MAP(CSheetTapCalc, CSheetCutCalc)
END_MESSAGE_MAP()

CPageCondBase* CSheetTapCalc::CreatePageCond(CData* pData)
{
	return new CPageCondTap(pData);
}
CPageCalcBase* CSheetTapCalc::CreatePageCalc(CData* pData)
{
	return new CPageCalcTap(pData);
}

CPropPageEx* CSheetTapCalc::CreatePageMemento(CData* pData)
{
	return new CPageMementoTapping(pData);
}


// Gestionnaires de messages de CSheetTapCalc



