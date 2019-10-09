// TapCalc.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resourceppc.h"
#include "AppSheet.h"

// CTapCalcApp:
// Consultez TapCalc.cpp pour l'implémentation de cette classe
//

class CTapCalcApp : public CAppSheet
{
	DECLARE_DYNCREATE(CTapCalcApp)

public:
	CTapCalcApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CTapCalcApp theApp;
