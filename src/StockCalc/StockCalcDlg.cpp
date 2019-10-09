// StockCalcDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "StockCalc.h"
#include "StockCalcDlg.h"
#include "textfile.h"
#include "CEFileFind.h"
#include "DlgMatfileMissing.h"
#include "DlgMatfileInvalid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// pour déploiement bdu fichir de données :
// StockCalc.txt|$(InputDir)|%CSIDL_PROGRAM_FILES%\WrkShpCalc|0


// Boîte de dialogue CStockCalcDlg

CStockCalcDlg::CStockCalcDlg(CWnd* pParent /*=NULL*/)
	: CDlgMain(CStockCalcDlg::IDD, FALSE, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	EnableScrollbars(TRUE);
	m_comboMat.SetFullDrop(TRUE);
	m_comboShape.SetFullDrop(TRUE);
	m_dVolume=0;
	m_dKg=0;
	m_dEurosPerKg=0;
	m_dEuros=0;
	m_dDensity=0;
}

void CStockCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgMain::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MAT, m_comboMat);
	DDX_Control(pDX, IDC_EDIT_DENSITY, m_editDensity);
	DDX_Control(pDX, IDC_COMBO_SHAPE, m_comboShape);
	DDX_Control(pDX, IDC_EDIT_KG, m_editKg);
	DDX_Control(pDX, IDC_EDIT_EUROS_PER_KG, m_editEurosPerKg);
	DDX_Control(pDX, IDC_EDIT_EUROS, m_editEuros);
	DDX_Control(pDX, IDC_EDIT_DENSITY, m_editDensity);
	DDX_Control(pDX, IDC_EDIT_DIM1, m_editDim1);
	DDX_Control(pDX, IDC_EDIT_DIM2, m_editDim2);
	DDX_Control(pDX, IDC_COMBO_SHAPE, m_comboShape);
	DDX_Control(pDX, IDC_COMBO_MAT, m_comboMat);
	//DDX_Control(pDX, IDC_EDIT_SECTION, m_editSection);
	DDX_Control(pDX, IDC_EDIT_VOLUME, m_editVolume);
	DDX_Control(pDX, IDC_EDIT_LENGTH, m_editLength);
	DDX_Control(pDX, IDC_EDIT_SECTION, m_editSection);
}

BEGIN_MESSAGE_MAP(CStockCalcDlg, CDlgMain)
//	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO_MAT, &CStockCalcDlg::OnCbnSelchangeComboMat)
	ON_CBN_SELCHANGE(IDC_COMBO_SHAPE, &CStockCalcDlg::OnCbnSelchangeComboShape)
	ON_EN_CHANGE(IDC_EDIT_KG, &CStockCalcDlg::OnEnChangeEditKg)
	ON_EN_CHANGE(IDC_EDIT_EUROS_PER_KG, &CStockCalcDlg::OnEnChangeEditEurosPerKg)
	ON_EN_CHANGE(IDC_EDIT_EUROS, &CStockCalcDlg::OnEnChangeEditEuros)
	ON_CBN_SELCHANGE(IDC_COMBO_SHAPE, &CStockCalcDlg::OnCbnSelchangeComboShape)
	ON_CBN_SELCHANGE(IDC_COMBO_MAT, &CStockCalcDlg::OnCbnSelchangeComboMat)
	ON_EN_CHANGE(IDC_EDIT_DENSITY, &CStockCalcDlg::OnEnChangeEditDensity)
	ON_EN_CHANGE(IDC_EDIT_DIM1, &CStockCalcDlg::OnEnChangeEditDim)
	ON_EN_CHANGE(IDC_EDIT_DIM2, &CStockCalcDlg::OnEnChangeEditDim)
	ON_EN_CHANGE(IDC_EDIT_LENGTH, &CStockCalcDlg::OnEnChangeEditDim)
END_MESSAGE_MAP()

// Gestionnaires de messages pour CStockCalcDlg

