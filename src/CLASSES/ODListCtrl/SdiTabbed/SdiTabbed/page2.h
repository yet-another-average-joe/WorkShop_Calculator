#pragma once

#include "ScrollPage.h"
#include "ODListCtrl.h"

// Boîte de dialogue Cpage2

class CPage2 : public CPage
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2();   // constructeur standard
	virtual ~CPage2();

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE2 };

	CODListCtrl m_wndList;

	CString m_strText[8];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
