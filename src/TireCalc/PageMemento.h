#pragma once

#include "PropPageEx.h"
#include "DlgScroll.h"
#include "afxwin.h"
#include "ComboEx.h"

// Boîte de dialogue CPageMemento

class CPageMemento : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageMemento)

public:
	CPageMemento();
	virtual ~CPageMemento();

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_MEMENTO };

protected:
	CDlgScroll* pDlg1;

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_staticPlaceHolder;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CComboEx m_comboChapter;
	afx_msg void OnCbnSelchangeComboChapter();
};
