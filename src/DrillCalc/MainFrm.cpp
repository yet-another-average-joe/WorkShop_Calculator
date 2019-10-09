// MainFrm.cpp : implémentation de la classe CMainFrame
//

#include "stdafx.h"
#include "DrillCalc.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifdef WIN32_PLATFORM_PSPC
#define TOOLBAR_HEIGHT 24
#endif // WIN32_PLATFORM_PSPC

#define CX_FRAME 260
#define CY_FRAME 350
#undef FIXED_WINDOW_SIZE

const DWORD dwAdornmentFlags = 0; // bouton Quitter

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// construction ou destruction de CMainFrame

CMainFrame::CMainFrame()
{
	// TODO : ajoutez ici le code d'une initialisation de membre
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


#ifdef _WIN32_WCE
	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
	    !m_wndCommandBar.AddAdornments(dwAdornmentFlags))
	{
		TRACE0("Impossible de créer CommandBar\n");
		return -1;      // échec de la création
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);
#endif

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
#ifdef _WIN32_WCE
	// cache la fenêtre ????
	//cs.style=0;
	//cs.dwExStyle=0;
#else 
	cs.cx=CX_FRAME;
	cs.cy=CY_FRAME;
#ifdef FIXED_WINDOW_SIZE
	cs.style = WS_BORDER | WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
	// Dimensionner la frame pour entourer correctement la vue...
#else
	cs.style = WS_BORDER | WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME;
#endif //FIXED_WINDOW_SIZE
#endif //_WIN32_WCE
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO : changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return TRUE;
}



// diagnostics pour CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}
#endif //_DEBUG

// gestionnaires de messages pour CMainFrame



