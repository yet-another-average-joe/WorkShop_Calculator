#pragma once

#include "PropPageEx.h"
#include "ComboDecimal.h"
#include "DataMatDb.h"
#include "PageTCA.h"
#include "SheetCutCalc.h"
#include "ScrollPad.h"
#include "EditDecimal.h"

// Boîte de dialogue CPageCalcBase
//
// gère les calculs sans notion d'avance ni de diamètres
// par défaut le diamètre est fixé à 10mm
//				la Vc est incrémentée de 0.5 par le scrollpad
//				N est incrémentée de 50 par le scrollpad
//
// controles EDIT en lecture seule
// couleur spécifique quand focus COLOR_INFOBK

class CPageCalcBase : public CPageTCA
{
	DECLARE_DYNAMIC(CPageCalcBase)

public:
	CPageCalcBase(UINT nIDTemplate, CData* pData);
	virtual ~CPageCalcBase();

	virtual void OnSlider(int nTBCode, UINT nPos);

protected:

// fonction appelée en cas de changement de couple outil / matière (Tool Workpiece pair)
// met à jour variables, controles, et recalcule la page
	virtual void OnChangeTWPair();
	void SetMeanVc(); // recadre la Vc à la moyenne

	virtual void Clear(); // appelée pour vider les champs

protected:
// Données de boîte de dialogue

	// helpers : récupèrent les valeurs affichées dans les edits
	double GetD()	{ double D=0; m_editD.GetDecimalValue(D); return D; }
	double GetVc()	{ double Vc=0; m_editVc.GetDecimalValue(Vc); return Vc; }
	double GetN()	{ double N=0; m_editN.GetDecimalValue(N); return N; }

	// helpers : changent les valeurs affichées par les edits
	void SetD(double D)		{ m_editD.SetFixedValue(D, 2); } // 2 décimales car incrément 0.25
	void SetVc(double Vc)	{ m_editVc.SetFixedValue(Vc, 1); } // décimale car incrément 0.1
	void SetN(double N)		{ m_editN.SetFixedValue(N, 0); } // pas de décimale

	// helpers : vident les edits
	void ClearD()		{ m_editD.SetWindowText_NoNotify(_T("")); }
	void ClearVc()		{ m_editVc.SetWindowText_NoNotify(_T("")); }
	void ClearN()		{ m_editN.SetWindowText_NoNotify(_T("")); }

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	virtual void CalcAndUpdateN();		// calcule et met à jour N en fonction de D et Vc
	virtual void CalcAndUpdateVc();	// calcule et met à jour Vc en fonction de N et Vc

	CStatic m_staticD;
	CStatic m_staticVc;
	CStatic m_staticN;

	CEditDecimal m_editN;
	CEditDecimal m_editD;
	CEditDecimal m_editVc;

	virtual BOOL OnInitDialog();

	// appelée par OnEnChangeEditD etc. (car non virtuelles !)
	virtual void OnChangeD();
	virtual void OnChangeVc();
	virtual void OnChangeN();

	afx_msg void OnEnChangeEditD();
	afx_msg void OnEnChangeEditVc();
	afx_msg void OnEnChangeEditN();
};

