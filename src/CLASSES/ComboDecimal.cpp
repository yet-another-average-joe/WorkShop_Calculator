// ComboBoxNumber.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ComboDecimal.h"


// CComboDecimal

IMPLEMENT_DYNAMIC(CComboDecimal, CComboEx)

CComboDecimal::CComboDecimal()
{
//	m_nCustStyle=normal;
}

CComboDecimal::~CComboDecimal()
{
}


BEGIN_MESSAGE_MAP(CComboDecimal, CComboEx)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_CONTROL_REFLECT(CBN_DROPDOWN, &CComboDecimal::OnCbnDropdown)
	//ON_WM_CHAR()
END_MESSAGE_MAP()

// Gestionnaires de messages de CComboDecimal

BOOL CComboDecimal::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN) 
		UINT nChar = pMsg->wParam;

	return CComboEx::PreTranslateMessage(pMsg);
}

//http://support.microsoft.com/kb/174667/en-us/

HBRUSH CComboDecimal::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor == CTLCOLOR_EDIT)
	{
		if (m_edit.GetSafeHwnd() == NULL)
		{
			m_edit.SubclassWindow(pWnd->GetSafeHwnd());
			m_edit.ModifyStyle(0, ES_NUMBER);
		}
	}

	return CComboEx::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CComboDecimal::OnDestroy()
{
	if (m_edit.GetSafeHwnd() != NULL)
		m_edit.UnsubclassWindow();

	CComboEx::OnDestroy();
}

int CComboDecimal::AddNumber(double fNumber, int count)
{
	CString str;

	DoubleToText(str, fNumber, count);

	return AddString(str);
}

double CComboDecimal::GetCurSelNumber()
{
	double fValue = 0;
	int nSel = GetCurSel();
	if(nSel!=CB_ERR)
	{
		CString str;
		int nLen = GetLBTextLen(nSel);
		TCHAR* buf = str.GetBuffer(nLen);
		GetLBText(nSel, buf);
		TextToDouble(buf, fValue);
		str.ReleaseBuffer();
	}

	return fValue;
}

double CComboDecimal::GetEditNumber()
{
	double fValue = 0;
	CString str;
	GetWindowText(str);
	TCHAR* buf = str.GetBuffer();
	TextToDouble(buf, fValue);
	str.ReleaseBuffer();

	return fValue;
}


//void CComboDecimal::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO : ajoutez ici le code de votre gestionnaire de messages et/ou les paramètres par défaut des appels
//
//	CComboEx::OnChar(nChar, nRepCnt, nFlags);
//}
