#pragma once

#include "ComboDecimal.h"
#include "PageCalcBase2.h"
#include "afxwin.h"

// Bo�te de dialogue CPageCalcDrill

class CPageCalcDrill : public CPageCalcBase2
{
	DECLARE_DYNAMIC(CPageCalcDrill)

public:
	CPageCalcDrill(CData* pData);
	virtual ~CPageCalcDrill();


protected:
// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_CALC };

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
};

