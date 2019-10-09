// TireCalcDlg.h : fichier d'en-t�te
//

#pragma once

#include "PropPageEx.h"
#include "EditDecimal.h"
#include "ComboDecimal.h"

#include "PageDimFlotation.h"
#include "PageDimMetric.h"
#include "PageDimMetric80.h"
#include "PageDimMillimetric.h"
#include "PageDimNumeric.h"
#include "afxwin.h"

#define NORM_METRIC			0
#define NORM_METRIC80		1
#define NORM_MILLIMETRIC	2
#define NORM_NUMERIC		3
#define NORM_FLOT			4


// Bo�te de dialogue CPageDim
class CPageDim : public CPropPageEx
{
// Construction
public:
	CPageDim();	// constructeur standard

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_PAGE_DIM };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

// Impl�mentation
protected:
	CPageDimFlotation		m_pageFlotation;
	CPageDimMetric			m_pageMetric;
	CPageDimMetric80		m_pageMetric80;
	CPageDimMillimetric		m_pageMillimetric;
	CPageDimNumeric			m_pageNumeric;

	CStringArray	m_strArrayNorm;

	CComboEx		m_comboNorm;

	// Fonctions g�n�r�es de la table des messages
	virtual BOOL OnInitDialog();
//#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
//	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
//#endif

	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeComboNorm();
public:
	CStatic m_staticPlaceHolder;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

