// SheetMillCalc.h : fichier d'en-tête
//

#pragma once

#include "SheetCutCalc.h"

// CSheetMillCalc

class CSheetMillCalc : public CSheetCutCalc
{
	DECLARE_DYNAMIC(CSheetMillCalc)

public:

	CSheetMillCalc(UINT iSelectPage = 0);
	virtual ~CSheetMillCalc();

	virtual CPageCondBase* CreatePageCond(CData* pData);
	virtual CPageCalcBase* CreatePageCalc(CData* pData);
	virtual CPropPageEx* CreatePageMemento(CData* pData);

protected:

	DECLARE_MESSAGE_MAP()
};
