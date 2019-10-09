#pragma once

#include "CEDialog.h"


// Boîte de dialogue CDlgNoMatFile

class CDlgNoMatFile : public CCEDialog
{
	DECLARE_DYNAMIC(CDlgNoMatFile)

public:
	CDlgNoMatFile(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDlgNoMatFile();

// Données de boîte de dialogue

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
