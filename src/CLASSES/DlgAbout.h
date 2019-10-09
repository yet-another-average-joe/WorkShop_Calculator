
#pragma once

#include "CEDialog.h"
#include "StaticBmp.h"

// IMPORTANT : IDR_MAINFRAME doit �tre �gal � 128 dans les applications
// (ID_MAINFRAME est par d�faut �gal � 128)
// n�cessaire pour que l'ic�ne de l'application s'affiche

// bo�te de dialogue CDlgAbout utilis�e pour la bo�te de dialogue '� propos de' pour votre application
class CDlgAbout : public CCEDialog
{
public:
	CDlgAbout(CWnd* pParent = NULL);

// Donn�es de bo�te de dialogue

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	UINT m_nIDIcon;

// Impl�mentation
protected:

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
};
