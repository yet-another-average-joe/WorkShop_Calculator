#pragma once

#include "CEDialog.h"

// Boîte de dialogue CDlgMatfileMissing

class CDlgMatfileMissing : public CCEDialog
{
	DECLARE_DYNAMIC(CDlgMatfileMissing)

public:
	CDlgMatfileMissing(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDlgMatfileMissing();

// Données de boîte de dialogue
	enum { IDD = IDD_MATFILE_MISSING_PORTRAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
