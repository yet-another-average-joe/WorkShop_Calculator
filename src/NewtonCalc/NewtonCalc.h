// NewtonCalc.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

#include "AppDlg.h"

// CNewtonCalcApp:
// Consultez NewtonCalc.cpp pour l'implémentation de cette classe
//

class CNewtonCalcApp : public CAppDlg
{
public:
	CNewtonCalcApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CNewtonCalcApp theApp;
