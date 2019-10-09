#pragma once

#include "DlgScroll.h"
#include "ComboDecimal.h"
#include "PageDimChild.h"

// Boîte de dialogue CPageDimMillimetric

class CPageDimMillimetric : public CPageDimChild
{
	DECLARE_DYNAMIC(CPageDimMillimetric)

public:
	CPageDimMillimetric(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CPageDimMillimetric();

// Données de boîte de dialogue
	enum { IDD = IDD_CHILD_DIM_MILLIMETRIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Implémentation
protected:
	virtual void Calculate();

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
//#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
//	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
//#endif

	DECLARE_MESSAGE_MAP()
};
