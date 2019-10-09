#pragma once

#include "EditDecimal.h"
#include "PageCondBase.h"

// classe de base pour conditions de coupe en
// - perçage : utilisable telle quelle (juste dériver une classe)
// - fraisage  :ajouter ap et ae

// Boîte de dialogue CPageCondBase2

class CPageCondBase2 : public CPageCondBase
{
	DECLARE_DYNAMIC(CPageCondBase2)

public:
	CPageCondBase2(UINT nIDTemplate, CData* pData);
	virtual ~CPageCondBase2();

protected:

	//virtual void UpdatePage(LPARAM lHint=0); // la classe parente s'en occupe
	virtual void Clear();

	// helpers
	void SetD(int i, double value);
	void SetFmin(int i, double value);
	void SetFmax(int i, double value);

	// inutile
	//double GetD(int i)	{ double val=0; m_editD[i].GetDecimalValue(val); return val; }
	//double GetFmin(int i)	{ double val=0; m_editFmin[i].GetDecimalValue(val); return val; }
	//double GetFmax(int i)	{ double val=0; m_editFmax[i].GetDecimalValue(val); return val; }
	double GetDlgItemValue(UINT nID); // retourne la valeur d'un edit (pour D, fmin ou fmax)

	void ClearD(int i)		{ m_editD[i].SetWindowText_NoNotify(_T("")); }
	void ClearFmin(int i)	{ m_editFmin[i].SetWindowText_NoNotify(_T("")); }
	void ClearFmax(int i)	{ m_editFmax[i].SetWindowText_NoNotify(_T("")); }

	double ReadD(int i);
	double ReadFmin(int i);
	double ReadFmax(int i);

	BOOL WriteD(int i, double value);
	BOOL WriteFmin(int i, double value);
	BOOL WriteFmax(int i, double value);

	// helper : passe tous les controles concernés en mode édition ou mode lecture
	// à redéfinir dans les classes dérivées
	virtual void UpdateControlsStyles(); // met à jour les attributs des controles

protected:
	void PositionFeedsGrid();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnEnChangeEditD(UINT nID);
	afx_msg void OnEnChangeEditFmin(UINT nID);
	afx_msg void OnEnChangeEditFmax(UINT nID);

// fonction appelée en cas de changement de couple outil / matière (Tool Workpiece pair)
// met à jour l'affichage des conditions de coupe
	virtual void OnChangeTWPair();// { CPageCondBase::OnChangeTWPair(); UpdateDisplayF(); }; // Tool Workpiece Pair

	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	CStatic			m_staticA[GRID_LINES];
	CEditDecimal	m_editD[GRID_LINES];
	CEditDecimal	m_editFmin[GRID_LINES];
	CEditDecimal	m_editFmax[GRID_LINES];
	CStatic			m_staticDiam;
	CStatic			m_staticFeed;
};

inline void CPageCondBase2::SetD(int i, double value)
{
	if(value>0)
		m_editD[i].SetFixedValue(value, 1);
	else
		ClearD(i);
}

inline void CPageCondBase2::SetFmin(int i, double value)
{
	if(value>0)
		m_editFmin[i].SetFixedValue(value, 3);
	else
		ClearFmin(i);
}

inline void CPageCondBase2::SetFmax(int i, double value)
{
	if(value>0)
		m_editFmax[i].SetDecimalValue(value, 3);
	else
		ClearFmax(i);
}

inline double CPageCondBase2::ReadD(int i)
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return 0;
	else
		return pCut->diam[i];
}

inline double CPageCondBase2::ReadFmin(int i)
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return 0;
	else
		return pCut->fmin[i];
}

inline double CPageCondBase2::ReadFmax(int i)
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return 0;
	else
		return pCut->fmax[i];
}

inline double CPageCondBase2::GetDlgItemValue(UINT nID)
{
	CEditDecimal* pEdit=(CEditDecimal*)GetDlgItem(nID);
	double val=0;
	pEdit->GetDecimalValue(val);
	return val;
}

inline BOOL CPageCondBase2::WriteD(int i, double value)
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return FALSE;
	else
		pCut->diam[i]=value;

	return TRUE;
}

inline BOOL CPageCondBase2::WriteFmin(int i, double value)
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return FALSE;
	else
		pCut->fmin[i]=value;

	return TRUE;
}

inline BOOL CPageCondBase2::WriteFmax(int i, double value)
{
	CCut* pCut=Data_Cut_GetCurSel();
	
	if(pCut==NULL)
		return FALSE;
	else
		pCut->fmax[i]=value;

	return TRUE;
}







