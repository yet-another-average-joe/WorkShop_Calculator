// SheetTapCalc.h : fichier d'en-t�te
//

#pragma once

#include "PropSheetEx.h"
#include "PageToolFile.h"
#include "PageTool.h"

class CPageCondBase;
class CPageCalcBase;


// CSheetCutCalc

class CSheetCutCalc : public CPropSheetEx
{
	DECLARE_DYNAMIC(CSheetCutCalc)

public:
	void LoadData(const CString& strPath);

	CSheetCutCalc(UINT m_nIdFileExt, UINT iSelectPage = 0);
	virtual ~CSheetCutCalc();

	virtual CPageCondBase* CreatePageCond(CData* pData)=0;
	virtual CPageCalcBase* CreatePageCalc(CData* pData)=0;
	virtual CPropPageEx* CreatePageMemento(CData* pData)=0;

	// liste des fichiers valides (sans extension)
	CStringList m_listToolFileName;

	void ListValidToolFiles();
protected:

	// classes cr�es dans le ctor de CPropSheetEx
	CPageToolFile*			m_pPageToolFile;
	CPageTool*				m_pPageTool;

	// pages devant �tre cr��es dnas le ctor de la classe d�riv�e
	CPageCondBase*			m_pPageCond;
	CPageCalcBase*			m_pPageCalc;
	CPropPageEx*			m_pPageMemento;

	virtual void OnFileNew();
	virtual void OnFileSave();
	virtual void OnFileSaveAs();
	virtual void OnFileSaveCopyAs();

	CString m_strPageToolFileClassName;
	CString m_strPageToolClassName;
	CString m_strPageCondClassName;
	CString m_strPageCalcClassName;
	CString m_strPageMementoClassName;

	// extension du fichier d'outils : doit �ytre initialis� 
	// dans le fichier de la classe d�riv�e, 
	// pour �tre renseign� avant appel de CSheetCutCalc()
	UINT m_nIdFileExt; 

	DECLARE_MESSAGE_MAP()

	// le slider de la page de calcul est cr�� dans la page calcul, est redimansionn�e
	// dans la page calcul, mais sa fen�tre parente est la PropSheet
	// afin d'�tre toujours au dessus des autres, mais de permettre un redimensionnement facile
	// il faut donc capturer ses messsages ici
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

