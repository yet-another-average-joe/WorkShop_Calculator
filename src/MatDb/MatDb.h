// MatDb.h�: fichier d'en-t�te principal pour l'application MatDb
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resourceppc.h"
#include "CLASSES_rc.h"
#include "AppSheet.h"
#include "DlgCatMissing.h"

// CMatDbApp:
// Consultez MatDb.cpp pour l'impl�mentation de cette classe
//

class CMatDbApp : public CAppSheet
{
public:
	CMatDbApp();

// Substitutions
public:
	virtual BOOL InitInstance();

// Impl�mentation
public:

	DECLARE_MESSAGE_MAP()
	afx_msg void OnWrkShpCalc();
	afx_msg void OnAppAbout();
};

extern CMatDbApp theApp;
