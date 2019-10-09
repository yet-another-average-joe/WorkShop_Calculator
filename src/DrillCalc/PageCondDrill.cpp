// PageCond.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "DrillCalc.h"
#include "PageCondDrill.h"
#include "CLASSES_rc.h"

// les champs vides sont cach�s ou simplement d�saciv�s

// Bo�te de dialogue CPageCondDrill

IMPLEMENT_DYNAMIC(CPageCondDrill, CPageCondBase2)

CPageCondDrill::CPageCondDrill(CData* pData)
	: CPageCondBase2(CPageCondDrill::IDD, pData)
{
	// il faut toujours �tre en mode scrollbars puisque la hauteur est fix�e
	// par le nombre de champs, m�me s'ils ne sont pas tous visibles
	// pour �viter l'�quivoque, voir ce que �a donne
	// en d�sactivant plut�t qu'en cachant les controles inutilis�s
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

