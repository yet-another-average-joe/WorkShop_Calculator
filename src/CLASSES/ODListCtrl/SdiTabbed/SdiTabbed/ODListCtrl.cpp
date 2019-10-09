// ODListCtrl.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "resourceppc.h"
#include "ODListCtrl.h"

#define IMAGE_SIZE	64
#define ITEM_WIDTH	200

// CODListCtrl

IMPLEMENT_DYNAMIC(CODListCtrl, CListCtrl)

CODListCtrl::CODListCtrl()
{

}

CODListCtrl::~CODListCtrl()
{
}


BEGIN_MESSAGE_MAP(CODListCtrl, CListCtrl)
END_MESSAGE_MAP()



// Gestionnaires de messages de CODListCtrl

void CODListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMI)
{
	// SEULE LA HAUTEUR SEMBLE ÊTRE UNITISEE
	lpMI->itemHeight = IMAGE_SIZE+6;
}

void CODListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS)
{
	CString str;
	LPTSTR buf=str.GetBuffer(257);

	LVITEM lvItem;
	lvItem.iItem=lpDIS->itemID;
	lvItem.mask=LVIF_PARAM;
	lvItem.lParam; 
	GetItem(&lvItem);

	CString* pStr = (CString*)lvItem.lParam; 

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	
	// save the current text and background colors
	COLORREF crOldBkColor = pDC->GetBkColor();
	CBrush brBkColor;
	brBkColor.CreateSolidBrush(crOldBkColor);

	CBrush brSel;
	brSel.CreateSolidBrush (GetSysColor(COLOR_HIGHLIGHT));
				
	COLORREF crOldTextColor = pDC->GetTextColor();

	// si item sélectionné, dessiner un rectangle
	if ((lpDIS->itemAction | ODA_SELECT) && (lpDIS->itemState & ODS_SELECTED))
	{
		pDC->FillRect(&lpDIS->rcItem, &brSel);
		pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	// sinon, remplir avec la couleur de fond standard et dessiner un rectangle autour de l'item
	else
	{
		pDC->FillRect(&lpDIS->rcItem, &brBkColor);
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
	}

	brSel.DeleteObject();
	brBkColor.DeleteObject();
	pDC->SetBkColor(crOldBkColor);

	// dessiner l'image
	HINSTANCE hInst = AfxGetApp()->m_hInstance;
	HICON hIcon =  (HICON) LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON3 + lpDIS->itemID), 
	IMAGE_ICON, IMAGE_SIZE, IMAGE_SIZE, 0);
	pDC->DrawIcon(lpDIS->rcItem.left+3, lpDIS->rcItem.top+3, hIcon);

	// dessiner le texte
	CRect rcText = lpDIS->rcItem;
	rcText.left+= IMAGE_SIZE+10;
	rcText.top+= 3;

	pDC->DrawText(*pStr, pStr->GetLength(), rcText, DT_LEFT|DT_WORDBREAK|DT_TOP); 
	pDC->SetTextColor(crOldTextColor);

	str.ReleaseBuffer();

	ReleaseDC(pDC);
}
