#if !defined(AFX_NUMPADDLG_H__880A457E_E0DD_4F62_8093_533309ACC352__INCLUDED_)
#define AFX_NUMPADDLG_H__880A457E_E0DD_4F62_8093_533309ACC352__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NumPadDlg.h : header file
//


#include "DialogTemplate.h"
//#include "SubWndContainer.h"
#include "SubStatic.h"
#include "StaticDecimal.h"


//---------------------------------------------------------------------------
//
//	CNumPadDlg dialog
//
//---------------------------------------------------------------------------


class CNumPadDlg : public CDialog
{
	enum Operation
	{
		opNone,
		opAdd,
		opSub,
		opMul,
		opDiv
	};

// Construction
public:
	enum Format
	{
		fmtInteger,
		fmtNumber,
		fmtCurrency
	};

	CNumPadDlg(enum Format format, BOOL bTemplate, CWnd* pParent = NULL);   // standard constructor

	void SetIntValue(int nVal) {m_dblVal = nVal;}
	void SetDblValue(double dblVal) {m_dblVal = dblVal;}
	void SetCurValue(CURRENCY cyVal);

	int GetIntValue() {return (int)m_dblVal;}
	double GetDblValue() {return m_dblVal;}
	CURRENCY GetCurValue();


// Dialog Data
	enum { IDD = IDD_NUMPAD };
	CStaticDecimal	m_sttDisplay;


// Overrides
	// ClassWizard generated virtual function overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	enum Format			m_format;
	double				m_dblVal,
						m_dblOpr,
						m_dblDec;
	Operation			m_op;
	bool				m_bError,
						m_bDec,
						m_bNew;
	TCHAR				m_szDec[8],
						m_szSep[8];
	CDialogTemplate		m_templ;
	CSubStatic*			m_pDisplay;

	BOOL				m_bTemplate;

	void UpdateDisplay();

	// Generated message map functions
	//{{AFX_MSG(CNumPadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAc();
	afx_msg void OnChs();
	afx_msg void OnAdd();
	afx_msg void OnSub();
	afx_msg void OnMul();
	afx_msg void OnDiv();
	afx_msg void OnEqual();
	afx_msg void OnDec();
	afx_msg void OnC();
	//}}AFX_MSG
	
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized); 
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	afx_msg void OnNumericKey(UINT nID);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedInv();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMPADDLG_H__880A457E_E0DD_4F62_8093_533309ACC352__INCLUDED_)
