// SheetParseCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ParserCalc.h"
#include "SheetParseCalc.h"


// CSheetParseCalc

IMPLEMENT_DYNAMIC(CSheetParseCalc, CPropSheetEx)

CSheetParseCalc::CSheetParseCalc(UINT iSelectPage /*=0*/)
	:CPropSheetEx(iSelectPage)
{
	m_pData=NULL;

	//m_pPageData = new CPageData(m_pData);
	m_pPageCalc = new CPageCalc(m_pData);
	//m_pPageConst= new CPageConst(m_pData);

	//AddPage(m_pPageData);
	AddPage(m_pPageCalc);
	//AddPage(m_pPageConst);
}

CSheetParseCalc::~CSheetParseCalc()
{
	delete m_pPageCalc;
	//delete m_pPageConst;
}


BEGIN_MESSAGE_MAP(CSheetParseCalc, CPropSheetEx)
END_MESSAGE_MAP()


// Gestionnaires de messages de CSheetParseCalc
