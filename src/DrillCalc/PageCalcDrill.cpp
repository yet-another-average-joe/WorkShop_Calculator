// PageCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DrillCalc.h"
#include "PageCalcDrill.h"
#include "CLASSES_rc.h"
#include "CLASSES.h"

// Boîte de dialogue CPageCalcDrill

IMPLEMENT_DYNAMIC(CPageCalcDrill, CPageCalcBase2)

CPageCalcDrill::CPageCalcDrill(CData* pData)
	: CPageCalcBase2(CPageCalcDrill::IDD, pData)
{
}

CPageCalcDrill::~CPageCalcDrill()
{
}

void CPageCalcDrill::DoDataExchange(CDataExchange* pDX)
{
	CPageCalcBase2::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPageCalcDrill, CPageCalcBase2)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageCalcDrill


