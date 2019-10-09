// MainFrm.h : interface de la classe CMainFrame
//


#pragma once



class CMainFrame : public CFrameWnd
{
protected: // création à partir de la sérialisation uniquement
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:

// Opérations
public:

// Substitutions
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implémentation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:  // membres incorporés de la barre de contrôle
#ifdef _WIN32_WCE
	CCommandBar m_wndCommandBar;
#endif
// Fonctions générées de la table des messages
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	DECLARE_MESSAGE_MAP()
};


