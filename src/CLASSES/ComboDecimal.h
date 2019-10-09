#pragma once
#include "ComboEx.h"

// CComboDecimal

#include "EditDecimal.h"

class CComboDecimal : public CComboEx, public CDecimalSupport<CComboDecimal>
{
	DECLARE_DYNAMIC(CComboDecimal)

public:
	CComboDecimal();
	virtual ~CComboDecimal();
	void SetWindowText_NoMap(LPCTSTR pszText) { SetWindowText(pszText); }
	int AddNumber(double fNumber, int count);

	// lecture de la valeur
	// la fa�on de la r�cup�rer est fonction du gestionnaire de message
	// ATTEBTION � bien utiliser la bonne fonction selon le contecte
	// sinon r�sultats pouvant �tre incorrects
	double GetCurSelNumber(); // retourne la valeur s�lectionn�e : CBN_SELCHANGE
	double GetEditNumber(); // returne la valeur de l'EDIT : CBN_EDITCHANGE
	CEditDecimal	m_edit;

protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
public:
	//afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


