#pragma once

// CPropSheetEx

class CPropPageEx;
class CData;

// classe pour application bas�e feuille de propri�t�s
// le titre est AFX_IDS_APP_TITLE qui doit �tre d�fini
//
// CPropertySheet contenant des CPropPageEx
// avec des fonctionnalit�s calqu�es sur
// le m�me principe que Doc / View
// le "document" est m_pData de type CData

class CPropSheetEx : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropSheetEx)

public:

	CPropSheetEx(BOOL fHideSHDoneBtn=FALSE,	// si TRUE, le bouton "ok" est remplac� par "X"
				UINT iSelectPage = 0,
				CWnd* pParent = NULL);
	virtual ~CPropSheetEx();

	CData*	m_pData;

	void SetEditMode(BOOL fMode) { m_fEditMode=fMode; }
	BOOL GetEditMode() { return m_fEditMode; }

	virtual void GetDataFolder(CString& strDataFolder); // retourne le dossier des donn�es
	virtual void GetDataFileExt(CString& strExt)=0; // retourne l'extension de fichier

protected:
	BOOL m_fHideSHDoneBtn;	// si TRUE, le bouton "ok" est remplac� par "X"
	CCommandBar	m_wndCommandBar; // command bar
	BOOL m_fEditMode;
	UINT m_nIdFileExt; // extension du fichier de donn�es
	int m_nLastActive;

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

public:
	virtual BOOL Data_FileRead(const CString& strFilePath); // chemin complet
protected:

	virtual void Data_Save();			// enregistre la base
	virtual void Data_SaveAs();			// enregistre la base sous
	virtual void Data_SaveCopyAs();		// enregistre une copie de la base

	BOOL Data_FileExist(const CString& strFileName);

	DECLARE_MESSAGE_MAP()
	// TCN_SELCHANGING ne prend pas en charge presult qui permet normalement de bloquer
	// le changement de s�lection. Donc : m�morisation de la page active � chaque changement. 
	// S'il y a changement non souhait� suite � appel de CPropPageEx::CanChage(), 
	// on revient � la page pr�c�dente
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnInitDialog();

	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnModeEdit();
	afx_msg void OnUpdateModeEdit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdMenuFileSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdMenuFileSaveAs(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdMenuFileSaveCopyAs(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdMenuFileNew(CCmdUI *pCmdUI);
	afx_msg void OnPaint();

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	afx_msg void OnIdMenuFileNew();
	afx_msg void OnIdMenuFileSave();
	afx_msg void OnIdMenuFileSaveAs();
	afx_msg void OnIdMenuFileSaveCopyAs();
};
