// PageCond.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MillCalc.h"
#include "PageCondMill.h"

// Boîte de dialogue CPageCondMill

IMPLEMENT_DYNAMIC(CPageCondMill, CPageCondBase2)

CPageCondMill::CPageCondMill(CData* pData)
	: CPageCondBase2(CPageCondMill::IDD, pData)
{
	// il faut toujours être en mode scrollbars puisque la hauteur est fixée
	// par le nombre de champs, même s'ils ne sont pas tous visibles
	// pour éviter l'équivoque, voir ce que ça donne
	// en désactivant plutôt qu'en cachant les controles inutilisés
	EnableScrollbars(TRUE);
}

CPageCondMill::~CPageCondMill()
{
}

void CPageCondMill::DoDataExchange(CDataExchange* pDX)
{
	CPageCondBase2::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPageCondMill, CPageCondBase2)
END_MESSAGE_MAP()

// Gestionnaires de messages de CPageCondMill

