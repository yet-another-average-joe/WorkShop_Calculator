#pragma once

#include "DecimalSupport.h"

// CStaticDecimal

class CStaticDecimal : public CStatic, public CDecimalSupport<CStaticDecimal>
{
	DECLARE_DYNAMIC(CStaticDecimal)

public:
	CStaticDecimal();
	virtual ~CStaticDecimal();
	void SetWindowText_NoNotify(LPCTSTR pszText) { SetWindowText(pszText); }

protected:
	DECLARE_MESSAGE_MAP()
};


