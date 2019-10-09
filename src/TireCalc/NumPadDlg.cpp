// NumPadDlg.cpp : implementation file
//
#include "stdafx.h"
#include "TireCalc.h"
#include "NumPadDlg.h"

#include "SubButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//---------------------------------------------------------------------------
//
//	CNumPadDlg dialog
//
//---------------------------------------------------------------------------


CNumPadDlg::CNumPadDlg(enum Format format, BOOL bTemplate, CWnd* pParent /*=NULL*/)
:	CDialog(CNumPadDlg::IDD, pParent),
	m_format	(format),
	m_bTemplate	(bTemplate),
	m_pDisplay	(NULL)
{
	//{{AFX_DATA_INIT(CNumPadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bFullScreen	= FALSE;
	m_bError		= false;
	m_bDec			= false;
	m_bNew			= true;
	m_dblOpr		=
	m_dblVal		= 0.0;
	m_dblDec		= 0.0;
	m_op			= opNone;

	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL,  m_szDec, 7);
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, m_szSep, 7);
}


void CNumPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNumPadDlg)
//	DDX_Control(pDX, IDC_DEC, m_btnDec);
		DDX_Control(pDX, IDC_DISPLAY, m_sttDisplay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNumPadDlg, CDialog)
	//{{AFX_MSG_MAP(CNumPadDlg)
	ON_BN_CLICKED(IDC_AC, OnAc)
	ON_BN_CLICKED(IDC_CHS, OnChs)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_SUB, OnSub)
	ON_BN_CLICKED(IDC_MUL, OnMul)
	ON_BN_CLICKED(IDC_DIV, OnDiv)
	ON_BN_CLICKED(IDC_EQUAL, OnEqual)
	ON_BN_CLICKED(IDC_DEC, OnDec)
	ON_BN_CLICKED(IDC_C, OnC)
	//}}AFX_MSG_MAP
	ON_WM_ACTIVATE()
	ON_WM_SETTINGCHANGE()

	ON_CONTROL_RANGE(BN_CLICKED, IDC_K0, IDC_K9, OnNumericKey)
	ON_BN_CLICKED(IDOK, &CNumPadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_INV, &CNumPadDlg::OnBnClickedInv)
END_MESSAGE_MAP()


//---------------------------------------------------------------------------
//
//	CNumPadDlg operations
//
//---------------------------------------------------------------------------


// CNumPadDlg::UpdateDisplay
//
//		Updates the display
//
void CNumPadDlg::UpdateDisplay()
{
	if(m_bError)
	{
			m_sttDisplay.SetWindowText(_T("ERROR"));
	}
	else
	{
		TCHAR	szFmtRaw[65],
				szFmtOut[65];
		CString strFmtOut;
		int		nRet;

		wsprintf(szFmtRaw, _T("%f"), m_dblVal);

		if(m_format == fmtNumber)
		{
			//nRet = GetNumberFormat(LOCALE_USER_DEFAULT, NULL, szFmtRaw, NULL, szFmtOut, 64);
			m_sttDisplay.SetDecimalValue(m_dblVal, 16);
			return;

		//
		// Display the number
		//
			m_sttDisplay.SetWindowText(szFmtOut);
		}
		else if(m_format == fmtCurrency)
		{
			nRet = GetCurrencyFormat(LOCALE_USER_DEFAULT, NULL, szFmtRaw, NULL, szFmtOut, 64);
		}
		else
		{
			NUMBERFMT	nfmt = {0, 0, 3, m_szDec, m_szSep, 1};

			nRet = GetNumberFormat(LOCALE_USER_DEFAULT, NULL, szFmtRaw, &nfmt, szFmtOut, 64);
		}

		if(!nRet)
			_tcscpy(szFmtOut, _T("Format!"));

		//
		// Display the number
		//
			m_sttDisplay.SetWindowText(szFmtOut);
	}
}


// CNumPadDlg::SetCurValue
//
//		Sets the value from a currency type
//
void CNumPadDlg::SetCurValue(CURRENCY cy)
{
	HRESULT	hr;

	hr = VarR8FromCy(cy, &m_dblVal);
	if(hr != S_OK)
		m_dblVal = 0;
}


// CNumPadDlg::GetCurValue
//
//		Retuens the value as a currency type
//
CURRENCY CNumPadDlg::GetCurValue()
{
	CURRENCY	cy;
	HRESULT		hr;

	hr = VarCyFromR8(m_dblVal, &cy);
	if(hr != S_OK)
	{
		cy.Hi	= 0;
		cy.Lo	= 0;
	}
	return cy;
}


