// WrkShpCalcDlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"
#include "DlgMain.h"
#include "BtnIcon.h"


// Boîte de dialogue CWrkShpCalcDlg
class CWrkShpCalcDlg : public CDlgMain
{
// Construction
public:
	CWrkShpCalcDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
	enum { IDD = IDD_WRKSHPCALC_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Implémentation
protected:
	HICON m_hIcon;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CBtnIcon m_btnMatDb;
	CBtnIcon m_btnDrillCalc;
	CBtnIcon m_btnLatheCalc;
	CBtnIcon m_btnMillCalc;
	CBtnIcon m_btnSysColor;
	CBtnIcon m_btnSystemMetrics;
	CBtnIcon m_btnTapCalc;
	CBtnIcon m_btnTireCalc;
	CBtnIcon m_btnNewtonCalc;
	CBtnIcon m_btnThunderCalc;
	CBtnIcon m_btnParserCalc;
	CBtnIcon m_btnStockCalc;
	afx_msg void OnBnClickedBtnMatdb();
	afx_msg void OnBnClickedBtnDrillcalc();
	afx_msg void OnBnClickedBtnLathecalc();
	afx_msg void OnBnClickedBtnMillcalc();
	afx_msg void OnBnClickedBtnSysColor();
	afx_msg void OnBnClickedBtnSystemMetrics();
	afx_msg void OnBnClickedBtnTapcalc();
	afx_msg void OnBnClickedBtnTirecalc();
	afx_msg void OnBnClickedBtnNewtoncalc();
	afx_msg void OnBnClickedBtnThundercalc();
	afx_msg void OnBnClickedBtnParsercalc();
	afx_msg void OnBnClickedBtnStockcalc();
};

