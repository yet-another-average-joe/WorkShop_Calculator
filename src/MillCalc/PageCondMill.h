#pragma once

#include "EditDecimal.h"
#include "PageCondBase2.h"

// Bo�te de dialogue CPageCondMill

class CPageCondMill : public CPageCondBase2
{
	DECLARE_DYNAMIC(CPageCondMill)

public:
	CPageCondMill(CData* pData);
	virtual ~CPageCondMill();

protected:
// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_COND };

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
};
