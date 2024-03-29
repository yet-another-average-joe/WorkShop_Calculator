// CEScrollPropPage.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "PropPageEx.h"
#include "PropSheetEx.h"
#include "CLASSES.h"

// PROBLEMEN STACK FAULT SI LARGEUR > 151 LORS DU CHANGEMENT D'ORIENTATION 

// d�filement SB_LINE

#define DELTAPOS_LINE_CX	(::GetSystemMetrics(SM_CXHSCROLL)/2) // 10 pixels en XGA, 20 en VGA
#define DELTAPOS_LINE_CY	(::GetSystemMetrics(SM_CYHSCROLL)/2) // 10 pixels en XGA, 20 en VGA

// laisse une petite marge en bas quand scrolling au max.
#define DELTA_CYDOC		0	//(-GetSystemMetrics(SM_CYHSCROLL)/2)

// taille id�lae pour ne pas avoir de barres de scrolling = 150x149
// �a laisse une marge � droite qui �vite de voir apparaitre une barre 
// de scrolling horizontale d�s qu'une verticale est n�cessaire


// IMPORTANT : GetScrollInfo() / SetScrollInfo() doit �tre utilis� avec SIF_ALL
// sinon, c'est n'importe quoi !!!!!!!!!!!!!!

// Bo�te de dialogue CPropPageEx

IMPLEMENT_DYNAMIC(CPropPageEx, CPropertyPage)

CPropPageEx::CPropPageEx(CData* pData)
{
	m_pData=pData;
	Init();
}

CPropPageEx::CPropPageEx(UINT nIDTemplate, CData* pData):
	CPropertyPage(nIDTemplate)
{
	m_pData=pData;
	Init();
}

CPropPageEx::~CPropPageEx()
{
}

void CPropPageEx::Init()
{
	m_cxTemplate=0;
	m_cyTemplate=0;
	m_fRcTemplateOk = FALSE;
	m_fEnableScrollbars = FALSE; // scrolling par d�faut
	m_fDoneDDE = FALSE;
}

void CPropPageEx::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	m_fDoneDDE = TRUE;
}

void CPropPageEx::EnableScrollbars(BOOL fEnable /*=TRUE*/)
{
	m_fEnableScrollbars=fEnable;
}

