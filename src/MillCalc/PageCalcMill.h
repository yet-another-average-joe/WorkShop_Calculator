#pragma once

#include "ComboDecimal.h"
#include "PageCalcBase2.h"
#include "ComboInteger.h"
#include "EditDecimal.h"

// Boîte de dialogue CPageCalcMill

class CPageCalcMill : public CPageCalcBase2
{
	DECLARE_DYNAMIC(CPageCalcMill)

public:
	CPageCalcMill(CData* pData);
	virtual ~CPageCalcMill();

	virtual void OnSlider(int nTBCode, UINT nPos);

protected:
	// helpers
	UINT GetZ()				{ return GetDlgItemInt(IDC_EDIT_Z); }
	void SetZ(UINT z)		{ SetDlgItemInt(IDC_EDIT_Z, z); }
	void ClearZ()			{ m_editZ.SetWindowText_NoNotify(_T("")); }
	
	void SetAe(double ae)	{ m_editAe.SetDecimalValue(ae, 3); }
	void SetAp(double ap)	{ m_editAp.SetDecimalValue(ap, 3); }

	void ClearAp()			{ m_editAp.SetWindowText_NoNotify(_T("")); }
	void ClearAe()			{ m_editAe.SetWindowText_NoNotify(_T("")); }

	// actions à faire en cas de changement de couple outil / matière
	virtual void OnChangeTWPair();
	virtual void Clear(); // appelée pour vider les champs
	virtual void CalcAndUpdateF();	// calcule et met à jour f en fonction de Vf et N
	virtual void CalcAndUpdateVf();	// calcule et met à jour Vf en fonction de f et N

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_CALC };

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	virtual void UpdateApAe();

	CStatic m_staticZ;
	CEditDecimal  m_editZ;
	CStatic m_staticAp;
	CStatic m_staticAe;
	CEditDecimal m_editAp;
	CEditDecimal m_editAe;

	virtual void OnChangeZ();

	afx_msg void OnEnChangeEditZ();
	virtual BOOL OnInitDialog();
};

