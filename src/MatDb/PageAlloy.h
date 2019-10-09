#pragma once

#include "PropPageEx.h"
#include "ComboCat.h"
#include "ListBoxUpDown2.h"
#include "DataMatDb.h"
#include "BtnIcon.h"
#include "EditEx.h"
#include "DataMatDb.h"

// Bo�te de dialogue CPageAlloy

class CPageAlloy : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageAlloy)

public:
	CPageAlloy(CData* pData);
	virtual ~CPageAlloy();

	virtual BOOL CanChangePage();
	virtual void UpdatePage();

	virtual void UpdateControlsStyles();	

protected:
	virtual void SetControlsPos();

	// helpers 
	int Cat_SetCurSel(CCat* pCat); // s�lectionne une classe de mati�re dans la combobox
	CCat* Combo_Cat_GetCurSel(); // renvoie la cat�gorie s�lectionn�e, ou NULL
	int Alloy_SetCurSel(CAlloy* pAlloy); // s�lectionne une nuance dans la listbox et met � jour l'edit
	CAlloy* Listbox_Alloy_GetCurSel(); // renvoie la nuance s�lectionn�e, ou NULL
	
	CCat* Data_Cat_GetCurSel();
	CAlloy* Data_Alloy_GetCurSel();
	void Data_Alloy_SetCurSel(CAlloy* pAlloy);
	void Data_Cat_SetCurSel(CCat* pCat);
	void Data_SetModifiedFlag(BOOL bModify=TRUE);

	CAlloy* m_pAlloyNew;	// utilis� pour la cr�ation de nouvelles mati�res (voir CListBoxUpDown)

	CBtnIcon m_btnNew;
	CBtnIcon m_btnDel;
	CBtnIcon m_btnUp;
	CBtnIcon m_btnDown;
	CListboxUpDown3 m_listboxAlloy;
	CComboCat m_comboCat;
	CEditEx m_editAlloy;

	BOOL m_fPosSaved;		// flag indiquant que la position a �t� r�cup�r�e (1er appel � SetControlsPos()
	int m_yListbox; // position d'origine de la listbox (d�finie par la resources)

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_ALLOY };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCbnSelchangeComboCat();
	afx_msg void OnEnChangeEditAlloy();
	afx_msg void OnLbnSelchangeListAlloy();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonNew();
	virtual BOOL OnInitDialog();
	// message envoy� par la listbox quadn r�organis�e par drag and drop
	afx_msg LRESULT OnDragAndDrop(WPARAM, LPARAM);
};

inline CCat* CPageAlloy::Data_Cat_GetCurSel() 
{ 
	return ((CDataMatDb*)m_pData)->Cat_GetCurSel(); 
}

inline CAlloy* CPageAlloy::Data_Alloy_GetCurSel() 
{ 
	return ((CDataMatDb*)m_pData)->Alloy_GetCurSel(); 
}

inline void CPageAlloy::Data_Alloy_SetCurSel(CAlloy* pAlloy) 
{ 
	((CDataMatDb*)m_pData)->Alloy_SetCurSel(pAlloy); 
}

inline void CPageAlloy::Data_Cat_SetCurSel(CCat* pCat) 
{ 
	((CDataMatDb*)m_pData)->Cat_SetCurSel(pCat); 
}

inline void CPageAlloy::Data_SetModifiedFlag(BOOL bModify)
{
	m_pData->SetModifiedFlag(bModify);
}

