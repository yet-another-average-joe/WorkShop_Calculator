#pragma once

#include "ObjNamed.h"
#include "Data.h"

//class CCat;
class CCat;
typedef CNamedObList CListAlloy;
typedef CNamedObList CListCat;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// alliage normalisé



// CAlloy
///////////////////////////////////////////////////////////////////////////////////

// version 1

class CAlloy : public CObjNamed
{
public:
	CAlloy();
	CAlloy(CString& strName, CCat* pCat);
	virtual ~CAlloy();

	CCat*	m_pCat;

	virtual void Serialize(CArchive& ar);
	DECLARE_SERIAL(CAlloy);
};

// CCat
///////////////////////////////////////////////////////////////////////////////////

// version 1

class CCat : public CObjNamed
{
private:
	CListAlloy m_listAlloy;
public:
	CCat();
	CCat(CString& strName, int nID);
	virtual ~CCat();

	virtual void DeleteContents();

	CListAlloy*		Alloy_GetList();
	POSITION		Alloy_GetHeadPosition();
	CAlloy*			Alloy_GetNext(POSITION& pos);
	POSITION		Alloy_AddTail(CAlloy* pAlloy);
	int				Alloy_GetCount();
	CAlloy*			Alloy_RemoveHead();
	CAlloy*			Alloy_GetHead();

	int m_nID; // identifiant unique
	BOOL m_fReadOnly; // interdit la modification du nom et de l'ID : pour les types Sunsteel
	virtual void Serialize(CArchive& ar);
	DECLARE_SERIAL(CCat);
};

inline CListAlloy*	CCat::Alloy_GetList()						
{ 
	return &m_listAlloy; 
}

inline POSITION CCat::Alloy_GetHeadPosition()				
{ 
	return m_listAlloy.GetHeadPosition(); 
}

inline CAlloy* CCat::Alloy_GetNext(POSITION& pos)		
{ 
	return (CAlloy*)m_listAlloy.GetNext(pos); 
}

inline POSITION CCat::Alloy_AddTail(CAlloy* pAlloy)		
{ 
	return m_listAlloy.AddTail(pAlloy); 
}

inline int CCat::Alloy_GetCount()					
{ 
	return m_listAlloy.GetCount(); 
}

inline CAlloy* CCat::Alloy_RemoveHead()					
{ 
	return (CAlloy*)m_listAlloy.RemoveHead(); 
}

inline CAlloy* CCat::Alloy_GetHead()						
{ 
	return m_listAlloy.IsEmpty() ? NULL : (CAlloy*)m_listAlloy.GetHead(); 
}

// CDataMatDb
///////////////////////////////////////////////////////////////////////////////////

// version 1

class CDataMatDb : public CData
{
public:
	CDataMatDb();
	virtual ~CDataMatDb();

	virtual void DeleteContents();

private:
	int			m_nNextID; // prochain identifiant. Incrémenté de 1 à chaque création, et stocké dans le fichier
	CListCat	m_listCat;
	CCat*		m_pCurSelCat;
	CAlloy*		m_pCurSelAlloy;

public:
	// appelée seulement au démarrage du programme, si pas de fichier sur le disque 
	virtual void FileNew();

	int GetNextID() { return m_nNextID; } 
	void IncNextID() { m_nNextID++; } // incrémente

	CListCat*	Cat_GetList();
	POSITION	Cat_GetHeadPosition();
	CCat*		Cat_GetNext(POSITION& pos);
	POSITION	Cat_AddTail(CCat* pCat);
	int			Cat_GetCount();
	CCat*		Cat_RemoveHead();
	CCat*		Cat_GetHead();

	virtual BOOL IsEmpty(); // retourne TRUE si liste de matières non vide

	void		Cat_SetCurSel(CCat* pCat);
	void		Alloy_SetCurSel(CAlloy* pAlloy);
	CCat*		Cat_GetCurSel();
	CAlloy*		Alloy_GetCurSel();

public:
	virtual void Serialize(CArchive& ar);

// Implémentation
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif
	DECLARE_SERIAL(CDataMatDb);
};

inline CListCat* CDataMatDb::Cat_GetList()
{
	return &m_listCat; 
}

inline POSITION CDataMatDb::Cat_GetHeadPosition()		
{ 
	return m_listCat.GetHeadPosition(); 
}

inline CCat* CDataMatDb::Cat_GetNext(POSITION& pos)
{ 
	return (CCat*)m_listCat.GetNext(pos); 
}

inline POSITION CDataMatDb::Cat_AddTail(CCat* pCat)
{ 
	return m_listCat.AddTail(pCat); 
}

inline int CDataMatDb::Cat_GetCount()
{ 
	return m_listCat.GetCount(); 
}

inline CCat* CDataMatDb::Cat_RemoveHead()
{ 
	return (CCat*)m_listCat.RemoveHead();
}

inline CCat* CDataMatDb::Cat_GetHead()
{ 
	return m_listCat.IsEmpty() ? NULL : (CCat*)m_listCat.GetHead(); 
}

inline void CDataMatDb::Cat_SetCurSel(CCat* pCat)
{ 
	m_pCurSelCat=pCat;
}

inline void CDataMatDb::Alloy_SetCurSel(CAlloy* pAlloy)
{ 
	m_pCurSelAlloy=pAlloy; 
}

inline CCat* CDataMatDb::Cat_GetCurSel()
{ 
	if(m_pCurSelCat==NULL)
		TRACE(_T("CDataMatDb::m_pCurSelCat = NULL\n"));
	return m_pCurSelCat; 
}

inline CAlloy* CDataMatDb::Alloy_GetCurSel()
{ 
	if(m_pCurSelAlloy==NULL)
		TRACE(_T("CDataMatDb::m_pCurSelAlloy = NULL\n"));
	return m_pCurSelAlloy; 
}
