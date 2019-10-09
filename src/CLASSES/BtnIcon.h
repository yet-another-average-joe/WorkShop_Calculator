#pragma once

#include "WinXPButtonST.h"

// CBtnIcon

class CBtnIcon : public CWinXPButtonST
{
public:
	CBtnIcon();
	virtual ~CBtnIcon();

	DWORD SetIconMulti(int nIcon, int nIconDis, CSize size);

protected:
	DECLARE_MESSAGE_MAP()
};


