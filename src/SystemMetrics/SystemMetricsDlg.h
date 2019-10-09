// SystemMetricsDlg.h : fichier d'en-t�te
//

#pragma once

#include "DlgMain.h"

// Bo�te de dialogue CSystemMetricsDlg
class CSystemMetricsDlg : public CDlgMain
{
// Construction
public:
	CSystemMetricsDlg(CWnd* pParent = NULL);

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_SYSTEMMETRICS_PORTRAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Impl�mentation
protected:
	int m_nSMCount;
	int m_nIndex[100];	
	CString m_strText[100];
	CString m_strDescr[100];	

	// Fonctions g�n�r�es de la table des messages
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	CListBox m_listboxSM;
	afx_msg void OnLbnSelchangeComboSm();
public:
	CEdit m_editDescr;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
