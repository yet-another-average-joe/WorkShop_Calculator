#pragma once

#include "EditDecimal.h"
#include "PageCondBase2.h"

// Boîte de dialogue CPageCondDrill

class CPageCondDrill : public CPageCondBase2
{
	DECLARE_DYNAMIC(CPageCondDrill)

public:
	CPageCondDrill(CData* pData);
	virtual ~CPageCondDrill();

protected:
// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_COND };

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
};
