#pragma once

#include "DlgScroll.h"
#include "ComboDecimal.h"
#include "PageDimChild.h"

// Boîte de dialogue CPageDimMetric

class CPageDimMetric : public CPageDimChild
{
	DECLARE_DYNAMIC(CPageDimMetric)

public:
	CPageDimMetric(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CPageDimMetric();

// Données de boîte de dialogue
	enum { IDD = IDD_CHILD_DIM_METRIC };

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
