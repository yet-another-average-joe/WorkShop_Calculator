// PageCalc.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ParserCalc.h"
#include "PageCalc.h"
#include "FormelParser.h"

// Boîte de dialogue CPageCalc

#define CRBKGND RGB(255,255,255)
#define CRTXT RGB(255,255,255)

IMPLEMENT_DYNAMIC(CPageCalc, CPropPageEx)

CPageCalc::CPageCalc(CData* pData)
	: CPropPageEx(CPageCalc::IDD, pData)
	, m_strExpr(_T(""))
	, m_strResult(_T(""))
{
	m_strExpr = _T("deg(arccos(sqrt(2)/2))");
	m_strResult = _T("");
	m_dPI = 3.14159265358979;
	m_dX = 0.0123;

	m_brBkgnd.CreateSolidBrush(CRBKGND);
}

CPageCalc::~CPageCalc()
{
	m_brBkgnd.DeleteObject();
}

void CPageCalc::DoDataExchange(CDataExchange* pDX)
{
	CPropPageEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_EXPR, m_editExpr);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Text(pDX, IDC_EDIT_EXPR, m_strExpr);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);

	DDX_Control(pDX, IDC_0, m_btn0);
	DDX_Control(pDX, IDC_1, m_btn1);
	DDX_Control(pDX, IDC_2, m_btn2);
	DDX_Control(pDX, IDC_3, m_btn3);
	DDX_Control(pDX, IDC_4, m_btn4);
	DDX_Control(pDX, IDC_5, m_btn5);
	DDX_Control(pDX, IDC_6, m_btn6);
	DDX_Control(pDX, IDC_7, m_btn7);
	DDX_Control(pDX, IDC_8, m_btn8);
	DDX_Control(pDX, IDC_9, m_btn9);
	DDX_Control(pDX, IDC_DOT, m_btnDot);
	DDX_Control(pDX, IDC_PI, m_btnPI);
	DDX_Control(pDX, IDC_X, m_btnX);

	DDX_Control(pDX, IDC_PLUS, m_btnPlus);
	DDX_Control(pDX, IDC_MINUS, m_btnMinus);
	DDX_Control(pDX, IDC_MUL, m_btnMul);
	DDX_Control(pDX, IDC_DIV, m_btnDiv);
	DDX_Control(pDX, IDC_EQU, m_btnEqu);

	DDX_Control(pDX, IDC_RAD, m_btnRad);
	DDX_Control(pDX, IDC_DEG, m_btnDeg);
	DDX_Control(pDX, IDC_ARC, m_checkArc);
	DDX_Control(pDX, IDC_HYP, m_checkHyp);
	DDX_Control(pDX, IDC_SIN, m_btnSin);
	DDX_Control(pDX, IDC_COS, m_btnCos);
	DDX_Control(pDX, IDC_TAN, m_btnTan);
	DDX_Control(pDX, IDC_SINH, m_btnSinh);
	DDX_Control(pDX, IDC_COSH, m_btnCosh);
	DDX_Control(pDX, IDC_TANH, m_btnTanh);
	DDX_Control(pDX, IDC_ASIN, m_btnAsin);
	DDX_Control(pDX, IDC_ACOS, m_btnAcos);
	DDX_Control(pDX, IDC_ATAN, m_btnAtan);
	DDX_Control(pDX, IDC_ASINH, m_btnAsinh);
	DDX_Control(pDX, IDC_ACOSH, m_btnAcosh);
	DDX_Control(pDX, IDC_ATANH, m_btnAtanh);

	DDX_Control(pDX, IDC_INT, m_btnInt);
	DDX_Control(pDX, IDC_ABS, m_btnAbs);
	DDX_Control(pDX, IDC_POW, m_btnPow);
	DDX_Control(pDX, IDC_LN, m_btnLn);
	DDX_Control(pDX, IDC_LOG, m_btnLog);
	DDX_Control(pDX, IDC_SQRT, m_btnSqrt);
	DDX_Control(pDX, IDC_EXP, m_btnExp);
	DDX_Control(pDX, IDC_10X, m_btn10x);
	DDX_Control(pDX, IDC_X2, m_btnX2);
	DDX_Control(pDX, IDC_PAR_OPEN, m_btnParOpen);
	DDX_Control(pDX, IDC_PAR_CLOSE, m_btnParClose);
}