BEGIN_MESSAGE_MAP(CPropPageEx, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// Gestionnaires de messages de CPropPageEx

void CPropPageEx::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nID=0;

	if(pScrollBar!=NULL)
		nID=pScrollBar->GetDlgCtrlID();

	// si nID == 0 c'st la scollbar de la fen�tre, sinon c'est un contr�le
	// normalement, pScrollBar devrait �tre NULL si c'est une scrollbar de fen�tre
	// mais ce n'est aps le cas (tracer pour voir)

	if(m_fEnableScrollbars==TRUE && nID==0)
	{
		OnScroll(SB_HORZ, nSBCode, nPos);

		CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void CPropPageEx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nID=0;

	if(pScrollBar!=NULL)
		nID=pScrollBar->GetDlgCtrlID();

	// si nID == 0 c'st la scollbar de la fen�tre, sinon c'est un contr�le
	// normalement, pScrollBar devrait �tre NULL si c'est une scrollbar de fen�tre
	// mais ce n'est aps le cas (tracer pour voir)

	if(m_fEnableScrollbars==TRUE && nID==0)
	{
		OnScroll(SB_VERT, nSBCode, nPos);

		CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
	}
}

// si nDeltaPos < 0 : d�filement vers le haut
// si nDeltaPos > 0 : d�filement vers le bas
// scrollInfo.nMin = 0;
// scrollInfo.nMax = cyTemplate
// scrollInfo.nPage = cyClient
// scrollInfo.nPos : de 0 � (scrollInfo.nMax - scrollInfo.nPage)

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

void CPropPageEx::ScrollBy(int nBar, int nDeltaPos) 
{
	if(nDeltaPos==0)
		return;

	SCROLLINFO scrollInfo;
    scrollInfo.cbSize = sizeof(SCROLLINFO); 
    scrollInfo.fMask = SIF_POS|SIF_RANGE|SIF_PAGE;

	BOOL bRet = GetScrollInfo(nBar, &scrollInfo, SIF_POS|SIF_RANGE|SIF_PAGE);

	int nScrollRange = scrollInfo.nMax - (int)scrollInfo.nPage; 

	// si �a veut monter trop haut
	if(scrollInfo.nPos + nDeltaPos < scrollInfo.nMin)
	{
		// scroller pour arriver au mini
		nDeltaPos = scrollInfo.nMin - scrollInfo.nPos;
		// position = minimum
		scrollInfo.nPos=scrollInfo.nMin;
	}
	else
	// si �a veut descendre trop bas
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

void CPropPageEx::OnScroll(int nBar, UINT nSBCode, UINT nPos)
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

void CPropPageEx::SaveTemplateSize(int cx, int cy)
{
	if(!m_fRcTemplateOk)
	{
		m_cxTemplate=cx;
		m_cyTemplate=cy-DELTA_CYDOC;
		m_fRcTemplateOk = TRUE;
	}
}

void CPropPageEx::OnSize(UINT nType, int cx, int cy)
{
	// 1er appel : dimensions de la resource -> � r�cup�rer
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

	CPropertyPage::OnSize(nType, cx, cy);

	// si OnInitDialog() a �t� appel�e et les controles cr��s/initialis�s
	if(m_fDoneDDE)
		SetControlsPos();
}

void CPropPageEx::SetPage(int nBar, UINT nPageNew)
{
	SCROLLINFO scrollInfo;

    scrollInfo.cbSize = sizeof(SCROLLINFO); 
    scrollInfo.fMask = SIF_ALL;

	// sauvegarde des param�tres

	// plac� � ce niveau sinon stack fault et plantage ??????????????????????
	GetScrollInfo(nBar, &scrollInfo, SIF_ALL);

	int nDoc = nBar==SB_HORZ ? m_cxTemplate : m_cyTemplate;		// dimension du document

	// si la fen�tre est plus grande que le document
	if(nDoc<(int)nPageNew)
	{
		int nPos=GetScrollPos(nBar);
		
		// s'il a �t� scroll� dans une fen�tre r�duite, le recadrer
		
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

	// sauvegarde des param�tres

	//GetScrollInfo(nBar, &scrollInfo, SIF_ALL);

	scrollInfo.nMin = 0;
	scrollInfo.nMax = nDoc;
	scrollInfo.nTrackPos = 0;

	if(nPageNew == scrollInfo.nPage) // pas de changement : cas trivial
	{
		scrollInfo.nPage = nPageNew;				// mettre � jour la valeur de page
	}
	else
	if(nPageNew < scrollInfo.nPage) // la fen�tre diminue
	{
		scrollInfo.nPage = nPageNew;				// mettre � jour la valeur de page
	}
	else // la fen�tre augmente : cas non trivial
	{
		// la fen�tre ne risque pas de d�passer le document, c'est � dire que le document se situera 
		// en dessous du bas de la fen�tre agrandie
		// la fen�tre agrandie arrivera exactement en bas du document 
		if(nPageNew + scrollInfo.nPos == nDoc)
		{
			scrollInfo.nPage = nPageNew;				// mettre � jour la valeur de page
		}
		// la fen�tre agrandie ne d�passera pas le bas du document
		else
			if(nPageNew + scrollInfo.nPos < (UINT)nDoc) // cas trivial
			{
				scrollInfo.nPage = nPageNew;				// mettre � jour la valeur de page
			}
			else // la fen�tre agrandie d�passera le bas du document
			{
				// il faut scroller le document vers le bas pour l'amener en bas de la fen�tre agrandie

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

void CPropPageEx::OnPaint()
{
	// workaround pour afficher la CommandBar
	CPropertyPage::OnPaint();
	CWnd* pSheet= GetParent();

	::SendMessage(pSheet->GetSafeHwnd(), WM_PAINT, 0, 0);
}

BOOL CPropPageEx::CanChangePage()
{
	return TRUE;
}

BOOL CPropPageEx::OnSetActive()
{
	UpdatePage();

	return CPropertyPage::OnSetActive();
}

void CPropPageEx::UpdatePage()
{
	UpdateControlsStyles();	
}
