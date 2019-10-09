#pragma once


// CTab

#include "Page.h"
//#include <Wcebar.h>


class CTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CTab)

public:
	CTab(); 
	CTab(UINT nIDCaption,CWnd* pParentWnd = NULL,UINT iSelectPage = 0);
	CTab(LPCTSTR pszCaption,CWnd* pParentWnd = NULL,UINT iSelectPage = 0);
	CTab(UINT nIDCaption,CWnd* pParentWnd,UINT iSelectPage,HBITMAP hbmWatermark,HPALETTE hpalWatermark = NULL,HBITMAP hbmHeader = NULL);
	CTab(LPCTSTR pszCaption,CWnd* pParentWnd,UINT iSelectPage,HBITMAP hbmWatermark,HPALETTE hpalWatermark = NULL,HBITMAP hbmHeader = NULL);

	// place une chaîne en bas des onglets dans une CCeCommandBar
	void SetLink(LPCTSTR pszLink) {m_strLink = pszLink;}
	
	virtual ~CTab();
	CPage* m_tabPages[2];
	int m_nNumberOfPages;

protected:
	void SetCaption(UINT nIDCaption);
	void SetCaption(LPCTSTR pszCaption);
	void Init();

	CCommandBar*	m_pWndEmptyCB;

	void HookCallback();

	static CString				m_strLink;
	static CString				m_strTitle;
	static PFNPROPSHEETCALLBACK	m_pCallBack;

	static int CALLBACK CePropertySheetCallBack(HWND hWnd, UINT message, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};


