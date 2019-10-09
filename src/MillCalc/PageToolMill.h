#pragma once

#include "PropPageEx.h"
#include "ListBoxUpDown2.h"
#include "BtnIcon.h"
#include "CLASSES_rc.h"
#include "DataToolDb.h"

class CDataToolDb;
class CTool;

// Boîte de dialogue CPageToolMill

// dans les fichiers de resource des projets utilsant cette classe, ajouter :
// impossible de placer des icones au fichier de resources CLASSES_rc.h
// car provoque une erreur "duplicate resource", lors qu'elles ne sont pas dupliquées !
//
//CLASSES_IDI_ADD                 ICON                    "..\\CLASSES\\res\\Add.ico"
//CLASSES_IDI_ADD_DISABLED        ICON                    "..\\CLASSES\\res\\Add_d.ico"
//CLASSES_IDI_DEL                 ICON                    "..\\CLASSES\\res\\Delete.ico"
//CLASSES_IDI_DEL_DISABLED        ICON                    "..\\CLASSES\\res\\Delete_d.ico"
//CLASSES_IDI_EDIT                ICON                    "..\\CLASSES\\res\\Edit.ico"
//CLASSES_IDI_EDIT_DISABLED       ICON                    "..\\CLASSES\\res\\Edit_d.ico"
//CLASSES_IDI_CANCEL              ICON                    "..\\CLASSES\\res\\Undo.ico"
//CLASSES_IDI_CANCEL_DISABLED     ICON                    "..\\CLASSES\\res\\Undo_d.ico"
//CLASSES_IDI_REC                 ICON                    "..\\CLASSES\\res\\Check.ico"
//CLASSES_IDI_REC_DISABLED        ICON                    "..\\CLASSES\\res\\Check_d.ico"
//CLASSES_IDI_UP                  ICON                    "..\\CLASSES\\res\\Up.ico"
//CLASSES_IDI_UP_DISABLED         ICON                    "..\\CLASSES\\res\\Up_d.ico"
//CLASSES_IDI_DOWN                ICON                    "..\\CLASSES\\res\\Down.ico"
//CLASSES_IDI_DOWN_DISABLED       ICON                    "..\\CLASSES\\res\\Down_d.ico"

class CPageToolMill : public CPropPageEx
{
	DECLARE_DYNCREATE(CPageToolMill)

public:
	CPageToolMill();
	CPageToolMill(UINT nIDTemplate, CData* pData);
	virtual ~CPageToolMill();

	virtual BOOL CanChangePage();
	virtual void UpdatePage(LPARAM lHint=0);
	virtual void ResetPage();

protected:
	// helpers

	CTool*			Data_Tool_GetCurSel();
	void			Data_Tool_SetCurSel(CTool* pTool);
	CNamedObList*	Data_Tool_GetList();
	POSITION		Data_Cat_GetHeadPosition();
	CCat*			Data_Cat_GetNext(POSITION& pos);

	void			Data_SetModifiedFlag(BOOL bModify=TRUE);

	CTool* Listbox_Tool_GetCurSel();

	virtual void SetControlsPos();

// Données de boîte de dialogue
	enum { IDD = CLASSES_IDD_PAGE_TOOL };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	CTool*	m_pToolNew;	// utilisé pour la création de nouvelles catégories de matières
	CTool*	m_pClipboard;

	CListBoxUpDown2 m_listboxTool;
	CEdit m_editTool;
	CBtnIcon m_btnNew;
	CBtnIcon m_btnEdit;
	CBtnIcon m_btnRec;
	CBtnIcon m_btnDel;
	CBtnIcon m_btnUp;
	CBtnIcon m_btnDown;
	CBtnIcon m_btnCancel;
	CBtnIcon m_btnCopy;
	CBtnIcon m_btnPaste;

	int Listbox_Tool_SetCurSel(CTool* pTool);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonRec();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonCopy();
	afx_msg void OnBnClickedButtonPaste();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnLbnSelchangeListTool();
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnDestroy();
};

inline CTool* CPageToolMill::Listbox_Tool_GetCurSel()
{
	int nCurSel=m_listboxTool.GetCurSel();
	if(nCurSel==CB_ERR)
		return NULL;

	CTool* pTool=(CTool*)m_listboxTool.GetItemDataPtr(nCurSel);
	return pTool;
}

inline CTool* CPageToolMill::Data_Tool_GetCurSel() 
{ 
	return ((CDataToolDb*)m_pData)->Tool_GetCurSel(); 
}

inline void CPageToolMill::Data_Tool_SetCurSel(CTool* pTool) 
{ 
	((CDataToolDb*)m_pData)->Tool_SetCurSel(pTool); 
}

inline void CPageToolMill::Data_SetModifiedFlag(BOOL bModify)
{
	m_pData->SetModifiedFlag(bModify);
}

inline CNamedObList* CPageToolMill::Data_Tool_GetList()
{
	return ((CDataToolDb*)m_pData)->Tool_GetList();
}

inline POSITION CPageToolMill::Data_Cat_GetHeadPosition()
{
	ASSERT(m_pData!=NULL);
	return ((CDataToolDb*)m_pData)->Cat_GetHeadPosition();
}

inline CCat* CPageToolMill::Data_Cat_GetNext(POSITION& pos)
{
	ASSERT(m_pData!=NULL);
	return ((CDataToolDb*)m_pData)->Cat_GetNext(pos);
}