// MillCalc.h�: fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resourceppc.h"
#include "AppSheet.h"

// CMillCalcApp:
// Consultez MillCalc.cpp pour l'impl�mentation de cette classe
//

class CMillCalcApp : public CAppSheet
{
	DECLARE_DYNCREATE(CMillCalcApp)

public:
	CMillCalcApp();

// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation
public:
	DECLARE_MESSAGE_MAP()
};

extern CMillCalcApp theApp;
