#pragma once

#include "ObjNamed.h"

// CListboxUpDown3

#define WMU_LBUPDOWN_DRAGGED	(WM_USER+100)

// gère l'édition d'une liste d'objet nommés 
// par l'intermédiaire d'une listbox, d'un edit et de boutons

class CListboxUpDown3 : public CListBox
{
	DECLARE_DYNAMIC(CListboxUpDown3)

public:

	CListboxUpDown3(	int nIdEdit,			// EDIT associé
						int nIdButtonNew,		// BUTTON nouveau
						int nIdButtonDel,		// BUTTON supprimer
						int nIdButtonUp,		// BUTTON monter 
						int nIdButtonDown);		// BUTTON descendre

	virtual ~CListboxUpDown3();

	// IMPERATIF : associer la liste d'objets nommés
	// SetNamedObList() réinitialise la listbox avec la liste
	void SetNamedObList(CNamedObList* pNamedObList);

	// bloque la gestion du drag and drop
	void EnableDragAndDrop(BOOL bEnableDragAndDrop=TRUE);
	
	// fonctions à placer dans les handlers de notifocations de contrôles
	// fonctions retournant l'objet ajouté, modifié, etc., ou NULL si erreur
	// ces fonctions synchronisent la base de données

	// il faut d'abord créer l'objet, puis le passer au helper
	CObjNamed*	OnBnClickedAdd(CObjNamed* pDataNew);
	void		OnBnClickedDel();
	CObjNamed*	OnBnClickedUp();
	CObjNamed*	OnBnClickedDown();
	void		OnLbnSelchange();

	// helpers sélectionne un objet, et met à jour l'edit
	int _SetCurSel(CObjNamed* pObj);
	int _SetCurSel(int nSelect);

	// helpers agissant uniquement sur la listbox
	// et ni sur la liste, ni sur l'edit, ni sur les boutons

	int Listbox_Add(CObjNamed* pData);
	// enlève sans le détruire l'item à la position nIndex
	// et retourne l'objet 
	CObjNamed* Listbox_Remove(int nIndex);
	// retourne l'item à la position nIndex
	CObjNamed* Listbox_Get(int nIndex);
	// déplace l'item sélectionné d'une position vers le haut ; retourne l'objet déplacé
	CObjNamed* Listbox_MoveCurSelUp();
	// déplace l'item sélectionné d'une position vers le bas ; retourne l'objet déplacé
	CObjNamed* Listbox_MoveCurSelDown();

	// met à jour l'EDIT associé
	//int Listbox_Insert(int nIndex, CObjNamed* pData);
	// supprime un item, décale la sélection ; retourne l'objet supprimé
	// ne met pas à jour l'edit
	// retourne l'objet
	// change le texte dans la liste en se basant sur le nom de l'objet nommé
	//int Set(int nIndex, CObjNamed* pData);
	// change le texte dans la liste et le titre de la liste de plugins
	//int Set(int nIndex, CString& str);


	void UpdateCmdUI();

protected:

	int m_nIdEdit; // EDIT associé

	// change le texte de l'edit en empêchant le traitement de EN_CHANGE
	// dans la message map de la fenêtre parente
	void SetEditText(LPCTSTR pszText);
	void EnableEdit(BOOL bEnable);

	// boutons associés (pour enable / disable) et leur gestion 
	int		m_nIdButtonDel;
	int		m_nIdButtonUp;
	int		m_nIdButtonDown;
	int		m_nIdButtonNew;


	CEdit*		GetEdit();
	CButton*	GetButtonDel();
	CButton*	GetButtonUp();
	CButton*	GetButtonDown();
	CButton*	GetButtonNew();

public:
	CNamedObList*	m_pNamedObList; // liste d'objets nomméé associée

protected:

// drag and drop
	int   m_nMovingIndex;
	int   m_nMoveToIndex;
	BOOL  m_fCaptured;
	DWORD m_dwInterval;    //scroll speed when an item is dragged above or below the window
	BOOL m_fDrag;
	BOOL m_bEnableDragAndDrop;

	void InsertDraggedItem();
	void DoTheScrolling(CPoint Point,CRect ClientRect);
	void DrawTheLines(int Index);


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void ___OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

inline CEdit* CListboxUpDown3::GetEdit()
{
	CWnd* pParent=GetParent();
	ASSERT_VALID(pParent);
	return (CEdit*)pParent->GetDlgItem(m_nIdEdit);
}

inline CButton* CListboxUpDown3::GetButtonDel()
{
	CWnd* pParent=GetParent();
	ASSERT_VALID(pParent);
	return (CButton*)pParent->GetDlgItem(m_nIdButtonDel);
}

inline CButton* CListboxUpDown3::GetButtonUp()
{
	CWnd* pParent=GetParent();
	ASSERT_VALID(pParent);
	return (CButton*)pParent->GetDlgItem(m_nIdButtonUp);
}

inline CButton* CListboxUpDown3::GetButtonDown()
{
	CWnd* pParent=GetParent();
	ASSERT_VALID(pParent);
	return (CButton*)pParent->GetDlgItem(m_nIdButtonDown);
}

inline CButton* CListboxUpDown3::GetButtonNew()
{
	CWnd* pParent=GetParent();
	ASSERT_VALID(pParent);
	return (CButton*)pParent->GetDlgItem(m_nIdButtonNew);
}

inline CObjNamed* CListboxUpDown3::Listbox_Get(int nIndex)
{
	return (CObjNamed*)GetItemDataPtr(nIndex);
}

// change le texte de l'edit en empêchant le traitement de EN_CHANGE
// dans la message map de la fenêtre parente
inline void CListboxUpDown3::SetEditText(LPCTSTR pszText)
{
	CWnd* pParent=GetParent();
	ASSERT_VALID(pParent);
	HWND hWndParent=pParent->m_hWnd;

	// prevent control notifications from being dispatched during UpdateData
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	HWND hWndOldLockout = pThreadState->m_hLockoutNotifyWindow;
	ASSERT(hWndOldLockout != hWndParent); // must not recurse
	pThreadState->m_hLockoutNotifyWindow = hWndParent;

	if(pszText!=NULL)
		pParent->SetDlgItemText(m_nIdEdit, pszText);
	else
		pParent->SetDlgItemText(m_nIdEdit, _T(""));

	pThreadState->m_hLockoutNotifyWindow = hWndOldLockout;
}

inline void CListboxUpDown3::EnableEdit(BOOL bEnable)
{
	GetEdit()->EnableWindow(bEnable);

}

inline void CListboxUpDown3::EnableDragAndDrop(BOOL bEnableDragAndDrop/*=TRUE*/)
{
	m_bEnableDragAndDrop=bEnableDragAndDrop;
}

