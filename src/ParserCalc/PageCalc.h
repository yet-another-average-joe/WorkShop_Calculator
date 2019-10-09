#pragma once

#include "Data.h"
#include "PropPageEx.h"
#include "afxwin.h"
#include "BtnIcon.h"

// Boîte de dialogue CPageCalc

class CPageCalc : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageCalc)

public:
	CPageCalc(CData* pData);
	virtual ~CPageCalc();

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_CALC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFileName;
	double	m_dPI;	// PI
	double	m_dX;	// X

	void SetEingabe(CString str);
	void SetEingabeFunc(CString str);
	virtual BOOL OnInitDialog();

	// boutons de fonctions
	// pour les fonctions arc et hyp, les boutons sin asin sinh etc. sont superposés
	// et affichés selon l'état de arc et hyp

	CEdit m_editExpr;
	CEdit m_editResult;
	CString m_strExpr;
	CString m_strResult;

	// chiffres
	CBtnIcon m_btn0;
	CBtnIcon m_btn1;
	CBtnIcon m_btn2;
	CBtnIcon m_btn3;
	CBtnIcon m_btn4;
	CBtnIcon m_btn5;
	CBtnIcon m_btn6;
	CBtnIcon m_btn7;
	CBtnIcon m_btn8;
	CBtnIcon m_btn9;
	CBtnIcon m_btnDot;
	CBtnIcon m_btnPI;
	afx_msg void OnNumber(UINT nID);
	afx_msg void OnDot();
	afx_msg void OnPi();

	// 4 opérations
	CBtnIcon m_btnPlus;
	CBtnIcon m_btnMinus;
	CBtnIcon m_btnMul;
	CBtnIcon m_btnDiv;
	CBtnIcon m_btnEqu;
	afx_msg void OnPlus();
	afx_msg void OnMinus();
	afx_msg void OnMul();
	afx_msg void OnDiv();
	afx_msg void OnEqu();

	// algèbre
	CBtnIcon m_btnParOpen;
	CBtnIcon m_btnParClose;
	CBtnIcon m_btnX;
	afx_msg void OnParOpen();
	afx_msg void OnParClose();
	afx_msg void OnXb();
	afx_msg void OnX();

	// trigo
	CBtnIcon m_btnRad;
	CBtnIcon m_btnDeg;
	CBtnIcon m_checkArc;
	CBtnIcon m_checkHyp;
	CBtnIcon m_btnSin;
	CBtnIcon m_btnCos;
	CBtnIcon m_btnTan;
	CBtnIcon m_btnSinh;
	CBtnIcon m_btnCosh;
	CBtnIcon m_btnTanh;
	CBtnIcon m_btnAsin;
	CBtnIcon m_btnAcos;
	CBtnIcon m_btnAtan;
	CBtnIcon m_btnAsinh;
	CBtnIcon m_btnAcosh;
	CBtnIcon m_btnAtanh;
	void UpdateTrigBtns();
	afx_msg void OnArc();
	afx_msg void OnHyp();
	afx_msg void OnRad();
	afx_msg void OnDeg();
	afx_msg void OnSin();
	afx_msg void OnCos();
	afx_msg void OnTan();
	afx_msg void OnSinh();
	afx_msg void OnCosh();
	afx_msg void OnTanh();
	afx_msg void OnAsin();
	afx_msg void OnAcos();
	afx_msg void OnAtan();
	afx_msg void OnAsinh();
	afx_msg void OnAcosh();
	afx_msg void OnAtanh();

	// autres fonctions

	CBtnIcon m_btnInt;
	CBtnIcon m_btnAbs;
	CBtnIcon m_btnPow;
	CBtnIcon m_btnLn;
	CBtnIcon m_btnLog;
	CBtnIcon m_btnSqrt;
	CBtnIcon m_btnExp;
	CBtnIcon m_btn10x;
	CBtnIcon m_btnX2;
	afx_msg void OnPow();
	afx_msg void OnExp();
	afx_msg void OnLn();
	afx_msg void OnInt();
	afx_msg void OnAbs();
	afx_msg void On10x();
	afx_msg void OnLog();
	afx_msg void OnX2();
	afx_msg void OnSqrt();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	CBrush	m_brBkgnd;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void SetBtnColors(CBtnIcon& btn);
	void SetBtnColors2(CBtnIcon& btn);
};
