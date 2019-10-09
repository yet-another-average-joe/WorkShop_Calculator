#pragma once


// CEditEx

// redessine le texte pour que les edits d�sactiv�s
// ne soient pas �crits en gris�
//
// attrinut disabled + readonly ->
// attribut 


//#define TEXT_COLOR_DISABLED RGB(255,255,255)
//#define BK_COLOR_DISABLED RGB(100,50,200)

// style "enfonc�" pour indiquer le focus en mode scrollpad

class CEditEx : public CEdit
{
	DECLARE_DYNAMIC(CEditEx)
public:
	// change le texte de l'edit en emp�chant le traitement de EN_CHANGE
	// dans la message map de la fen�tre parente

	CEditEx();
	virtual ~CEditEx();
	void SetWindowText_NoNotify(LPCTSTR lpszText);

	// apr�s modifs, appeler RedrawWindow();
	COLORREF m_crBkColor;
	COLORREF m_crTextColor;
	COLORREF m_crBkColorDisabled;
	COLORREF m_crTextColorDisabled;
	COLORREF m_crBkColorReadOnly;
	COLORREF m_crTextColorReadOnly;
	// si TRUE, texte noir dans edit disabled
	// si disabled ET read only, le fond standard bleu (BTNFACE) est s�lectionn�
	// sinon fond blanc
	BOOL m_bNoGray;			// texte normal (pas gris�) sur edit d�sactiv�
	BOOL m_bFrameFocus;		// frame affich� si focus
	BOOL m_bNoCaret;		// pas de caret (utile pour read only et d�sactiv�s)

protected:
	COLORREF m_crBkColorOld;
	CBrush m_brBkgnd;
	BOOL m_bNotify;

	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEnChange();
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
public:
	// traite OnPaint pour emp�cher le texte gris�
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


