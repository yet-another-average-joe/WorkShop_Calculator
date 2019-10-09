// SdiTabbedDoc.h : interface de la classe CSdiTabbedDoc
//


#pragma once

class CSdiTabbedDoc : public CDocument
{
protected: // création à partir de la sérialisation uniquement
	CSdiTabbedDoc();
	DECLARE_DYNCREATE(CSdiTabbedDoc)

// Attributs
public:

// Opérations
public:

// Substitutions
public:
	virtual BOOL OnNewDocument();

	virtual void Serialize(CArchive& ar);


// Implémentation
public:
	virtual ~CSdiTabbedDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};