//---------------------------------------------------------------------------
//
//	CNumPadDlg message handlers
//
//---------------------------------------------------------------------------


// CNumPadDlg::OnInitDialog
//
//		Initializes the dialog
//
BOOL CNumPadDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// pour avoir un bouton, et que ce soit le "X"
	ModifyStyle(0, WS_NONAVDONEBUTTON | WS_SYSMENU, 0/*SWP_NOSIZE*/);

	UpdateDisplay();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CNumPadDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);
}


// CNumPadDlg::OnSettingChange
//
//		Handle the setting changes
//
void CNumPadDlg::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CWnd::OnSettingChange(uFlags, lpszSection);
}


//---------------------------------------------------------------------------
//
//	CNumPadDlg command handlers
//
//---------------------------------------------------------------------------


// CNumPadDlg::OnNumericKey
//
//		Processes all numeric keys
//
void CNumPadDlg::OnNumericKey(UINT nID)
{
	if(m_bNew)
	{
		m_dblVal = 0.0;
		m_bNew = false;
		m_bDec = false;
	}

	if(m_bDec)
	{
		m_dblVal += (nID - IDC_K0) * m_dblDec;
		m_dblDec *= 0.1;
	}
	else if(fabs(m_dblVal) < 1e14)
		m_dblVal = m_dblVal * 10.0 + (nID - IDC_K0);
	else
		MessageBeep(MB_ICONEXCLAMATION);

	UpdateDisplay();
}


// CNumPadDlg::OnAc
//
//		Clears all values
//
void CNumPadDlg::OnAc() 
{
	m_bDec   =
	m_bError = false;
	m_bNew	 = true;
	m_dblOpr =
	m_dblVal = 0.0;
	m_op	 = opNone;

	UpdateDisplay();
}


// CNumPadDlg::OnC
//
//		Clears the last entry
//
void CNumPadDlg::OnC() 
{
	m_bDec   =
	m_bError = false;
	m_bNew	 = true;
	m_dblVal = 0.0;

	UpdateDisplay();
}


// CNumPadDlg::OnChs
//
//		Changes the sign
//
void CNumPadDlg::OnChs() 
{
	m_dblVal = -m_dblVal;

	UpdateDisplay();
}


// CNumPadDlg::OnAdd
//
//		Adds two numbers
//
void CNumPadDlg::OnAdd() 
{
	OnEqual();

	m_dblOpr	= m_dblVal;
	m_op		= opAdd;
}


// CNumPadDlg::OnSub
//
//		Subtracts two numbers
//
void CNumPadDlg::OnSub() 
{
	OnEqual();

	m_dblOpr	= m_dblVal;
	m_op		= opSub;
}


// CNumPadDlg::OnMul
//
//		Multiplies two numbers
//
void CNumPadDlg::OnMul() 
{
	OnEqual();

	m_dblOpr	= m_dblVal;
	m_op		= opMul;
}


// CNumPadDlg::OnDiv
//
//		Divides two numbers
//
void CNumPadDlg::OnDiv() 
{
	OnEqual();

	m_dblOpr	= m_dblVal;
	m_op		= opDiv;
}


// CNumPadDlg::OnEqual
//
//		Calculates the result of an operation
//
void CNumPadDlg::OnEqual() 
{
	m_bError = FALSE;

	switch(m_op)
	{
	case opAdd:
		m_dblVal += m_dblOpr;
		break;

	case opSub:
		m_dblVal = m_dblOpr - m_dblVal;
		break;

	case opMul:
		m_dblVal *= m_dblOpr;
		break;

	case opDiv:
		if(m_dblVal == 0.0)
			m_bError = TRUE;
		else
			m_dblVal = m_dblOpr / m_dblVal;
		break;

	default:
		m_dblOpr = 0.0;
	}

	m_bDec = false;
	m_bNew = true;

	UpdateDisplay();

	m_op = opNone;
}


// CNumPadDlg::OnDec
//
//		Entering decimal numbers
//
void CNumPadDlg::OnDec() 
{
	if(!m_bDec)
	{
		m_bDec = true;
		m_dblDec = 0.1;

		if(m_bNew)
		{
			m_dblVal = 0.0;
			m_bNew = false;
		}

		UpdateDisplay();
	}
}

void CNumPadDlg::OnBnClickedOk()
{
	OnEqual();
	OnOK();
}

void CNumPadDlg::OnBnClickedInv()
{
	m_dblVal = 1/m_dblVal;

	UpdateDisplay();
}