BOOL CStockCalcDlg::OnInitDialog()
{
	CDlgMain::OnInitDialog();

	m_editDensity.m_fSigned=FALSE;
	m_editKg.m_fSigned=FALSE;
	m_editEurosPerKg.m_fSigned=FALSE;
	m_editEuros.m_fSigned=FALSE;
	m_editDim1.m_fSigned=FALSE;
	m_editDim2.m_fSigned=FALSE;
	m_editSection.m_fSigned=FALSE;
	m_editVolume.m_fSigned=FALSE;
	m_editLength.m_fSigned=FALSE;

	m_comboShape.SetCurSel(0);

	CString strFilePath;
	::GetModuleFileName(NULL, strFilePath.GetBuffer(_MAX_PATH), _MAX_PATH);
	strFilePath.ReleaseBuffer();
	strFilePath = strFilePath.Left(strFilePath.ReverseFind('\\'));
	strFilePath += _T("\\");
	CString strFileName;
	strFileName.LoadStringW(IDS_FILE_NAME);
	strFilePath += strFileName;//_T("StockCalc.txt");

	m_comboShape.SetCurSel(0);
	OnCbnSelchangeComboShape();

	CCEFileFind ff;
	if(ff.FindFile(strFilePath))
	{
		ImportTxtFile(strFilePath);


		if(m_comboMat.GetCount()>0)
		{
			m_comboMat.SetCurSel(0);
			OnCbnSelchangeComboMat();
		}
		else
		{
			CDlgMatfileInvalid dlg;
			dlg.DoModal();
			// désactiver la combo Matières
			m_comboMat.EnableWindow(FALSE);
		}
	}
	else
	{
		CDlgMatfileMissing dlg;
		dlg.DoModal();
		// désactiver la combo Matières
		m_comboMat.EnableWindow(FALSE);
	}

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

//void CStockCalcDlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDlgMain::OnSize(nType, cx, cy);
//	//if (AfxIsDRAEnabled())
//	//{
//	//	DRA::RelayoutDialog(
//	//		AfxGetResourceHandle(), 
//	//		this->m_hWnd, 
//	//		DRA::GetDisplayMode() != DRA::Portrait ? 
//	//		MAKEINTRESOURCE(IDD_STOCKCALC_DIALOG_WIDE) : 
//	//		MAKEINTRESOURCE(IDD_STOCKCALC_DIALOG));
//	//}
//}

void CStockCalcDlg::ImportTxtFile(const CString& strFileName)
{
	CTextFileRead file(strFileName);

	CString s;
	while (file.ReadLine(s)) // tant qu'il y a des lignes
	{
		// vider les espaces en début et fin de ligne
		s.Trim();

		// ligne vide : sauter
		if(s.IsEmpty())
			continue;

		// si la ligne commence par '#', c'st un commentaire
		if(s.Find(_T("#"))==0)
			continue;

		// il doit y avoir le séparateur ";" entre libellé et valeur de masse volumique
		int nSep=s.Find(_T(";"));
		if(nSep==-1)
			continue;

		CString strText;	// libellé
		CString strVal;	// masse volumique
		int nLen=s.GetLength();

		// libellé : à gauche de ";"
		strText=s.Left(nSep);
		strText.Trim();

		// le libellé ne doit pas être vide
		if(strText.IsEmpty())
			continue;

		strVal=s.Right(nLen-nSep-1);
		strVal.Trim();

		// la valeur ne doit pas être vide
		if(strVal.IsEmpty())
			continue;

		//TRACE(_T("libellé : ---%s--- ; masse vol. : ---%s---\n"), strText, strVal);

		LPCTSTR szBuf;
		szBuf=strVal.GetBuffer();

		TCHAR* endPtr;
		double d=_tcstod(szBuf, &endPtr);
		
		// la valeur doit être valide
		if(*endPtr != _T('\0'))
			continue;
		
		ASSERT(*endPtr == _T('\0'));


		TRACE(_T("libellé : ---%s--- ; masse vol. : ---%f---\n"), strText, d);

		strVal.ReleaseBuffer();
		DWORD dwVal=(DWORD)((int)1000*d);

		// ajouter les données
		int nInsert=m_comboMat.GetCount();
		int n=m_comboMat.InsertString(nInsert, strText);
		ASSERT(n==nInsert);
		m_comboMat.SetItemData(n, dwVal);
	}
	
	file.Close();
}

void CStockCalcDlg::OnCbnSelchangeComboShape()
{
	TRACE(_T("OnCbnSelchangeComboShape()\n"));
	// vider les tous les champs, sauf densité, longueur et prix au kg
	m_dVolume=0;
	m_dKg=0;
	m_dEuros=0;
	m_editDim1.SetWindowText_NoNotify(_T(""));
	m_editDim2.SetWindowText_NoNotify(_T(""));
	m_editLength.SetWindowText_NoNotify(_T(""));
	m_editVolume.SetWindowText_NoNotify(_T(""));
	m_editKg.SetWindowText_NoNotify(_T(""));
	m_editEuros.SetWindowText_NoNotify(_T(""));
	m_editSection.SetWindowText_NoNotify(_T(""));

	int nSelShape=m_comboShape.GetCurSel();

	CString str;
	
	switch(nSelShape)
	{
	case 0: // rond
		str.LoadStringW(IDS_DIAM);
		SetDlgItemText(IDC_STATIC_DIM1, str);
		//SetDlgItemText(IDC_STATIC_DIM1, _T("Diamètre (mm) :"));
		GetDlgItem(IDC_STATIC_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DIM2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DIM2)->ShowWindow(SW_HIDE);
		break;
	case 1:	// tube
		str.LoadStringW(IDS_DIAM1);
		SetDlgItemText(IDC_STATIC_DIM1, str);
		str.LoadStringW(IDS_DIAM2);
		SetDlgItemText(IDC_STATIC_DIM2, str);
		//SetDlgItemText(IDC_STATIC_DIM1, _T("Diamètre 1 (mm) :"));
		//SetDlgItemText(IDC_STATIC_DIM2, _T("Diamètre 2 (mm) :"));
		GetDlgItem(IDC_STATIC_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DIM2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DIM2)->ShowWindow(SW_SHOW);
		break;
	case 2:	// carré
		str.LoadStringW(IDS_SIDE);
		SetDlgItemText(IDC_STATIC_DIM1, str);
		//SetDlgItemText(IDC_STATIC_DIM1, _T("Côté (mm) :"));
		GetDlgItem(IDC_STATIC_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DIM2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DIM2)->ShowWindow(SW_HIDE);
		break;
	case 3:	// rectangle
		str.LoadStringW(IDS_WIDTH);
		SetDlgItemText(IDC_STATIC_DIM1, str);
		str.LoadStringW(IDS_HEIGHT);
		SetDlgItemText(IDC_STATIC_DIM2, str);
		//SetDlgItemText(IDC_STATIC_DIM1, _T("Largeur (mm) :"));
		//SetDlgItemText(IDC_STATIC_DIM2, _T("Hauteur (mm) :"));
		GetDlgItem(IDC_STATIC_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DIM2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DIM2)->ShowWindow(SW_SHOW);
		break;
	case 4:	// hexagone
		str.LoadStringW(IDS_WIDTHFLATS);
		SetDlgItemText(IDC_STATIC_DIM1, str);
		//SetDlgItemText(IDC_STATIC_DIM1, _T("Largeur sur plats (mm) :"));
		GetDlgItem(IDC_STATIC_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DIM2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DIM1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DIM2)->ShowWindow(SW_HIDE);
		break;
	default:
		ASSERT(0);
		break;
	}
}

void CStockCalcDlg::OnCbnSelchangeComboMat()
{
	TRACE(_T("OnCbnSelchangeComboMat()\n"));
	int nSel=m_comboMat.GetCurSel();
	ASSERT(nSel!=LB_ERR);
	DWORD dwVal=m_comboMat.GetItemData(nSel);
	m_dDensity=((double)dwVal/1000.0);

	if(m_dDensity==0)
		m_editDensity.SetWindowText_NoNotify(_T(""));
	else
		m_editDensity.SetDecimalValue(m_dDensity, 3);
	
	OnEnChangeEditDim();
}

void CStockCalcDlg::OnEnChangeEditKg()
{
	TRACE(_T("OnEnChangeEditKg()\n"));
	m_dKg=0;
	m_editKg.GetDecimalValue(m_dKg);

	// calculer la masse volumique et mettre le champ à jour
	if(m_dVolume==0)
		m_editDensity.SetWindowText_NoNotify(_T(""));
	else
	{
		if(m_dKg==0)
			m_editKg.SetWindowText_NoNotify(_T(""));
		else
			m_editDensity.SetDecimalValue(m_dKg/m_dVolume, 3);
	}

	// recalculer le prix (prix/kg prioritaire)
	m_dEuros=m_dKg*m_dEurosPerKg;

	if(m_dEuros==0)
		m_editEuros.SetWindowText_NoNotify(_T(""));
	else
		m_editEuros.SetDecimalValue(m_dEuros, 3);
}

void CStockCalcDlg::OnEnChangeEditEurosPerKg()
{
	TRACE(_T("OnEnChangeEditEurosPerKg()\n"));
	m_dEurosPerKg=0;
	m_editEurosPerKg.GetDecimalValue(m_dEurosPerKg);

	m_dEuros=m_dEurosPerKg*m_dKg;

	if(m_dEuros==0)
		m_editEuros.SetWindowText_NoNotify(_T(""));
	else
		m_editEuros.SetDecimalValue(m_dEuros, 3);
}

void CStockCalcDlg::OnEnChangeEditEuros()
{
	TRACE(_T("OnEnChangeEditEuros()\n"));
	m_dEuros=0;
	m_editEuros.GetDecimalValue(m_dEuros);

	if(m_dKg==0)
	{
		m_dEurosPerKg=0; // mise à zéro arbitraire
		m_editEurosPerKg.SetWindowText_NoNotify(_T(""));
	}
	else
	{
		m_dEurosPerKg=m_dEuros/m_dKg;
		if(m_dEurosPerKg==0)
			m_editEurosPerKg.SetWindowText_NoNotify(_T(""));
		else
			m_editEurosPerKg.SetDecimalValue(m_dEurosPerKg, 3);
	}
}

void CStockCalcDlg::OnEnChangeEditDim()
{
	TRACE(_T("OnEnChangeEditDim()\n"));
	double dDim1;

	if(!m_editDim1.GetDecimalValue(dDim1))
		dDim1=0;

	double dDim2;

	if(!m_editDim2.GetDecimalValue(dDim2))
		dDim2=0;

	int nSelShape=m_comboShape.GetCurSel();

	ASSERT(nSelShape!=CB_ERR);

	double dSection=0;
	
	// calcul section
	switch(nSelShape)
	{
	case 0: // rond
		dSection=RoundGetSection(dDim1, dDim2)/100; // en cm²
		break;
	case 1:	// tube
		dSection=TubeGetSection(dDim1, dDim2)/100; // en cm²
		break;
	case 2:	// carré
		dSection=SquareGetSection(dDim1, dDim2)/100; // en cm²
		break;
	case 3:	// rectangle
		dSection=RectangleGetSection(dDim1, dDim2)/100; // en cm²
		break;
	case 4:	// hexagone
		dSection=HexagonGetSection(dDim1, dDim2)/100; // en cm²
		break;
	default:
		ASSERT(0);
		break;
	}

	if(dSection==0)
		m_editSection.SetWindowText_NoNotify(_T(""));
	else
		m_editSection.SetDecimalValue(dSection*100, 3);

	// calcul volume
	double dLength=0; // en mm
	if(m_editLength.GetDecimalValue(dLength))
	{
		m_dVolume=dSection/100*dLength/100; // section en cm², longueur en mm, volume en dm3
		if(m_dVolume==0)
			m_editVolume.SetWindowText_NoNotify(_T(""));
		else
			m_editVolume.SetDecimalValue(m_dVolume, 3);
	}
	
	// calcul masse
	m_dKg=m_dVolume*m_dDensity;
	if(m_dKg==0)
		m_editKg.SetWindowText_NoNotify(_T(""));
	else
		m_editKg.SetDecimalValue(m_dKg, 3);

	// calcul euros/kg
	m_dEuros=m_dEurosPerKg*m_dKg;
	if(m_dEuros==0)
		m_editEuros.SetWindowText_NoNotify(_T(""));
	else
		m_editEuros.SetDecimalValue(m_dEuros, 3);
}

void CStockCalcDlg::OnEnChangeEditDensity()
{
	TRACE(_T("OnEnChangeEditDensity()\n"));
	m_dDensity=0;
	m_editDensity.GetDecimalValue(m_dDensity);
	OnEnChangeEditDim();
}
