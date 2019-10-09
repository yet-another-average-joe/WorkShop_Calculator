#pragma once

#include "EditDecimal.h"
#include "PageCondBase.h"

// Boîte de dialogue CPageCondLathe

class CPageCondLathe : public CPageCondBase
{
	DECLARE_DYNAMIC(CPageCondLathe)

public:
	CPageCondLathe(CData* pData=NULL);
	virtual ~CPageCondLathe();

protected:
	virtual void SetControlsPos();

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_COND };

	DECLARE_MESSAGE_MAP()

public:
};
