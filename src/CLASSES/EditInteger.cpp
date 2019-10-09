// EditNumber.cpp : implementation file
//

#include "stdafx.h"
#include "EditInteger.h"

IMPLEMENT_DYNAMIC(CEditInteger, CEditEx)

CEditInteger::CEditInteger()
{
}

CEditInteger::~CEditInteger()
{
}


BEGIN_MESSAGE_MAP(CEditInteger, CEditEx)
	ON_WM_CHAR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditInteger message handlers

void CEditInteger::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (!strchr("0123456789", nChar) && nChar != VK_BACK && nChar != VK_RETURN) // 0x08 : BACKSPACE
	{
		MessageBeep(0);
		return;  
	}
   	
	CEditEx::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CEditInteger::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		// passer la requete de calcul a la fenetre parente
		//((CGCalc1View*)GetParent())->CalculateFormEngine();
	}
	
	return CEditEx::PreTranslateMessage(pMsg);
}
