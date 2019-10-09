
#pragma once

#include "CEDialog.h"
#include "StaticBmp.h"

// IMPORTANT : IDR_MAINFRAME doit être égal à 128 dans les applications
// (ID_MAINFRAME est par défaut égal à 128)
// nécessaire pour que l'icône de l'application s'affiche

// boîte de dialogue CDlgAbout utilisée pour la boîte de dialogue 'À propos de' pour votre application
class CDlgAbout : public CCEDialog
{
public:
	CDlgAbout(CWnd* pParent = NULL);

// Données de boîte de dialogue

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	UINT m_nIDIcon;

// Implémentation
protected:

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
};
