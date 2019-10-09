// SubWnd.h: interface for the CSubWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBWND_H__CC1A06BA_247A_4D9C_B068_AC04739D4641__INCLUDED_)
#define AFX_SUBWND_H__CC1A06BA_247A_4D9C_B068_AC04739D4641__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define SWS_VISIBLE		0x00000001

#define CLICK_DOWN		0x00000001
#define CLICK_UP		0x00000002
#define CLICK_DOUBLE	0x00000004


class CSubWnd  
{
public:
	CSubWnd(DWORD dwStyle, const RECT &rc, UINT nID);
	CSubWnd(DWORD dwStyle, LPCTSTR pszText, int x, int y, int cx, int cy, UINT nID);
	virtual ~CSubWnd();

	/// Paints the control.
	virtual void Paint(CDC &dc);

	/// The control is being clicked.
	virtual void Click(DWORD dwClick, POINT pt);

	/// Sets the sub window container.
	void SetContainer(CWnd* pContainerWnd) {m_pWnd = pContainerWnd;}

	/// Sets the sub window text.
	void SetText(LPCTSTR pszText);

	/// Checks if the sub window is visible.
	bool IsVisible() {return m_dwStyle & SWS_VISIBLE;}

	/// Shows or hides the sub window.
	void Show(bool bShow = true);

	const CRect& GetRect() const {return m_rc;}

protected:
	CWnd*		m_pWnd;			//!< Parent window
	CRect		m_rc;			//!< Rectangle
	DWORD		m_dwStyle;		//!< Style
	UINT		m_nID;			//!< ID
	CString		m_strText;		//!< Text
};


#endif // !defined(AFX_SUBWND_H__CC1A06BA_247A_4D9C_B068_AC04739D4641__INCLUDED_)
