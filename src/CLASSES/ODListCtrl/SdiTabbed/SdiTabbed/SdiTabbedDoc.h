// SdiTabbedDoc.h : interface de la classe CSdiTabbedDoc
//


#pragma once

class CSdiTabbedDoc : public CDocument
{
protected: // cr�ation � partir de la s�rialisation uniquement
	CSdiTabbedDoc();
	DECLARE_DYNCREATE(CSdiTabbedDoc)

// Attributs
public:

// Op�rations
public:

// Substitutions
public:
	virtual BOOL OnNewDocument();

	virtual void Serialize(CArchive& ar);


// Impl�mentation
public:
	virtual ~CSdiTabbedDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// Fonctions g�n�r�es de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};


