#pragma once


#include "PropSheetEx.h"

class CData;

// Boîte de dialogue CPropPageEx

class CPropPageEx : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageEx)

public:
	// constructeurs
	CPropPageEx(CData* pData);
	CPropPageEx(UINT nIDTemplate, CData* pData);

	virtual ~CPropPageEx();

	// désactive le scrolling
	virtual void EnableScrollbars(BOOL fEnable=TRUE);

	// utilisé par la CPropSheet pour autoriser / interdire 
	// le changement de page ; sert en particulier en mode édition
	// quand une opération doit être validée ou annulée
	// retourne TRUE par défaut
	virtual BOOL CanChangePage(); 


	// SetEditMode et GetEditMode appellent simplement 
	// les mêmes fonctions de la CPropSheet parente
	void SetEditMode(BOOL fMode);
	BOOL GetEditMode();

public:

	// met à jour la page ; par défaut appelle UpdateControlsStyles()
	virtual void UpdatePage();

protected:

	// repositionne les contrôles en fonction du dimensionnement 
	// de la page : SIP, orientation, etc. 
	virtual void SetControlsPos() {} //=0;
	// gère affichage, activation etc. des contrôles
	virtual void UpdateControlsStyles() {} //=0;
	// par défaut, appelle UpdatePage();	
	virtual BOOL OnSetActive();

	CPropSheetEx* GetPropSheet() { return (CPropSheetEx*)GetParent(); }

	CData*	m_pData;
	BOOL	m_fDoneDDE; // DDE fait : contrôles créés et initialisés

	// Données de boîte de dialogue
protected:

	//BOOL	m_fEditMode;
	int		m_cxTemplate;
	int		m_cyTemplate;
	// si TRUE, scrolling. TRUE par défaut; à positionner dans le constructeur
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
	// calcule la taille en pixels d'un dialogue à partir de la resource
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


