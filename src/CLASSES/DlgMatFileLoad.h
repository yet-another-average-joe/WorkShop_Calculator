#pragma once

#include "CEDialog.h"


// Boîte de dialogue CDlgMatFileLoad

class CDlgMatFileLoad : public CCEDialog
{
	DECLARE_DYNAMIC(CDlgMatFileLoad)

public:
	CDlgMatFileLoad(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDlgMatFileLoad();
	CString m_strFileExt;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_listboxFileName;
	CString m_strFileName;
	afx_msg void OnLbnSelchangeListboxMatFile();
};
