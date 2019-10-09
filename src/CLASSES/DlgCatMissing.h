#pragma once

#include "CEDialog.h"

// Boîte de dialogue CDlgCatMissing

class CDlgCatMissing : public CCEDialog
{
	DECLARE_DYNAMIC(CDlgCatMissing)

public:
	CDlgCatMissing(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDlgCatMissing();

	CString m_strFileName;

// Données de boîte de dialogue

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	virtual BOOL OnInitDialog();
};
