#pragma once

#include "CEDialog.h"
#include "BtnIcon.h"

// Bo�te de dialogue CDlgOdometer

class CDlgOdometer : public CCEDialog
{
	DECLARE_DYNAMIC(CDlgOdometer)

public:
	CDlgOdometer(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDlgOdometer();

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_ODOMETER };

protected:
	CBtnIcon m_btnCalc;

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnCalc();
public:
	virtual BOOL OnInitDialog();
};
