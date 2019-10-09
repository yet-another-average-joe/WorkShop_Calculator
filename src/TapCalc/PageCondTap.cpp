// PageCondTurning.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TapCalc.h"
#include "PageCondTap.h"
#include "CLASSES_rc.h"
//#include "SheetTapCalc.h"

// les champs vides sont cachés ou simplement désacivés

// Boîte de dialogue CPageCondTap

// A FAIRE :
// mmm

IMPLEMENT_DYNAMIC(CPageCondTap, CPageCondBase)

CPageCondTap::CPageCondTap(CData* pData/*=NULL*/)
	: CPageCondBase(CPageCondTap::IDD, pData)
{
	EnableScrollbars(FALSE);
}

CPageCondTap::~CPageCondTap()
{
}

BEGIN_MESSAGE_MAP(CPageCondTap, CPageCondBase)
END_MESSAGE_MAP()


