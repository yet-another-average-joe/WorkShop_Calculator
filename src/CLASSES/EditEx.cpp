// EditEx.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "EditEx.h"

  #define RED        RGB(127,  0,  0)
  #define GREEN      RGB(  0,127,  0)
  #define BLUE       RGB(  0,  0,127)
  #define LIGHTRED   RGB(255,  0,  0)
  #define LIGHTGREEN RGB(  0,255,  0)
  #define LIGHTBLUE  RGB(  0,  0,255)
  #define BLACK      RGB(  0,  0,  0)
  #define WHITE      RGB(255,255,255)
  #define GRAY       RGB(192,192,192)

// CEditEx

IMPLEMENT_DYNAMIC(CEditEx, CEdit)

CEditEx::CEditEx()
{
	m_bNotify=TRUE;

	m_crBkColor				= ::GetSysColor(COLOR_WINDOW);
	m_crTextColor			= ::GetSysColor(COLOR_WINDOWTEXT);
	m_crBkColorDisabled		= ::GetSysColor(COLOR_WINDOW);
	m_crTextColorDisabled	= ::GetSysColor(COLOR_GRAYTEXT);
	m_crBkColorReadOnly		= ::GetSysColor(COLOR_BTNFACE);
	m_crTextColorReadOnly	= ::GetSysColor(COLOR_WINDOWTEXT);
	m_bNoGray				= FALSE;
	m_bNoCaret				= FALSE;
	m_bFrameFocus			= FALSE;

	m_brBkgnd.CreateSolidBrush(m_crBkColor); 
}

CEditEx::~CEditEx()
{
	m_brBkgnd.DeleteObject();
}

BEGIN_MESSAGE_MAP(CEditEx, CEdit)
	ON_CONTROL_REFLECT_EX(EN_CHANGE, &CEditEx::OnEnChange)
//	ON_WM_CTLCOLOR_REFLECT()
ON_WM_PAINT()
ON_WM_SETFOCUS()
ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// Gestionnaires de messages de CEditEx

void CEditEx::SetWindowText_NoNotify(LPCTSTR lpszText)
{
	ASSERT(lpszText!=NULL);
	CString strOld;
	GetWindowText(strOld);

	if(strOld == lpszText)
		return; // do nothing, already set
	
	BOOL bPrevious = m_bNotify;
	m_bNotify = FALSE;
	SetWindowText(lpszText);
	m_bNotify = bPrevious;
}

BOOL CEditEx::OnEnChange()
{
	return !m_bNotify;
}
   
HBRUSH CEditEx::CtlColor(CDC* pDC, UINT nCtlColor)
{
	COLORREF crBkColor;
	COLORREF crTextColor;

	if(IsWindowEnabled())
	{
		if(GetStyle() & ES_READONLY)
		{
			crBkColor=m_crBkColorReadOnly;
			crTextColor=m_crTextColorReadOnly;
		}
		else
		{
			crBkColor=m_crBkColor;
			crTextColor=m_crTextColor;
		}
	}
	else
	{
		if(GetStyle() & ES_READONLY)
			crBkColor=m_crBkColorReadOnly;
		else
			crBkColor=m_crBkColorDisabled;

		if(m_bNoGray)
			crTextColor=m_crTextColor;
		else
			crTextColor=m_crTextColorDisabled;
	}
	
	HBRUSH hbr;
	hbr = (HBRUSH)m_brBkgnd;
	pDC->SetBkColor(crBkColor);
	pDC->SetTextColor(crTextColor);

	return hbr;
}

void CEditEx::OnPaint()
{
	COLORREF crBkColor;
	COLORREF crTextColor;

	if(IsWindowEnabled())
	{
		if(GetStyle() & ES_READONLY)
		{
			crBkColor=m_crBkColorReadOnly;
			crTextColor=m_crTextColorReadOnly;
		}
		else
		{
			crBkColor=m_crBkColor;
			crTextColor=m_crTextColor;
		}
	}
	else
	{
		if(GetStyle() & ES_READONLY)
			crBkColor=m_crBkColorReadOnly;
		else
			crBkColor=m_crBkColorDisabled;

		if(m_bNoGray)
			crTextColor=m_crTextColor;
		else
			crTextColor=m_crTextColorDisabled;
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
	else 
		if (winStyle & ES_RIGHT)
			style = DT_RIGHT;
		else
			style = DT_LEFT;

	if (winStyle & ES_MULTILINE)
		style|=DT_WORDBREAK;
	
	dc.DrawText(str, &rect, style);
}

// style "enfoncé" pour indiquer le focus en mode scrollpad

// jamais appelées
void CEditEx::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);

	if(GetStyle() && ES_READONLY && m_bNoCaret)
		DestroyCaret();

	if(m_bFrameFocus)
	{
		ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);
		//SetSel(0, -1);
		//PostMessage(WM_KEYDOWN,VK_END,0);	
		PostMessage( EM_SETSEL,   0, -1);
	}

}

void CEditEx::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	if(m_bFrameFocus)
		ModifyStyleEx(WS_EX_CLIENTEDGE, 0,SWP_FRAMECHANGED);
}
