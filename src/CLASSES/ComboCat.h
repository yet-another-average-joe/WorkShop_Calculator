#pragma once

#include "ComboEx.h"
#include "DataMatDb.h"
// CComboCat

class CComboCat : public CComboEx
{
	DECLARE_DYNAMIC(CComboCat)

public:
	CComboCat();
	virtual ~CComboCat();

	void SetCatList(CListCat* pListCat);
	CCat* GetCat(int nIndex) { return (CCat*) GetItemDataPtr(nIndex); }

protected:
	DECLARE_MESSAGE_MAP()
};
