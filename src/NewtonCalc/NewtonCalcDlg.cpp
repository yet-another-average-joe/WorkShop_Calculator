// NewtonCalcDlg.cpp : fichier d'impl�mentation
//

#include "stdafx.h"
#include "NewtonCalc.h"
#include "NewtonCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Bo�te de dialogue CNewtonCalcDlg

CNewtonCalcDlg::CNewtonCalcDlg(CWnd* pParent /*=NULL*/)
	: CDlgMain(CNewtonCalcDlg::IDD, NULL, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	EnableScrollbars(FALSE);
	m_pTimer=NULL;
	m_nTime=0;
}

void CNewtonCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgMain::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNewtonCalcDlg, CDlgMain)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Gestionnaires de messages pour CNewtonCalcDlg

BOOL CNewtonCalcDlg::OnInitDialog()
{
	CDlgMain::OnInitDialog();

	// D�finir l'ic�ne de cette bo�te de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fen�tre principale de l'application n'est pas une bo�te de dialogue
	SetIcon(m_hIcon, TRUE);			// D�finir une grande ic�ne
	SetIcon(m_hIcon, FALSE);		// D�finir une petite ic�ne

	// TODO�: ajoutez ici une initialisation suppl�mentaire
	
	return TRUE;  // retourne TRUE, sauf si vous avez d�fini le focus sur un contr�le
}

void CNewtonCalcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 10 ms � 340 m/s : 3.4 m
	m_nTime++; // millisecondes

	// distance = 1/2gt�
	// vitesse = gt

	double fTime=((double)m_nTime)/100;
	double fH=9.81*fTime*fTime/2;
	double fV=9.81*fTime;

	CString str;
	str.Format(_T("%0.2f"), ((double)m_nTime)/100.0);
	SetDlgItemText(IDC_STATIC_TIME, str);
	SetDlgItemInt(IDC_STATIC_DISTANCE, (int)fH);
	str.Format(_T("%0.2f"), fH);
	SetDlgItemText(IDC_STATIC_DISTANCE, str);
	str.Format(_T("%0.2f"), fV);
	SetDlgItemText(IDC_STATIC_MPS, str);
	str.Format(_T("%0.2f"), fV*3.6);
	SetDlgItemText(IDC_STATIC_KPH, str);


	CDlgMain::OnTimer(nIDEvent);
}

void CNewtonCalcDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_pTimer==NULL)
	{
		m_pTimer=SetTimer(1, 10, NULL);
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
