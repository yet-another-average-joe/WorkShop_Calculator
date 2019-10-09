// ThunderCalcDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ThunderCalc.h"
#include "ThunderCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Boîte de dialogue CThunderCalcDlg

CThunderCalcDlg::CThunderCalcDlg(CWnd* pParent /*=NULL*/)
	: CDlgMain(CThunderCalcDlg::IDD, FALSE, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	EnableScrollbars(FALSE);
	m_pTimer=NULL;
	m_nDistance=0;
	m_nTime=0;
}

void CThunderCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgMain::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThunderCalcDlg, CDlgMain)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Gestionnaires de messages pour CThunderCalcDlg

BOOL CThunderCalcDlg::OnInitDialog()
{
	CDlgMain::OnInitDialog();

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO : ajoutez ici une initialisation supplémentaire
	
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}


void CThunderCalcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 10 ms à 340 m/s : 3.4 m
	m_nTime++; // millisecondes
	m_nDistance+=34; // décimètres
	CString str;
	str.Format(_T("%0.2f"), ((double)m_nTime)/100.0);
	SetDlgItemText(IDC_STATIC_TIME, str);
	SetDlgItemInt(IDC_STATIC_DISTANCE, m_nDistance/10);

	CDlgMain::OnTimer(nIDEvent);
}

void CThunderCalcDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_pTimer==NULL)
	{
		m_pTimer=SetTimer(1, 10, NULL);
		m_nDistance=0;
		m_nTime=0;
		SetDlgItemInt(IDC_STATIC_DISTANCE, 0);
		SetDlgItemInt(IDC_STATIC_TIME, 0);
	}
	else
	{
		KillTimer(m_pTimer);
		m_pTimer=FALSE;
	}

	CDlgMain::OnLButtonDown(nFlags, point);
}
