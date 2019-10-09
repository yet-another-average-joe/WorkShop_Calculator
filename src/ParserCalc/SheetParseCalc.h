#pragma once

#include "PropSheetEx.h"
#include "PageCalc.h"

// CSheetParseCalc

class CSheetParseCalc : public CPropSheetEx
{
	DECLARE_DYNAMIC(CSheetParseCalc)

public:
	CSheetParseCalc(UINT iSelectPage = 0);
	virtual ~CSheetParseCalc();

protected:
	CPageCalc*	m_pPageCalc;
	DECLARE_MESSAGE_MAP()
};


