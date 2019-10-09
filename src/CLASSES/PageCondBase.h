#pragma once

#include "PropPageEx.h"
#include "EditDecimal.h"
#include "DataToolDb.h"
#include "PageTCA.h"
#include "BtnIcon.h"

// Boîte de dialogue CPageCondBase

// outil catégorie et nuance sont gérées par CpageTCA
//
// cette classe ajoute la gestion de la Vc (valeurs min et max)
//
//	CEditDecimal	m_editVcmin;
//	CEditDecimal	m_editVcmax;
//
// BOUTONS DELETE/COPY/PASTE NON GERES, A VOIR + TAR
// AVEC VALIDATION DES DONNEES AFFICHEES DANS LES CONTROLES
// TOUTES LES FONCTIONS DES BOUTONS SONT COMMENTEES
// ET ILS SONT CAHES + DESACTIVES DANS LA RESOURCE

class CPageCondBase : public CPageTCA
{
	DECLARE_DYNAMIC(CPageCondBase)

public:
	CPageCondBase(UINT nIDTemplate, CData* pData);
	virtual ~CPageCondBase();

	virtual void OnSlider(int nTBCode, UINT nPos);

protected:
	virtual void SetControlsPos();

	CCut*	m_pClipboard;

	// actualise les affichages des données
	virtual void OnChangeTWPair();
	// actualise la visibilité des controles
	virtual void UpdateControlsStyles();

	// helpers lisant et écrivant dnas les edits
	void ClearVcmin()			{ m_editVcmin.SetWindowText_NoNotify(_T("")); }
	void ClearVcmax()			{ m_editVcmax.SetWindowText_NoNotify(_T("")); }
	int GetVcmin()				{ double Vc=0; m_editVcmin.GetDecimalValue(Vc); return (int)Vc; }
	int GetVcmax()				{ double Vc=0; m_editVcmax.GetDecimalValue(Vc);	return (int)Vc; }
	void SetVcmin(int value);
	void SetVcmax(int value);
	int ReadVcmin();
	int ReadVcmax();
	BOOL WriteVcmin(int value);
	BOOL WriteVcmax(int value);


// Données de boîte de dialogue

	DECLARE_MESSAGE_MAP()

	virtual void Clear(); // appelée pour vider les champs

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	CStatic			m_staticA0;
	CEditDecimal	m_editVcmin;
	CEditDecimal	m_editVcmax;
	CStatic			m_staticVc;
//	CBtnIcon		m_btnDel;
//	CBtnIcon		m_btnCopy;
//	CBtnIcon		m_btnPaste;

	virtual BOOL OnInitDialog();

//	afx_msg void OnBnClickedDel();
//	afx_msg void OnBnClickedCopy();
//	afx_msg void OnBnClickedPaste();
	
	afx_msg void OnEnChangeVcmin();
	afx_msg void OnEnChangeVcmax();
	
	afx_msg void OnDestroy();
};

// pour la saisie clavier : texte sélectionné
inline void CPageCondBase::SetVcmin(int value)
{
	if(value>0)
	{
		m_editVcmin.SetFixedValue(value, 0);
		m_editVcmin.SetSel(0, -1);
	}
	else
		ClearVcmin();
}

// pour la saisie clavier : texte sélectionné
inline void CPageCondBase::SetVcmax(int value)
{ 
	if(value>0)
	{
		m_editVcmax.SetFixedValue(value, 0); 
		m_editVcmax.SetSel(0, -1);
	}
	else
		ClearVcmax();
}

inline int CPageCondBase::ReadVcmin()
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return 0;
	else
		return pCut->nVcmin;
}

inline int CPageCondBase::ReadVcmax()
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return 0;
	else
		return pCut->nVcmax;
}

inline BOOL CPageCondBase::WriteVcmin(int value)
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return FALSE;
	else
		pCut->nVcmin=value;

	return TRUE;
}

inline BOOL CPageCondBase::WriteVcmax(int value)
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return FALSE;
	else
		pCut->nVcmax=value;

	return TRUE;
}
