// SdiTabbedDoc.cpp : impl�mentation de la classe CSdiTabbedDoc
//

#include "stdafx.h"
#include "SdiTabbed.h"

#include "SdiTabbedDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdiTabbedDoc

IMPLEMENT_DYNCREATE(CSdiTabbedDoc, CDocument)

BEGIN_MESSAGE_MAP(CSdiTabbedDoc, CDocument)
END_MESSAGE_MAP()

// construction ou destruction de CSdiTabbedDoc

CSdiTabbedDoc::CSdiTabbedDoc()
{
	// TODO�: ajoutez ici le code d'une construction unique

}

CSdiTabbedDoc::~CSdiTabbedDoc()
{
}

BOOL CSdiTabbedDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO�: ajoutez ici le code de r�initialisation
	// (Les documents SDI r�utiliseront ce document)

	return TRUE;
}

// s�rialisation de CSdiTabbedDoc


void CSdiTabbedDoc::Serialize(CArchive& ar)
{
	(ar);
}



// diagnostics pour CSdiTabbedDoc

#ifdef _DEBUG
void CSdiTabbedDoc::AssertValid() const
{
	CDocument::AssertValid();
}
#endif //_DEBUG


// commandes pour CSdiTabbedDoc

