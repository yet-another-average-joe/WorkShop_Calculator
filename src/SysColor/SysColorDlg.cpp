// SysColorDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "SysColor.h"
#include "SysColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Boîte de dialogue CSysColorDlg

CSysColorDlg::CSysColorDlg(CWnd* pParent /*=NULL*/):
		CDlgMain(	CSysColorDlg::IDD,   // ID de dialogue
							FALSE,	// si TRUE, le bouton "ok" est remplacé par "X"
							pParent /*= NULL*/)
{
}

void CSysColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgMain::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SC, m_listboxSC);
	DDX_Control(pDX, IDC_EDIT_DESCR, m_editDescr);
}

BEGIN_MESSAGE_MAP(CSysColorDlg, CDlgMain)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LIST_SC, &CSysColorDlg::OnLbnSelchangeComboSc)
	ON_WM_ACTIVATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Gestionnaires de messages pour CSysColorDlg

BOOL CSysColorDlg::OnInitDialog()
{
	CDlgMain::OnInitDialog();

	int i=0;

	m_nIndex[i]	=COLOR_3DDKSHADOW;
	m_strText[i]	=_T("COLOR_3DDKSHADOW");
	m_strDescr[i++]	=_T("Dark shadow for three-dimensional display elements.");
 
	m_nIndex[i]	=COLOR_3DFACE;
	m_strText[i]	=_T("COLOR_3DFACE");
	m_strDescr[i++]	=_T("Face color for three-dimensional display elements and for dialog box backgrounds.");
 
	m_nIndex[i]	=COLOR_3DHIGHLIGHT;
	m_strText[i]	=_T("COLOR_3DHIGHLIGHT");
	m_strDescr[i++]	=_T("Highlight color for three-dimensional display elements (for edges facing the light source.)");
 
	m_nIndex[i]	=COLOR_3DHILIGHT;
	m_strText[i]	=_T("COLOR_3DHILIGHT");
	m_strDescr[i++]	=_T("Highlight color for three-dimensional display elements (for edges facing the light source.)");
 
	m_nIndex[i]	=COLOR_3DLIGHT;
	m_strText[i]	=_T("COLOR_3DLIGHT");
	m_strDescr[i++]	=_T("Light color for three-dimensional display elements (for edges facing the light source.)");
 
	m_nIndex[i]	=COLOR_3DSHADOW;
	m_strText[i]	=_T("COLOR_3DSHADOW");
	m_strDescr[i++]	=_T("Shadow color for three-dimensional display elements (for edges facing away from the light source).");
 
	m_nIndex[i]	=COLOR_ACTIVEBORDER;
	m_strText[i]	=_T("COLOR_ACTIVEBORDER");
	m_strDescr[i++]	=_T("Active window border.");
 
	m_nIndex[i]	=COLOR_ACTIVECAPTION;
	m_strText[i]	=_T("COLOR_ACTIVECAPTION");
	m_strDescr[i++]	=_T("Active window title bar. Specifies the left side color in the color gradient of an active window's title bar if the gradient effect is enabled.");

	m_nIndex[i]	=COLOR_APPWORKSPACE;
	m_strText[i]	=_T("COLOR_APPWORKSPACE");
	m_strDescr[i++]	=_T("Background color of multiple document interface (MDI) applications.");
 
	m_nIndex[i]	=COLOR_BACKGROUND;
	m_strText[i]	=_T("COLOR_BACKGROUND");
	m_strDescr[i++]	=_T("Desktop.");
 
	m_nIndex[i]	=COLOR_BTNFACE;
	m_strText[i]	=_T("COLOR_BTNFACE");
	m_strDescr[i++]	=_T("Face color for three-dimensional display elements and for dialog box backgrounds.");
 
	m_nIndex[i]	=COLOR_BTNHIGHLIGHT;
	m_strText[i]	=_T("COLOR_BTNHIGHLIGHT");
	m_strDescr[i++]	=_T("Highlight color for three-dimensional display elements (for edges facing the light source.)");
 
	//m_nIndex[i]	=COLOR_BTNHILIGHT;
	//m_strText[i]	=_T("COLOR_BTNHILIGHT");
	//m_strDescr[i++]	=_T("Highlight color for three-dimensional display elements (for edges facing the light source.)");
 
	m_nIndex[i]	=COLOR_BTNSHADOW;
	m_strText[i]	=_T("COLOR_BTNSHADOW");
	m_strDescr[i++]	=_T("Shadow color for three-dimensional display elements (for edges facing away from the light source).");
 
	m_nIndex[i]	=COLOR_BTNTEXT;
	m_strText[i]	=_T("COLOR_BTNTEXT");
	m_strDescr[i++]	=_T("Text on push buttons.");
 
	m_nIndex[i]	=COLOR_CAPTIONTEXT;
	m_strText[i]	=_T("COLOR_CAPTIONTEXT");
	m_strDescr[i++]	=_T("Text in caption, size box, and scroll bar arrow box.");
 
	m_nIndex[i]	=COLOR_DESKTOP;
	m_strText[i]	=_T("COLOR_DESKTOP");
	m_strDescr[i++]	=_T("Desktop.");
 
	m_nIndex[i]	=COLOR_GRADIENTACTIVECAPTION;
	m_strText[i]	=_T("COLOR_GRADIENTACTIVECAPTION");
	m_strDescr[i++]	=_T("Right side color in the color gradient of an active window's title bar. COLOR_ACTIVECAPTION specifies the left side color. Use SPI_GETGRADIENTCAPTIONS with the SystemParametersInfo function to determine whether the gradient effect is enabled.");
 
	m_nIndex[i]	=COLOR_GRADIENTINACTIVECAPTION;
	m_strText[i]	=_T("COLOR_GRADIENTINACTIVECAPTION");
	m_strDescr[i++]	=_T("Right side color in the color gradient of an inactive window's title bar. COLOR_INACTIVECAPTION specifies the left side color.");
 
	m_nIndex[i]	=COLOR_GRAYTEXT;
	m_strText[i]	=_T("COLOR_GRAYTEXT");
	m_strDescr[i++]	=_T("Grayed (disabled) text. This color is set to 0 if the current display driver does not support a solid gray color.");
 
	m_nIndex[i]	=COLOR_HIGHLIGHT;
	m_strText[i]	=_T("COLOR_HIGHLIGHT");
	m_strDescr[i++]	=_T("Item(s) selected in a control.");
 
	m_nIndex[i]	=COLOR_HIGHLIGHTTEXT;
	m_strText[i]	=_T("COLOR_HIGHLIGHTTEXT");
	m_strDescr[i++]	=_T("Text of item(s) selected in a control.");
 
	//m_nIndex[i]	=COLOR_HOTLIGHT;
	//m_strText[i]	=_T("COLOR_HOTLIGHT");
	//m_strDescr[i++]	=_T("Color for a hyperlink or hot-tracked item.");
 
	m_nIndex[i]	=COLOR_INACTIVEBORDER;
	m_strText[i]	=_T("COLOR_INACTIVEBORDER");
	m_strDescr[i++]	=_T("Inactive window border.");
 
	m_nIndex[i]	=COLOR_INACTIVECAPTION;
	m_strText[i]	=_T("COLOR_INACTIVECAPTION");
	m_strDescr[i++]	=_T("Inactive window caption. Specifies the left side color in the color gradient of an inactive window's title bar if the gradient effect is enabled."); 
 
	m_nIndex[i]	=COLOR_INACTIVECAPTIONTEXT;
	m_strText[i]	=_T("COLOR_INACTIVECAPTIONTEXT");
	m_strDescr[i++]	=_T("Color of text in an inactive caption.");
 
	m_nIndex[i]	=COLOR_INFOBK;
	m_strText[i]	=_T("COLOR_INFOBK");
	m_strDescr[i++]	=_T("Background color for tooltip controls.");
 
	m_nIndex[i]	=COLOR_INFOTEXT;
	m_strText[i]	=_T("COLOR_INFOTEXT");
	m_strDescr[i++]	=_T("Text color for tooltip controls.");
 
	m_nIndex[i]	=COLOR_MENU;
	m_strText[i]	=_T("COLOR_MENU");
	m_strDescr[i++]	=_T("Menu background.");
 
	//m_nIndex[i]	=COLOR_MENUHILIGHT;
	//m_strText[i]	=_T("COLOR_MENUHILIGHT");
	//m_strDescr[i++]	=_T("The color used to highlight menu items when the menu appears as a flat menu (see SystemParametersInfo). The highlighted menu item is outlined with COLOR_HIGHLIGHT. Windows 2000: This value is not supported.");

	//m_nIndex[i]	=COLOR_MENUBAR;
	//m_strText[i]	=_T("COLOR_MENUBAR");
	//m_strDescr[i++]	=_T("The background color for the menu bar when menus appear as flat menus (see SystemParametersInfo). However, COLOR_MENU continues to specify the background color of the menu popup. Windows 2000: This value is not supported.");
 
	m_nIndex[i]	=COLOR_MENUTEXT;
	m_strText[i]	=_T("COLOR_MENUTEXT");
	m_strDescr[i++]	=_T("Text in menus.");
 
	m_nIndex[i]	=COLOR_SCROLLBAR;
	m_strText[i]	=_T("COLOR_SCROLLBAR");
	m_strDescr[i++]	=_T("Scroll bar gray area.");
 
	m_nIndex[i]	=COLOR_WINDOW;
	m_strText[i]	=_T("COLOR_WINDOW");
	m_strDescr[i++]	=_T("Window background.");
 
	m_nIndex[i]	=COLOR_WINDOWFRAME;
	m_strText[i]	=_T("COLOR_WINDOWFRAME");
	m_strDescr[i++]	=_T("Window frame.");
 
	m_nIndex[i]	=COLOR_WINDOWTEXT;
	m_strText[i]	=_T("COLOR_WINDOWTEXT");
	m_strDescr[i++]	=_T("Text in windows.");
 
	m_nSCCount = i;

	for(int j=0; j<m_nSCCount; j++)
		m_listboxSC.AddString(m_strText[j]);

	m_listboxSC.SetCurSel(0);
	DWORD color=GetSysColor(m_nIndex[0]);
	SetDlgItemInt(IDC_EDIT_R, GetRValue(color));
	SetDlgItemInt(IDC_EDIT_G, GetGValue(color));
	SetDlgItemInt(IDC_EDIT_B, GetBValue(color));

	// ne marche pas sur les static dans OnInitDialog
	// m_staticDescr.SetWindowText(m_strDescr[0]);
	
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

// la resource est relue après OnInitDialog, ce qui réinitialise le static 
// il faut donc le remettre à jour

void CSysColorDlg::OnSize(UINT nType, int cx, int cy)
{
	// inutile
	//CDlgMain::OnSize(nType, cx, cy);

	UINT nIdResource;
	switch(DRA::GetDisplayMode())
	{
	case DRA::Portrait:
		nIdResource=IDD_SYSCOLOR_PORTRAIT;
		break;
	case DRA::Landscape:
		nIdResource=IDD_SYSCOLOR_SQUARE;
		break;
	case DRA::Square:
		nIdResource=IDD_SYSCOLOR_SQUARE;
		break;
	default:
		ASSERT(0);
		break;
	}

	DRA::RelayoutDialog(AfxGetResourceHandle(), this->m_hWnd, MAKEINTRESOURCE(nIdResource));

	switch(DRA::GetDisplayMode())
	{
	case DRA::Portrait:
		// rien
		break;
	case DRA::Landscape:
		// étirer m_editDescr et m_listboxSC
		{
			CRect rcClient;
			GetClientRect(rcClient);
			CRect rc;
			m_editDescr.GetWindowRect(rc);
			ScreenToClient(rc);
			m_editDescr.SetWindowPos(NULL, 0, 0, rcClient.Width()-rc.left*2, rc.Height(), SWP_NOMOVE|SWP_NOZORDER);
			m_listboxSC.GetWindowRect(rc);
			ScreenToClient(rc);
			m_listboxSC.SetWindowPos(NULL, 0, 0, rcClient.Width()-rc.left*2, rc.Height(), SWP_NOMOVE|SWP_NOZORDER);
		}
		break;
	case DRA::Square:
		// rien
		break;
	default:
		ASSERT(0);
		break;
	}

	int nSel=m_listboxSC.GetCurSel();
	m_editDescr.SetWindowText(m_strDescr[nSel]);
}

void CSysColorDlg::OnLbnSelchangeComboSc()
{
	int nSel=m_listboxSC.GetCurSel();

	DWORD color=GetSysColor(m_nIndex[nSel]);
	SetDlgItemInt(IDC_EDIT_R, GetRValue(color));
	SetDlgItemInt(IDC_EDIT_G, GetGValue(color));
	SetDlgItemInt(IDC_EDIT_B, GetBValue(color));

	m_editDescr.SetWindowText(m_strDescr[nSel]);

	CWnd* pWnd=GetDlgItem(IDC_STATIC_COLOR);
	pWnd->Invalidate(TRUE);
}


HBRUSH CSysColorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDlgMain::OnCtlColor(pDC, pWnd, nCtlColor);

	// IDC_COLOR_STATIC -> couleur de fond = celle retournée par GetSysColor()
	if(nCtlColor==CTLCOLOR_STATIC && pWnd->GetDlgCtrlID()==IDC_STATIC_COLOR)
	{
		int nSel=m_listboxSC.GetCurSel();

		DWORD color=GetSysColor(m_nIndex[nSel]);
		return CreateSolidBrush(color);
	}

	return hbr;
}
