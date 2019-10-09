// SubButton.h: interface for the CSubButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBBUTTON_H__F09B3CE2_3DB5_41AA_B4F0_3667510B98EA__INCLUDED_)
#define AFX_SUBBUTTON_H__F09B3CE2_3DB5_41AA_B4F0_3667510B98EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SubWnd.h"


#define SBS_ACTIVE		0x8000000
#define SBS_ROUND		0x0001000


class CSubButton : public CSubWnd  
{
public:
	CSubButton(DWORD dwStyle, const RECT &rc, UINT nID);
	CSubButton(DWORD dwStyle, LPCTSTR pszText, int x, int y, int cx, int cy, UINT nID);
	virtual ~CSubButton();

	virtual void Paint(CDC &dc);
	virtual void Click(DWORD dwClick, POINT pt);

	bool IsActive() {return (m_dwStyle & SBS_ACTIVE) == SBS_ACTIVE;}

	void Activate(bool bActivate = true);
};

#endif // !defined(AFX_SUBBUTTON_H__F09B3CE2_3DB5_41AA_B4F0_3667510B98EA__INCLUDED_)
