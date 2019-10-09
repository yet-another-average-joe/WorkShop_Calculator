#pragma once

#include "ComboDecimal.h"
#include "PageCalcbase.h"

// Bo�te de dialogue CPageCalcLathe
//
// probl�me de calcul : la relation D / Vc / N doit toujours �tre juste
//
// donc les Vc prises en compte doivent �tre calcul�es en fonction 
// de l'op�ration lorsqu'on agit sur les combo : il faut les r�cup�rer � partir
// des donn�es outil / mati�re / op�ration

class CPageCalcLathe : public CPageCalcBase
{
	DECLARE_DYNAMIC(CPageCalcLathe)

public:
	CPageCalcLathe(CData* pData=NULL);
	virtual ~CPageCalcLathe();

	virtual void OnSlider(int nTBCode, UINT nPos);

protected:
// mise � jour en fonction de la base de donn�es et de l'op�ration
	virtual void OnChangeTWPair();
	virtual void SetControlsPos();
								
protected:
// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_CALC };

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	double m_fCorrect;

	virtual BOOL OnInitDialog();

	CComboEx m_comboOperation;
	CStatic m_staticOperation;
	
	afx_msg void OnCbnSelchangeComboOperation();
};

