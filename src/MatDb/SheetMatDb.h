#pragma once

#include "PropSheetEx.h"
#include "PageData.h"
#include "PageCat.h"
#include "PageAlloy.h"
#include "PageSearch.h"
#include "DataMatDb.h"

// Boîte de dialogue CSheetMatDb

class CSheetMatDb : public CPropSheetEx
{
	DECLARE_DYNAMIC(CSheetMatDb)

public:
	CSheetMatDb(UINT iSelectPage = 0);   // constructeur standard
	virtual ~CSheetMatDb();
	void GetDataFileExt(CString& strExt);

protected:
	CPageData*		m_pPageData;
	CPageCat*		m_pPageCat;
	CPageAlloy*		m_pPageAlloy;
	CPageSearch*	m_pPageSearch;

	DECLARE_MESSAGE_MAP()
};
