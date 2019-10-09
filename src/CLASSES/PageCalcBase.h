#pragma once

#include "PropPageEx.h"
#include "ComboDecimal.h"
#include "DataMatDb.h"
#include "PageTCA.h"
#include "SheetCutCalc.h"
#include "ScrollPad.h"
#include "EditDecimal.h"

// Bo�te de dialogue CPageCalcBase
//
// g�re les calculs sans notion d'avance ni de diam�tres
// par d�faut le diam�tre est fix� � 10mm
//				la Vc est incr�ment�e de 0.5 par le scrollpad
//				N est incr�ment�e de 50 par le scrollpad
//
// controles EDIT en lecture seule
// couleur sp�cifique quand focus COLOR_INFOBK

class CPageCalcBase : public CPageTCA
{
	DECLARE_DYNAMIC(CPageCalcBase)

public:
	CPageCalcBase(UINT nIDTemplate, CData* pData);
	virtual ~CPageCalcBase();

	virtual void OnSlider(int nTBCode, UINT nPos);

protected:

// fonction appel�e en cas de changement de couple outil / mati�re (Tool Workpiece pair)
// met � jour variables, controles, et recalcule la page
	virtual void OnChangeTWPair();
	void SetMeanVc(); // recadre la Vc � la moyenne

	virtual void Clear(); // appel�e pour vider les champs

protected:
// Donn�es de bo�te de dialogue

	// helpers : r�cup�rent les valeurs affich�es dans les edits
	double GetD()	{ double D=0; m_editD.GetDecimalValue(D); return D; }
	double GetVc()	{ double Vc=0; m_editVc.GetDecimalValue(Vc); return Vc; }
	double GetN()	{ double N=0; m_editN.GetDecimalValue(N); return N; }

	// helpers : changent les valeurs affich�es par les edits
	void SetD(double D)		{ m_editD.SetFixedValue(D, 2); } // 2 d�cimales car incr�ment 0.25
	void SetVc(double Vc)	{ m_editVc.SetFixedValue(Vc, 1); } // d�cimale car incr�ment 0.1
	void SetN(double N)		{ m_editN.SetFixedValue(N, 0); } // pas de d�cimale

	// helpers : vident les edits
	void ClearD()		{ m_editD.SetWindowText_NoNotify(_T("")); }
	void ClearVc()		{ m_editVc.SetWindowText_NoNotify(_T("")); }
	void ClearN()		{ m_editN.SetWindowText_NoNotify(_T("")); }

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	virtual void CalcAndUpdateN();		// calcule et met � jour N en fonction de D et Vc
	virtual void CalcAndUpdateVc();	// calcule et met � jour Vc en fonction de N et Vc

	CStatic m_staticD;
	CStatic m_staticVc;
	CStatic m_staticN;

	CEditDecimal m_editN;
	CEditDecimal m_editD;
	CEditDecimal m_editVc;

	virtual BOOL OnInitDialog();

	// appel�e par OnEnChangeEditD etc. (car non virtuelles !)
	virtual void OnChangeD();
	virtual void OnChangeVc();
	virtual void OnChangeN();

	afx_msg void OnEnChangeEditD();
	afx_msg void OnEnChangeEditVc();
	afx_msg void OnEnChangeEditN();
};

