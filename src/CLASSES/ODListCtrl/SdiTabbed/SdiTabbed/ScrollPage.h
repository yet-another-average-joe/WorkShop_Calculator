#pragma once

#include "Page.h"

// Boîte de dialogue CScrollPropPage

class CScrollPage : public CPage
{
	DECLARE_DYNAMIC(CScrollPage)

public:
	CScrollPage(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~CScrollPage();

// Données de boîte de dialogue
	UINT m_nID;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void ScrollBy(int nBar, int nDeltaPos);
	void OnScroll(int nBar, UINT nSBCode, UINT nPos);
protected:
	// rectangle du template, obtenu au premier appel de OnSize
	void	SaveTemplateSize(int cx, int cy);
	int		m_cxTemplate;
	int		m_cyTemplate;
	BOOL	m_bRcTemplateOk;	// flag : rectangle obtenu - 1er appel)
	
	void SetScrollbar(int nBar, int cx);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
