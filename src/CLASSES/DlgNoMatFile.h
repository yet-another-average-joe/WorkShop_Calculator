#pragma once

#include "CEDialog.h"


// Bo�te de dialogue CDlgNoMatFile

class CDlgNoMatFile : public CCEDialog
{
	DECLARE_DYNAMIC(CDlgNoMatFile)

public:
	CDlgNoMatFile(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDlgNoMatFile();

// Donn�es de bo�te de dialogue

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