BEGIN_MESSAGE_MAP(CPageCalc, CPropPageEx)
	ON_COMMAND_RANGE(IDC_0, IDC_9, OnNumber)
	ON_BN_CLICKED(IDC_DOT, OnDot)
	ON_BN_CLICKED(IDC_PI, OnPi)
	ON_BN_CLICKED(IDC_X, OnX)

	ON_BN_CLICKED(IDC_PLUS, OnPlus)
	ON_BN_CLICKED(IDC_MINUS, OnMinus)
	ON_BN_CLICKED(IDC_MUL, OnMul)
	ON_BN_CLICKED(IDC_DIV, OnDiv)
	ON_BN_CLICKED(IDC_EQU, OnEqu)

	ON_BN_CLICKED(IDC_ARC, OnArc)
	ON_BN_CLICKED(IDC_HYP, OnHyp)
	ON_BN_CLICKED(IDC_RAD, OnRad)
	ON_BN_CLICKED(IDC_DEG, OnDeg)
	ON_BN_CLICKED(IDC_SIN, OnSin)
	ON_BN_CLICKED(IDC_COS, OnCos)
	ON_BN_CLICKED(IDC_TAN, OnTan)
	ON_BN_CLICKED(IDC_SINH, OnSinh)
	ON_BN_CLICKED(IDC_COSH, OnCosh)
	ON_BN_CLICKED(IDC_TANH, OnTanh)
	ON_BN_CLICKED(IDC_ASIN, OnAsin)
	ON_BN_CLICKED(IDC_ACOS, OnAcos)
	ON_BN_CLICKED(IDC_ATAN, OnAtan)
	ON_BN_CLICKED(IDC_ASINH, OnAsinh)
	ON_BN_CLICKED(IDC_ACOSH, OnAcosh)
	ON_BN_CLICKED(IDC_ATANH, OnAtanh)

	ON_BN_CLICKED(IDC_POW, OnPow)
	ON_BN_CLICKED(IDC_PAR_OPEN, OnParOpen)
	ON_BN_CLICKED(IDC_PAR_CLOSE, OnParClose)
	ON_BN_CLICKED(IDC_EXP, OnExp)
	ON_BN_CLICKED(IDC_LN, OnLn)
	ON_BN_CLICKED(IDC_INT, OnInt)
	ON_BN_CLICKED(IDC_ABS, OnAbs)
	ON_BN_CLICKED(IDC_10X, On10x)
	ON_BN_CLICKED(IDC_LOG, OnLog)
	ON_BN_CLICKED(IDC_X2, OnX2)
	ON_BN_CLICKED(IDC_SQRT, OnSqrt)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Gestionnaires de messages de CPageCalc

void CPageCalc::SetBtnColors(CBtnIcon& btn)
{
	btn.SetColor(CCeButtonST::BTNST_COLOR_FG_OUT, RGB(255,255,255));
	btn.SetColor(CCeButtonST::BTNST_COLOR_FG_IN, RGB(255,255,255));
	btn.SetColor(CCeButtonST::BTNST_COLOR_BK_IN, CRBKGND);
	btn.SetColor(CCeButtonST::BTNST_COLOR_BK_OUT, CRBKGND);
	btn.SetColor(CCeButtonST::BTNST_COLOR_BK_FOCUS, CRBKGND);
}

void CPageCalc::SetBtnColors2(CBtnIcon& btn)
{
	btn.SetColor(CCeButtonST::BTNST_COLOR_FG_OUT, RGB(0,0,0));
	btn.SetColor(CCeButtonST::BTNST_COLOR_BK_IN, CRBKGND);
	btn.SetColor(CCeButtonST::BTNST_COLOR_BK_OUT, CRBKGND);
	btn.SetColor(CCeButtonST::BTNST_COLOR_BK_FOCUS, CRBKGND);
}

