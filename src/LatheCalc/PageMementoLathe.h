#pragma once

#include "PropPageEx.h"

// Bo�te de dialogue CPageMementoTurning

class CPageMementoTurning : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageMementoTurning)

public:
	CPageMementoTurning(CData* pData=NULL);
	virtual ~CPageMementoTurning();

protected:
// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_MEMENTO };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
