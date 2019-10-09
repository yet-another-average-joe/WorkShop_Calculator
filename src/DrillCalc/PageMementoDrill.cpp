// PageMemento.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DrillCalc.h"
#include "PageMementoDrill.h"


// Boîte de dialogue CPageMementoDrill

IMPLEMENT_DYNAMIC(CPageMementoDrill, CPropPageEx)

CPageMementoDrill::CPageMementoDrill(CData* pData)
	: CPropPageEx(CPageMementoDrill::IDD, pData)
{
	EnableScrollbars(TRUE);
}

CPageMementoDrill::~CPageMementoDrill()
{
}

void CPageMementoDrill::UpdatePage()
{
}

void CPageMementoDrill::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageMementoDrill, CPropPageEx)
END_MESSAGE_MAP()


