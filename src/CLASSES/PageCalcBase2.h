#pragma once

#include "ComboDecimal.h"
#include "PageCalcBase.h"
#include "Editdecimal.h"

// en rosbif, couple outil matière = tool workpiece pair

// fonctionalités de base pour calcul en perçage

// Boîte de dialogue CPageCalcBase2

class CPageCalcBase2 : public CPageCalcBase
{
	DECLARE_DYNAMIC(CPageCalcBase2)

public:
	CPageCalcBase2(UINT nIDTemplate, CData* pData);
	virtual ~CPageCalcBase2();

	virtual void OnSlider(int nTBCode, UINT nPos);

protected:
	// actions à faire en cas de changement de couple outil / matière
	virtual void OnChangeTWPair();
	// à redéfinir dans les classes dérivées
	virtual void UpdateControlsStyles(); // met à jour les attributs des controles

	// helpers
	double GetF()				{ double f=0; m_editF.GetDecimalValue(f); return f;}
	double GetVf()				{ double Vf=0; m_editVf.GetDecimalValue(Vf); return Vf; }
	void SetF(double f)			{ m_editF.SetDecimalValue(f, 3); }
	void SetVf(double Vc)		{ m_editVf.SetDecimalValue(Vc, 3); }
	void ClearF()				{ m_editF.SetWindowText_NoNotify(_T("")); }
	void ClearVf()				{ m_editVf.SetWindowText_NoNotify(_T("")); }

	virtual void Clear(); // appelée pour vider les champs

	// calcule les limites de f par interpolation, en fonction de D
	// retourne 0, 1 ou 2 selon qu'il y a : rien, fmain seul (=fMax), ou fmin et fMax
	int CalcF(double& fmin, double& fmax);

	virtual void CalcAndUpdateF();	// calcule et met à jour f en fonction de Vf et N
	virtual void CalcAndUpdateVf();	// calcule et met à jour Vf en fonction de f et N

protected:
// Données de boîte de dialogue

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	CStatic m_staticF;
	CStatic m_staticVf;
	CEditDecimal m_editF;	// avance / tour :
	CEditDecimal m_editVf;

	virtual BOOL OnInitDialog();

	// appelée par CPageCalcBase / CPageCalcBase2 ::OnEnChangeEditD (car non virtuelle)
	virtual void OnChangeD();
	virtual void OnChangeN();
	virtual void OnChangeF();
	virtual void OnChangeVf();

	afx_msg void OnEnChangeEditF();
	afx_msg void OnEnChangeEditVf();
};

