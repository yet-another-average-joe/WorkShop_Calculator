#pragma once
#include "EditInteger.h"
#include "ComboEx.h"


// CComboInteger

class CComboInteger : public CComboEx
{
	DECLARE_DYNAMIC(CComboInteger)

public:
	CComboInteger();
	virtual ~CComboInteger();
	BOOL m_fSigned; // = FALSE par défaut

	int AddNumber(int n);

	// lecture de la valeur
	// la façon de la récupérer est fonction du gestionnaire de message
	// ATTEBTION à bien utiliser la bonne fonction selon le contecte
	// sinon résultats pouvant être incorrects
	int GetCurSelNumber(); // retourne la valeur sélectionnée : CBN_SELCHANGE
	int GetEditNumber(); // returne la valeur de l'EDIT : CBN_EDITCHANGE

	CEditInteger	m_edit;

protected:
	DECLARE_MESSAGE_MAP()
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


