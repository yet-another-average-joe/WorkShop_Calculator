// ComboBoxInteger.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ComboInteger.h"
#include "EditDecimal.h"


// CComboInteger

IMPLEMENT_DYNAMIC(CComboInteger, CComboEx)

CComboInteger::CComboInteger()
{
	m_fSigned=FALSE;
}

CComboInteger::~CComboInteger()
{
}


BEGIN_MESSAGE_MAP(CComboInteger, CComboEx)
	ON_WM_CHAR()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
//	ON_CONTROL_REFLECT(CBN_DROPDOWN, &CComboInteger::OnCbnDropdown)
END_MESSAGE_MAP()



// Gestionnaires de messages de CComboInteger

void CComboInteger::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// bloque le signe '-'

	if(m_fSigned==FALSE && nChar=='-'/*m_NegativeSign[0]*/)
	{
		MessageBeep(0);
		return;
	}

	//BOOL bHandled = FALSE;
	//CDecimalSupport<CEditDecimal>::OnChar(0, nChar, 0, bHandled);
	//if (!bHandled)
	//	CEdit::OnChar(nChar , nRepCnt,  nFlags);
}


//BOOL CComboInteger::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO : ajoutez ici votre code spécialisé et/ou l'appel de la classe de base
//
//	return CComboEx::PreTranslateMessage(pMsg);
//}

//http://support.microsoft.com/kb/174667/en-us/

HBRUSH CComboInteger::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		//[ASCII 160][ASCII 160][ASCII 160]Edit control
		if (m_edit.GetSafeHwnd() == NULL)
			m_edit.SubclassWindow(pWnd->GetSafeHwnd());
	}

	return CComboEx::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CComboInteger::OnDestroy()
{
	if (m_edit.GetSafeHwnd() != NULL)
         m_edit.UnsubclassWindow();

	  CComboEx::OnDestroy();
}

int CComboInteger::AddNumber(int n)
{
	CString str;

	str.Format(_T("%d"), n);

	return AddString(str);
}

int CComboInteger::GetCurSelNumber()
{
	int n = 0;
	int nSel = GetCurSel();
	if(nSel!=CB_ERR)
	{
		CString str;
		int nLen = GetLBTextLen(nSel);
		TCHAR* buf = str.GetBuffer(nLen);
		GetLBText(nSel, buf);
		//TextToDouble(buf, fValue);
		n=_wtoi(buf);
		str.ReleaseBuffer();
	}

	return n;
}

int CComboInteger::GetEditNumber()
{
	int n = 0;
	CString str;
	GetWindowText(str);
	const TCHAR* buf = str.GetBuffer();
	//TextToDouble(buf, fValue);
	n=_wtoi(buf);
	str.ReleaseBuffer();

	return n;
}

