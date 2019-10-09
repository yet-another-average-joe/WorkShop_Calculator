// ParserCalc.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#include "AppSheet.h"
#include "resourceppc.h"

// CParserCalcApp:
// Consultez ParserCalc.cpp pour l'implémentation de cette classe
//

class CParserCalcApp : public CAppSheet
{
public:
	CParserCalcApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CParserCalcApp theApp;
