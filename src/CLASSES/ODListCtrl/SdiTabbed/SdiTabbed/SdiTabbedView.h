// SdiTabbedView.h : interface de la classe CSdiTabbedView
//


#pragma once

#include "Tab.h"

class CSdiTabbedView : public CView
{
protected: // création à partir de la sérialisation uniquement
	CSdiTabbedView();
	DECLARE_DYNCREATE(CSdiTabbedView)

// Attributs
public:
	CSdiTabbedDoc* GetDocument() const;

	CTab* m_pSheet;

// Opérations
public:

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitué pour dessiner cette vue

protected:

// Implémentation
public:
	virtual ~CSdiTabbedView();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // version de débogage dans SdiTabbedView.cpp
inline CSdiTabbedDoc* CSdiTabbedView::GetDocument() const
   { return reinterpret_cast<CSdiTabbedDoc*>(m_pDocument); }
#endif

