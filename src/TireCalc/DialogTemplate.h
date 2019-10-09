// DialogTemplate.h: interface for the CDialogTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGTEMPLATE_H__AFBD7D89_7AF8_4A6F_9010_FFB279EC4696__INCLUDED_)
#define AFX_DIALOGTEMPLATE_H__AFBD7D89_7AF8_4A6F_9010_FFB279EC4696__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//
// This code is heavily based on a flipcode article on the same subject:
// http://www.flipcode.com/cgi-bin/msg.cgi?showThread=COTD-DialogTemplate&forum=cotd&id=-1
//


#define PUSHBUTTON		(WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON)
#define DEFPUSHBUTTON	(WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_DEFPUSHBUTTON)
#define RTEXT			(WS_CHILD|WS_VISIBLE|WS_GROUP|SS_RIGHT)


class CDialogTemplate  
{
public:
	CDialogTemplate();
	CDialogTemplate(LPCTSTR pszCaption, DWORD dwStyle, int x, int y, int w, int h,
					LPCTSTR pszFontName = NULL, WORD wFontSize = 8);
	virtual ~CDialogTemplate();

	void Header(LPCTSTR pszCaption, DWORD dwStyle, int x, int y, int w, int h,
				LPCTSTR pszFontName = NULL, WORD wFontSize = 8);

	bool IsValid() const {return m_pBuf != NULL;}

	bool AddButton(LPCTSTR pszCaption, DWORD dwStyle, DWORD dwExStyle, short x, short y, short cx, short cy, WORD nID);
	bool AddEdit(LPCTSTR pszCaption, DWORD dwStyle, DWORD dwExStyle, short x, short y, short cx, short cy, WORD nID);
	bool AddStatic(LPCTSTR pszCaption, DWORD dwStyle, DWORD dwExStyle, short x, short y, short cx, short cy, WORD nID);
	bool AddList(LPCTSTR pszCaption, DWORD dwStyle, DWORD dwExStyle, short x, short y, short cx, short cy, WORD nID);
	bool AddScroll(LPCTSTR pszCaption, DWORD dwStyle, DWORD dwExStyle, short x, short y, short cx, short cy, WORD nID);
	bool AddCombo(LPCTSTR pszCaption, DWORD dwStyle, DWORD dwExStyle, short x, short y, short cx, short cy, WORD nID);

	//! Adds a dialog item template
	bool AddItem(LPCTSTR pszType, LPCTSTR pszCaption, const DLGITEMTEMPLATE &item);

	operator const DLGTEMPLATE* () const
	{
		ASSERT(IsValid());
		return (DLGTEMPLATE*) m_pBuf;
	}

protected:
	char*		m_pBuf;
	int			m_nMax,
				m_nPos;

	void Construct();

	//! Aligns the next insertion point.
	bool Align(int nSize);

	bool Add(LPCTSTR pszStr) {return Add(pszStr, sizeof(wchar_t) * (wcslen(pszStr) + 1));}

	bool Add(WORD wData) {return Add(&wData, sizeof(WORD));}

	bool Add(const void *pData, int nSize);

	bool AddControl(WORD wType, LPCTSTR pszCaption, const DLGITEMTEMPLATE &item);
	
	bool Alloc(int nSize);
};

#endif // !defined(AFX_DIALOGTEMPLATE_H__AFBD7D89_7AF8_4A6F_9010_FFB279EC4696__INCLUDED_)
