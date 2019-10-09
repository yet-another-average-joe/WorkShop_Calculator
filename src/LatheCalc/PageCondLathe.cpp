// PageCondTurning.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "LatheCalc.h"
#include "PageCondLathe.h"
//#include "SheetLatheCalc.h"

// les champs vides sont cachés ou simplement désacivés

// Boîte de dialogue CPageCondLathe

// A FAIRE :
// mmm

IMPLEMENT_DYNAMIC(CPageCondLathe, CPageCondBase)

CPageCondLathe::CPageCondLathe(CData* pData/*=NULL*/)
	: CPageCondBase(CPageCondLathe::IDD, pData)
{
	EnableScrollbars(FALSE);
}

CPageCondLathe::~CPageCondLathe()
{
}

BEGIN_MESSAGE_MAP(CPageCondLathe, CPageCondBase)
END_MESSAGE_MAP()

void CPageCondLathe::SetControlsPos()
{
	CPageCondBase::SetControlsPos();

	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER/*|SWP_NOREDRAW*/;

	//CRect rc;
	//m_staticVc.GetWindowRect(rc);
	//ScreenToClient(rc);
	//m_staticVc.SetWindowPos(NULL, ::GetSystemMetrics(SM_CXEDGE), rc.top, rc.Width(), rc.Height(), uFlags);
}
