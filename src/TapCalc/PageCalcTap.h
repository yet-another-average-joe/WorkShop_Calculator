#pragma once

#include "ComboDecimal.h"
#include "PageCalcbase.h"
#include "afxwin.h"

// Bo�te de dialogue CPageCalcTap

class CPageCalcTap : public CPageCalcBase
{
	DECLARE_DYNAMIC(CPageCalcTap)

public:
	CPageCalcTap(CData* pData=NULL);
	virtual ~CPageCalcTap();

protected:
// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_CALC };

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
};


