#pragma once

#include "CEDialog.h"

// Boîte de dialogue CDlgMatfilInvalid

class CDlgMatfileInvalid : public CCEDialog
{
	DECLARE_DYNAMIC(CDlgMatfileInvalid)

public:
	CDlgMatfileInvalid(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDlgMatfileInvalid();

// Données de boîte de dialogue
	enum { IDD = IDD_MATFILE_INVALID_PORTRAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
