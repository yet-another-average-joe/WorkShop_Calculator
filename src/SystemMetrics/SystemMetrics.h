// SystemMetrics.h�: fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

#include "AppDlg.h"

// CSystemMetricsApp:
// Consultez SystemMetrics.cpp pour l'impl�mentation de cette classe
//

class CSystemMetricsApp : public CAppDlg
{
public:
	CSystemMetricsApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation

	DECLARE_MESSAGE_MAP()
};

extern CSystemMetricsApp theApp;
