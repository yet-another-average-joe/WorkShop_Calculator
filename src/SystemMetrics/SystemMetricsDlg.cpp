// SystemMetricsDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "SystemMetrics.h"
#include "SystemMetricsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Boîte de dialogue CSystemMetricsDlg

CSystemMetricsDlg::CSystemMetricsDlg(CWnd* pParent /*= NULL*/):
		CDlgMain(	CSystemMetricsDlg::IDD,   // ID de dialogue
							FALSE,	// si TRUE, le bouton "ok" est remplacé par "X"
							pParent /*= NULL*/)
{
}

void CSystemMetricsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgMain::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SM, m_listboxSM);
	DDX_Control(pDX, IDC_EDIT_DESCR, m_editDescr);
}

BEGIN_MESSAGE_MAP(CSystemMetricsDlg, CDlgMain)
	ON_LBN_SELCHANGE(IDC_LIST_SM, &CSystemMetricsDlg::OnLbnSelchangeComboSm)
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Gestionnaires de messages pour CSystemMetricsDlg

BOOL CSystemMetricsDlg::OnInitDialog()
{
	CDlgMain::OnInitDialog();

	int i=0;
//	m_nIndex[i]	=SM_ARRANGE;
//	m_strText[i]	=_T("SM_ARRANGE");
//	m_strDescr[i++]	=_T("Flags specifying how the system arranged minimized windows. For more information about minimized windows, see the following Remarks section");
	
//	m_nIndex[i]	=SM_CLEANBOOT;
//	m_strText[i]	=_T("SM_CLEANBOOT");
//	m_strDescr[i++]	=_T("Value that specifies how the system was started, as shown in the following table. 0 Normal boot 1 Fail-safe boot 2 Fail-safe with network boot Fail-safe boot (also called SafeBoot) bypasses the users startup files");

	m_nIndex[i]	=SM_CMONITORS;
	m_strText[i]	=_T("SM_CMONITORS");
	m_strDescr[i++]	=_T("Number of display monitors on the Windows CE-based device. Supported in Windows CE versions 4.0 and later."); 
	
//	m_nIndex[i]	=SM_CMOUSEBUTTONS;
//	m_strText[i]	=_T("SM_CMOUSEBUTTONS");
//	m_strDescr[i++]	=_T("Number of buttons on mouse, or zero if no mouse is installed");
	
	m_nIndex[i]	=SM_CXBORDER;
	m_strText[i]	=_T("SM_CXBORDER"); 
	m_strDescr[i++]	=_T("Width in pixels, of a window border. This is equivalent to the SM_CXEDGE value for windows with the 3-D look.");

	m_nIndex[i]	=SM_CYBORDER;
	m_strText[i]	=_T("SM_CYBORDER");
	m_strDescr[i++]	=_T("Height, in pixels, of a window border. This is equivalent to the SM_CYEDGE value for windows with the 3-D look.");

	//m_nIndex[i]	=SM_CXCURSOR;
	//m_strText[i]	=_T("SM_CXCURSOR");
	//m_strDescr[i++]	=_T("Width, in pixels, of a cursor. The system cannot create cursors of other sizes.");

	//m_nIndex[i]	=SM_CYCURSOR;
	//m_strText[i]	=_T("SM_CYCURSOR");
	//m_strDescr[i++]	=_T("Height, in pixels, of a cursor. The system cannot create cursors of other sizes.");

	m_nIndex[i]	=SM_CXDLGFRAME;
	m_strText[i]	=_T("SM_CXDLGFRAME");
	m_strDescr[i++]	=_T("Same as SM_CXFIXEDFRAME.");

	m_nIndex[i]	=SM_CYDLGFRAME;
	m_strText[i]	=_T("SM_CYDLGFRAME");
	m_strDescr[i++]	=_T("Same as SM_CYFIXEDFRAME.");

	m_nIndex[i]	=SM_CXDOUBLECLK;
	m_strText[i]	=_T("SM_CXDOUBLECLK");
	m_strDescr[i++]	=_T("Width, in pixels, of the rectangle around the location of a first click in a double-click sequence. The second click must occur within this rectangle for the system to consider the two clicks a double-click. (The two clicks must also occur within a specified time.");
	
	m_nIndex[i]	=SM_CYDOUBLECLK;
	m_strText[i]	=_T("SM_CYDOUBLECLK");
	m_strDescr[i++]	=_T("Height, in pixels, of the rectangle around the location of a first click in a double-click sequence. The second click must occur within this rectangle for the system to consider the two clicks a double-click. (The two clicks must also occur within a specified time.");

	//m_nIndex[i]	=SM_CXDRAG;
	//m_strText[i]	=_T("SM_CXDRAG");
	//m_strDescr[i++]	=_T("Width, in pixels, of a rectangle centered on a drag point to allow for limited movement of the mouse pointer before a drag operation begins. This allows the user to click and release the mouse button easily without unintentionally starting a drag operation");

	//m_nIndex[i]	=SM_CYDRAG;
	//m_strText[i]	=_T("SM_CYDRAG");
	//m_strDescr[i++]	=_T("Height, in pixels, of a rectangle centered on a drag point to allow for limited movement of the mouse pointer before a drag operation begins. This allows the user to click and release the mouse button easily without unintentionally starting a drag operation"

	m_nIndex[i]	=SM_CXEDGE;
	m_strText[i]	=_T("SM_CXEDGE");
	m_strDescr[i++]	=_T("Width, in pixels, of a 3-D border. This is the 3-D counterpart of SM_CXBORDER.");
	
	m_nIndex[i]	=SM_CYEDGE;
	m_strText[i]	=_T("SM_CYEDGE");
	m_strDescr[i++]	=_T("Height, in pixels, of a 3-D border. This is the 3-D counterparts of SM_CYBORDER.");

	m_nIndex[i]	=SM_CXFIXEDFRAME;
	m_strText[i]	=_T("SM_CXFIXEDFRAME");
	m_strDescr[i++]	=_T("Thickness, in pixels, of the frame around the perimeter of a window that has a caption but is not sizable. SM_CXFIXEDFRAME is the width of the horizontal border. Same as SM_CXDLGFRAME.");
	
	m_nIndex[i]	=SM_CYFIXEDFRAME;
	m_strText[i]	=_T("SM_CYFIXEDFRAME");
	m_strDescr[i++]	=_T("Thickness, in pixels, of the frame around the perimeter of a window that has a caption but is not sizable. SM_CYFIXEDFRAME is the height of the vertical border. Same as SM_CYDLGFRAME.");

//	m_nIndex[i]	=SM_CXFRAME;
//	m_strText[i]	=_T("SM_CXFRAME");
//	m_strDescr[i++]	=_T("Same as SM_CXSIZEFRAME");

//	m_nIndex[i]	=SM_CYFRAME;
//	m_strText[i]	=_T("SM_CYFRAME");
//	m_strDescr[i++]	=_T("Same as SM_CYSIZEFRAME");

	m_nIndex[i]	=SM_CXFULLSCREEN;
	m_strText[i]	=_T("SM_CXFULLSCREEN");
	m_strDescr[i++]	=_T("Width of the client area for a full-screen window on the primary display monitor. To get the coordinates of the portion of the screen not obscured by the system taskbar or by application desktop toolbars, call the SystemParametersInfo function with the SPI_GETWORKAREA value.");
	
	m_nIndex[i]	=SM_CYFULLSCREEN;
	m_strText[i]	=_T("SM_CYFULLSCREEN");
	m_strDescr[i++]	=_T("Height of the client area for a full-screen window on the primary display monitor. To get the coordinates of the portion of the screen not obscured by the system taskbar or by application desktop toolbars, call the SystemParametersInfo function with the SPI_GETWORKAREA value.");

	m_nIndex[i]	=SM_CXHSCROLL;
	m_strText[i]	=_T("SM_CXHSCROLL");
	m_strDescr[i++]	=_T("Width, in pixels, of the arrow bitmap on a horizontal scroll bar; and height, in pixels, of a horizontal scroll bar.");

	m_nIndex[i]	=SM_CYHSCROLL;
	m_strText[i]	=_T("SM_CYHSCROLL");
	m_strDescr[i++]	=_T("Height, in pixels, of the arrow bitmap on a horizontal scroll bar; and height, in pixels, of a horizontal scroll bar.");

//	m_nIndex[i]	=SM_CXHTHUMB;
//	m_strText[i]	=_T("SM_CXHTHUMB");
//	m_strDescr[i++]	=_T("Width, in pixels, of the thumb box in a horizontal scroll bar");

	m_nIndex[i]	=SM_CXICON;
	m_strText[i]	=_T("SM_CXICON");
	m_strDescr[i++]	=_T("The default width, in pixels, of an icon. The LoadIcon function can load only icons of these dimensions.");

	m_nIndex[i]	=SM_CYICON;
	m_strText[i]	=_T("SM_CYICON");
	m_strDescr[i++]	=_T("The default height, in pixels, of an icon. The LoadIcon function can load only icons of these dimensions.");
	
	m_nIndex[i]	=SM_CXICONSPACING;
	m_strText[i]	=_T("SM_CXICONSPACING");
	m_strDescr[i++]	=_T("Width, in pixels, of a grid cell for items in large icon view. Each item fits into a rectangle of this size when arranged. These values are always greater than or equal to SM_CXICON.");

	m_nIndex[i]	=SM_CYICONSPACING;
	m_strText[i]	=_T("SM_CYICONSPACING");
	m_strDescr[i++]	=_T("Height, in pixels, of a grid cell for items in large icon view. Each item fits into a rectangle of this size when arranged. These values are always greater than or equal to SM_CXICON.");
	
	//m_nIndex[i]	=SM_CXMAXIMIZED;
	//m_strText[i]	=_T("SM_CXMAXIMIZED");
	//m_strDescr[i++]	=_T("Default width, in pixels, of a maximized top-level window on the primary display monitor");

	//m_nIndex[i]	=SM_CYMAXIMIZED;
	//m_strText[i]	=_T("SM_CYMAXIMIZED");
	//m_strDescr[i++]	=_T("Default height, in pixels, of a maximized top-level window on the primary display monitor");
	
	//m_nIndex[i]	=SM_CXMAXTRACK;
	//m_strText[i]	=_T("SM_CXMAXTRACK");
	//m_strDescr[i++]	=_T("Default maximum width, in pixels, of a window that has a caption and sizing borders. This metric refers to the entire desktop. The user cannot drag the window frame to a size larger than these dimensions");

	//m_nIndex[i]	=SM_CYMAXTRACK;
	//m_strText[i]	=_T("SM_CYMAXTRACK");
	//m_strDescr[i++]	=_T("Default maximum height, in pixels, of a window that has a caption and sizing borders. This metric refers to the entire desktop. The user cannot drag the window frame to a size larger than these dimensions");

///////////////////////////////////////////////////////////////////////////////////////////////
	// EN PRINCIPE OK, MAIS CONSTANTE NON DEFINIE
	//m_nIndex[i]	=SM_CXMENUCHECK;
	//m_strText[i]	=_T("SM_CXMENUCHECK");
	//m_strDescr[i++]	=_T("Width, in pixels, of the default menu check-mark bitmap"); 
	//
	//m_nIndex[i]	=SM_CYMENUCHECK;
	//m_strText[i]	=_T("SM_CYMENUCHECK");
	//m_strDescr[i++]	=_T("Height, in pixels, of the default menu check-mark bitmap"); 
///////////////////////////////////////////////////////////////////////////////////////////////
	//m_nIndex[i]	=SM_CXMENUSIZE;
	//m_strText[i]	=_T("SM_CXMENUSIZE");
	//m_strDescr[i++]	=_T("Width, in pixels, of menu bar buttons, such as the child window close button used in the multiple document interface");
	
	//m_nIndex[i]	=SM_CYMENUSIZE;
	//m_strText[i]	=_T("SM_CYMENUSIZE");
	//m_strDescr[i++]	=_T("Height, in pixels, of menu bar buttons, such as the child window close button used in the multiple document interface");
	
	//m_nIndex[i]	=SM_CXMIN;
	//m_strText[i]	=_T("SM_CXMIN");
	//m_strDescr[i++]	=_T("Minimum width, in pixels, of a window");

	//m_nIndex[i]	=SM_CYMIN;
	//m_strText[i]	=_T("SM_CYMIN");
	//m_strDescr[i++]	=_T("Minimum height, in pixels, of a window");

	//m_nIndex[i]	=SM_CXMINIMIZED;
	//m_strText[i]	=_T("SM_CXMINIMIZED");
	//m_strDescr[i++]	=_T("Width, in pixels, of a normal minimized window");

	//m_nIndex[i]	=SM_CYMINIMIZED;
	//m_strText[i]	=_T("SM_CYMINIMIZED");
	//m_strDescr[i++]	=_T("Height, in pixels, of a normal minimized window");

	//m_nIndex[i]	=SM_CXMINSPACING;
	//m_strText[i]	=_T("SM_CXMINSPACING");
	//m_strDescr[i++]	=_T("Width, in pixels, of a grid cell for minimized windows. Each minimized window fits into a rectangle this size when arranged. This value is always greater than or equal to SM_CXMINIMIZED");

	//m_nIndex[i]	=SM_CYMINSPACING;
	//m_strText[i]	=_T("SM_CYMINSPACING");
	//m_strDescr[i++]	=_T("Height, in pixels, of a grid cell for minimized windows. Each minimized window fits into a rectangle this size when arranged. This value is always greater than or equal to SM_CYMINIMIZED");

	//m_nIndex[i]	=SM_CXMINTRACK;
	//m_strText[i]	=_T("SM_CXMINTRACK");
	//m_strDescr[i++]	=_T("Minimum tracking width, in pixels, of a window. The user cannot drag the window frame to a size smaller than these dimensions");  

	//m_nIndex[i]	=SM_CYMINTRACK;
	//m_strText[i]	=_T("SM_CYMINTRACK");
	//m_strDescr[i++]	=_T("Minimum tracking height, in pixels, of a window. The user cannot drag the window frame to a size smaller than these dimensions");  
	
	m_nIndex[i]	=SM_CXSCREEN;
	m_strText[i]	=_T("SM_CXSCREEN"); 
	m_strDescr[i++]	=_T("Width, in pixels, of the screen of the primary display monitor. These are the same values you obtain by calling GetDeviceCaps(hdcPrimaryMonitor, HORZRES).");

	m_nIndex[i]	=SM_CYSCREEN;
	m_strText[i]	=_T("SM_CYSCREEN"); 
	m_strDescr[i++]	=_T("Height, in pixels, of the screen of the primary display monitor. These are the same values you obtain by calling GetDeviceCaps(hdcPrimaryMonitor, VERTRES).");

	//m_nIndex[i]	=SM_CXSIZE;
	//m_strText[i]	=_T("SM_CXSIZE");
	//m_strDescr[i++]	=_T("Width, in pixels, of a button in a window's caption or title bar");

	//m_nIndex[i]	=SM_CYSIZE;
	//m_strText[i]	=_T("SM_CYSIZE");
	//m_strDescr[i++]	=_T("Height, in pixels, of a button in a window's caption or title bar");
	
	//m_nIndex[i]	=SM_CXSIZEFRAME,
	//m_strText[i]	=_T("SM_CXSIZEFRAME");
	//m_strDescr[i++]	=_T("Width, in pixels, of the sizing border around the perimeter of a window that can be resized. SM_CXSIZEFRAME is the width of the horizontal border. Same as SM_CXFRAME");

	//m_nIndex[i]	=SM_CYSIZEFRAME;
	//m_strText[i]	=_T("SM_CYSIZEFRAME");
	//m_strDescr[i++]	=_T("Height, in pixels, of the sizing border around the perimeter of a window that can be resized. =SM_CYSIZEFRAME is the height of the horizontal border. Same as =SM_CYFRAME");
	
	m_nIndex[i]	=SM_CXSMICON;
	m_strText[i]	=_T("SM_CXSMICON");
	m_strDescr[i++]	=_T("Recommended width, in pixels, of a small icon. Small icons typically appear in window captions and in small icon view."); 

	m_nIndex[i]	=SM_CYSMICON;
	m_strText[i]	=_T("SM_CYSMICON");
	m_strDescr[i++]	=_T("Recommended height, in pixels, of a small icon. Small icons typically appear in window captions and in small icon view."); 
	
	//m_nIndex[i]	=SM_CXSMSIZE;
	//m_strText[i]	=_T("SM_CXSMSIZE");
	//m_strDescr[i++]	=_T("Width, in pixels, of small caption buttons");
	
	//m_nIndex[i]	=SM_CYSMSIZE;
	//m_strText[i]	=_T("SM_CYSMSIZE");
	//m_strDescr[i++]	=_T("Height, in pixels, of small caption buttons");

	m_nIndex[i]	=SM_CXVIRTUALSCREEN;
	m_strText[i]	=_T("SM_CXVIRTUALSCREEN");
	m_strDescr[i++]	=_T("Width, in pixels, of the virtual screen. The virtual screen is the bounding rectangle of all display monitors. Supported in Windows CE versions 4.0 and later.");

	m_nIndex[i]	=SM_CYVIRTUALSCREEN;
	m_strText[i]	=_T("SM_CYVIRTUALSCREEN");
	m_strDescr[i++]	=_T("Height, in pixels, of the virtual screen. The virtual screen is the bounding rectangle of all display monitors. Supported in Windows CE versions 4.0 and later.");
	
	m_nIndex[i]	=SM_CXVSCROLL;
	m_strText[i]	=_T("SM_CXVSCROLL");
	m_strDescr[i++]	=_T("Width, in pixels, of a vertical scroll bar; and height, in pixels, of the arrow bitmap on a vertical scroll bar.");
	
	m_nIndex[i]	=SM_CYVSCROLL;
	m_strText[i]	=_T("SM_CYVSCROLL");
	m_strDescr[i++]	=_T("Width, in pixels, of a vertical scroll bar; and height, in pixels, of the arrow bitmap on a vertical scroll bar.");

	m_nIndex[i]	=SM_CYCAPTION;
	m_strText[i]	=_T("SM_CYCAPTION");
	m_strDescr[i++]	=_T("Height, in pixels, of a normal caption area"); 
	
	//m_nIndex[i]	=SM_CYKANJIWINDOW;
	//m_strText[i]	=_T("SM_CYKANJIWINDOW");
	//m_strDescr[i++]	=_T("For double-byte character set versions of the system, this is the height, in pixels, of the Kanji window at the bottom of the screen"); 
	
	m_nIndex[i]	=SM_CYMENU;
	m_strText[i]	=_T("SM_CYMENU");
	m_strDescr[i++]	=_T("Height, in pixels, of a single-line menu bar"); 
	
	//m_nIndex[i]	=SM_CYSMCAPTION;
	//m_strText[i]	=_T("SM_CYSMCAPTION");
	//m_strDescr[i++]	=_T("Height, in pixels, of a small caption");
	
	//m_nIndex[i]	=SM_CYVTHUMB;
	//m_strText[i]	=_T("SM_CYVTHUMB");
	//m_strDescr[i++]	=_T("Height, in pixels, of the thumb box in a vertical scroll bar");
	
	m_nIndex[i]	=SM_DBCSENABLED;
	m_strText[i]	=_T("SM_DBCSENABLED");
	m_strDescr[i++]	=_T("TRUE or nonzero if the double-byte character set (DBCS) version of USER.EXE is installed; FALSE or zero otherwise.");
	
	m_nIndex[i]	=SM_DEBUG;
	m_strText[i]	=_T("SM_DEBUG");
	m_strDescr[i++]	=_T("TRUE or nonzero if the debugging version of USER.EXE is installed; FALSE or zero otherwise."); 
	
	//m_nIndex[i]	=SM_MENUDROPALIGNMENT;
	//m_strText[i]	=_T("SM_MENUDROPALIGNMENT");
	//m_strDescr[i++]	=_T("TRUE or nonzero if drop-down menus are right-aligned with the corresponding menu-bar item; FALSE or zero if the menus are left-aligned"); 
	
	//m_nIndex[i]	=SM_MIDEASTENABLED;
	//m_strText[i]	=_T("SM_MIDEASTENABLED");
	//m_strDescr[i++]	=_T("TRUE if the system is enabled for Hebrew and Arabic languages");
	
	m_nIndex[i]	=SM_MOUSEPRESENT;
	m_strText[i]	=_T("SM_MOUSEPRESENT");
	m_strDescr[i++]	=_T("TRUE or nonzero if a mouse is installed; FALSE or zero otherwise.");
	
	//m_nIndex[i]	=SM_MOUSEWHEELPRESENT;
	//m_strText[i]	=_T("SM_MOUSEWHEELPRESENT"); 
	//m_strDescr[i++]	=_T("TRUE or nonzero if a mouse with a wheel is installed; FALSE or zero otherwise");
	
	//m_nIndex[i]	=SM_NETWORK;
	//m_strText[i]	=_T("SM_NETWORK"); 
	//m_strDescr[i++]	=_T("The least significant bit is set if a network is present; otherwise, it is cleared. The other bits are reserved for future use"); 
	
	//m_nIndex[i]	=SM_PENWINDOWS;
	//m_strText[i]	=_T("SM_PENWINDOWS"); 
	//m_strDescr[i++]	=_T("TRUE or nonzero if the Microsoft Windows for Pen computing extensions are installed; FALSE or zero otherwise");
	
	//m_nIndex[i]	=SM_SECURE;
	//m_strText[i]	=_T("SM_SECURE"); 
	//m_strDescr[i++]	=_T("TRUE if security is present; FALSE otherwise");
	
	m_nIndex[i]	=SM_SAMEDISPLAYFORMAT;
	m_strText[i]	=_T("SM_SAMEDISPLAYFORMAT"); 
	m_strDescr[i++]	=_T("TRUE if all the display monitors have the same color format, FALSE otherwise. Supported in Windows CE versions 4.0 and later.");
	
	//m_nIndex[i]	=SM_SHOWSOUNDS;
	//m_strText[i]	=_T("SM_SHOWSOUNDS"); 
	//m_strDescr[i++]	=_T("TRUE or nonzero if the user requires an application to present information visually in situations where it would otherwise present the information only in audible form; FALSE, or zero, otherwise");
	
	//m_nIndex[i]	=SM_SLOWMACHINE;
	//m_strText[i]	=_T("SM_SLOWMACHINE"); 
	//m_strDescr[i++]	=_T("TRUE if the computer has a low-end (slow) processor; FALSE otherwise");
	
	//m_nIndex[i]	=SM_SWAPBUTTON;
	//m_strText[i]	=_T("SM_SWAPBUTTON"); 
	//m_strDescr[i++]	=_T("TRUE or nonzero if the meanings of the left and right mouse buttons are swapped; FALSE or zero otherwise");
	
	m_nIndex[i]	=SM_XVIRTUALSCREEN;
	m_strText[i]	=_T("SM_XVIRTUALSCREEN");
	m_strDescr[i++]	=_T("Coordinate for the left side of the virtual screen. The virtual screen is the bounding rectangle of all display monitors. Supported in Windows CE versions 4.0 and later.");
	
	m_nIndex[i]	=SM_YVIRTUALSCREEN;
	m_strText[i]	=_T("SM_YVIRTUALSCREEN");
	m_strDescr[i++]	=_T("Coordinate for the top of the virtual screen. The virtual screen is the bounding rectangle of all display monitors. Supported in Windows CE versions 4.0 and later.");

	m_nSMCount = i;

	for(int j=0; j<m_nSMCount; j++)
	{
		//LPCTSTR lpszBuf;
		m_listboxSM.AddString(m_strText[j]);//InsertString(j, m_strText[j]);
	}

	m_listboxSM.SetCurSel(0);
	int nValue=GetSystemMetrics(m_nIndex[0]);
	SetDlgItemInt(IDC_EDIT_VALUE, nValue);

	// ne marche pas sur les static dans OnInitDialog
	// m_staticDescr.SetWindowText(m_strDescr[0]);
	
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CSystemMetricsDlg::OnLbnSelchangeComboSm()
{
	int nSel=m_listboxSM.GetCurSel();

	int nValue=GetSystemMetrics(m_nIndex[nSel]);
	SetDlgItemInt(IDC_EDIT_VALUE, nValue);

	m_editDescr.SetWindowText(m_strDescr[nSel]);
}

// la resource est relue après OnInitDialog, ce qui réinitialise le static 
// il faut donc le remettre à jour

void CSystemMetricsDlg::OnSize(UINT nType, int cx, int cy)
{
	// inutile
	//CDlgMain::OnSize(nType, cx, cy);

	UINT nIdResource;
	switch(DRA::GetDisplayMode())
	{
	case DRA::Portrait:
		nIdResource=IDD_SYSTEMMETRICS_PORTRAIT;
		break;
	case DRA::Landscape:
		nIdResource=IDD_SYSTEMMETRICS_SQUARE;
		break;
	case DRA::Square:
		nIdResource=IDD_SYSTEMMETRICS_SQUARE;
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
		// étirer m_editDescr
		{
			CRect rcClient;
			GetClientRect(rcClient);
			CRect rc;
			m_editDescr.GetWindowRect(rc);
			ScreenToClient(rc);
			m_editDescr.SetWindowPos(NULL, 0, 0, rcClient.Width()-rc.left*2, rc.Height(), SWP_NOMOVE|SWP_NOZORDER);
		}
		break;
	case DRA::Square:
		// rien
		break;
	default:
		ASSERT(0);
		break;
	}

	int nSel=m_listboxSM.GetCurSel();
	m_editDescr.SetWindowText(m_strDescr[nSel]);
}
