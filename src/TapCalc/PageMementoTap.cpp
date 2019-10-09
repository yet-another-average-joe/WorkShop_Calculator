// PageMementoTurning.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TapCalc.h"
#include "PageMementoTap.h"


// Boîte de dialogue CPageMementoTapping

IMPLEMENT_DYNAMIC(CPageMementoTapping, CPropPageEx)


CPageMementoTapping::CPageMementoTapping(CData* pData/*=NULL*/)
	: CPropPageEx(CPageMementoTapping::IDD, pData)
{
	EnableScrollbars(TRUE);
}

CPageMementoTapping::~CPageMementoTapping()
{
}

void CPageMementoTapping::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageMementoTapping, CPropPageEx)
END_MESSAGE_MAP()


