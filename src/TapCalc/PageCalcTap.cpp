// PageCalcTap.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "TapCalc.h"
#include "PageCalcTap.h"
#include "SheetTapCalc.h"


// Bo�te de dialogue CPageCalcTap

IMPLEMENT_DYNAMIC(CPageCalcTap, CPageCalcBase)

CPageCalcTap::CPageCalcTap(CData* pData/*=NULL*/)
	: CPageCalcBase(CPageCalcTap::IDD, pData)
{
}

CPageCalcTap::~CPageCalcTap()
{
}

void CPageCalcTap::DoDataExchange(CDataExchange* pDX)
{
	CPageCalcBase::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPageCalcTap, CPageCalcBase)
END_MESSAGE_MAP()

// Gestionnaires de messages de CPageCalcTap

