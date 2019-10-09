// SubStatic.cpp: implementation of the CSubStatic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TireCalc.h"
#include "SubStatic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//---------------------------------------------------------------------------
//
//	CSubStatic
//
//---------------------------------------------------------------------------


CSubStatic::CSubStatic(DWORD dwStyle, const RECT &rc, UINT nID)
:	CSubWnd	(dwStyle, rc, nID)
{

}


CSubStatic::CSubStatic(DWORD dwStyle, LPCTSTR pszText, int x, int y, int cx, int cy, UINT nID)
:	CSubWnd(dwStyle, pszText, x, y, cx, cy, nID)
{
}


CSubStatic::~CSubStatic()
{

}


//---------------------------------------------------------------------------
//
//	CSubStatic virtual methods
//
//---------------------------------------------------------------------------


// CSubStatic::Paint
//
//		Paints the button
//
void CSubStatic::Paint(CDC &dc)
{
	CRect	rc(m_rc);
	UINT	nFormat	= DT_SINGLELINE | DT_VCENTER;

	ASSERT(m_pWnd);

	//
	// Draw the static
	//
	if(m_dwStyle & SSS_ROUND)
	{
		POINT	pt = {8, 8};

		dc.RoundRect(&m_rc, pt);
	}
	else
		dc.Rectangle(&m_rc);

	rc.DeflateRect(2, 2);

	switch(m_dwStyle & SSS_ALIGN_MASK)
	{
	case SSS_LEFT:
		nFormat |= DT_LEFT;
		break;

	case SSS_RIGHT:
		nFormat |= DT_RIGHT;
		break;

	case SSS_CENTER:
		nFormat |= DT_CENTER;
		break;

	default:
		nFormat |= DT_LEFT;
	}

	dc.DrawText(m_strText, &rc, nFormat);
}
