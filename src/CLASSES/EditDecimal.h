#pragma once

//#include "EditEx.h"
#include "DecimalSupport.h"
#include "EditEx.h"
// CEditDecimal

#define NO_ENCHANGE

#define COLOR_BK_LOWER		RGB(0, 0, 255)
#define COLOR_TEXT_LOWER	RGB(255, 255, 255)

#define COLOR_BK_UPPER		RGB(255, 0, 0)
#define COLOR_TEXT_UPPER	RGB(255, 255, 255)


class CEditDecimal : public CEditEx, public CDecimalSupport<CEditDecimal>
{
	DECLARE_DYNAMIC(CEditDecimal)

public:
	CEditDecimal();
	virtual ~CEditDecimal();
	BOOL m_fSigned; // = FALSE par défaut
	// avec changement de couleurs si d est en dessous ou au dessus 
	// des limits de l'intervalle dLower -> dUpper
	double m_fLower;
	double m_fUpper;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	COLORREF m_crBkColorLower;
	COLORREF m_crTextColorLower;
	COLORREF m_crBkColorUpper;
	COLORREF m_crTextColorUpper;

	afx_msg void OnPaint();
};


