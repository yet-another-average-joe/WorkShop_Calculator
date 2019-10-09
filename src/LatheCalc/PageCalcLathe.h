#pragma once

#include "ComboDecimal.h"
#include "PageCalcbase.h"

// Boîte de dialogue CPageCalcLathe
//
// problème de calcul : la relation D / Vc / N doit toujours être juste
//
// donc les Vc prises en compte doivent être calculées en fonction 
// de l'opération lorsqu'on agit sur les combo : il faut les récupérer à partir
// des données outil / matière / opération

class CPageCalcLathe : public CPageCalcBase
{
	DECLARE_DYNAMIC(CPageCalcLathe)

public:
	CPageCalcLathe(CData* pData=NULL);
	virtual ~CPageCalcLathe();

	virtual void OnSlider(int nTBCode, UINT nPos);

protected:
// mise à jour en fonction de la base de données et de l'opération
	virtual void OnChangeTWPair();
	virtual void SetControlsPos();
								
protected:
// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_CALC };

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	double m_fCorrect;

	virtual BOOL OnInitDialog();

	CComboEx m_comboOperation;
	CStatic m_staticOperation;
	
	afx_msg void OnCbnSelchangeComboOperation();
};

