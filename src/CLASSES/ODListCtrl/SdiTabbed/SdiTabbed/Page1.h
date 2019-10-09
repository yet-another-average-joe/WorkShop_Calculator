#pragma once

#include "ScrollPage.h"

// Boîte de dialogue CPage1

class CPage1 : public CScrollPage
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1();   // constructeur standard
	virtual ~CPage1();

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
