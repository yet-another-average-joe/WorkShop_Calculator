#pragma once


// Bo�te de dialogue CPage

class CPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage)

public:
	CPage(); 
	CPage(UINT nIDTemplate, UINT nIDCaption = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));
	CPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));
	CPage(UINT nIDTemplate, UINT nIDCaption, UINT nIDHeaderTitle, UINT nIDHeaderSubTitle = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));
	CPage(LPCTSTR lpszTemplateName, UINT nIDCaption, UINT nIDHeaderTitle, UINT nIDHeaderSubTitle = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));

	virtual ~CPage();

// Donn�es de bo�te de dialogue
	UINT m_nID;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};
