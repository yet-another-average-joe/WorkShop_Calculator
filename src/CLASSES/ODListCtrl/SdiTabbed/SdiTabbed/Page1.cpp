// Page1.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "SdiTabbed.h"
#include "Page1.h"


// Boîte de dialogue CPage1

IMPLEMENT_DYNAMIC(CPage1, CScrollPage)

CPage1::CPage1()
	: CScrollPage(CPage1::IDD)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CScrollPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage1, CScrollPage)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPage1
