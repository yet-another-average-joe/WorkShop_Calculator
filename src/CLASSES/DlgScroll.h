#pragma once


// Bo�te de dialogue CDlgScroll

class CDlgScroll : public CDialog
{
	DECLARE_DYNAMIC(CDlgScroll)

public:
	CDlgScroll(UINT nIDTemplate, CWnd* pParentWnd = NULL);

	virtual ~CDlgScroll();

	// active/d�sactive le scrolling
	virtual void EnableScrollbars(BOOL fEnable=TRUE);

	// Donn�es de bo�te de dialogue
private:
	int		m_cxTemplate;
	int		m_cyTemplate;
	// si TRUE, scrolling. TRUE par d�faut; � positionner dans le constructeur
	BOOL	m_fEnableScrollbars;
	// rectangle du template, obtenu au premier appel de OnSize
	void	SaveTemplateSize(int cx, int cy);
	BOOL	m_fRcTemplateOk;	// flag : rectangle obtenu - 1er appel)

// Donn�es de bo�te de dialogue

protected:
	BOOL	m_fDoneDDE; // DDE fait : contr�les cr��s et initialis�s
	void Init();
	void SetPage(int nBar, UINT nPage);
	void ScrollBy(int nBar, int nDeltaPos);
	void OnScroll(int nBar, UINT nSBCode, UINT nPos);
	// calcule la taille en pixels d'un dialogue � partir de la resource
	BOOL GetDialogSize(CSize& size, UINT nIdTemplate);

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg void OnPaint();
};

inline void CDlgScroll::EnableScrollbars(BOOL fEnable /*=TRUE*/)
{
	m_fEnableScrollbars=fEnable;
}

