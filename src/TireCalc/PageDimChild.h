#pragma once

#include "DlgScroll.h"
#include "ComboDecimal.h"

// Boîte de dialogue CPageDimChild

class CPageDimChild : public CDlgScroll
{
	DECLARE_DYNAMIC(CPageDimChild)

public:
	CPageDimChild(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~CPageDimChild();

// Données de boîte de dialogue
	enum { IDD = IDD_PAGEDIMCHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Implémentation
protected:

	void FillWidthMetric();
	void FillAspectRatio();
	void FillAspectRatio80();
	void FillAspectRatioNumeric();
	void FillWidthNumeric();
	void FillWidthFlotation();
	void FillDiamFlotation();
	void FillRimInches();
	void FillRimMillimetric();

	CComboDecimal	m_comboWidth;			// ItemData = largeur
	CComboDecimal	m_comboAspectRatio;		// ItemData = aspect ratio
	CComboDecimal	m_comboRim;				// ItemData = diamètre
	CComboEx		m_comboCorrect;			// Itemdata = %
	CComboDecimal	m_comboDiam;

	// affichage résultats

	CEditDecimal	m_editWidth;
	CEditDecimal	m_editHeight;
	CEditDecimal	m_editDiam;
	CEditDecimal	m_editDev;

	virtual void Calculate()=0;
	void CalculateMetric();
	void CalculateMillimetric();
	void CalculateNumeric();
	void CalculateFlotation();

	// _in : centièmes de pouce

	//void CalculateMillimetric(double fRim_in, double fWidth_mm, double fRatio,
	//		double& fWidth_m, double& fHeight_m, double& fDiam_m, double& fDev_m);

	double GetCorrect();

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
//#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
//	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
//#endif

	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeComboRim();
	afx_msg void OnCbnSelchangeComboWidth();
	afx_msg void OnCbnSelchangeComboAspectRatio();
	afx_msg void OnCbnSelchangeComboCorrect();
	afx_msg void OnCbnSelchangeComboDiam();
};

inline double CPageDimChild::GetCorrect()
{
	int nSel=m_comboCorrect.GetCurSel();
	ASSERT(nSel!=CB_ERR);
	int nCorrect=m_comboCorrect.GetItemData(nSel);
	return 1.0+((double)nCorrect)/100.0;
}
