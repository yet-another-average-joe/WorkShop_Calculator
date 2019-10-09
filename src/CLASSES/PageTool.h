#pragma once

#include "PropPageEx.h"
#include "ListBoxUpDown2.h"
#include "BtnIcon.h"
#include "CLASSES_rc.h"
#include "DataToolDb.h"
#include "EditDecimal.h"

class CDataToolDb;
class CTool;

// Boîte de dialogue CPageTool

// dans les fichiers de resource des projets utilsant cette classe, ajouter :
// impossible de placer des icones au fichier de resources CLASSES_rc.h
// car provoque une erreur "duplicate resource", lors qu'elles ne sont pas dupliquées !
//
//CLASSES_IDI_ADD                 ICON                    "..\\CLASSES\\res\\Add.ico"
//CLASSES_IDI_ADD_DISABLED        ICON                    "..\\CLASSES\\res\\Add_d.ico"
//CLASSES_IDI_DEL                 ICON                    "..\\CLASSES\\res\\Delete.ico"
//CLASSES_IDI_DEL_DISABLED        ICON                    "..\\CLASSES\\res\\Delete_d.ico"
//CLASSES_IDI_UP                  ICON                    "..\\CLASSES\\res\\Up.ico"
//CLASSES_IDI_UP_DISABLED         ICON                    "..\\CLASSES\\res\\Up_d.ico"
//CLASSES_IDI_DOWN                ICON                    "..\\CLASSES\\res\\Down.ico"
//CLASSES_IDI_DOWN_DISABLED       ICON                    "..\\CLASSES\\res\\Down_d.ico"

class CPageTool : public CPropPageEx
{
	DECLARE_DYNCREATE(CPageTool)

public:
	// si fMillTool == TRUE, affichage de ae et ap
	CPageTool(BOOL fMillTool=FALSE);
	CPageTool(CData* pData, BOOL fMillTool=FALSE);
	virtual ~CPageTool();

	virtual BOOL CanChangePage();
	virtual void ResetPage();

protected:
	// gère la visibilité et l'activation des controles
	virtual void UpdateControlsStyles();	
	virtual void OnChangeEditMode();
	virtual BOOL OnSetActive();

	// helpers
	void ClearAp()			{ m_editAp.SetWindowText_NoNotify(_T("")); }
	void ClearAe()			{ m_editAe.SetWindowText_NoNotify(_T("")); }
	void SetAp(int i)		{ m_editAp.SetDecimalValue(i); }
	void SetAe(int i)		{ m_editAe.SetDecimalValue(i); }
	int GetAp();
	int GetAe();

	CTool*			Data_Tool_GetCurSel();
	void			Data_Tool_SetCurSel(CTool* pTool);
	CNamedObList*	Data_Tool_GetList();
	POSITION		Data_Cat_GetHeadPosition();
	CCat*			Data_Cat_GetNext(POSITION& pos);

	void			Data_SetModifiedFlag(BOOL bModify=TRUE);

	CTool* Listbox_Tool_GetCurSel();

	virtual void SetControlsPos();
	void InitializeButtons();

// Données de boîte de dialogue
	enum { IDD = CLASSES_IDD_PAGE_TOOL };

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	//CTool*	m_pToolNew;	// utilisé pour la création de nouvelles catégories de matières
	CTool*	m_pClipboard;

	BOOL m_fMillTool;
	CListboxUpDown3 m_listboxTool;
	CEditEx m_editTool;
	CBtnIcon m_btnNew;
	CBtnIcon m_btnDel;
	CBtnIcon m_btnUp;
	CBtnIcon m_btnDown;
	CBtnIcon m_btnCopy;
	CBtnIcon m_btnPaste;
	CEditDecimal m_editAe;
	CEditDecimal m_editAp;
	CStatic m_staticAp;
	CStatic m_staticAe;
	CStatic m_staticXd1;
	CStatic m_staticXd2;

	// positions "resource" des contrôles de référence
	BOOL m_fPosSaved;
	int m_yEditTool;
	int m_yEditAp;
	int m_yListTool;

	int Listbox_Tool_SetCurSel(CTool* pTool);

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonCopy();
	afx_msg void OnBnClickedButtonPaste();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnLbnSelchangeListTool();
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeIdcEditAp();
	afx_msg void OnEnChangeIdcEditAe();
	// message envoyé par la listbox quadn réorganisée par drag and drop
	afx_msg LRESULT OnDragAndDrop(WPARAM, LPARAM);
};

inline CTool* CPageTool::Listbox_Tool_GetCurSel()
{
	int nCurSel=m_listboxTool.GetCurSel();
	if(nCurSel==CB_ERR)
		return NULL;

	CTool* pTool=(CTool*)m_listboxTool.GetItemDataPtr(nCurSel);
	return pTool;
}

inline CTool* CPageTool::Data_Tool_GetCurSel() 
{ 
	return ((CDataToolDb*)m_pData)->Tool_GetCurSel(); 
}

inline void CPageTool::Data_Tool_SetCurSel(CTool* pTool) 
{ 
	((CDataToolDb*)m_pData)->Tool_SetCurSel(pTool); 
}

inline void CPageTool::Data_SetModifiedFlag(BOOL bModify)
{
	m_pData->SetModifiedFlag(bModify);
}

inline CNamedObList* CPageTool::Data_Tool_GetList()
{
	return ((CDataToolDb*)m_pData)->Tool_GetList();
}

inline POSITION CPageTool::Data_Cat_GetHeadPosition()
{
	ASSERT(m_pData!=NULL);
	return ((CDataToolDb*)m_pData)->Cat_GetHeadPosition();
}

inline CCat* CPageTool::Data_Cat_GetNext(POSITION& pos)
{
	ASSERT(m_pData!=NULL);
	return ((CDataToolDb*)m_pData)->Cat_GetNext(pos);
}