// BmpStatic.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "StaticBmp.h"

// CStaticBmp

IMPLEMENT_DYNAMIC(CStaticBmp, CStatic)

CStaticBmp::CStaticBmp(BOOL bSquare)
{
	m_bSquare=bSquare;
}

CStaticBmp::~CStaticBmp()
{
}

void CStaticBmp::SetBmp(int nID)
{
	m_nBmpID = nID;
}

// Gestionnaires de messages de CStaticBmp

BEGIN_MESSAGE_MAP(CStaticBmp, CStatic)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CStaticBmp::OnPaint()
{
	CStatic::OnPaint(); // impératif, sinon problèmes avec l'arrière plan sous émulateur

	CDC* pDC = GetDC();

	if(m_nBmpID==NULL)
		return;

	CDC dcMem;
	BITMAP bmp;
	CBitmap* pBmp;

	CRect rect;
	GetClientRect(rect);
	int cxClient = rect.Width();
	int cyClient = rect.Height();

	pBmp=new CBitmap();
	pBmp->LoadBitmapW(MAKEINTRESOURCE(m_nBmpID));
	pBmp->GetBitmap(&bmp);

	dcMem.CreateCompatibleDC(pDC);
	dcMem.SelectObject(pBmp);

	int bkmodeOld=pDC->SetBkMode(TRANSPARENT);
	pDC->StretchBlt(0, 0, cxClient, cyClient, &dcMem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	pDC->SetBkMode(bkmodeOld);

	pBmp->DeleteObject();
	pBmp->Detach();
	delete pBmp;
}

void CStaticBmp::PreSubclassWindow()
{
	// TODO : ajoutez ici votre code spécialisé et/ou l'appel de la classe de base

	CStatic::PreSubclassWindow();
	ModifyStyle(0, SS_OWNERDRAW);
}
