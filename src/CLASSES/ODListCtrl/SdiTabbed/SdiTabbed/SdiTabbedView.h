// SdiTabbedView.h�: interface de la classe CSdiTabbedView
//


#pragma once

#include "Tab.h"

class CSdiTabbedView : public CView
{
protected: // cr�ation � partir de la s�rialisation uniquement
	CSdiTabbedView();
	DECLARE_DYNCREATE(CSdiTabbedView)

// Attributs
public:
	CSdiTabbedDoc* GetDocument() const;

	CTab* m_pSheet;

// Op�rations
public:

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitu� pour dessiner cette vue

protected:

// Impl�mentation
public:
	virtual ~CSdiTabbedView();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// Fonctions g�n�r�es de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // version de d�bogage dans SdiTabbedView.cpp
inline CSdiTabbedDoc* CSdiTabbedView::GetDocument() const
   { return reinterpret_cast<CSdiTabbedDoc*>(m_pDocument); }
#endif

