// PageCondTurning.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "TapCalc.h"
#include "PageCondTap.h"
#include "CLASSES_rc.h"
//#include "SheetTapCalc.h"

// les champs vides sont cach�s ou simplement d�saciv�s

// Bo�te de dialogue CPageCondTap

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


