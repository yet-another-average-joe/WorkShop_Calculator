// PageMemento.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MillCalc.h"
#include "PageMementoMill.h"


// Boîte de dialogue CPageMementoMill

IMPLEMENT_DYNAMIC(CPageMementoMill, CPropPageEx)

CPageMementoMill::CPageMementoMill(CData* pData)
	: CPropPageEx(CPageMementoMill::IDD, pData)
{
	EnableScrollbars(TRUE);
}

CPageMementoMill::~CPageMementoMill()
{
}

void CPageMementoMill::UpdatePage()
{
}

void CPageMementoMill::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageMementoMill, CPropPageEx)
END_MESSAGE_MAP()


