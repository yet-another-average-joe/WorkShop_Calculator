#pragma once

#include "PropPageEx.h"

class CDataToolDb;

// Bo�te de dialogue CPageMementoMill

class CPageMementoMill : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageMementoMill)

public:
	CPageMementoMill(CData* pData);
	virtual ~CPageMementoMill();

protected:
	virtual void UpdatePage();

protected:
// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_MEMENTO };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
