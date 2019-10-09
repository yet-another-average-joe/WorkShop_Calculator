// SubWnd.cpp: implementation of the CSubWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TireCalc.h"
#include "SubWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//---------------------------------------------------------------------------
//
//	CSubWnd
//
//---------------------------------------------------------------------------


CSubWnd::CSubWnd(DWORD dwStyle, const RECT &rc, UINT nID)
:	m_pWnd		(NULL),
	m_rc		(rc),
	m_dwStyle	(dwStyle),
	m_nID		(nID)
{

}


CSubWnd::CSubWnd(DWORD dwStyle, LPCTSTR pszText, int x, int y, int cx, int cy, UINT nID)
:	m_pWnd		(NULL),
	m_rc		(x, y, x + cx, y + cy),
	m_dwStyle	(dwStyle),
	m_nID		(nID),
	m_strText	(pszText)
{
}



CSubWnd::~CSubWnd()
{

}


//---------------------------------------------------------------------------
//
//	CSubWnd operations
//
//---------------------------------------------------------------------------


// CSubWnd::SetText
//
//		Sets the sub window text and repaints
//
void CSubWnd::SetText(LPCTSTR pszText)
{
	ASSERT(m_pWnd);

	m_strText = pszText;

	if(IsWindow(m_pWnd->GetSafeHwnd()))
		m_pWnd->InvalidateRect(&m_rc, FALSE);
}


// CSubWnd::Show
//
//		Shows or hides the sub window
//
void CSubWnd::Show(bool bShow)
{
	ASSERT(m_pWnd);

	if(bShow)
		m_dwStyle |= SWS_VISIBLE;
	else
		m_dwStyle &= ~SWS_VISIBLE;

	if(IsWindow(m_pWnd->GetSafeHwnd()))
		m_pWnd->InvalidateRect(&m_rc);
}


//---------------------------------------------------------------------------
//
//	CSubWnd virtual methods
//
//---------------------------------------------------------------------------


// CSubWnd::Paint
//
//		Empty paint handler
//
void CSubWnd::Paint(CDC &dc)
{
}


// CSubWnd::Click
//
//		Empty click handler
//
void CSubWnd::Click(DWORD dwClick, POINT pt)
{
}
