// DlgNoMatFile.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "DlgNoMatFile.h"
#include "CLASSES_rc.h"


// Bo�te de dialogue CDlgNoToolFile

IMPLEMENT_DYNAMIC(CDlgNoMatFile, CCEDialog)

CDlgNoMatFile::CDlgNoMatFile(CWnd* pParent /*=NULL*/)
	: CCEDialog(CLASSES_IDD_NOMATFILE, pParent)
{
	m_nStyle=CEMB_OKQUIT;
}

CDlgNoMatFile::~CDlgNoMatFile()
{
}

void CDlgNoMatFile::DoDataExchange(CDataExchange* pDX)
{
	CCEDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgNoMatFile, CCEDialog)
END_MESSAGE_MAP()


// Gestionnaires de messages de CDlgNoToolFile

