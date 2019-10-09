#pragma once

// Boîte de dialogue CCEDialog
// dialogue avec une barre de titre

#define CEMB_OK					0
#define CEMB_OKCANCEL			1
#define CEMB_YESNO				2
#define CEMB_YESNOCANCEL		3
#define CEMB_OKQUIT				4
#define CEMB_OKQUITCANCEL		5


class CCEDialog : public CDialog
{
	DECLARE_DYNAMIC(CCEDialog)
// Construction
public:
	CCEDialog(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	void CreateFont();

	int		m_cyHeader;			// hauteur du header
	CFont	m_fontBold;			// fonte du header
	CCommandBar m_wndCommandBar;
	CString m_strHeader;		// texte du header = titre défini dans la resource

	// menu
	
	// CEMB_OK					-> CLASSES_IDR_MENU_OK = par défaut
	// CEMB_OKCANCEL			-> CLASSES_IDR_MENU_OKCANCEL
	// CEMB_YESNO				-> CLASSES_IDR_MENU_YESNO
	// CEMB_YESNOCANCEL			-> CLASSES_IDR_MENU_YESNO + X  
	// CEMB_OKQUIT				-> CLASSES_IDR_MENU_OKQUIT
	// CEMB_OKQUITCANCEL		-> CLASSES_IDR_MENU_OKQUIT + X

	UINT	m_nStyle;			// menu : boutons

	// Generated message map functions
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

