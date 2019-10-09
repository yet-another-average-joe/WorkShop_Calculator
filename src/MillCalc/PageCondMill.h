#pragma once

#include "EditDecimal.h"
#include "PageCondBase2.h"

// Boîte de dialogue CPageCondMill

class CPageCondMill : public CPageCondBase2
{
	DECLARE_DYNAMIC(CPageCondMill)

public:
	CPageCondMill(CData* pData);
	virtual ~CPageCondMill();

protected:
// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_COND };

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
};
