#pragma once

#include "PropPageEx.h"
#include "DataToolDb.h"
#include "ComboCat.h"
#include "ComboEx.h"
#include "ScrollPad.h"

// Bo�te de dialogue CPageTCA
//
// Tool / Cat / Alloy
// g�re les interactions entre outils cat�gories et nuance
// le scrollpad permet de les s�lectionner combos ferm�es
// CHANGER LE NOM POUR CPageTWPair (page tool workpiece pair)
//
// CONVENTION :
//
// fonctions Read/Write : donn�es de la base
// fonctions Get/Set : donn�es des contr�les

class CPageTCA : public CPropPageEx
{
	DECLARE_DYNAMIC(CPageTCA)

public:
	CPageTCA(UINT nIDTemplate, CData* pData);
	virtual ~CPageTCA();

protected:
	virtual BOOL OnInitDialog();

	// lit les donn�es et les place dans les controles
	// appelle simplement UpdateControlsStyles() dans CPageTCA
	virtual void OnChangeTWPair();
	// g�re la visibilit� et l'activation des controles
	virtual void UpdateControlsStyles();
	//virtual void OnChangeEditMode()=0;

	// vide tous les champs suppl�mentaires des classes d�riv�es
	virtual void Clear()=0; 

	virtual void SetControlsPos();

	BOOL m_fNoHintCondChanged;

	virtual void FillComboTool();
	virtual void FillComboCat();
	virtual void FillComboAlloy();

	// remplit les combos et les synchronise entre elles
	// en utilisant les helpers ci-dessous
	void InitializeTCACombos();

	// reremplit les combos (indicateur d'outil / mati�re param�tr�...)
	virtual void OnChangeEditMode(); 

	// helpers

	// fontions pour les combo ; retournent l'index, ou CB_ERR si erreur
	// (uniquement interactions entre les 3 combos)
	int Combo_Tool_SetCurSel(CTool* pTool);
	int Combo_Cat_SetCurSel(CCat* pCat);
	int Combo_Alloy_SetCurSel(CAlloy* pAlloy);

	CTool* Combo_Tool_GetCurSel();
	CCat* Combo_Cat_GetCurSel();
	CAlloy* Combo_Alloy_GetCurSel();

	// fonctions pour les donn�es
	// retourne les valeurs lues dans la base
	// (� jour par rapport � leur modification)
	double	ReadDmin();
	double	ReadDmax();
	int	ReadVcmin();
	int	ReadVcmax();

	void Data_Tool_SetCurSel(CTool* pTool);
	void Data_Cat_SetCurSel(CCat* pCat);
	void Data_Alloy_SetCurSel(CAlloy* pAlloy);
	
	CCut* Data_Cut_GetCurSel();
	void Data_Cut_GetCurSel(CCut* pCut);

// handlers appel�s par UpdatePage() ; identiques aux pr�c�dentes
// mais sans mise � jour de m_pData, ni envoi de hints aux autres pages
	virtual void OnHintToolSelChanged();
	virtual void OnHintCatSelChanged();
	virtual void OnHintAlloySelChanged();

	CTool* Data_Tool_GetCurSel();
	CCat* Data_Cat_GetCurSel();
	CAlloy* Data_Alloy_GetCurSel();

	POSITION Data_Tool_GetHeadPosition();
	CTool* Data_Tool_GetNext(POSITION& pos);
	POSITION Data_Cat_GetHeadPosition();
	CCat* Data_Cat_GetNext(POSITION& posCat);

// Donn�es de bo�te de dialogue
public: // la prop sheet doit pouvoir y acc�der pour les d�sactiver
	// si pas de fichier de donn�es
	CComboEx	m_comboTool;
	CComboEx	m_comboCat;
	CStatic		m_staticAlloy;
	CComboEx	m_comboAlloy;

	// le ScrollPad de la page de calcul est redimensionn�
	// dans la page calcul, mais sa fen�tre parente est la Prop Sheet
	// afin d'�tre toujours au dessus des autres, de ne jamais �tre scroll�e,
	// mais de permettre un redimensionnement facile, et de r�agir aux touches directionnelles
	// Il faut donc capturer les messsages dans la Prop Sheet et appeler la fonction de gestion
	// le la page concern�e en capaturant WM_VSCROLL : CPageCalcBase::OnSlider()
	// impossible de le cr�er dans la PropertySheet : assertion
	// nTBCode : SB_LINEUP, SB_LINEDOWN, etc. utils� pour indiquer le sens de d�placement
	
	CScrollPad m_scrollPad;
	virtual void OnSlider(int nTBCode, UINT nPos);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCbnSelChangeTool();
	afx_msg void OnCbnSelChangeCat();
	afx_msg void OnCbnSelChangeAlloy();

	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	// pour cacher et d�sactiver le slider magique afin de ne pas perturber le fonctionnement
	// des autres pages (touches permettant de g�rer le passsage d'un controle � l'autre)

	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();

