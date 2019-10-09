#pragma once

#include "PropPageEx.h"

// Boîte de dialogue CPageMementoTapping

class CPageMementoTapping : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageMementoTapping)

public:
	CPageMementoTapping(CData* pData=NULL);
	virtual ~CPageMementoTapping();

protected:
	virtual void OnChangeEditMode() {}
// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_MEMENTO };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
