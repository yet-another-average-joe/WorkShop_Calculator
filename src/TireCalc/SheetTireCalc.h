#pragma once

#include "PropSheetEx.h"

class CPageDim;
class CPageMisc;
class CPageMemento;
class CPageRatings;


// CSheetTireCalc

class CSheetTireCalc : public CPropSheetEx
{
	DECLARE_DYNAMIC(CSheetTireCalc)

public:
	CSheetTireCalc(UINT iSelectPage = 0);
	virtual ~CSheetTireCalc();

protected:
	CPageDim* m_pPageDim;
	CPageRatings* m_pPageRatings;
	CPageMisc* m_pPageMisc;
	CPageMemento* m_pPageMemento;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuOdometer();
};


