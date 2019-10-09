// SubStatic.h: interface for the CSubStatic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBSTATIC_H__48F28FA2_AF30_4218_8969_1675AFD7FD9A__INCLUDED_)
#define AFX_SUBSTATIC_H__48F28FA2_AF30_4218_8969_1675AFD7FD9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SubWnd.h"


#define SSS_ROUND		0x0001000
#define SSS_LEFT		0x8000000
#define SSS_RIGHT		0x4000000
#define SSS_CENTER		0xC000000

#define SSS_ALIGN_MASK	0xC000000


class CSubStatic : public CSubWnd  
{
public:
	CSubStatic(DWORD dwStyle, const RECT &rc, UINT nID);
	CSubStatic(DWORD dwStyle, LPCTSTR pszText, int x, int y, int cx, int cy, UINT nID);
	virtual ~CSubStatic();

	virtual void Paint(CDC &dc);
};

#endif // !defined(AFX_SUBSTATIC_H__48F28FA2_AF30_4218_8969_1675AFD7FD9A__INCLUDED_)
