#pragma once

#include "ComboDecimal.h"
#include "PageCalcBase.h"
#include "Editdecimal.h"

// en rosbif, couple outil mati�re = tool workpiece pair

// fonctionalit�s de base pour calcul en per�age

// Bo�te de dialogue CPageCalcBase2

class CPageCalcBase2 : public CPageCalcBase
{
	DECLARE_DYNAMIC(CPageCalcBase2)

public:
	CPageCalcBase2(UINT nIDTemplate, CData* pData);
	virtual ~CPageCalcBase2();

	virtual void OnSlider(int nTBCode, UINT nPos);

protected:
	// actions � faire en cas de changement de couple outil / mati�re
	virtual void OnChangeTWPair();
	// � red�finir dans les classes d�riv�es
	virtual void UpdateControlsStyles(); // met � jour les attributs des controles

	// helpers
	double GetF()				{ double f=0; m_editF.GetDecimalValue(f); return f;}
	double GetVf()				{ double Vf=0; m_editVf.GetDecimalValue(Vf); return Vf; }
	void SetF(double f)			{ m_editF.SetDecimalValue(f, 3); }
	void SetVf(double Vc)		{ m_editVf.SetDecimalValue(Vc, 3); }
	void ClearF()				{ m_editF.SetWindowText_NoNotify(_T("")); }
	void ClearVf()				{ m_editVf.SetWindowText_NoNotify(_T("")); }

	virtual void Clear(); // appel�e pour vider les champs

	// calcule les limites de f par interpolation, en fonction de D
	// retourne 0, 1 ou 2 selon qu'il y a : rien, fmain seul (=fMax), ou fmin et fMax
	int CalcF(double& fmin, double& fmax);

	virtual void CalcAndUpdateF();	// calcule et met � jour f en fonction de Vf et N
	virtual void CalcAndUpdateVf();	// calcule et met � jour Vf en fonction de f et N

protected:
// Donn�es de bo�te de dialogue

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	CStatic m_staticF;
	CStatic m_staticVf;
	CEditDecimal m_editF;	// avance / tour :
	CEditDecimal m_editVf;

	virtual BOOL OnInitDialog();

	// appel�e par CPageCalcBase / CPageCalcBase2 ::OnEnChangeEditD (car non virtuelle)
	virtual void OnChangeD();
	virtual void OnChangeN();
	virtual void OnChangeF();
	virtual void OnChangeVf();

	afx_msg void OnEnChangeEditF();
	afx_msg void OnEnChangeEditVf();
};

