// StockCalcDlg.h : fichier d'en-t�te
//

#pragma once

#include "DlgMain.h"
#include "afxwin.h"
#include "ComboEx.h"
#include "EditDecimal.h"

// Bo�te de dialogue CStockCalcDlg
class CStockCalcDlg : public CDlgMain
{
// Construction
public:
	CStockCalcDlg(CWnd* pParent = NULL);	// constructeur standard

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_STOCKCALC_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Impl�mentation
protected:
	HICON m_hIcon;
	void ImportTxtFile(const CString& strFileName);

	// Fonctions g�n�r�es de la table des messages
	virtual BOOL OnInitDialog();
//#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
//	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
//#endif
	DECLARE_MESSAGE_MAP()
public:

	double m_dVolume;

	// valeurs stock�es pour calculer sur des valeurs exactes et non celles des champs
	double m_dKg;
	double m_dEurosPerKg;
	double m_dEuros;
	double m_dDensity;

	CComboEx m_comboMat;
	CEditDecimal m_editDensity;
	CComboEx m_comboShape;
	CEditDecimal m_editKg;
	CEditDecimal m_editEurosPerKg;
	CEditDecimal m_editEuros;
	CEditDecimal m_editDim1;
	CEditDecimal m_editDim2;
	CEditDecimal m_editSection;
	//CEditDecimal m_editSection;
	CEditDecimal m_editVolume;
	CEditDecimal m_editLength;
	afx_msg void OnCbnSelchangeComboMat();
	afx_msg void OnEnChangeEditDensity();
	afx_msg void OnEnChangeEditDim();
	afx_msg void OnCbnSelchangeComboShape();
	afx_msg void OnEnChangeEditKg();
	afx_msg void OnEnChangeEditEurosPerKg();
	afx_msg void OnEnChangeEditEuros();
	afx_msg void OnEnChangeEditLength();
};

// les membres dimensions des classes d�riv�es pointent vers les 
// membres de la boite de dialogue

inline double RoundGetSection(double dDim1 /* diam�tre */, double dDim2 /* non pris en compte */) 
{ 
	return dDim1*dDim1*3.14159/4; 
}

inline double TubeGetSection(double dDim1 /* diam�tre 1*/, double dDim2 /* diam�tre 2 */) 
{ 
	if(dDim1>dDim2)
		return (dDim1*dDim1-dDim2*dDim2)*3.14159/4; 
	else
		return (dDim2*dDim2-dDim1*dDim1)*3.14159/4; 
}

inline double SquareGetSection(double dDim1 /* c�t� */, double dDim2 /* non pris en compte */) 
{ 
	return dDim1*dDim1; 
}

inline double RectangleGetSection(double dDim1 /* largeur */, double dDim2 /* hauteur */) 
{ 
	return dDim1*dDim2; 
}

inline double HexagonGetSection(double dDim1 /* largeur */, double dDim2 /* hauteur */) 
{ 
	return 2*sqrt(3.0)*dDim1*dDim1/4; 
}
