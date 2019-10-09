// Page.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "SdiTabbed.h"
#include "Page.h"


// Boîte de dialogue CPage

IMPLEMENT_DYNAMIC(CPage, CPropertyPage)

CPage::CPage():
	CPropertyPage()
{
}

CPage::CPage(UINT nIDTemplate, UINT nIDCaption /*= 0*/, DWORD dwSize /*= sizeof(PROPSHEETPAGE)*/):
	CPropertyPage(nIDTemplate, nIDCaption, dwSize)
{
}

CPage::CPage(LPCTSTR lpszTemplateName, UINT nIDCaption /*= 0*/, DWORD dwSize /*= sizeof(PROPSHEETPAGE)*/):
	CPropertyPage(lpszTemplateName, nIDCaption, dwSize)
{
}

CPage::CPage(UINT nIDTemplate, UINT nIDCaption, UINT nIDHeaderTitle, UINT nIDHeaderSubTitle /*= 0*/, DWORD dwSize /*= sizeof(PROPSHEETPAGE)*/):
	CPropertyPage(nIDTemplate, nIDCaption, nIDHeaderTitle, nIDHeaderSubTitle, dwSize)
{
}

CPage::CPage(LPCTSTR lpszTemplateName, UINT nIDCaption, UINT nIDHeaderTitle, UINT nIDHeaderSubTitle /*= 0*/, DWORD dwSize /*= sizeof(PROPSHEETPAGE)*/):
	CPropertyPage(lpszTemplateName, nIDCaption, nIDHeaderTitle, nIDHeaderSubTitle, dwSize)
{
}

CPage::~CPage()
{
}

void CPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage, CPropertyPage)
END_MESSAGE_MAP()


// Gestionnaires de messages de CPage
