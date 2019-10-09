#pragma once

#include "EditDecimal.h"
#include "PageCondBase.h"

// Boîte de dialogue CPageCondTap

class CPageCondTap : public CPageCondBase
{
	DECLARE_DYNAMIC(CPageCondTap)

public:
	CPageCondTap(CData* pData=NULL);
	virtual ~CPageCondTap();

protected:

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_COND };

	DECLARE_MESSAGE_MAP()
};
