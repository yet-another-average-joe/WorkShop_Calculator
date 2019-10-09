#pragma once

#include "PropPageEx.h"

class CDataToolDb;

// Boîte de dialogue CPageMementoMill

class CPageMementoMill : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageMementoMill)

public:
	CPageMementoMill(CData* pData);
	virtual ~CPageMementoMill();

protected:
	virtual void UpdatePage();

protected:
// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_MEMENTO };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
