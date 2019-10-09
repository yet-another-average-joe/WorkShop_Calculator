#pragma once

#include "PropPageEx.h"
#include "DataMatDb.h"
#include "EditEx.h"

// Boîte de dialogue CPageSearch

class CAlloy;

class CPageSearch : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageSearch)

public:
	CPageSearch(CData* pData);
	virtual ~CPageSearch();

	virtual BOOL CanChangePage() { return TRUE; }
	virtual void UpdatePage();

	virtual void UpdateControlsStyles();	

private:
	int Combo_Alloy_SetCurSel(CAlloy* pAlloy); // sélectionne une classe de matière dans la combobox
	CAlloy* Data_Alloy_GetCurSel();
	void Data_Cat_SetCurSel(CCat* pCat);
	void Data_Alloy_SetCurSel(CAlloy* pAlloy);
	POSITION Data_Cat_GetHeadPosition();
	CCat* Data_Cat_GetNext(POSITION& pos);

protected:
	virtual void SetControlsPos();

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_SEARCH };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()

	CStatic m_staticCat;
	CEditEx m_editCat;
	CStatic m_staticAlloy;
	CListBox m_listboxAlloy;

	afx_msg void OnLbnSelchangeListAlloy();
};

inline int CPageSearch::Combo_Alloy_SetCurSel(CAlloy* pAlloy)
{
	ASSERT(pAlloy!=NULL);
	return m_listboxAlloy.SelectString(0, pAlloy->m_strName);
}

inline CAlloy* CPageSearch::Data_Alloy_GetCurSel()
{
	return ((CDataMatDb*)m_pData)->Alloy_GetCurSel();
}

inline void CPageSearch::Data_Cat_SetCurSel(CCat* pCat)
{
	((CDataMatDb*)m_pData)->Cat_SetCurSel(pCat);
}

inline void CPageSearch::Data_Alloy_SetCurSel(CAlloy* pAlloy)
{
	((CDataMatDb*)m_pData)->Alloy_SetCurSel(pAlloy);
}

inline POSITION CPageSearch::Data_Cat_GetHeadPosition()
{
	return ((CDataMatDb*)m_pData)->Cat_GetHeadPosition();
}

inline CCat* CPageSearch::Data_Cat_GetNext(POSITION& pos)
{
	return ((CDataMatDb*)m_pData)->Cat_GetNext(pos);
}
