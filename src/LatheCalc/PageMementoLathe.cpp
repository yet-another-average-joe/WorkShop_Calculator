// PageMementoTurning.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "LatheCalc.h"
#include "PageMementoLathe.h"


// Boîte de dialogue CPageMementoTurning

IMPLEMENT_DYNAMIC(CPageMementoTurning, CPropPageEx)


CPageMementoTurning::CPageMementoTurning(CData* pData/*=NULL*/)
	: CPropPageEx(CPageMementoTurning::IDD, pData)
{
	EnableScrollbars(TRUE);
}

CPageMementoTurning::~CPageMementoTurning()
{
}

void CPageMementoTurning::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageMementoTurning, CPropPageEx)
END_MESSAGE_MAP()


