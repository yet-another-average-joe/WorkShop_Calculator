// CEComboBox.cpp�: fichier d'impl�mentation
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
	// fixe la hauteur de la combo d�roul�e pour qu'elle arrive en bas de la page

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

		// � revoir pour faire d�rouler vers le haut s'il y a
		// plus de place vers le haut
		cy=rcScreen.Height()-rc.top;
	}

	// pas d'affichage de la liste d�roulante si vide
	if(GetCount()<1)
		cy=::GetSystemMetrics(SM_CXHSCROLL); // hauteur de la combo (celle du bouton)

	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOZORDER);
}

void CComboEx::PreSubclassWindow()
{
	// sinon, ligne noire en bas lorsqu'on d�roule
	// la hauteur de la liste d�roulante sera celle 
	// d�finie dans OnCbnDropdown()
	if(m_bFullDrop)
		ModifyStyle(0, CBS_NOINTEGRALHEIGHT, 0);

	CComboBox::PreSubclassWindow();
}
