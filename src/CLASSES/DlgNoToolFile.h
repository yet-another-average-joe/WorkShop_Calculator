#pragma once

#include "CEDialog.h"


// Boîte de dialogue CDlgNoToolFile

class CDlgNoToolFile : public CCEDialog
{
	DECLARE_DYNAMIC(CDlgNoToolFile)

public:
	CDlgNoToolFile(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDlgNoToolFile();

// Données de boîte de dialogue

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
