#pragma once

#include "PropPageEx.h"

// Bo�te de dialogue CPageMementoTapping

class CPageMementoTapping : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageMementoTapping)

public:
	CPageMementoTapping(CData* pData=NULL);
	virtual ~CPageMementoTapping();

protected:
	virtual void OnChangeEditMode() {}
// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_MEMENTO };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
