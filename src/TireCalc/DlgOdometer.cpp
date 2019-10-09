// DlgOdometer.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "TireCalc.h"
#include "DlgOdometer.h"
#include "NumPadDlg.h"


// Boîte de dialogue CDlgOdometer

IMPLEMENT_DYNAMIC(CDlgOdometer, CDialog)

CDlgOdometer::CDlgOdometer(CWnd* pParent /*=NULL*/)
	: CCEDialog(CDlgOdometer::IDD, pParent)
{

}

CDlgOdometer::~CDlgOdometer()
{
}

void CDlgOdometer::DoDataExchange(CDataExchange* pDX)
{
	CCEDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CALC, m_btnCalc);
}


BEGIN_MESSAGE_MAP(CDlgOdometer, CCEDialog)
	ON_BN_CLICKED(IDC_BTN_CALC, &CDlgOdometer::OnBnClickedBtnCalc)
END_MESSAGE_MAP()


// Gestionnaires de messages de CDlgOdometer

BOOL CDlgOdometer::OnInitDialog()
{
	CCEDialog::OnInitDialog();

	CSize size(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	m_btnCalc.SetIconMulti(IDI_CALC, IDI_CALC, size);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}

void CDlgOdometer::OnBnClickedBtnCalc()
{
	CNumPadDlg pad(CNumPadDlg::fmtNumber, TRUE);
	pad.DoModal();
}
