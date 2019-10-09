// DlfNoToolFile.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DlgNoToolFile.h"
#include "CLASSES_rc.h"


// Boîte de dialogue CDlgNoToolFile

IMPLEMENT_DYNAMIC(CDlgNoToolFile, CCEDialog)

CDlgNoToolFile::CDlgNoToolFile(CWnd* pParent /*=NULL*/)
	: CCEDialog(CLASSES_IDD_NOTOOLFILE, pParent)
{
	m_nStyle=CEMB_OK;//QUIT;
}

CDlgNoToolFile::~CDlgNoToolFile()
{
}

void CDlgNoToolFile::DoDataExchange(CDataExchange* pDX)
{
	CCEDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgNoToolFile, CCEDialog)
END_MESSAGE_MAP()


// Gestionnaires de messages de CDlgNoToolFile

