// MatDb.h�: fichier d'en-t�te principal pour l'application MatDb
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resourceppc.h"
#include "AppSheet.h"

// CDrillcalcApp:
// Consultez MatDb.cpp pour l'impl�mentation de cette classe
//

class CDrillCalcApp : public CAppSheet
{
	DECLARE_DYNCREATE(CDrillCalcApp)

public:
	CDrillCalcApp();

// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation

	DECLARE_MESSAGE_MAP()
};

extern CDrillCalcApp theApp;
