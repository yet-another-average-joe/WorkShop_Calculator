// SheetLatheCalc.h : fichier d'en-tête
//

#pragma once

#include "SheetCutCalc.h"

// CSheetLatheCalc

class CSheetLatheCalc : public CSheetCutCalc
{
	DECLARE_DYNAMIC(CSheetLatheCalc)

public:

	CSheetLatheCalc(UINT iSelectPage = 0);
	virtual ~CSheetLatheCalc();

	virtual CPageCondBase* CreatePageCond(CData* pData);
	virtual CPageCalcBase* CreatePageCalc(CData* pData);
	virtual CPropPageEx* CreatePageMemento(CData* pData);

protected:

	DECLARE_MESSAGE_MAP()
public:
};

