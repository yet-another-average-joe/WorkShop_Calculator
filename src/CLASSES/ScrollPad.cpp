// MagicSlider.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ScrollPad.h"

// CScrollPad

IMPLEMENT_DYNAMIC(CScrollPad, CStatic)

CScrollPad::CScrollPad()
{
	m_br.CreateSysColorBrush(COLOR_BTNFACE);
	m_brHilight.CreateSysColorBrush(COLOR_BTNTEXT);
	m_bDragging=FALSE;
	m_nSensitivity=10; // 10px par défaut
}

CScrollPad::~CScrollPad()
{
}

BEGIN_MESSAGE_MAP(CScrollPad, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// Gestionnaires de messages de CScrollPad

void CScrollPad::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDragging = TRUE;
	m_bDragChanged = FALSE;
	SetCapture();
	SetFocus();

	m_bDragChanged = TRUE;
	m_pt=point;
	m_dy=0;
	PostMessageToParent();//WM_VSCROLL);
	Invalidate(TRUE);
}

void CScrollPad::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDragging)
	{
		m_bDragChanged = TRUE;
		//m_dy+=point.y-m_pt.y;
		m_dy-=point.y-m_pt.y;
		m_pt=point;

		//if(fabs(m_dy)>=SENSIVITY)
		if(abs(m_dy)>=m_nSensitivity)
		{
			PostMessageToParent();//WM_VSCROLL);
			m_dy=0;
		}
	}
}

void CScrollPad::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_bDragging)
	{
		m_bDragging = FALSE;
		::ReleaseCapture();
		//m_dy+=point.y-m_pt.y;
		m_dy-=point.y-m_pt.y;
		m_pt=point;

		m_bDragChanged = TRUE;

		//if(m_bDragChanged && fabs(m_dy)>=SENSIVITY)
		if(m_bDragChanged && abs(m_dy)>=m_nSensitivity)
		{
			PostMessageToParent();//WM_VSCROLL);
			m_bDragChanged = FALSE;
		}
	}

	m_dy=0;
	Invalidate(TRUE);
}

void CScrollPad::PostMessageToParent()//const int nTBCode)// const
{
	CWnd* pWnd = GetParent();
	if(!::IsWindow(pWnd->GetSafeHwnd())) 
		return;

	// envoyer un tick tous les N pixels ; "N pixel" : SENSIVITY (voir OnMouseMove())
	if(m_dy>0) 
		pWnd->PostMessage(WM_VSCROLL, SB_LINEUP, (LPARAM)GetSafeHwnd());
	else if(m_dy<0) 
		pWnd->PostMessage(WM_VSCROLL, SB_LINEDOWN, (LPARAM)GetSafeHwnd());
}


void CScrollPad::OnSetFocus(CWnd* pOldWnd)
{
	// restituer le focus à la fenêtre qui était sélectionnée
	// ordre ??
	pOldWnd->SetFocus();
	CStatic::OnSetFocus(pOldWnd);
}

void CScrollPad::OnPaint()
{
	CPaintDC dc(this);

	PaintGradient(&dc);
}

BOOL CScrollPad::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CScrollPad::PaintGradient(CDC* pDC)
{
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(rect);

	COLORREF cr1=::GetSysColor(COLOR_ACTIVECAPTION);
	COLORREF cr2=::GetSysColor(COLOR_BTNFACE);

	int r1=GetRValue(cr1);
	int g1=GetGValue(cr1);
	int b1=GetBValue(cr1);
	int r2=GetRValue(cr2);
	int g2=GetGValue(cr2);
	int b2=GetBValue(cr2);

	if(m_bDragging)
	{
		cr2=::GetSysColor(COLOR_ACTIVECAPTION);
		cr1=::GetSysColor(COLOR_BTNFACE);

		r2=220;
		g2=255;
		b2=220;
		r1=127;
		g1=127;
		b1=127;
	}
	else
	{
		cr1=RGB(127,0,0);//::GetSysColor(COLOR_ACTIVECAPTION);
		cr2=::GetSysColor(COLOR_BTNFACE);

		r1=GetRValue(cr1);
		g1=GetGValue(cr1);
		b1=GetBValue(cr1);
		r2=GetRValue(cr2);
		g2=GetGValue(cr2);
		b2=GetBValue(cr2);
	}

	for(int i=0;i<rect.Height();i+=10)
	{ 
		int r,g,b;
		r = r1 + (i * (r2-r1) / rect.Height());
		g = g1 + (i * (g2-g1) / rect.Height());
		b = b1 + (i * (b2-b1) / rect.Height());
		pDC->FillSolidRect(0, i, rect.Width(), 10,RGB(r,g,b));
	}
}
