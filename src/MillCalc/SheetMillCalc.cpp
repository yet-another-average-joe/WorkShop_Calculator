// SheetMillCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MillCalc.h"
#include "SheetMillCalc.h"
#include "PageCondMill.h"
#include "PageCalcMill.h"
#include "PageMementoMill.h"

// CSheetMillCalc

IMPLEMENT_DYNAMIC(CSheetMillCalc, CSheetCutCalc)

CSheetMillCalc::CSheetMillCalc(UINT iSelectPage /*= 0*/)
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
	
		m_pPageTool=new CPageTool(m_pData, TRUE);
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

		m_pPageCalc=new CPageCalcMill(m_pData);//CreatePageCalc(m_pData);
		AddPage(m_pPageCalc);

		m_pPageMemento=new CPageMementoMill(m_pData);//CreatePageCond(m_pData);
		AddPage(m_pPageMemento);
	}
}

CSheetMillCalc::~CSheetMillCalc()
{
}

BEGIN_MESSAGE_MAP(CSheetMillCalc, CSheetCutCalc)
END_MESSAGE_MAP()

CPageCondBase* CSheetMillCalc::CreatePageCond(CData* pData)
{
	return new CPageCondMill(pData);
}
CPageCalcBase* CSheetMillCalc::CreatePageCalc(CData* pData)
{
	return new CPageCalcMill(pData);
}

CPropPageEx* CSheetMillCalc::CreatePageMemento(CData* pData)
{
	return new CPageMementoMill(pData);
}

// Gestionnaires de messages de CSheetMillCalc


