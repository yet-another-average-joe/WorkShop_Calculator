// BtnIcon.cpp : fichier d'implémentation
//

#include "stdafx.h"
//#include "WrkShpCalc.h"
#include "BtnIcon.h"


// CBtnIcon

CBtnIcon::CBtnIcon()
{
	COLORREF crBtnColorBkIn=GetSysColor(COLOR_3DDKSHADOW); // couleur de fond des boutons enfoncés
	COLORREF crBtnColorBkOut=GetSysColor(COLOR_WINDOW); // couleur de fond des boutons
	COLORREF crBtnColorBkFocus=GetSysColor(COLOR_WINDOW); // couleur de fond des boutons

	m_crColors[CCeButtonST::BTNST_COLOR_BK_IN] = crBtnColorBkIn;
	m_crColors[CCeButtonST::BTNST_COLOR_BK_OUT] = crBtnColorBkOut;
	m_crColors[CCeButtonST::BTNST_COLOR_BK_FOCUS] = crBtnColorBkFocus;
	m_bIsRounded = TRUE;
}

CBtnIcon::~CBtnIcon()
{
}


BEGIN_MESSAGE_MAP(CBtnIcon, CWinXPButtonST)
END_MESSAGE_MAP()


DWORD CBtnIcon::SetIconMulti(int nIcon, int nIconDis, CSize size)
{
	ASSERT(nIcon);
	ASSERT(nIconDis);

	HICON		hIconIn			= NULL;
	HICON		hIconOut		= NULL;
	HICON		hIconDis		= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIconIn), RT_GROUP_ICON);

	hIconOut = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIcon), IMAGE_ICON, size.cx, size.cy, 0);
	hIconDis = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconDis), IMAGE_ICON, size.cx, size.cy, 0);

	return SetIcon(hIconOut, size, hIconOut, size, hIconDis, size);
} // End of SetIcon
