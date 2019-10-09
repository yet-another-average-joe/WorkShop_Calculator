// SysColorDlg.h : fichier d'en-tête
//

#pragma once

#include "DlgMain.h"

// Boîte de dialogue CSysColorDlg
class CSysColorDlg : public CDlgMain
{
// Construction
public:
	CSysColorDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
	enum { IDD = IDD_SYSCOLOR_PORTRAIT };

	int m_nSCCount;
	int m_nIndex[100];	
	CString m_strText[100];
	CString m_strDescr[100];	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Implémentation
protected:
	CListBox m_listboxSC;
	CEdit m_editDescr;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
	afx_msg void OnLbnSelchangeComboSc();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