BOOL CPageCalc::OnInitDialog()
{
	CPropPageEx::OnInitDialog();



	// superposer les boutons trigo
	CRect rc;

	m_btnSin.GetWindowRect(rc);
	ScreenToClient(rc);
	m_btnAsin.MoveWindow(rc);
	m_btnSinh.MoveWindow(rc);
	m_btnAsinh.MoveWindow(rc);

	m_btnCos.GetWindowRect(rc);
	ScreenToClient(rc);
	m_btnAcos.MoveWindow(rc);
	m_btnCosh.MoveWindow(rc);
	m_btnAcosh.MoveWindow(rc);

	m_btnTan.GetWindowRect(rc);
	ScreenToClient(rc);
	m_btnAtan.MoveWindow(rc);
	m_btnTanh.MoveWindow(rc);
	m_btnAtanh.MoveWindow(rc);

	int cx=rc.Width();
	int cy=rc.Height();
	// 72x38 en VGA -> 64x32 2*SM_CXMICON x	SM_CYMICON
	
	m_btnSinh.ShowWindow(SW_HIDE);
	m_btnCosh.ShowWindow(SW_HIDE);
	m_btnTanh.ShowWindow(SW_HIDE);
	m_btnAsin.ShowWindow(SW_HIDE);
	m_btnAcos.ShowWindow(SW_HIDE);
	m_btnAtan.ShowWindow(SW_HIDE);
	m_btnAsinh.ShowWindow(SW_HIDE);
	m_btnAcosh.ShowWindow(SW_HIDE);
	m_btnAtanh.ShowWindow(SW_HIDE);

	GetDlgItem(IDC_1)->GetWindowRect(rc);
	cx=rc.Width();
	cy=rc.Height();

	CSize size(2*::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));


	// boutons de fonctions
	m_btnSin.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnCos.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnTan.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnSinh.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnCosh.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnTanh.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnAsin.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnAcos.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnAtan.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnAsinh.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnAcosh.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnAtanh.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnInt.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnAbs.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnPow.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnRad.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnLn.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnLog.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnSqrt.SetIconMulti(IDI_SQRT, IDI_SQRT, size);
	m_btnExp.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btn10x.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnX2.SetIconMulti(IDI_BLACK, IDI_BLACK, size);
	m_btnDeg.SetIconMulti(IDI_BLACK, IDI_BLACK, size);

	SetBtnColors(m_btnSin);
	SetBtnColors(m_btnCos);
	SetBtnColors(m_btnTan);
	SetBtnColors(m_btnSinh);
	SetBtnColors(m_btnCosh);
	SetBtnColors(m_btnTanh);
	SetBtnColors(m_btnAsin);
	SetBtnColors(m_btnAcos);
	SetBtnColors(m_btnAtan);
	SetBtnColors(m_btnAsinh);
	SetBtnColors(m_btnAcosh);
	SetBtnColors(m_btnAtanh);
	SetBtnColors(m_btnInt);
	SetBtnColors(m_btnAbs);
	SetBtnColors(m_btnPow);
	SetBtnColors(m_btnRad);
	SetBtnColors(m_btnLn);
	SetBtnColors(m_btnLog);
	SetBtnColors(m_btnSqrt);
	SetBtnColors(m_btnExp);
	SetBtnColors(m_btn10x);
	SetBtnColors(m_btnX2);
	SetBtnColors(m_btnDeg);

