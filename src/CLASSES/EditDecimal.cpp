// EditDecimal.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "EditDecimal.h"


// CEditDecimal

IMPLEMENT_DYNAMIC(CEditDecimal, CEditEx)

CEditDecimal::CEditDecimal()
{
	m_fSigned=FALSE;
	m_fLower=0;
	m_fUpper=0;

	m_crTextColorLower = COLOR_TEXT_LOWER;
	m_crBkColorLower = COLOR_BK_LOWER;

	m_crTextColorUpper = COLOR_TEXT_UPPER;
	m_crBkColorUpper = COLOR_BK_UPPER;
}

CEditDecimal::~CEditDecimal()
{
}

BEGIN_MESSAGE_MAP(CEditDecimal, CEditEx)
	ON_WM_CHAR()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

// Gestionnaires de messages de CEditDecimal

void CEditDecimal::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// bloque le signe '-'

	if(m_fSigned==FALSE && nChar==m_NegativeSign[0])
	{
		MessageBeep(0);
		return;
	}

	BOOL bHandled = FALSE;
	CDecimalSupport<CEditDecimal>::OnChar(0, nChar, 0, bHandled);
	if (!bHandled)
		CEditEx::OnChar(nChar , nRepCnt,  nFlags);
}

void CEditDecimal::OnPaint()
{
	COLORREF crBkColor;
	COLORREF crTextColor;

	double d=0;
	GetDecimalValue(d);

	if(m_fLower<m_fUpper)
	{
		if(d<m_fLower)
		{
			crBkColor=m_crBkColorLower;
			crTextColor=m_crTextColorLower;
		}
		else 
		if(d>m_fUpper)
		{
			crBkColor=m_crBkColorUpper;
			crTextColor=m_crTextColorUpper;
		}
		else
		{
			crBkColor=m_crBkColor;
			crTextColor=m_crTextColor;
		}

		CPaintDC dc(this);
		CString str;
		dc.SelectObject(GetFont());
		GetWindowText(str);

		// récupérer la couleur du texte normal
		
		dc.SetTextColor(crTextColor);
		dc.SetBkColor(crBkColor);

		CRect rect;
		GetClientRect(&rect);
		dc.FillSolidRect(&rect, crBkColor);     
		GetRect(&rect);
		int winStyle = GetStyle();
		int style;
		if (winStyle & ES_CENTER)
		style = DT_CENTER;
		else if (winStyle & ES_RIGHT)
		style = DT_RIGHT;
		else
		style = DT_LEFT;
		dc.DrawText(str, &rect, style);
	}
		else
			CEditEx::OnPaint();
}

HBRUSH CEditDecimal::CtlColor(CDC* pDC, UINT nCtlColor)
{
	COLORREF crBkColor;
	COLORREF crTextColor;

	double d=0;
	GetDecimalValue(d);

	if(m_fLower<m_fUpper)
	{
		if(d<m_fLower)
		{
			crBkColor=m_crBkColorLower;
			crTextColor=m_crTextColorLower;
		}
		else 
		if(d>m_fUpper)
		{
			crBkColor=m_crBkColorUpper;
			crTextColor=m_crTextColorUpper;
		}
		else
		{
			crBkColor=m_crBkColor;
			crTextColor=m_crTextColor;
		}

	HBRUSH hbr;
	m_brBkgnd.DeleteObject();
	m_brBkgnd.CreateSolidBrush(crBkColor);
	hbr = (HBRUSH)m_brBkgnd;
	pDC->SetBkColor(crBkColor);
	pDC->SetTextColor(crTextColor);

	return hbr;
	}
	else
		return CEditEx::CtlColor(pDC, nCtlColor);
}

