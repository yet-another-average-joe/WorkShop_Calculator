#pragma once

#include "PropPageEx.h"

class CDataToolDb;

// Boîte de dialogue CPageMementoDrill

class CPageMementoDrill : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageMementoDrill)

public:
	CPageMementoDrill(CData* pData);
	virtual ~CPageMementoDrill();

protected:
	virtual void UpdatePage();

protected:
// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_MEMENTO };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
