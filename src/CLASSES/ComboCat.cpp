// ComboMat.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ComboCat.h"

// CComboCat

IMPLEMENT_DYNAMIC(CComboCat, CComboEx)

CComboCat::CComboCat()
{

}

CComboCat::~CComboCat()
{
}

BEGIN_MESSAGE_MAP(CComboCat, CComboEx)
END_MESSAGE_MAP()

// Gestionnaires de messages de CComboCat

void CComboCat::SetCatList(CListCat* pListCat)
{
	ResetContent();

	POSITION pos=pListCat->GetHeadPosition();

	while(pos)
	{
		CCat* pCat = (CCat*)pListCat->GetNext(pos);
		ASSERT(pCat!=NULL);

		int nIndex=AddString(pCat->m_strName);

		if(nIndex==CB_ERR || nIndex==CB_ERRSPACE)
		{
			ASSERT(0);
			return;
		}

		if(SetItemDataPtr(nIndex, pCat)==CB_ERR)
		{
			ASSERT(0);
			return;
		}
	}
}
