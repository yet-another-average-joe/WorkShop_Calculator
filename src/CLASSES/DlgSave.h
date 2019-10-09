#pragma once

#include "CEDialog.h"
#include "EditFileName.h"

// Boîte de dialogue CDlgSave

class CDlgSave : public CCEDialog
{
	DECLARE_DYNAMIC(CDlgSave)

public:
	CDlgSave(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDlgSave();
	CString m_strFileExt;
	UINT m_nIDTitle;

// Données de boîte de dialogue
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
	CCommandBar m_wndCommandBar;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_listboxFileName;
	CEditFileName m_editFileName;
	CString m_strFileName;
	afx_msg void OnLbnSelchangeListboxDatafile();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeIdcEditFilename();
};
