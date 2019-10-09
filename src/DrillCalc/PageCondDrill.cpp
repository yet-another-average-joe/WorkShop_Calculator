// PageCond.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DrillCalc.h"
#include "PageCondDrill.h"
#include "CLASSES_rc.h"

// les champs vides sont cachés ou simplement désacivés

// Boîte de dialogue CPageCondDrill

IMPLEMENT_DYNAMIC(CPageCondDrill, CPageCondBase2)

CPageCondDrill::CPageCondDrill(CData* pData)
	: CPageCondBase2(CPageCondDrill::IDD, pData)
{
	// il faut toujours être en mode scrollbars puisque la hauteur est fixée
	// par le nombre de champs, même s'ils ne sont pas tous visibles
	// pour éviter l'équivoque, voir ce que ça donne
	// en désactivant plutôt qu'en cachant les controles inutilisés
	EnableScrollbars(TRUE);
}

CPageCondDrill::~CPageCondDrill()
{
}

void CPageCondDrill::DoDataExchange(CDataExchange* pDX)
{
	CPageCondBase2::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageCondDrill, CPageCondBase2)
END_MESSAGE_MAP()

// Gestionnaires de messages de CPageCondDrill

