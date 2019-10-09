#pragma once

#include "PropPageEx.h"

// Boîte de dialogue CPageMisc

class CPageMisc : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageMisc)

public:
	CPageMisc();
	virtual ~CPageMisc();

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_MISC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_editMisc;
	CListBox m_listMisc;
	afx_msg void OnLbnSelchangeListMisc();
};
