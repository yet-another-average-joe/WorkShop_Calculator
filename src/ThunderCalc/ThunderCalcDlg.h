// ThunderCalcDlg.h : fichier d'en-t�te
//

#pragma once

#include "DlgMain.h"

// Bo�te de dialogue CThunderCalcDlg
class CThunderCalcDlg : public CDlgMain
{
// Construction
public:
	CThunderCalcDlg(CWnd* pParent = NULL);	// constructeur standard

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_THUNDERCALC_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Impl�mentation
protected:
	HICON m_hIcon;

	// Fonctions g�n�r�es de la table des messages
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	UINT_PTR  m_pTimer;
	int m_nDistance;
	int m_nTime;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
