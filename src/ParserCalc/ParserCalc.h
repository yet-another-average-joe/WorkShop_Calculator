// ParserCalc.h�: fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#include "AppSheet.h"
#include "resourceppc.h"

// CParserCalcApp:
// Consultez ParserCalc.cpp pour l'impl�mentation de cette classe
//

class CParserCalcApp : public CAppSheet
{
public:
	CParserCalcApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation

	DECLARE_MESSAGE_MAP()
};

extern CParserCalcApp theApp;
