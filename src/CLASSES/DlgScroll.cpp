// DlgScroll.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DlgScroll.h"

#define DELTAPOS_LINE_CX	(::GetSystemMetrics(SM_CXHSCROLL)/2) // 10 pixels en XGA, 20 en VGA
#define DELTAPOS_LINE_CY	(::GetSystemMetrics(SM_CYHSCROLL)/2) // 10 pixels en XGA, 20 en VGA

// sinon, la page est trop grande et apparition d'une barre de scrolling inutile
#define DELTA_CYDOC	(GetSystemMetrics(SM_CYHSCROLL)*2)
//#define _DELTA_CYDOC	(GetSystemMetrics(SM_CYHSCROLL)*2)

// Boîte de dialogue CDlgScroll

IMPLEMENT_DYNAMIC(CDlgScroll, CDialog)

CDlgScroll::CDlgScroll(UINT nIDTemplate, CWnd* pParentWnd /*= NULL*/)
	: CDialog(nIDTemplate, pParentWnd)
{
	Init();
}

void CDlgScroll::Init()
{
	m_cxTemplate=0;
	m_cyTemplate=0;
	m_fRcTemplateOk = FALSE;
	m_fEnableScrollbars = TRUE;//FALSE; // scrolling par défaut
	m_fDoneDDE = FALSE;
}

CDlgScroll::~CDlgScroll()
{
}

void CDlgScroll::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	m_fDoneDDE = TRUE;
}

BEGIN_MESSAGE_MAP(CDlgScroll, CDialog)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
//	ON_WM_PAINT()
END_MESSAGE_MAP()

// Gestionnaires de messages de CDlgScroll

void CDlgScroll::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nID=0;

	if(pScrollBar!=NULL)
		nID=pScrollBar->GetDlgCtrlID();

	// si nID == 0 c'st la scollbar de la fenêtre, sinon c'est un contrôle
	// normalement, pScrollBar devrait être NULL si c'est une scrollbar de fenêtre
	// mais ce n'est aps le cas (tracer pour voir)

	if(m_fEnableScrollbars==TRUE && nID==0)
	{
		OnScroll(SB_HORZ, nSBCode, nPos);

		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void CDlgScroll::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nID=0;

	if(pScrollBar!=NULL)
		nID=pScrollBar->GetDlgCtrlID();

	// si nID == 0 c'st la scollbar de la fenêtre, sinon c'est un contrôle
	// normalement, pScrollBar devrait être NULL si c'est une scrollbar de fenêtre
	// mais ce n'est aps le cas (tracer pour voir)

	if(m_fEnableScrollbars==TRUE && nID==0)
	{
		OnScroll(SB_VERT, nSBCode, nPos);

		CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	}
}

// si nDeltaPos < 0 : défilement vers le haut
// si nDeltaPos > 0 : défilement vers le bas
// scrollInfo.nMin = 0;
// scrollInfo.nMax = cyTemplate
// scrollInfo.nPage = cyClient
// scrollInfo.nPos : de 0 à (scrollInfo.nMax - scrollInfo.nPage)

// VScroll() se base sur scrollInfo pour les limites,
// scrolle et corrige scrollInfo.nPos si hors limites

// SDK :

// The nPage member must specify a value from 0 to nMax - nMin +1
//
//										> donc nPage compris entre de 0 et nMax-nMin+1
//
// The nPos member must specify a value between nMin and nMax - max( nPage- 1, 0). 
//
//										> donc nPos compris entre de 0 et max(0, nPage-1)
//
// If either value is beyond its range, the function sets it to a value that is just within the range. 


//	nPage compris entre de 0 et nMax-nMin+1
//	nPos compris entre de 0 et max(0, nPage-1)

void CDlgScroll::ScrollBy(int nBar, int nDeltaPos) 
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
		ScrollWindowEx(0, -nDeltaPos, NULL, NULL, NULL, NULL, SW_SCROLLCHILDREN|SW_ERASE|SW_INVALIDATE);
	else
		ScrollWindowEx(-nDeltaPos, 0, NULL, NULL, NULL, NULL, SW_SCROLLCHILDREN|SW_ERASE|SW_INVALIDATE);
}

void CDlgScroll::OnScroll(int nBar, UINT nSBCode, UINT nPos)
{
	SCROLLINFO scrollInfo;
    scrollInfo.cbSize = sizeof(SCROLLINFO); 
    scrollInfo.fMask = SIF_POS|SIF_RANGE|SIF_PAGE;

	BOOL bRet = GetScrollInfo(nBar, &scrollInfo, SIF_POS|SIF_RANGE|SIF_PAGE);

	int nDeltaPos=0;

	switch (nSBCode)
	{
		case SB_TOP: 
			ASSERT(0);
			break;
		case SB_BOTTOM: 
			ASSERT(0);
			break;

		case SB_LINEUP:			nDeltaPos = nBar==SB_HORZ?-DELTAPOS_LINE_CX:-DELTAPOS_LINE_CY; break;
		case SB_LINEDOWN:		nDeltaPos = nBar==SB_HORZ?DELTAPOS_LINE_CX:DELTAPOS_LINE_CY; break;
		case SB_PAGEUP:			nDeltaPos = -(int)scrollInfo.nPage;	break;
		case SB_PAGEDOWN:		nDeltaPos = (int)scrollInfo.nPage; break;
		case SB_THUMBTRACK:		nDeltaPos = nPos-scrollInfo.nPos;	break;
		default:				nDeltaPos = 0;	break;
	}

	if(nDeltaPos)
		ScrollBy(nBar, nDeltaPos);
}

