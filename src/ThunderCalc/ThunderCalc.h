// ThunderCalc.h�: fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

#include "AppDlg.h"

// CThunderCalcApp:
// Consultez ThunderCalc.cpp pour l'impl�mentation de cette classe
//

class CThunderCalcApp : public CAppDlg
{
public:
	CThunderCalcApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation

	DECLARE_MESSAGE_MAP()
};

extern CThunderCalcApp theApp;
