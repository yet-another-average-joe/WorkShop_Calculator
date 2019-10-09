#pragma once

#include "PropPageEx.h"
#include "ComboEx.h"
#include "CLASSES_rc.h"
#include "DataToolDb.h"
#include "EditEx.h"


// Boîte de dialogue CPageToolFile

class CPageToolFile : public CPropPageEx
{
	DECLARE_DYNCREATE(CPageToolFile)

public:
	CPageToolFile();
	CPageToolFile(CData* pData);
	virtual ~CPageToolFile();

	// nIDFileExt = ID de resource pour l'extension diu fichier d'outils
	void SetToolFileExt(UINT nIDFileExt);

	// sélectionne un fichier dans la combo
	virtual void Combo_SelectFileName(const CString& strFileName);
	// remet à jour la liste de fichiers
	virtual void UpdateFileList();

	virtual void ResetPage();
	//virtual void OnChangeEditMode();
	virtual void UpdateControlsStyles();	

	virtual void OnFileNew();
	virtual void OnFileSave();
	virtual void OnFileSaveAs();
	virtual void OnFileSaveCopyAs();

// helpers

	void Data_Cat_SetCurSel(CCat* pCat);
	CCat* Data_Cat_GetHead();

	void Data_GetMatFileName(CString& str);
	void Data_GetMatFileComment(CString& str);

	// flag positionné si une catégorie de matière est absence 
	// du fichier de matière lors de la lecture 
	// les données chargées en mémoire sont débarassées
	// automatiquement des enregistrements orphelins
	void Data_Cat_SetMissingFlag(BOOL bMissing);
	BOOL Data_Cat_GetMissingFlag();

protected:
	virtual void SetControlsPos(); // utilise des appels à DeferWindowPos
	CString m_strFileExt; // extension pour le fichier d'outils

// Données de boîte de dialogue
	enum { IDD = CLASSES_IDD_PAGE_TOOLFILE };

	CStatic		m_staticToolFile;
	CComboEx	m_comboToolFile;

	CStatic		m_staticToolFileComment;
	CEditEx		m_editToolFileComment;
	
	CStatic		m_staticMatFile;
	CEditEx		m_editMatFile;

	CStatic		m_staticMatFileComment;
	CEditEx		m_editMatFileComment;

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	afx_msg void OnCbnSelchangeComboToolFile();
	afx_msg void OnEnChangeEditCommentToolFile();
	virtual BOOL OnInitDialog();
};

inline void CPageToolFile::Combo_SelectFileName(const CString& strFileName)
{
	m_comboToolFile.SelectString(0, strFileName);
#ifdef _DEBUG
	int nCurSel=m_comboToolFile.GetCurSel();
	if(nCurSel==LB_ERR)
		return;
	CString str;
	m_comboToolFile.GetLBText(nCurSel, str);
	ASSERT(str==strFileName);
#endif
}

inline void CPageToolFile::SetToolFileExt(UINT nIDFileExt) 	
{
	VERIFY(m_strFileExt.LoadString(nIDFileExt));
}

inline void CPageToolFile::Data_Cat_SetCurSel(CCat* pCat) 
{ 
	((CDataToolDb*)m_pData)->Cat_SetCurSel(pCat); 
}

inline CCat* CPageToolFile::Data_Cat_GetHead() 
{ 
	return ((CDataToolDb*)m_pData)->Cat_GetHead(); 
}

inline void CPageToolFile::Data_GetMatFileName(CString& str)
{
	((CDataToolDb*)m_pData)->GetMatFileName(str);
}

inline void CPageToolFile::Data_GetMatFileComment(CString& str)
{
	((CDataToolDb*)m_pData)->GetMatFileComment(str);
}

inline void CPageToolFile::Data_Cat_SetMissingFlag(BOOL bMissing)
{
	((CDataToolDb*)m_pData)->SetCatMissingFlag(bMissing);
}

inline BOOL CPageToolFile::Data_Cat_GetMissingFlag()
{
	return ((CDataToolDb*)m_pData)->GetCatMissingFlag();
}
