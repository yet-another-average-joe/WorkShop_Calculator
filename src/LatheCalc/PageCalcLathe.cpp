// PageCalcTurning.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "LatheCalc.h"
#include "PageCalcLathe.h"
#include "SheetLatheCalc.h"

class t_OperationInfo {
public:
	UINT nText;
	int	nPercent;
};

t_OperationInfo OperationInfo[] = {
	{IDS_CHARIOTAGE, 100},
	{IDS_CHARIOTAGE_FINITION, 133},
	{IDS_DRESSAGE, 80},
	{IDS_ALESAGE, 75},
	{IDS_PERCAGE, 75},
	{IDS_TRONCONNAGE, 50},
	{IDS_FILETAGE, 33},
	{IDS_ALESAGE_MACHINE, 25}
};

// valeurs par défaut pour le slider
#define SLIDER_DMIN	1
#define SLIDER_DMAX	150

// donner une valeur par défaut au diamètre, sinon problème !


// Boîte de dialogue CPageCalcLathe

IMPLEMENT_DYNAMIC(CPageCalcLathe, CPageCalcBase)

CPageCalcLathe::CPageCalcLathe(CData* pData/*=NULL*/)
	: CPageCalcBase(CPageCalcLathe::IDD, pData)
{
	m_fCorrect=100.0;
	m_comboOperation.SetFullDrop(TRUE);
}

CPageCalcLathe::~CPageCalcLathe()
{
}

void CPageCalcLathe::DoDataExchange(CDataExchange* pDX)
{
	CPageCalcBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_OPERATION, m_comboOperation);
	DDX_Control(pDX, IDC_STATIC_OPERATION, m_staticOperation);
}

BEGIN_MESSAGE_MAP(CPageCalcLathe, CPageCalcBase)
	ON_CBN_SELCHANGE(IDC_COMBO_OPERATION, &CPageCalcLathe::OnCbnSelchangeComboOperation)
END_MESSAGE_MAP()

// Gestionnaires de messages de CPageCalcLathe

BOOL CPageCalcLathe::OnInitDialog()
{
	CPageCalcBase::OnInitDialog();

	// remplit la combo "Opérations"

	for(int i = 0; i < 8 ; i++) 
	{
		CString str;
		str.LoadString(OperationInfo[i].nText);
		m_comboOperation.AddString(str);
		m_comboOperation.SetItemData(i, OperationInfo[i].nPercent);
	}

	m_comboOperation.SetCurSel(0);
	m_fCorrect=(double)m_comboOperation.GetItemData(0);

	if(m_pData!=NULL)
	{
		m_staticOperation.ShowWindow(SW_SHOW);
		m_staticOperation.EnableWindow(TRUE);
		m_comboOperation.ShowWindow(SW_SHOW);
		m_comboOperation.EnableWindow(TRUE);
	}
	else
	{
		// pas de données : mode calculette, désactiver les combos
		m_staticOperation.ShowWindow(SW_HIDE);
		m_staticOperation.EnableWindow(FALSE);
		m_comboOperation.ShowWindow(SW_HIDE);
		m_comboOperation.EnableWindow(FALSE);
	}

	OnChangeTWPair();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageCalcLathe::OnCbnSelchangeComboOperation()
{
	int nOperation = m_comboOperation.GetCurSel();
	ASSERT(nOperation!=LB_ERR);
	m_fCorrect = (double) m_comboOperation.GetItemData(nOperation);
	m_editVc.m_fLower=ReadVcmin()*m_fCorrect/100.0;
	m_editVc.m_fUpper=ReadVcmax()*m_fCorrect/100.0;
	
	// recadrer la Vc
	SetMeanVc();

	CalcAndUpdateN();
}

void CPageCalcLathe::OnChangeTWPair()
{
	if(m_comboOperation.GetCount()<=0)
		return; // pas initialisée
	
	int nOperation = m_comboOperation.GetCurSel();
	ASSERT(nOperation!=LB_ERR);

	m_fCorrect = (double) m_comboOperation.GetItemData(nOperation);

	// appelée par OnInitDialog(), et donc combo opération pas encore remplie
	// 100% ce qui correspondra au premier item (un peu bourrin)
	m_editVc.m_fLower=ReadVcmin()*m_fCorrect/100.0;
	m_editVc.m_fUpper=ReadVcmax()*m_fCorrect/100.0;

	// recadrer la Vc

	SetMeanVc();

	CalcAndUpdateN();
}

void CPageCalcLathe::OnSlider(int nTBCode, UINT nPos)
{
	CPageCalcBase::OnSlider(nTBCode, nPos);

	CWnd* pwndFocus=GetFocus();
	int nID=pwndFocus->GetDlgCtrlID();

	switch(nID)
	{
	// MAJ m_editD et calcul résultat -> m_editN
	case IDC_COMBO_OPERATION: 
		{
			int nCount=m_comboOperation.GetCount();
			int nCurSel=m_comboOperation.GetCurSel();

			switch(nTBCode)
			{
			case SB_LINEUP:
				if(nCurSel>0)
				{
					m_comboOperation.SetCurSel(nCurSel-1);
					OnCbnSelchangeComboOperation();
				}
				break;
			case SB_LINEDOWN:
				if(nCurSel<nCount-1)
				{
					m_comboOperation.SetCurSel(nCurSel+1);
					OnCbnSelchangeComboOperation();
				}
				break;
			default:
				ASSERT(0);
				break;
			}
		}
		break;
	default:
		return;
	}
}

// pour étendre la combo "opération" au bord droit
void CPageCalcLathe::SetControlsPos()
{
	CPageCalcBase::SetControlsPos();

	CRect rcClient;
	GetClientRect(rcClient);
	int cxMargin = RepositionScrollPad(rcClient);
	UINT uFlags=SWP_NOZORDER|SWP_NOOWNERZORDER;

	CRect rc;
	m_staticOperation.GetWindowRect(rc);
	ScreenToClient(rc);
	m_staticOperation.SetWindowPos(NULL, cxMargin, rc.top, rc.Width(), rc.Height(), uFlags|SWP_NOSIZE);

	// combo dérivée de CComboEx : gère la hauteur dans CBN_DROPDOWN
	int xRightStaticOperation=rc.right;
	
	m_comboOperation.GetWindowRect(rc);
	ScreenToClient(rc);
	m_comboOperation.SetWindowPos(NULL, xRightStaticOperation+::GetSystemMetrics(SM_CXEDGE), 
					rc.top, rcClient.Width()-xRightStaticOperation-2*::GetSystemMetrics(SM_CXEDGE), rc.Height(), uFlags);
}