//	m_btnSin.SetColor(CCeButtonST::BTNST_COLOR_BK_OUT, RGB(200,200,200));


	m_checkArc.SetIconMulti(IDI_BLUE, IDI_BLUE, size);
	m_checkHyp.SetIconMulti(IDI_BLUE, IDI_BLUE, size);
	SetBtnColors(m_checkArc);
	SetBtnColors(m_checkHyp);


	//m_checkArc.SetColor(CCeButtonST::BTNST_COLOR_FG_OUT, RGB(255,255,255));
	//m_checkHyp.SetColor(CCeButtonST::BTNST_COLOR_FG_OUT, RGB(255,255,255));

	//m_checkArc.SetColor(CCeButtonST::BTNST_COLOR_BK_IN, RGB(192,192,192));
	//m_checkHyp.SetColor(CCeButtonST::BTNST_COLOR_BK_IN, RGB(192,192,192));

	//m_checkArc.SetColor(CCeButtonST::BTNST_COLOR_BK_OUT, RGB(192,192,192));
	//m_checkHyp.SetColor(CCeButtonST::BTNST_COLOR_BK_OUT, RGB(192,192,192));

	//m_checkArc.SetColor(CCeButtonST::BTNST_COLOR_BK_FOCUS, RGB(192,192,192));
	//m_checkHyp.SetColor(CCeButtonST::BTNST_COLOR_BK_FOCUS, RGB(192,192,192));

	// nombres
	m_btn0.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btn1.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btn2.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btn3.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btn4.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btn5.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btn6.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btn7.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btn8.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btn9.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);
	m_btnPI.SetIconMulti(IDI_PI, IDI_PI, size);
	m_btnDot.SetIconMulti(IDI_LGREEN, IDI_LGREEN, size);

	SetBtnColors2(m_btn0);
	SetBtnColors2(m_btn1);
	SetBtnColors2(m_btn2);
	SetBtnColors2(m_btn3);
	SetBtnColors2(m_btn4);
	SetBtnColors2(m_btn5);
	SetBtnColors2(m_btn6);
	SetBtnColors2(m_btn7);
	SetBtnColors2(m_btn8);
	SetBtnColors2(m_btn9);
	SetBtnColors2(m_btnPI);
	SetBtnColors2(m_btnDot);

	// 4 opérations
	m_btnMul.SetIconMulti(IDI_MUL, IDI_MUL, size);
	m_btnDiv.SetIconMulti(IDI_DIV, IDI_DIV, size);
	m_btnPlus.SetIconMulti(IDI_PLUS, IDI_PLUS, size);
	m_btnMinus.SetIconMulti(IDI_MINUS, IDI_MINUS, size);
	SetBtnColors2(m_btnMul);
	SetBtnColors2(m_btnDiv);
	SetBtnColors2(m_btnPlus);
	SetBtnColors2(m_btnMinus);

	// égal
	m_btnEqu.SetIconMulti(IDI_CALC, IDI_CALC, size);
	SetBtnColors(m_btnEqu);

	//
	m_btnX.SetIconMulti(IDI_GREY, IDI_GREY, size);
	m_btnParOpen.SetIconMulti(IDI_GREY, IDI_GREY, size);
	m_btnParClose.SetIconMulti(IDI_GREY, IDI_GREY, size);
	SetBtnColors2(m_btnX);
	SetBtnColors2(m_btnParOpen);
	SetBtnColors2(m_btnParClose);

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CPageCalc::OnNumber(UINT nID) 
{
	ASSERT(nID >= IDC_0 && nID <= IDC_9);
	TCHAR buffer[20];   
	_itow(nID - IDC_0, buffer, 10);
	SetEingabe(buffer);
}

void CPageCalc::OnDot()
{	
	SetEingabe(_T(".")); 
}

void CPageCalc::OnEqu()
{
	int ErrorPosition;
	CString Errortext;
	Errortext.Empty();

	UpdateData(true);

	CFormulaParser FormulaParser;

	//__________________________________________________________________________________________________
	double retValue = FormulaParser.Calculation(m_strExpr, m_dX, ErrorPosition, Errortext);
	//__________________________________________________________________________________________________
	
	CWnd* pWnd = GetDlgItem(IDC_EDIT_EXPR);
	pWnd->SetFocus();
  if (ErrorPosition == 0)
	{
    if (Errortext == "")
		{
			//swprintf(buffer, _T("%f"), retValue);
			//m_strResult = 	buffer;
			m_strResult.Format(_T("%f"), retValue);
		}
		else
			m_strResult = 	_T("Error: ") + Errortext;
		pWnd->SendMessage(EM_SETSEL,32767,32767); 
	}
  else
	{
		m_strResult = 	Errortext;
		pWnd->SendMessage(EM_SETSEL,ErrorPosition - 1,ErrorPosition);
	}

	UpdateData(false);
}

void CPageCalc::OnX()  				{	SetEingabe(_T("x")); }
void CPageCalc::OnXb()  			{	SetEingabe(_T("X")); } 
void CPageCalc::OnPi() 				{	SetEingabe(_T("PI")); }

void CPageCalc::OnPlus()			{	SetEingabe(_T("+")); }
void CPageCalc::OnMinus()  			{	SetEingabe(_T("-")); }
void CPageCalc::OnMul() 			{	SetEingabe(_T("*")); }
void CPageCalc::OnDiv()				{	SetEingabe(_T("/")); }

