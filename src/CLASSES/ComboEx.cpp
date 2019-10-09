// CEComboBox.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ComboEx.h"


// CComboEx

IMPLEMENT_DYNAMIC(CComboEx, CComboBox)

CComboEx::CComboEx()
{
	m_bFullDrop=FALSE;
}

CComboEx::~CComboEx()
{
}

BEGIN_MESSAGE_MAP(CComboEx, CComboBox)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, &CComboEx::OnCbnDropdown)
END_MESSAGE_MAP()

// Gestionnaires de messages de CComboEx

void CComboEx::OnCbnDropdown()
{
	// fixe la hauteur de la combo déroulée pour qu'elle arrive en bas de la page

	int cy=0;
	int cx=0;
	CRect rc;
	GetWindowRect(rc);
	cx=rc.Width();

	if(m_bFullDrop==TRUE && GetCount()>0)
	{
		CRect rcScreen;
		CWnd* pDesktop=GetDesktopWindow();
		pDesktop->GetWindowRect(rcScreen);
		pDesktop->ScreenToClient(rcScreen);
		pDesktop->ScreenToClient(rc);

		// à revoir pour faire dérouler vers le haut s'il y a
		// plus de place vers le haut
		cy=rcScreen.Height()-rc.top;
	}

	// pas d'affichage de la liste déroulante si vide
	if(GetCount()<1)
		cy=::GetSystemMetrics(SM_CXHSCROLL); // hauteur de la combo (celle du bouton)

	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOZORDER);
}

void CComboEx::PreSubclassWindow()
{
	// sinon, ligne noire en bas lorsqu'on déroule
	// la hauteur de la liste déroulante sera celle 
	// définie dans OnCbnDropdown()
	if(m_bFullDrop)
		ModifyStyle(0, CBS_NOINTEGRALHEIGHT, 0);

	CComboBox::PreSubclassWindow();
}
