#pragma once

// CComboEx

// combo box se redimensionnant automatiquement pour offrir
// une hauteur maximum sans venir recouvrir le SIP
// se base sur sa position et la hauteur de la fenêtre parente

class CComboEx : public CComboBox
{
	DECLARE_DYNAMIC(CComboEx)

public:
	CComboEx();
	virtual ~CComboEx();
	void SetFullDrop(BOOL bFullDrop=TRUE);

	// pour compatibilité avec CDecimalSupport
	void SetWindowText_NoNotify(LPCTSTR lpszText)
	{ 
		SetWindowText(lpszText);
	}

protected:
	int m_bFullDrop;
	// impossible de sous classer la listbox : pas de CTLCOLOR_LISTBOX avec WinCE
	// CListBox m_listbox;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnDropdown();
	virtual void PreSubclassWindow();
};

inline void CComboEx::SetFullDrop(BOOL bFullDrop/*=TRUE*/)
{
	m_bFullDrop=bFullDrop;
}