	// repositionne le slider dans le rectangle rc
	// et retourne la largeur du slider, augment�e de ses marges
	int RepositionScrollPad(const CRect& rc);
};

inline void CPageTCA::Data_Tool_SetCurSel(CTool* pTool)
{
	ASSERT(m_pData!=NULL); 
	((CDataToolDb*)m_pData)->Tool_SetCurSel(pTool);
}

inline void CPageTCA::Data_Cat_SetCurSel(CCat* pCat)
{
	ASSERT(m_pData!=NULL); 
	((CDataToolDb*)m_pData)->Cat_SetCurSel(pCat);
}

inline void CPageTCA::Data_Alloy_SetCurSel(CAlloy* pAlloy)
{
	ASSERT(m_pData!=NULL); 
	((CDataToolDb*)m_pData)->Alloy_SetCurSel(pAlloy);
}

inline CTool* CPageTCA::Combo_Tool_GetCurSel()
{
	int nCurSel=m_comboTool.GetCurSel();
	if(nCurSel==CB_ERR)
		return NULL;

	CTool* pTool=(CTool*)m_comboTool.GetItemDataPtr(nCurSel);
	return pTool;
}

inline CCat* CPageTCA::Combo_Cat_GetCurSel()
{
	int nCurSel=m_comboCat.GetCurSel();
	if(nCurSel==CB_ERR)
		return NULL;

	CCat* pCat=(CCat*)m_comboCat.GetItemDataPtr(nCurSel);
	return pCat;
}

inline CAlloy* CPageTCA::Combo_Alloy_GetCurSel()
{
	int nCurSel=m_comboAlloy.GetCurSel();
	if(nCurSel==CB_ERR)
		return NULL;
	
	CAlloy* pAlloy=(CAlloy*)m_comboAlloy.GetItemDataPtr(nCurSel);
	return pAlloy;
}

inline CTool* CPageTCA::Data_Tool_GetCurSel() 
{ 
	ASSERT(m_pData!=NULL); 
	return ((CDataToolDb*)m_pData)->Tool_GetCurSel(); 
}

inline CCat* CPageTCA::Data_Cat_GetCurSel() 
{ 
	//ASSERT(m_pData!=NULL); 
	if(m_pData==NULL)
		return NULL;
	else
		return ((CDataToolDb*)m_pData)->Cat_GetCurSel(); 
}

inline CAlloy* CPageTCA::Data_Alloy_GetCurSel() 
{ 
	ASSERT(m_pData!=NULL); 
	return ((CDataToolDb*)m_pData)->Alloy_GetCurSel(); 
}

inline POSITION CPageTCA::Data_Tool_GetHeadPosition()
{
	return ((CDataToolDb*)m_pData)->Tool_GetHeadPosition();
}

inline CTool* CPageTCA::Data_Tool_GetNext(POSITION& pos)
{
	ASSERT(m_pData!=NULL); 
	return ((CDataToolDb*)m_pData)->Tool_GetNext(pos);
}

inline POSITION CPageTCA::Data_Cat_GetHeadPosition()
{
	ASSERT(m_pData!=NULL); 
	return ((CDataToolDb*)m_pData)->Cat_GetHeadPosition();
}

inline CCat* CPageTCA::Data_Cat_GetNext(POSITION& posCat)
{
	ASSERT(m_pData!=NULL); 
	return ((CDataToolDb*)m_pData)->Cat_GetNext(posCat);
}

inline void CPageTCA::Data_Cut_GetCurSel(CCut* pCut)
{
	ASSERT(m_pData!=NULL); 
}

inline double CPageTCA::ReadDmin()
{
	CCut* pCut=Data_Cut_GetCurSel();

	if(pCut==NULL)
		return 0;

	return pCut->diam[0];
}

inline double CPageTCA::ReadDmax()
{
	CCut* pCut=Data_Cut_GetCurSel();

	if(pCut==NULL)
		return 0;

	double fDmax=0;

	int i=0;
	for(; i<GRID_LINES; i++)
	{
		double value=pCut->diam[i];
		if(value>0)
			fDmax=max(fDmax, value);// d�terminer Dmax
		else
			break;
	}
	return fDmax;
}

inline int CPageTCA::ReadVcmin()
{
	CCut* pCut=Data_Cut_GetCurSel();

	if(pCut==NULL)
		return 0;

	return pCut->nVcmin;
}

inline int CPageTCA::ReadVcmax()
{
	CCut* pCut=Data_Cut_GetCurSel();

	if(pCut==NULL)
		return 0;

	return pCut->nVcmax;
}
