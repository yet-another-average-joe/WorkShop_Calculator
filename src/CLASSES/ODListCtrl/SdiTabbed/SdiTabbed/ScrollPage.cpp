// ScrollPropPage2.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ScrollPage.h"

// défilement SB_LINE

#define DELTAPOS_LINE	10

// Boîte de dialogue CScrollPage

IMPLEMENT_DYNAMIC(CScrollPage, CPage)

CScrollPage::CScrollPage(UINT nIDTemplate, CWnd* pParentWnd)
	: CPage(nIDTemplate),//, pParentWnd),
		m_nID(nIDTemplate)
{
	m_cxTemplate=0;
	m_cyTemplate=0;
	m_bRcTemplateOk = FALSE;
}

CScrollPage::~CScrollPage()
{
}

void CScrollPage::DoDataExchange(CDataExchange* pDX)
{
	CPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScrollPage, CPage)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

// Gestionnaires de messages de CScrollPage

BOOL CScrollPage::OnInitDialog()
{
	CPage::OnInitDialog();

	ScrollWindowEx(0, 0, NULL, NULL, NULL, NULL, SW_SCROLLCHILDREN); 
    SetScrollPos(SB_HORZ, 0, TRUE);
    SetScrollPos(SB_VERT, 0, TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

// si nDeltaPos < 0 : défilement vers le haut
// si nDeltaPos > 0 : défilement vers le bas
// scrollInfo.nMin = 0;
// scrollInfo.nMax = cyTemplate
// scrollInfo.nPage = cyClient
// scrollInfo.nPos : de 0 à (scrollInfo.nMax - scrollInfo.nPage)

// VScroll() se base sur scrollInfo pour les limites,
// scrolle et corrige scrollInfo.nPos si hors limites

void CScrollPage::ScrollBy(int nBar, int nDeltaPos) 
{
	if(nDeltaPos==0)
		return;

	SCROLLINFO scrollInfo;
    scrollInfo.cbSize = sizeof(SCROLLINFO); 
    scrollInfo.fMask = SIF_POS|SIF_RANGE|SIF_PAGE;

	BOOL bRet = GetScrollInfo(nBar, &scrollInfo, SIF_POS|SIF_RANGE|SIF_PAGE);

	int nScrollRange = scrollInfo.nMax - (int)scrollInfo.nPage; 

	// si ça veut monter trop haut
	if(scrollInfo.nPos + nDeltaPos < scrollInfo.nMin)
	{
		// scroller pour arriver au mini
		nDeltaPos = scrollInfo.nMin - scrollInfo.nPos;
		// position = minimum
		scrollInfo.nPos=scrollInfo.nMin;
	}
	else
	// si ça veut descendre trop bas
	if(scrollInfo.nPos + nDeltaPos > nScrollRange)
	{
		// scroller pour arriver au maxi
		nDeltaPos =  nScrollRange - scrollInfo.nPos;
		// position = maximum
		scrollInfo.nPos = nScrollRange;
	}
	else
		scrollInfo.nPos += nDeltaPos;
	
	SetScrollInfo(nBar, &scrollInfo, TRUE);
	if(nBar==SB_VERT)
		ScrollWindowEx(0, -nDeltaPos, NULL, NULL, NULL, NULL, SW_SCROLLCHILDREN);
	else
		ScrollWindowEx(-nDeltaPos, 0, NULL, NULL, NULL, NULL, SW_SCROLLCHILDREN);
}

void CScrollPage::OnScroll(int nBar, UINT nSBCode, UINT nPos)
{
	SCROLLINFO scrollInfo;
    scrollInfo.cbSize = sizeof(SCROLLINFO); 
    scrollInfo.fMask = SIF_POS|SIF_RANGE|SIF_PAGE;

	BOOL bRet = GetScrollInfo(nBar, &scrollInfo, SIF_POS|SIF_RANGE|SIF_PAGE);

	int nDeltaPos=0;

	switch (nSBCode)
	{
// inutile
//		case SB_TOP: break;
//		case SB_BOTTOM: break;

		case SB_LINEUP:			nDeltaPos = -DELTAPOS_LINE; break;
		case SB_LINEDOWN:		nDeltaPos = DELTAPOS_LINE; break;
		case SB_PAGEUP:			nDeltaPos = -(int)scrollInfo.nPage;	break;
		case SB_PAGEDOWN:		nDeltaPos = (int)scrollInfo.nPage; break;
		case SB_THUMBTRACK:		nDeltaPos=nPos-scrollInfo.nPos;	break;
		default:				nDeltaPos = 0;	break;
	}

	ScrollBy(nBar, nDeltaPos);
}

void CScrollPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnScroll(SB_HORZ, nSBCode, nPos);

	CPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CScrollPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	OnScroll(SB_VERT, nSBCode, nPos);

	CPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CScrollPage::SaveTemplateSize(int cx, int cy)
{
	if(!m_bRcTemplateOk)
	{
		m_cxTemplate=cx;
		m_cyTemplate=cy;
		m_bRcTemplateOk = TRUE;
	}
}

void CScrollPage::OnSize(UINT nType, int cx, int cy)
{
	// 1er appel : dimensions de la resource -> à récupérer
	SaveTemplateSize(cx, cy);
	// régler la scrollbar verticale en fonction du template et du nouveau cy
	// il faut corriger le rectrangle client en fonction du TabCtrl parent.
	
	int dx=0;
	int dy=0;

	if(GetParent()->IsKindOf(RUNTIME_CLASS(CTabCtrl)))
	{
		// correction : hauteur du TabCtrl
		CRect rc;
		((CTabCtrl*)GetParent())->GetItemRect(0, rc);
		dy=rc.Height()+2;
	}

	SetScrollbar(SB_HORZ, cx);
	SetScrollbar(SB_VERT, cy+dy);

	CPage::OnSize(nType, cx, cy);
}

void CScrollPage::SetScrollbar(int nBar, int cx)
{
	SCROLLINFO scrollInfo;

    scrollInfo.cbSize = sizeof(SCROLLINFO); 
    scrollInfo.fMask = SIF_POS|SIF_RANGE|SIF_PAGE;

	// sauvegarde des anciens paramètres

	GetScrollInfo(nBar, &scrollInfo, SIF_POS|SIF_RANGE|SIF_PAGE);
	int nPosOld = scrollInfo.nPos;
	int cxClientOld = scrollInfo.nPage;
	int nScrollRangeOld = (nBar==SB_HORZ?m_cxTemplate:m_cyTemplate) - cxClientOld; 
	int nRemainScrollOld = nScrollRangeOld - nPosOld;
	int cxDeltaClient = cx - cxClientOld;

	// valeurs actualisées pour scrollInfo, sauf nPos qui doit être corrigé

	scrollInfo.nMin = 0;
	scrollInfo.nMax = nBar==SB_HORZ?m_cxTemplate:m_cyTemplate; // invariable, mais obligé de mettre à jour à chaque fois...
	scrollInfo.nPage = cx;

	// calculer le décalage au cas où la fenêtre est augmentée 
	// après avoir été secrollée vers le maxi, 
	// scroller la fenêtre au maxi et corriger la scrollbar

	int nDelta = 0;
	// si ce qui reste de scrolling se trouve dans la zone du clavier virtuel
	if(nRemainScrollOld <= cxDeltaClient)
	{
		nDelta = cxDeltaClient - nRemainScrollOld;
		scrollInfo.nPos = nPosOld - 2*nDelta;

		SetScrollInfo(nBar, &scrollInfo, TRUE);
		ScrollBy(nBar, -nDelta);
		// à ce stade, le scrolling est correct
		// mais la barre de scrolling est incorrecte
		// correction en sens inverse: 
		scrollInfo.nPos+=nDelta;
	}
	
	SetScrollInfo(nBar, &scrollInfo, TRUE);
}
