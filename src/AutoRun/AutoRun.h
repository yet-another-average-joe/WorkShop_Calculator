// AutoRun.h�: fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

// CAutoRunApp:
// Consultez AutoRun.cpp pour l'impl�mentation de cette classe
//

class CAutoRunApp : public CWinApp
{
public:
	CAutoRunApp();
	
// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation
	BOOL m_bLaunched; // mis � TRUE si WrkShpCalc.exe a �t� lanc�

	DECLARE_MESSAGE_MAP()
};

extern CAutoRunApp theApp;
