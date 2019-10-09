#pragma once

#include "PropPageEx.h"
#include "ComboEx.h"

// Boîte de dialogue CPageRatings

class CPageRatings : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageRatings)

public:
	CPageRatings();
	virtual ~CPageRatings();

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_RATINGS };

protected:
	CEdit			m_editSpeed;
	CEdit			m_editLoad;
	CComboEx		m_comboSpeedRating;
	CComboEx		m_comboLoadIndex;

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeComboLoadIndex();
	afx_msg void OnCbnSelchangeComboSpeedRating();
public:
	virtual BOOL OnInitDialog();
};
