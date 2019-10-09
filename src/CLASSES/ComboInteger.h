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
	BOOL m_fSigned; // = FALSE par d�faut

	int AddNumber(int n);

	// lecture de la valeur
	// la fa�on de la r�cup�rer est fonction du gestionnaire de message
	// ATTEBTION � bien utiliser la bonne fonction selon le contecte
	// sinon r�sultats pouvant �tre incorrects
	int GetCurSelNumber(); // retourne la valeur s�lectionn�e : CBN_SELCHANGE
	int GetEditNumber(); // returne la valeur de l'EDIT : CBN_EDITCHANGE

	CEditInteger	m_edit;

protected:
	DECLARE_MESSAGE_MAP()
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


