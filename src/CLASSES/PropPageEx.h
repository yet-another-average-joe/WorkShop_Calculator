#pragma once


#include "PropSheetEx.h"

class CData;

// Bo�te de dialogue CPropPageEx

class CPropPageEx : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageEx)

public:
	// constructeurs
	CPropPageEx(CData* pData);
	CPropPageEx(UINT nIDTemplate, CData* pData);

	virtual ~CPropPageEx();

	// d�sactive le scrolling
	virtual void EnableScrollbars(BOOL fEnable=TRUE);

	// utilis� par la CPropSheet pour autoriser / interdire 
	// le changement de page ; sert en particulier en mode �dition
	// quand une op�ration doit �tre valid�e ou annul�e
	// retourne TRUE par d�faut
	virtual BOOL CanChangePage(); 


	// SetEditMode et GetEditMode appellent simplement 
	// les m�mes fonctions de la CPropSheet parente
	void SetEditMode(BOOL fMode);
	BOOL GetEditMode();

public:

	// met � jour la page ; par d�faut appelle UpdateControlsStyles()
	virtual void UpdatePage();

protected:

	// repositionne les contr�les en fonction du dimensionnement 
	// de la page : SIP, orientation, etc. 
	virtual void SetControlsPos() {} //=0;
	// g�re affichage, activation etc. des contr�les
	virtual void UpdateControlsStyles() {} //=0;
	// par d�faut, appelle UpdatePage();	
	virtual BOOL OnSetActive();

	CPropSheetEx* GetPropSheet() { return (CPropSheetEx*)GetParent(); }

	CData*	m_pData;
	BOOL	m_fDoneDDE; // DDE fait : contr�les cr��s et initialis�s

	// Donn�es de bo�te de dialogue
protected:

	//BOOL	m_fEditMode;
	int		m_cxTemplate;
	int		m_cyTemplate;
	// si TRUE, scrolling. TRUE par d�faut; � positionner dans le constructeur
	BOOL	m_fEnableScrollbars;
	// rectangle du template, obtenu au premier appel de OnSize
	void	SaveTemplateSize(int cx, int cy);
	BOOL	m_fRcTemplateOk;	// flag : rectangle obtenu - 1er appel)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
	void Init();
	void SetPage(int nBar, UINT nPage);
	void ScrollBy(int nBar, int nDeltaPos);
	void OnScroll(int nBar, UINT nSBCode, UINT nPos);
	// calcule la taille en pixels d'un dialogue � partir de la resource
	BOOL GetDialogSize(CSize& size, UINT nIdTemplate);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
};

inline void CPropPageEx::SetEditMode(BOOL fMode)
{
	CPropSheetEx* pSheet=(CPropSheetEx*)GetParent();
	ASSERT(pSheet!=NULL);
	pSheet->SetEditMode(fMode);
}

inline BOOL CPropPageEx::GetEditMode()
{
	CPropSheetEx* pSheet=(CPropSheetEx*)GetParent();
	ASSERT(pSheet!=NULL);
	return pSheet->GetEditMode();
}


