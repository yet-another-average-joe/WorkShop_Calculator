// AutoRun.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

// CAutoRunApp:
// Consultez AutoRun.cpp pour l'implémentation de cette classe
//

class CAutoRunApp : public CWinApp
{
public:
	CAutoRunApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation
	BOOL m_bLaunched; // mis à TRUE si WrkShpCalc.exe a été lancé

	DECLARE_MESSAGE_MAP()
};

extern CAutoRunApp theApp;
