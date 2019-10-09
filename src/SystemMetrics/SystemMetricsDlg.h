// SystemMetricsDlg.h : fichier d'en-tête
//

#pragma once

#include "DlgMain.h"

// Boîte de dialogue CSystemMetricsDlg
class CSystemMetricsDlg : public CDlgMain
{
// Construction
public:
	CSystemMetricsDlg(CWnd* pParent = NULL);

// Données de boîte de dialogue
	enum { IDD = IDD_SYSTEMMETRICS_PORTRAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Implémentation
protected:
	int m_nSMCount;
	int m_nIndex[100];	
	CString m_strText[100];
	CString m_strDescr[100];	

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	CListBox m_listboxSM;
	afx_msg void OnLbnSelchangeComboSm();
public:
	CEdit m_editDescr;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