void CPageCalc::OnRad() 			{	SetEingabeFunc(_T("rad()")); }
void CPageCalc::OnDeg() 			{	SetEingabeFunc(_T("deg()")); }
void CPageCalc::OnArc()				{	UpdateTrigBtns(); }
void CPageCalc::OnHyp()				{	UpdateTrigBtns(); }

void CPageCalc::OnSin()				{	SetEingabeFunc(_T("sin()")); }
void CPageCalc::OnCos() 			{	SetEingabeFunc(_T("cos()")); }
void CPageCalc::OnTan() 			{	SetEingabeFunc(_T("tan()")); }
void CPageCalc::OnSinh() 			{	SetEingabeFunc(_T("sinh()")); }
void CPageCalc::OnCosh() 			{	SetEingabeFunc(_T("cosh()")); }
void CPageCalc::OnTanh()			{	SetEingabeFunc(_T("tanh()")); }
void CPageCalc::OnAsin()			{	SetEingabeFunc(_T("arcsin()")); }
void CPageCalc::OnAcos()			{	SetEingabeFunc(_T("arccos()")); }
void CPageCalc::OnAtan()			{	SetEingabeFunc(_T("arctan()")); }
void CPageCalc::OnAsinh()			{	SetEingabeFunc(_T("arsinh()")); }
void CPageCalc::OnAcosh()			{	SetEingabeFunc(_T("arcosh()")); }
void CPageCalc::OnAtanh()			{	SetEingabeFunc(_T("artanh()")); }

void CPageCalc::OnPow() 			{	SetEingabe(_T("^")); }
void CPageCalc::OnParOpen() 		{	SetEingabe(_T("(")); }
void CPageCalc::OnParClose()	 	{	SetEingabe(_T(")")); }
void CPageCalc::On10x() 			{	SetEingabe(_T("10^")); }
void CPageCalc::OnX2() 				{	SetEingabe(_T("^2")); }
void CPageCalc::OnExp() 			{	SetEingabeFunc(_T("exp()")); }
void CPageCalc::OnLn() 				{	SetEingabeFunc(_T("ln()")); }
void CPageCalc::OnInt() 			{	SetEingabeFunc(_T("int()")); }
void CPageCalc::OnAbs()				{	SetEingabeFunc(_T("abs()")); }
void CPageCalc::OnLog() 			{	SetEingabeFunc(_T("log()")); }
void CPageCalc::OnSqrt() 			{	SetEingabeFunc(_T("sqrt()")); }



void CPageCalc::SetEingabe(CString str)
{
	CEdit* pWnd=(CEdit*)GetDlgItem(IDC_EDIT_EXPR);
	pWnd->ReplaceSel(str);
	UpdateData(true);
//	m_strExpr_vorher = m_strExpr;
	//m_strExpr += str;
	//UpdateData(false);

	pWnd->SetFocus();
	//pWnd->SendMessage(EM_SETSEL,32767,32767); //Cursor ans Ende
	pWnd->Invalidate();
	pWnd->RedrawWindow();				

	
}

// déplace le caret pour le placer entre les parenthèses
void CPageCalc::SetEingabeFunc(CString str)
{
	CEdit* pWnd=(CEdit*)GetDlgItem(IDC_EDIT_EXPR);
	pWnd->ReplaceSel(str);
	m_editExpr.SendMessage(WM_KEYDOWN, VK_LEFT, 0);
	UpdateData(true);
//	m_strExpr_vorher = m_strExpr;
	//m_strExpr += str;
	//UpdateData(false);

	pWnd->SetFocus();
	//pWnd->SendMessage(EM_SETSEL,32767,32767); //Cursor ans Ende
	pWnd->Invalidate();
	pWnd->RedrawWindow();				

	
}

