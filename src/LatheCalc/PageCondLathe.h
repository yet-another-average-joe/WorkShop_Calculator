#pragma once

#include "EditDecimal.h"
#include "PageCondBase.h"

// Bo�te de dialogue CPageCondLathe

class CPageCondLathe : public CPageCondBase
{
	DECLARE_DYNAMIC(CPageCondLathe)

public:
	CPageCondLathe(CData* pData=NULL);
	virtual ~CPageCondLathe();

protected:
	virtual void SetControlsPos();

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_COND };

	DECLARE_MESSAGE_MAP()

public:
};
