#pragma once

#include "PropPageEx.h"
#include "ListBoxUpDown2.h"
#include "BtnIcon.h"
#include "DataMatDb.h"
#include "EditEx.h"

// Boîte de dialogue CPageCat

class CCat;

class CPageCat : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageCat)

public:
	CPageCat(CData* pData);
	virtual ~CPageCat();

	virtual BOOL CanChangePage();
	virtual void UpdatePage();

	virtual void UpdateControlsStyles();	

protected:
	// helpers

	CCat*			Data_Cat_GetCurSel();
	void			Data_Cat_SetCurSel(CCat* pCat);
	CNamedObList*	Data_Cat_GetList();
	void			Data_IncNextID();
	int				Data_GetNextID();
	void			Data_Alloy_SetCurSel(CAlloy* pAlloy);
	void			Data_SetModifiedFlag(BOOL bModify=TRUE);

	int		SetCurSel(CCat* pCat); // sélectionne dans la listbox et met à jour l'edit
	CCat*	Listbox_Cat_GetCurSel();

	virtual void SetControlsPos();

	CCat* m_pCatNew;		// utilisé pour la création de nouvelles matières (voir CListBoxUpDown)
	BOOL m_fPosSaved;		// flag indiquant que la position a été récupérée (1er appel à SetControlsPos()
	int m_yListbox; // position d'origine de la listbox (définie par la resources)

	CListboxUpDown3 m_listboxCat;
	CEditEx m_editCat;
	CEditEx m_editId;
	CBtnIcon m_btnNew;
	CBtnIcon m_btnDel;
	CBtnIcon m_btnUp;
	CBtnIcon m_btnDown;
	CStatic m_staticId;

// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_CAT };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnLbnSelchangeListCat();
	virtual BOOL OnInitDialog();
	// message envoyé par la listbox quadn réorganisée par drag and drop
	afx_msg LRESULT OnDragAndDrop(WPARAM, LPARAM);
};

inline CCat* CPageCat::Data_Cat_GetCurSel() 
{ 
	return ((CDataMatDb*)m_pData)->Cat_GetCurSel(); 
}

inline void CPageCat::Data_Cat_SetCurSel(CCat* pCat) 
{ 
	((CDataMatDb*)m_pData)->Cat_SetCurSel(pCat); 
}

inline void CPageCat::Data_Alloy_SetCurSel(CAlloy* pAlloy) 
{ 
	((CDataMatDb*)m_pData)->Alloy_SetCurSel(pAlloy); 
}

inline int CPageCat::Data_GetNextID() 
{ 
	return ((CDataMatDb*)m_pData)->GetNextID(); 
}

inline void CPageCat::Data_SetModifiedFlag(BOOL bModify)
{
	m_pData->SetModifiedFlag(bModify);
}

inline  CNamedObList* CPageCat::Data_Cat_GetList()
{
	return ((CDataMatDb*)m_pData)->Cat_GetList();
}

inline void CPageCat::Data_IncNextID()
{
	((CDataMatDb*)m_pData)->IncNextID();
}
