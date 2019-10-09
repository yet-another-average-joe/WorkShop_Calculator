// CEDialog.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "CEDialog.h"
#include "CLASSES_rc.h"

#define _COLOR_TITLE		GetSysColor(COLOR_HIGHLIGHT)
#define _COLOR_SEPARATOR	GetSysColor(COLOR_WINDOWFRAME)
#define _CY_SEPARATOR		GetSystemMetrics(SM_CYBORDER)
#define _CY_HEADER			(GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYBORDER))
#define _FONT_SIZE

// Boîte de dialogue CCEDialog

IMPLEMENT_DYNAMIC(CCEDialog, CDialog)

CCEDialog::CCEDialog(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	m_nStyle=CEMB_OK;
	CreateFont();
}

void CCEDialog::CreateFont()
{
	m_nStyle=MB_OK;

	LOGFONT		lf;
	memset(&lf, 0, sizeof(lf));
	m_cyHeader=_CY_HEADER;

	CString cSvar = _T("");
	HKEY hKey;
	BOOL bSuccess=TRUE;
	TCHAR szFntName[256];
	DWORD dwItalic;
	DWORD dwWeight;
	DWORD dwCharSet;
	DWORD dwType;

	::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SYSTEM\\GWE\\Menu\\BarFnt"), 0, KEY_QUERY_VALUE, &hKey);
	DWORD dwDataBufSize = 256;
	dwType=REG_SZ;
	::RegQueryValueEx(hKey, _T("Nm"), NULL, &dwType, (LPBYTE)&szFntName, &dwDataBufSize);
	dwType=REG_DWORD;
	::RegQueryValueEx(hKey, _T("It"), NULL, &dwType, (LPBYTE)&dwItalic, &dwDataBufSize);
	::RegQueryValueEx(hKey, _T("Wt"), NULL, &dwType, (LPBYTE)&dwWeight, &dwDataBufSize);
	::RegQueryValueEx(hKey, _T("CS"), NULL, &dwType, (LPBYTE)&dwCharSet, &dwDataBufSize);
	RegCloseKey(hKey);

	DWORD dwFontSize;
	SHGetUIMetrics(SHUIM_FONTSIZE_PIXEL, &dwFontSize, sizeof(dwFontSize), NULL);

	lf.lfHeight			= -(int)dwFontSize;
	lf.lfWeight			= FW_BOLD;
	lf.lfItalic			= (BYTE)dwItalic;
	lf.lfCharSet		= (BYTE)dwCharSet;
	lf.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfQuality		= DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	lstrcpy(lf.lfFaceName, szFntName);

	m_fontBold.CreateFontIndirect(&lf);
}
  
void CCEDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CCEDialog::OnInitDialog()
{
	// assure que le titre de la boite de dialogue sera bien le nom de l'application
	GetWindowText(m_strHeader); // récupère le titre de la resource pour le header
	LPCTSTR lpsz=AfxGetAppName();
	SetWindowText(lpsz);

	CDialog::OnInitDialog();

	UINT nIdMenu=0;

	switch(m_nStyle)
	{
	case CEMB_OK:
		nIdMenu=CLASSES_IDR_MENU_OK;
		break;
	case CEMB_OKCANCEL:
		nIdMenu=CLASSES_IDR_MENU_OKCANCEL;
		break;
	case CEMB_YESNO:
		nIdMenu=CLASSES_IDR_MENU_YESNO;
		break;
	case CEMB_YESNOCANCEL:
		nIdMenu=CLASSES_IDR_MENU_YESNO;
		break;
	case CEMB_OKQUIT:
	case CEMB_OKQUITCANCEL:
		nIdMenu=CLASSES_IDR_MENU_OKQUIT;
		break;
	default:
		ASSERT(0);
		break;
	}

	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(nIdMenu) ||
	    !m_wndCommandBar.AddAdornments(0))
	{
		TRACE0("Impossible de créer CommandBar\n");
		return -1;      // échec de la création
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);

	switch(m_nStyle)
	{
	case CEMB_OK:
	case CEMB_OKCANCEL:
	case CEMB_YESNO:
	case CEMB_OKQUIT:
		ModifyStyle(0, WS_NONAVDONEBUTTON, SWP_NOSIZE);
		::SHDoneButton(m_hWnd, SHDB_HIDE);
	case CEMB_YESNOCANCEL:
	case CEMB_OKQUITCANCEL:
		break;
	default:
		ASSERT(0);
		break;
	}

	return TRUE;	// retourne TRUE sauf si vous avez défini le focus sur un contrôle
			// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

BEGIN_MESSAGE_MAP(CCEDialog, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CCEDialog::OnPaint() 
{
	CPaintDC dc(this);

	CString strTitle=m_strHeader;
	//GetWindowText(strTitle);

	CRect	rcClient;
	GetClientRect(&rcClient);
	int cxClient=rcClient.Width();

	// titre
	CFont *pFontOld = dc.SelectObject(&m_fontBold);
	dc.SetTextColor(_COLOR_TITLE);
	dc.DrawText(strTitle, -1, CRect(8, 0, cxClient, m_cyHeader), DT_VCENTER | DT_SINGLELINE);
	dc.SelectObject(pFontOld);

	// séparateur
	CPen blackPen(PS_SOLID, _CY_SEPARATOR, _COLOR_SEPARATOR);
	CPen *pPenOld = dc.SelectObject(&blackPen);
	dc.MoveTo(0, m_cyHeader-1);
	dc.LineTo(cxClient, m_cyHeader-1);
	dc.SelectObject(pPenOld);	
}

BOOL CCEDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if(wParam==CLASSES_IDM_QUIT)
	{
		PostQuitMessage(0);
		return FALSE;
	}

	return CDialog::OnCommand(wParam, lParam);
}
