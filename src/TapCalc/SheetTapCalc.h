// SheetTapCalc.h : fichier d'en-tête
//

#pragma once

#include "SheetCutCalc.h"

// CSheetTapCalc

class CSheetTapCalc : public CSheetCutCalc
{
	DECLARE_DYNAMIC(CSheetTapCalc)

public:

	CSheetTapCalc(UINT iSelectPage = 0);
	virtual ~CSheetTapCalc();

	virtual CPageCondBase* CreatePageCond(CData* pData);
	virtual CPageCalcBase* CreatePageCalc(CData* pData);
	virtual CPropPageEx* CreatePageMemento(CData* pData);

protected:

	DECLARE_MESSAGE_MAP()
public:
};

