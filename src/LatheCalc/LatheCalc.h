// LatheCalc.h�: fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resourceppc.h"
#include "AppSheet.h"

// CLatheCalcApp:
// Consultez LatheCalc.cpp pour l'impl�mentation de cette classe
//

class CLatheCalcApp : public CAppSheet
{
	DECLARE_DYNCREATE(CLatheCalcApp)

public:
	CLatheCalcApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation

	DECLARE_MESSAGE_MAP()
};

extern CLatheCalcApp theApp;
