
#include "stdafx.h"
#include "DlgAbout.h"
#include "CLASSES_rc.h"

#define ID_ICON	128

CDlgAbout::CDlgAbout(CWnd* pParent /*= NULL*/) : 
	CCEDialog(CLASSES_IDD_ABOUTBOX_PORTRAIT)
{
	m_nStyle=CEMB_OK;
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CCEDialog::DoDataExchange(pDX);
}

BOOL CDlgAbout::OnInitDialog()
{
	CCEDialog::OnInitDialog();

	// affichage :
	// ligne 1 : nom_de_fichier, version x.x.x.x
	// ligne 2 : description
	// ligne 3 : Copyright (multiligne)
	// icone : grande icone

	CString strModule;
	LPTSTR lpszModule=strModule.GetBuffer(_MAX_PATH);
	::GetModuleFileName(NULL, lpszModule, _MAX_PATH);
	strModule.ReleaseBuffer();
	TCHAR* lpszFileDescription;
	TCHAR* lpszFileVersion;
	TCHAR* lpszLegalCopyright;
	TCHAR* lpszOriginalFilename;
	TCHAR* lpszProductName;
	TCHAR* lpszInternalName;
	DWORD dwNull;
	UINT dwBytes;
	PBYTE pData;
	dwBytes=::GetFileVersionInfoSize(strModule.GetBuffer(_MAX_PATH),&dwNull);
	pData=new BYTE[dwBytes];
	::GetFileVersionInfo(strModule.GetBuffer(_MAX_PATH),NULL,dwBytes,pData);
	::VerQueryValue(pData, _T("\\StringFileInfo\\040c04e4\\ProductName"), (LPVOID*)&lpszProductName, &dwBytes); 
	::VerQueryValue(pData, _T("\\StringFileInfo\\040c04e4\\OriginalFilename"), (LPVOID*)&lpszOriginalFilename, &dwBytes); 
	::VerQueryValue(pData, _T("\\StringFileInfo\\040c04e4\\FileVersion"), (LPVOID*)&lpszFileVersion, &dwBytes); 
	::VerQueryValue(pData,TEXT("\\StringFileInfo\\040c04e4\\FileDescription"),(LPVOID*)&lpszFileDescription,&dwBytes);
	::VerQueryValue(pData, _T("\\StringFileInfo\\040c04e4\\LegalCopyright"), (LPVOID*)&lpszLegalCopyright, &dwBytes); 
	::VerQueryValue(pData, _T("\\StringFileInfo\\040c04e4\\InternalName"), (LPVOID*)&lpszInternalName, &dwBytes); 
	strModule.ReleaseBuffer();

	CString strProductName = lpszProductName;
	CString strOriginalFilename = lpszOriginalFilename;
	CString strFileVersion = lpszFileVersion;
	CString strFileDescription = lpszFileDescription;
	CString strLegalCopyright = lpszLegalCopyright;
	CString strInternalName=lpszInternalName;		//!< The dialog title string.
	//CString strTitle;
	//GetWindowText(strTitle);
	//strTitle=strTitle+_T(" ")+strInternalName;
	m_strHeader=m_strHeader+_T(" ")+strInternalName;
	//SetWindowText(strTitle);

	delete pData; // les pointeurs chaine sont automatiquement libérés quand pData est libéré

	CString strEdit=strProductName + _T("\r\n\r\n") + 
					strFileDescription + _T("\r\n") +
					strOriginalFilename + _T("  v. ") + strFileVersion + _T("\r\n\r\n") +
					strLegalCopyright;

	GetDlgItem(CLASSES_IDC_TEXT_ABOUT)->SetWindowText(strEdit);

	return TRUE;	// retourne TRUE sauf si vous avez défini le focus sur un contrôle
			// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

BEGIN_MESSAGE_MAP(CDlgAbout, CCEDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CDlgAbout::OnSize(UINT nType, int cx, int cy)
{
	UINT nIdResource;
	switch(DRA::GetDisplayMode())
	{
	case DRA::Portrait:
	case DRA::Square:
		nIdResource=CLASSES_IDD_ABOUTBOX_PORTRAIT;
		break;
	case DRA::Landscape:
		nIdResource=CLASSES_IDD_ABOUTBOX_LANDSCAPE;
		break;
	default:
		ASSERT(0);
		break;
	}

	DRA::RelayoutDialog(AfxGetResourceHandle(), this->m_hWnd, MAKEINTRESOURCE(nIdResource));
}

void CDlgAbout::OnPaint()
{
	// icone de l'application
	CPaintDC dc(this); // device context for painting

	CRect rc;
	CWnd* pPlaceHolder=GetDlgItem(CLASSES_IDC_STATIC_PLACEHOLDER);
	pPlaceHolder->GetWindowRect(rc);
	ScreenToClient(rc);
	int cx=::GetSystemMetrics(SM_CXICON)*3/2;
	int cy=::GetSystemMetrics(SM_CYICON)*3/2;
	HICON hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(ID_ICON), IMAGE_ICON, cx, cy, 0);
	dc.DrawIcon(rc.left, rc.top, hIcon);

	// trace la ligne et dessine le texte
	CCEDialog::OnPaint();
}