void CPageCalc::UpdateTrigBtns()
{
	BOOL bArc;
	switch(m_checkArc.GetCheck())
	{
	case BST_UNCHECKED:
		bArc=FALSE;
		break;
	case BST_CHECKED:
		bArc=TRUE;
		break;
	default:
		ASSERT(FALSE);
		return;
	}

	BOOL bHyp;
	switch(m_checkHyp.GetCheck())
	{
	case BST_UNCHECKED:
		bHyp=FALSE;
		break;
	case BST_CHECKED:
		bHyp=TRUE;
		break;
	default:
		ASSERT(FALSE);
		return;
	}

	if(!bArc && !bHyp)
	{
		m_btnSin.ShowWindow(SW_SHOW);
		m_btnCos.ShowWindow(SW_SHOW);
		m_btnTan.ShowWindow(SW_SHOW);
		m_btnSinh.ShowWindow(SW_HIDE);
		m_btnCosh.ShowWindow(SW_HIDE);
		m_btnTanh.ShowWindow(SW_HIDE);
		m_btnAsin.ShowWindow(SW_HIDE);
		m_btnAcos.ShowWindow(SW_HIDE);
		m_btnAtan.ShowWindow(SW_HIDE);
		m_btnAsinh.ShowWindow(SW_HIDE);
		m_btnAcosh.ShowWindow(SW_HIDE);
		m_btnAtanh.ShowWindow(SW_HIDE);
	}
	else
	if(bArc && !bHyp)
	{
		m_btnSin.ShowWindow(SW_HIDE);
		m_btnCos.ShowWindow(SW_HIDE);
		m_btnTan.ShowWindow(SW_HIDE);
		m_btnSinh.ShowWindow(SW_HIDE);
		m_btnCosh.ShowWindow(SW_HIDE);
		m_btnTanh.ShowWindow(SW_HIDE);
		m_btnAsin.ShowWindow(SW_SHOW);
		m_btnAcos.ShowWindow(SW_SHOW);
		m_btnAtan.ShowWindow(SW_SHOW);
		m_btnAsinh.ShowWindow(SW_HIDE);
		m_btnAcosh.ShowWindow(SW_HIDE);
		m_btnAtanh.ShowWindow(SW_HIDE);
	}
	else
	if(!bArc && bHyp)
	{
		m_btnSin.ShowWindow(SW_HIDE);
		m_btnCos.ShowWindow(SW_HIDE);
		m_btnTan.ShowWindow(SW_HIDE);
		m_btnSinh.ShowWindow(SW_SHOW);
		m_btnCosh.ShowWindow(SW_SHOW);
		m_btnTanh.ShowWindow(SW_SHOW);
		m_btnAsin.ShowWindow(SW_HIDE);
		m_btnAcos.ShowWindow(SW_HIDE);
		m_btnAtan.ShowWindow(SW_HIDE);
		m_btnAsinh.ShowWindow(SW_HIDE);
		m_btnAcosh.ShowWindow(SW_HIDE);
		m_btnAtanh.ShowWindow(SW_HIDE);
	}
	else
	if(bArc && bHyp)
	{
		m_btnSin.ShowWindow(SW_HIDE);
		m_btnCos.ShowWindow(SW_HIDE);
		m_btnTan.ShowWindow(SW_HIDE);
		m_btnSinh.ShowWindow(SW_HIDE);
		m_btnCosh.ShowWindow(SW_HIDE);
		m_btnTanh.ShowWindow(SW_HIDE);
		m_btnAsin.ShowWindow(SW_HIDE);
		m_btnAcos.ShowWindow(SW_HIDE);
		m_btnAtan.ShowWindow(SW_HIDE);
		m_btnAsinh.ShowWindow(SW_SHOW);
		m_btnAcosh.ShowWindow(SW_SHOW);
		m_btnAtanh.ShowWindow(SW_SHOW);
	}

	CWnd* pWnd = GetDlgItem(IDC_EDIT_EXPR);
	pWnd->SetFocus();
}

BOOL CPageCalc::OnEraseBkgnd(CDC* pDC)
{
	// TODO : ajoutez ici le code de votre gestionnaire de messages et/ou les paramètres par défaut des appels
	//CBrush br;
	//br.CreateSolidBrush(RGB(200,200,200));
	//CRect rc;
	//GetClientRect(rc);
	//pDC->FillRect(rc, &br);
	//br.DeleteObject();


	return CPropPageEx::OnEraseBkgnd(pDC);
}

HBRUSH CPageCalc::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CPropPageEx::OnCtlColor(pDC, pWnd, nCtlColor);

	//// TODO:  Modifier ici les attributs du DC

	//// TODO:  Retourner un autre pinceau si le pinceau par défaut n'est pas souhaité
	//return hbr;

	return (HBRUSH)m_brBkgnd.m_hObject;
}
