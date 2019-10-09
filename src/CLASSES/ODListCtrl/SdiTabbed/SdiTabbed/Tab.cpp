// Tab.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "SdiTabbed.h"
#include "Tab.h"
#include "Page1.h"
#include "Page2.h"

// CTab

PFNPROPSHEETCALLBACK	CTab::m_pCallBack = NULL;

CString CTab::m_strLink;
CString CTab::m_strTitle;


IMPLEMENT_DYNAMIC(CTab, CPropertySheet)


CTab::CTab()
{
	Init();
}

CTab::CTab(UINT nIDCaption, CWnd* pParentWnd /*= NULL*/, UINT iSelectPage /*= 0*/):
	CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	SetCaption(nIDCaption);
	Init();
}

	CTab::CTab(LPCTSTR pszCaption, CWnd* pParentWnd /*= NULL*/, UINT iSelectPage /*= 0*/):
	CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	SetCaption(pszCaption);
	Init();
}

	CTab::CTab(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark /*= NULL*/, HBITMAP hbmHeader /*= NULL*/):
	CPropertySheet(nIDCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
{
	SetCaption(nIDCaption);
	Init();
}

	CTab::CTab(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage, HBITMAP hbmWatermark, HPALETTE hpalWatermark /*= NULL*/, HBITMAP hbmHeader /*= NULL*/):
	CPropertySheet(pszCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
{
	SetCaption(pszCaption);
	Init();
}

void CTab::SetCaption(LPCTSTR pszCaption)
{
	m_strTitle = pszCaption;
}

void CTab::SetCaption(UINT nIDCaption)
{
	m_strTitle.LoadString(nIDCaption);
}

void CTab::Init()
{
	HookCallback();

	m_tabPages[0]=new CPage1;
	m_tabPages[1]=new CPage2;

	AddPage(m_tabPages[0]);
	AddPage(m_tabPages[1]);
	m_nNumberOfPages=2;

}

CTab::~CTab()
{
	for(int i=0; i < m_nNumberOfPages; i++)
		delete m_tabPages[i];

	if(m_pWndEmptyCB)
		delete m_pWndEmptyCB;
}

BEGIN_MESSAGE_MAP(CTab, CPropertySheet)
END_MESSAGE_MAP()


int CALLBACK CTab::CePropertySheetCallBack(HWND hWnd, UINT message, LPARAM lParam)
{
	if(message == PSCB_GETLINKTEXT)
	{
		if(!m_strLink.IsEmpty())
		{
			LPTSTR	pBuf = (LPTSTR)lParam;

			wcscpy(pBuf, m_strLink);
		}
	}
	else if(message == PSCB_GETTITLE)
	{
		if(!m_strTitle.IsEmpty())
		{
			LPTSTR	pBuf = (LPTSTR)lParam;

			wcscpy(pBuf, m_strTitle);
		}
	}
	return (m_pCallBack)(hWnd, message, lParam);
}


void CTab::HookCallback()
{
	m_pCallBack = m_psh.pfnCallback;

	m_psh.pfnCallback = CePropertySheetCallBack;
}

BOOL CTab::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// Create the empty command bar.
	m_pWndEmptyCB = new CCommandBar;

	if(m_pWndEmptyCB != NULL)
	{
		m_pWndEmptyCB->CreateEx(this);
	}
	
	return bResult;

}
