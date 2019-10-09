// SheetLatheCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "LatheCalc.h"
#include "SheetLatheCalc.h"
#include "PageCondLathe.h"
#include "PageCalcLathe.h"
#include "PageMementoLathe.h"
#include "DlgNoToolFile.h"

//CSheetLatheCalc::m_nIdFileExt=IDS_FILE_EXT;

// CSheetLatheCalc

IMPLEMENT_DYNAMIC(CSheetLatheCalc, CSheetCutCalc)

CSheetLatheCalc::CSheetLatheCalc(UINT iSelectPage /*= 0*/):
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

		m_pPageCalc=new CPageCalcLathe(m_pData);//CreatePageCalc(m_pData);
		AddPage(m_pPageCalc);

		m_pPageMemento=new CPageMementoTurning(m_pData);//CreatePageCond(m_pData);
		AddPage(m_pPageMemento);
	}
}

CSheetLatheCalc::~CSheetLatheCalc()
{
}

BEGIN_MESSAGE_MAP(CSheetLatheCalc, CSheetCutCalc)
END_MESSAGE_MAP()

CPageCondBase* CSheetLatheCalc::CreatePageCond(CData* pData)
{
	return new CPageCondLathe(pData);
}
CPageCalcBase* CSheetLatheCalc::CreatePageCalc(CData* pData)
{
	return new CPageCalcLathe(pData);
}

CPropPageEx* CSheetLatheCalc::CreatePageMemento(CData* pData)
{
	return new CPageMementoTurning(pData);
}


// Gestionnaires de messages de CSheetLatheCalc



