// PageCond.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "MillCalc.h"
#include "PageCondMill.h"

// Bo�te de dialogue CPageCondMill

IMPLEMENT_DYNAMIC(CPageCondMill, CPageCondBase2)

CPageCondMill::CPageCondMill(CData* pData)
	: CPageCondBase2(CPageCondMill::IDD, pData)
{
	// il faut toujours �tre en mode scrollbars puisque la hauteur est fix�e
	// par le nombre de champs, m�me s'ils ne sont pas tous visibles
	// pour �viter l'�quivoque, voir ce que �a donne
	// en d�sactivant plut�t qu'en cachant les controles inutilis�s
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