void CDlgScroll::SaveTemplateSize(int cx, int cy)
{
	if(!m_fRcTemplateOk)
	{
		m_cxTemplate=cx-1;
		m_cyTemplate=cy-DELTA_CYDOC;
		m_fRcTemplateOk = TRUE;
	}
}

void CDlgScroll::OnSize(UINT nType, int cx, int cy)
{
	// 1er appel : dimensions de la resource -> à récupérer
	SaveTemplateSize(cx, cy);

	if(m_fEnableScrollbars)
	{
		SetPage(SB_HORZ, cx);
		SetPage(SB_VERT, cy);
	}
	else
	{
		SetPage(SB_HORZ, m_cxTemplate+1);
		SetPage(SB_VERT, m_cyTemplate+1);
	}

	CDialog::OnSize(nType, cx, cy);

	// si OnInitDialog() a été appelée et les controles créés/initialisés
	//if(m_fDoneDDE)
	//	SetControlsPos();
}

void CDlgScroll::SetPage(int nBar, UINT nPageNew)
{
	SCROLLINFO scrollInfo;

    scrollInfo.cbSize = sizeof(SCROLLINFO); 
    scrollInfo.fMask = SIF_ALL;

	// sauvegarde des paramètres

	// placé à ce niveau sinon stack fault et plantage ??????????????????????
	GetScrollInfo(nBar, &scrollInfo, SIF_ALL);

	int nDoc = nBar==SB_HORZ ? m_cxTemplate : m_cyTemplate;		// dimension du document

	// si la fenêtre est plus grande que le document
	if(nDoc<(int)nPageNew)
	{
		int nPos=GetScrollPos(nBar);
		
		// s'il a été scrollé dans une fenêtre réduite, le recadrer
		
		if(nPos>0)
			ScrollBy(nBar, -nPos);

		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO); 
		si.fMask = SIF_ALL;
		si.nMin = 0;
		si.nMax = nDoc;
		si.nPage = nPageNew;
		si.nPos = 0;
		si.nTrackPos = 0;
		SetScrollInfo(nBar, &si, TRUE/*FALSE*/); // il y a d'autres occasions de redessiner...
		return;
	}

	// sauvegarde des paramètres

	///GetScrollInfo(nBar, &scrollInfo, SIF_ALL);

	scrollInfo.nMin = 0;
	scrollInfo.nMax = nDoc;
	scrollInfo.nTrackPos = 0;

	if(nPageNew == scrollInfo.nPage) // pas de changement : cas trivial
	{
		scrollInfo.nPage = nPageNew;				// mettre à jour la valeur de page
	}
	else
	if(nPageNew < scrollInfo.nPage) // la fenêtre diminue
	{
		scrollInfo.nPage = nPageNew;				// mettre à jour la valeur de page
	}
	else // la fenêtre augmente : cas non trivial
	{
		// la fenêtre ne risque pas de dépasser le document, c'est à dire que le document se situera 
		// en dessous du bas de la fenêtre agrandie
		// la fenêtre agrandie arrivera exactement en bas du document 
		if(nPageNew + scrollInfo.nPos == nDoc)
		{
			scrollInfo.nPage = nPageNew;				// mettre à jour la valeur de page
		}
		// la fenêtre agrandie ne dépassera pas le bas du document
		else
			if(nPageNew + scrollInfo.nPos < (UINT)nDoc) // cas trivial
			{
				scrollInfo.nPage = nPageNew;				// mettre à jour la valeur de page
			}
			else // la fenêtre agrandie dépassera le bas du document
			{
				// il faut scroller le document vers le bas pour l'amener en bas de la fenêtre agrandie

				int nDeltaPos = (nPageNew - scrollInfo.nPage) - (nDoc - (scrollInfo.nPos + scrollInfo.nPage));
				ScrollBy(nBar, -nDeltaPos);
				//TRACE(_T("nDeltaPos=%d\n"), nDeltaPos);

				scrollInfo.fMask = SIF_ALL;
				scrollInfo.nPage = nPageNew;
				scrollInfo.nPos -= nDeltaPos;
				scrollInfo.nMin = 0;
				scrollInfo.nMax = nDoc;

				// puis corriger la scrollbar
				SetScrollInfo(nBar, &scrollInfo, TRUE);
				return;
			}
	}

	scrollInfo.fMask = SIF_ALL;
	SetScrollInfo(nBar, &scrollInfo, TRUE);
}

//void CDlgScroll::OnPaint()
//{
//	// workaround pour afficher la CommandBar
//	CDialog::OnPaint();
//	CWnd* pSheet= GetParent();
//
//	::SendMessage(pSheet->GetSafeHwnd(), WM_PAINT, 0, 0);
//}


