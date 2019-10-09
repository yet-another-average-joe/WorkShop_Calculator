#pragma once

#include "PropPageEx.h"
#include "DataMatDb.h"
#include "ComboEx.h"
#include "EditEx.h"

//class CDataMatDb;

// Boîte de dialogue CPageData

class CPageData : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageData)

public:
	CPageData(CData* pData);
	virtual ~CPageData();

protected:
	// sélectionne un fichier, met à jour les contrôles
	virtual void Combo_SelectFileName(const CString& strFileName);
	// remet à jour la liste de fichiers
	virtual void UpdateFileList();

	virtual void SetControlsPos();
	virtual void UpdatePage();
	virtual void UpdateControlsStyles();	

protected:
// Données de boîte de dialogue
	enum { IDD = IDD_PAGE_DATA };

	CStatic m_staticDataFile;
	CComboEx m_comboDataFile;
	CStatic m_staticComment;
	CEditEx m_editComment;

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditComment();
	afx_msg void OnCbnSelchangeComboDatafile();
};

inline void CPageData::Combo_SelectFileName(const CString& strFileName)
{
	int n=m_comboDataFile.FindStringExact(0, strFileName);
	m_comboDataFile.SetCurSel(n);
#ifdef _DEBUG
	int nCurSel=m_comboDataFile.GetCurSel();
	if(nCurSel==LB_ERR)
		return;
	CString str;
	m_comboDataFile.GetLBText(nCurSel, str);
	ASSERT(str==strFileName);
#endif
}

