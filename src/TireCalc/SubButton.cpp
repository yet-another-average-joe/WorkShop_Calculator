// SubButton.cpp: implementation of the CSubButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SubButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//---------------------------------------------------------------------------
//
//	CSubButton
//
//---------------------------------------------------------------------------


CSubButton::CSubButton(DWORD dwStyle, const RECT &rc, UINT nID)
:	CSubWnd	(dwStyle, rc, nID)
{

}


CSubButton::CSubButton(DWORD dwStyle, LPCTSTR pszText, int x, int y, int cx, int cy, UINT nID)
:	CSubWnd(dwStyle, pszText, x, y, cx, cy, nID)
{
}


CSubButton::~CSubButton()
{

}


// CSubButton::Activate
//
//		Activates or deactivates the buton
//
void CSubButton::Activate(bool bActivate)
{
	ASSERT(m_pWnd);

	if(bActivate)
		m_dwStyle |= SBS_ACTIVE;
	else
		m_dwStyle &= ~SBS_ACTIVE;

	if(IsVisible())
	{
		CClientDC	dc(m_pWnd);

		Paint(dc);
	}
}


//---------------------------------------------------------------------------
//
//	CSubButton virtual methods
//
//---------------------------------------------------------------------------


// CSubButton::Paint
//
//		Paints the button
//
void CSubButton::Paint(CDC &dc)
{

	CBrush		brush;
	CBrush*		pOldBrush;
	COLORREF	rgbBack,
				rgbText,
				rgbOldT,
				rgbOldB;

	ASSERT(m_pWnd);

	//
	// Create the painting objects
	//
	if(IsActive())
	{
		rgbBack = RGB(  0,  0,  0);
		rgbText	= RGB(255,255,255);
	}
	else
	{
		rgbBack = RGB(192,192,192);
		rgbText = RGB(  0,  0,  0);
	}

	brush.CreateSolidBrush(rgbBack);

	pOldBrush	= dc.SelectObject(&brush);
	rgbOldT		= dc.SetTextColor(rgbText);
	rgbOldB		= dc.SetBkColor  (rgbBack);

	//
	// Draw the button
	//
	if(m_dwStyle & SBS_ROUND)
	{
		POINT	pt = {8, 8};

		dc.RoundRect(&m_rc, pt);
	}
	else
		dc.Rectangle(&m_rc);
	dc.DrawText(m_strText, &m_rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	dc.SetTextColor(rgbOldT);
	dc.SetBkColor  (rgbOldB);
	dc.SelectObject(pOldBrush);
}


// CSubButton::Click
//
//		Empty click handler
//
void CSubButton::Click(DWORD dwClick, POINT pt)
{
	bool	bOn	= (dwClick & CLICK_DOWN);

	ASSERT(m_pWnd);

	//
	// Make a double click work right
	//
	if(dwClick & CLICK_DOUBLE)
		Click(CLICK_UP,	pt);

	if(m_rc.PtInRect(pt))
	{
		//
		// Inside this button
		//
		if(IsActive() && !bOn)
		{
			CWnd*	pParent = m_pWnd->GetParent();

			if(pParent)
				pParent->SendMessage(WM_COMMAND, m_nID, (LPARAM)m_pWnd->GetSafeHwnd());
		}

		Activate(bOn);
	}
	else
	{
		//
		// Outside this button
		//
		if(IsActive())
			Activate(false);
	}
}
