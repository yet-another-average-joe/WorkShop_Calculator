#pragma once


// CEditEx

// redessine le texte pour que les edits désactivés
// ne soient pas écrits en grisé
//
// attrinut disabled + readonly ->
// attribut 


//#define TEXT_COLOR_DISABLED RGB(255,255,255)
//#define BK_COLOR_DISABLED RGB(100,50,200)

// style "enfoncé" pour indiquer le focus en mode scrollpad

class CEditEx : public CEdit
{
	DECLARE_DYNAMIC(CEditEx)
public:
	// change le texte de l'edit en empêchant le traitement de EN_CHANGE
	// dans la message map de la fenêtre parente

	CEditEx();
	virtual ~CEditEx();
	void SetWindowText_NoNotify(LPCTSTR lpszText);

	// après modifs, appeler RedrawWindow();
	COLORREF m_crBkColor;
	COLORREF m_crTextColor;
	COLORREF m_crBkColorDisabled;
	COLORREF m_crTextColorDisabled;
	COLORREF m_crBkColorReadOnly;
	COLORREF m_crTextColorReadOnly;
	// si TRUE, texte noir dans edit disabled
	// si disabled ET read only, le fond standard bleu (BTNFACE) est sélectionné
	// sinon fond blanc
	BOOL m_bNoGray;			// texte normal (pas grisé) sur edit désactivé
	BOOL m_bFrameFocus;		// frame affiché si focus
	BOOL m_bNoCaret;		// pas de caret (utile pour read only et désactivés)

protected:
	COLORREF m_crBkColorOld;
	CBrush m_brBkgnd;
	BOOL m_bNotify;

	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEnChange();
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
public:
	// traite OnPaint pour empêcher le texte grisé
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


