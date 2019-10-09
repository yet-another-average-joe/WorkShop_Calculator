#pragma once

#include "DlgScroll.h"

// Boîte de dialogue CDlgMain

// pour application CAppDlg

class CDlgMain : public CDlgScroll
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(	UINT nIDTemplate,		// template du dialogue
						BOOL fHideSHDoneBtn=FALSE,	// si TRUE, le bouton "ok" est remplacé par "X"
						CWnd* pParent = NULL);
	virtual ~CDlgMain();
	
protected:
	BOOL m_fHideSHDoneBtn;	// si TRUE, le bouton "ok" est remplacé par "X"
	CCommandBar	m_wndCommandBar; // command bar

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnWrkShpCalc();
	afx_msg void OnAbout();
};
