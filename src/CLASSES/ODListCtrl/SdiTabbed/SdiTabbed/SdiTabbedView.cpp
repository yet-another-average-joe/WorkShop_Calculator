// SdiTabbedView.cpp : implémentation de la classe CSdiTabbedView
//

#include "stdafx.h"
#include "SdiTabbed.h"

#include "SdiTabbedDoc.h"
#include "SdiTabbedView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdiTabbedView

IMPLEMENT_DYNCREATE(CSdiTabbedView, CView)

BEGIN_MESSAGE_MAP(CSdiTabbedView, CView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// construction ou destruction de CSdiTabbedView

CSdiTabbedView::CSdiTabbedView()
{
	// TODO : ajoutez ici du code de construction
	m_pSheet = new CTab(_T("CCommandBar : texte"), this);
}

CSdiTabbedView::~CSdiTabbedView()
{
}

// dessin de CSdiTabbedView
void CSdiTabbedView::OnDraw(CDC* /*pDC*/)
{
	//CSdiTabbedDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);

	// TODO : ajoutez ici le code de dessin pour les données natives
}



// diagnostics pour CSdiTabbedView

#ifdef _DEBUG
void CSdiTabbedView::AssertValid() const
{
	CView::AssertValid();
}

CSdiTabbedDoc* CSdiTabbedView::GetDocument() const // la version non déboguée est en ligne
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSdiTabbedDoc)));
	return (CSdiTabbedDoc*)m_pDocument;
}
#endif //_DEBUG


// gestionnaires de messages pour CSdiTabbedView

void CSdiTabbedView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// !!! NE PAS REDIMENSIONNER LA PROPERTYSHEET !!!

//	m_pSheet->MoveWindow(0,0,cx,cy);
}

void CSdiTabbedView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_pSheet->Create(this, WS_CHILD | WS_VISIBLE /*| WS_THICKFRAME*/);
	m_pSheet->ModifyStyle(0, WS_CHILD);

	CButton *btnApply;

	btnApply = reinterpret_cast<CButton *>(m_pSheet->GetDlgItem(ID_APPLY_NOW));
	if(btnApply)
		btnApply->DestroyWindow();

	// Destroy the Help button
	CButton *btnHelp;

	btnHelp = reinterpret_cast<CButton *>(m_pSheet->GetDlgItem(IDHELP));
	if(btnHelp)
		btnHelp->DestroyWindow();


}

int CSdiTabbedView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CSdiTabbedView::OnDestroy()
{
	CView::OnDestroy();

	// TODO : ajoutez ici le code de votre gestionnaire de messages
	m_pSheet->DestroyWindow();
}
