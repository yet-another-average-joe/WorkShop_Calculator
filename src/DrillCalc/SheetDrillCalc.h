// SheetDrillCalc.h : fichier d'en-tête
//

#pragma once

#include "SheetCutCalc.h"

// CSheetDrillCalc

class CSheetDrillCalc : public CSheetCutCalc
{
	DECLARE_DYNAMIC(CSheetDrillCalc)

public:

	CSheetDrillCalc(UINT iSelectPage = 0);
	virtual ~CSheetDrillCalc();

	virtual CPageCondBase* CreatePageCond(CData* pData);
	virtual CPageCalcBase* CreatePageCalc(CData* pData);
	virtual CPropPageEx* CreatePageMemento(CData* pData);

protected:

	DECLARE_MESSAGE_MAP()
};


