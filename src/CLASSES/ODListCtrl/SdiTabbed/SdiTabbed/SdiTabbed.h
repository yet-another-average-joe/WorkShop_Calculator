// SdiTabbed.h�: fichier d'en-t�te principal pour l'application SdiTabbed
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resourceppc.h"

// CSdiTabbedApp:
// Consultez SdiTabbed.cpp pour l'impl�mentation de cette classe
//

class CSdiTabbedApp : public CWinApp
{
public:
	CSdiTabbedApp();

// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation
public:
	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()
};

extern CSdiTabbedApp theApp;
