// DrillCalcDoc.h : interface de la classe CDataToolDb
//


#pragma once

#include "DataMatDb.h"

/*
	pour chaque outil, toutes les matières sont associées à la lecture,
	à la sauvegarde, seules les matières "valides" sont enregistrées
*/

/*
outil:
- nom
- map matière <-> condition de coupe

condition de coupe

pour chaque matière
- Vc min
- Vc max
- tableaux diamètre / fmin / fmax

CMap

// pour chaque outil:
//
// liste de nos de matières
//
// nom
// map CCat* -> CCut*

map n°matière / condition de coupe

condition de coupe :
Vcmin
Vcmax
diamètre - fmin - fmax
*/

#define GRID_LINES 8

// CCut
///////////////////////////////////////////////////////////////////////////////////

// version 1

class CCut : public CObject
{
public:
	CCut();
	CCut(CCut& cut);
	virtual ~CCut();

	// nVcmin = 0 ET nVcmax = 0 : équivalent à pCut vide
	int nVcmin;
	int nVcmax;
	int m_nVersion;

	// valeurs utiliséees uniquement pour forets et fraises
	// diam = 0 : équivalent à pas de définition d'avance
	double diam[GRID_LINES];
	double fmin[GRID_LINES]; // = fzmin pour les fraises
	double fmax[GRID_LINES]; // = fzmax pour les fraises

	int GetDataDim(); // retourne le nombre de lignes dans lesquelles fmin > 0

	double GetDiamMax();
	double GetDiamMin();

	BOOL IsValid() {return nVcmin>0;}
	void Clear(); // met tout à zéro

	CCut& operator = (const CCut& cut);

	virtual void Serialize(CArchive& ar);
	DECLARE_SERIAL(CCut);
};

inline double CCut::GetDiamMin()
{
	return diam[0];
}

inline double CCut::GetDiamMax()
{
	return diam[GetDataDim()-1];
}


// liste de conditions de coupe
typedef CList<CCut*, CCut*> CListCut;

// map Id de matière -> objet conditions de coupe CCut
typedef CMap<int, int, CCut*, CCut*> CMapCatCut;


// CTool
///////////////////////////////////////////////////////////////////////////////////

// version 1

class CTool : public CObjNamed
{
public:
	CTool();
	CTool(CString& strName);
	CTool(CTool& tool);
	virtual ~CTool();

	CTool& operator = (CTool& tool);

	// valeurs utiliséees uniquement pour les fraises
	int m_ae; // pénétration radiale (largeur de passe) en % du diamètre de l'outil
	int m_ap; // pénétration axiale (profondeur ou hauteur de passe) en % du diamètre de l'outil

public:
	POSITION	CatId_GetHeadPosition();
	int			CatId_GetNext(POSITION& pos);
	POSITION	CatId_AddTail(int nId);
	int			CatId_GetCount();
	int			CatId_RemoveHead();
	int			CatId_GetHead();

private:
	// liste Id matière (nécessaire puisque une map n'est pas ordonnée)
	CList<int, int> m_listCatId;
	// liste des conditions de coupe
	CListCut	m_listCut;
	// map Id de matière <-> objet conditions de coupe CCut
	CMapCatCut m_mapCatCut;

public:
	// pointeur vers la liste complète des matières
	CDataMatDb*	m_pMatDb;

private:
	BOOL m_fCatMissing; // flag indiquant que le fichier de matières a été modifié

public:

	// gestion du cas d'un fichier de matières dont une ou plusieurs matières ont
	// été supprimées après la création du fichier d'outils
	// dans ce cas, les conditions de coupe ne sont pas lues.

	void SetCatMissingFlag(BOOL fMissing) { m_fCatMissing=fMissing; }
	BOOL GetCatMissingFlag() { return m_fCatMissing; }

public:

// helpers
	POSITION	Cut_GetHeadPosition();
	CCut*		Cut_GetNext(POSITION& pos);
	POSITION	Cut_AddTail(CCut* pCut);
	int			Cut_GetCount();
	CCut*		Cut_RemoveHead();
	CCut*		Cut_GetHead();

	POSITION MapCatCut_GetStartPosition();
	void MapCatCut_GetNextAssoc(POSITION pos, int nIdCat, CCut* pCut);
	void MapCatCut_RemoveAll();
	void MapCatCut_SetAt(int nIdCat, CCut* pCut);
	CCut* MapCatCut_GetAt(int nIdCat);
	void AddCut(int nIdCat, CCut* pCut);

	virtual void Serialize(CArchive& ar);
	DECLARE_SERIAL(CTool);
};

inline POSITION CTool::CatId_GetHeadPosition()
{ 
	return m_listCatId.GetHeadPosition(); 
}

inline int CTool::CatId_GetNext(POSITION& pos)	
{ 
	return m_listCatId.GetNext(pos); 
}

inline POSITION CTool::CatId_AddTail(int nId)			
{ 
	return m_listCatId.AddTail(nId); 
}

inline int CTool::CatId_GetCount()				
{ 
	return m_listCatId.GetCount(); 
}

inline int CTool::CatId_RemoveHead()
{ 
	return m_listCatId.RemoveHead(); 
}

inline int CTool::CatId_GetHead()					
{ 
	return m_listCatId.IsEmpty() ? -1 : m_listCatId.GetHead(); 
}

inline POSITION CTool::Cut_GetHeadPosition()		
{ 
	return m_listCut.GetHeadPosition(); 
}

inline CCut* CTool::Cut_GetNext(POSITION& pos)	
{ 
	return m_listCut.GetNext(pos); 
}

inline POSITION CTool::Cut_AddTail(CCut* pCut)		
{ 
	return m_listCut.AddTail(pCut); 
}

inline int CTool::Cut_GetCount()				
{ 
	return m_listCut.GetCount(); 
}

inline CCut* CTool::Cut_RemoveHead()			
{ 
	return m_listCut.RemoveHead(); 
}

inline CCut* CTool::Cut_GetHead()				
{ 
	return m_listCut.IsEmpty() ? NULL : m_listCut.GetHead(); 
}

inline POSITION CTool::MapCatCut_GetStartPosition() 
{ 
	return m_mapCatCut.GetStartPosition(); 
}

inline void CTool::MapCatCut_GetNextAssoc(POSITION pos, int nIdCat, CCut* pCut) 
{ 
	return m_mapCatCut.GetNextAssoc(pos, nIdCat, pCut); 
}

inline void CTool::MapCatCut_RemoveAll() 
{ 
	m_mapCatCut.RemoveAll(); 
}

inline void CTool::MapCatCut_SetAt(int nIdCat, CCut* pCut) 
{ 
	m_mapCatCut.SetAt(nIdCat, pCut); 
}

inline CCut* CTool::MapCatCut_GetAt(int nIdCat) 
{ 
	return m_mapCatCut[nIdCat]; 
}

void inline CTool::AddCut(int nIdCat, CCut* pCut) 
{ 
	ASSERT(nIdCat!=NULL);
	ASSERT(pCut!=NULL);
	Cut_AddTail(pCut); 
	CatId_AddTail(nIdCat); 
	MapCatCut_SetAt(nIdCat, pCut); 
}

// mappe un Id avec une catégorie de matière

typedef CMap<int, int, CCat*, CCat*> CMapCat;

// liste des outils
typedef CNamedObList CListTool;

// CDataToolDb
///////////////////////////////////////////////////////////////////////////////////

// version 1

class CDataToolDb : public CData
{
protected: // création à partir de la sérialisation uniquement
//	DECLARE_DYNCREATE(CDataToolDb)

public:
	CDataToolDb();
	~CDataToolDb();
	virtual void DeleteContents();

// fonctions de gestion de fichiers
	BOOL LoadMaterials(CString& strDataPath) { return m_MatDb.FileRead(strDataPath); }

	// gestion du cas d'un fichier de matières dont une ou plusieurs matières ont
	// été supprimées après la création du fichier d'outils
	// dans ce cas, les conditions de coupe ne sont pas lues.

	void SetCatMissingFlag(BOOL fMissing);
	BOOL GetCatMissingFlag();
	BOOL GetMatFileName(CString& strMatFileName);
	void SetMatFileName(const CString& strMatFileName);

// helpers
	void	Tool_SetCurSel(CTool* pTool);
	CTool*	Tool_GetCurSel();

	CListTool*	Tool_GetList();
	POSITION	Tool_GetHeadPosition();
	CTool*		Tool_GetNext(POSITION& pos);
	POSITION	Tool_AddTail(CTool* pTool);
	int			Tool_GetCount();
	CTool*		Tool_RemoveHead();
	CTool*		Tool_GetHead();

	virtual BOOL IsEmpty(); // TRUE si liste d'outil non vide

	void	Cat_SetCurSel(CCat* pCat);
	CCat*	Cat_GetCurSel();
	void	Alloy_SetCurSel(CAlloy* pAlloy);
	CAlloy*	Alloy_GetCurSel();

	CListCat*	Cat_GetList();
	POSITION	Cat_GetHeadPosition();
	CCat*		Cat_GetNext(POSITION& pos);
	POSITION	Cat_AddTail(CCat* pCat);
	int			Cat_GetCount();
	CCat*		Cat_RemoveHead();
	CCat*		Cat_GetHead();

	POSITION MapCat_GetStartPosition();
	void MapCat_GetNextAssoc(POSITION pos, int nIdCat, CCat* pCat);
	void MapCat_RemoveAll();
	void MapCat_SetAt(int nCat, CCat* pCat);
	CCat* MapCat_GetAt(int nId);

	void AddCat(CCat* pCat);

	void GetMatFileComment(CString& strComment);
	void SetMatFileComment(const CString& strComment);

private:
	int m_nVersion;
	BOOL m_fCatMissing; // flag indiquant que le fichier de matières a été modifié
	CListTool	m_listTool;
	CTool*		m_pCurSelTool;

// catégories de matières
public:
	CDataMatDb	m_MatDb;
	CMapCat		m_mapCat;

public:
	virtual void Serialize(CArchive& ar);
	DECLARE_SERIAL(CDataToolDb);

// Implémentation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif
};

inline void CDataToolDb::Cat_SetCurSel(CCat* pCat)
{
#ifdef _DEBUG
	if(pCat)
		ASSERT(pCat->IsKindOf(RUNTIME_CLASS(CCat)));
#endif
	m_MatDb.Cat_SetCurSel(pCat); 
}

inline void CDataToolDb::Alloy_SetCurSel(CAlloy* pAlloy)	
{ 
#ifdef _DEBUG
	if(pAlloy)
		ASSERT(pAlloy->IsKindOf(RUNTIME_CLASS(CAlloy)));
#endif
	m_MatDb.Alloy_SetCurSel(pAlloy); 
}

inline void CDataToolDb::SetCatMissingFlag(BOOL fMissing) 
{ 
	m_fCatMissing=fMissing; 
}

inline BOOL CDataToolDb::GetCatMissingFlag() 
{ 
	return m_fCatMissing; 
}

inline void CDataToolDb::SetMatFileName(const CString& strMatFileName) 
{ 
	m_MatDb.SetFileName(strMatFileName); 
}

inline void CDataToolDb::Tool_SetCurSel(CTool* pTool) 
{ 
	m_pCurSelTool = pTool; 
}

inline CTool* CDataToolDb::Tool_GetCurSel() 
{ 
	return m_pCurSelTool; 
}

inline CListTool* CDataToolDb::Tool_GetList()				
{ 
	return &m_listTool; 
}

inline POSITION CDataToolDb::Tool_GetHeadPosition()		
{ 
	return m_listTool.GetHeadPosition(); 
}

inline CTool* CDataToolDb::Tool_GetNext(POSITION& pos)	
{ 
	return (CTool*)m_listTool.GetNext(pos); 
}

inline POSITION CDataToolDb::Tool_AddTail(CTool* pTool)	
{ 
	return m_listTool.AddTail(pTool); 
}

inline int CDataToolDb::Tool_GetCount()				
{ 
	return m_listTool.GetCount(); 
}

inline CTool* CDataToolDb::Tool_RemoveHead()			
{ 
	return (CTool*)m_listTool.RemoveHead(); 
}

inline CTool* CDataToolDb::Tool_GetHead()				
{ 
	return m_listTool.IsEmpty() ? NULL : (CTool*)m_listTool.GetHead(); 
}

inline CCat* CDataToolDb::Cat_GetCurSel()					
{ 
	return m_MatDb.Cat_GetCurSel(); 
}

inline CAlloy* CDataToolDb::Alloy_GetCurSel()				
{
	return m_MatDb.Alloy_GetCurSel();
}

inline CListCat* CDataToolDb::Cat_GetList()				
{ 
	return m_MatDb.Cat_GetList(); 
}

inline POSITION CDataToolDb::Cat_GetHeadPosition()		
{ 
	return m_MatDb.Cat_GetHeadPosition(); 
}

inline CCat* CDataToolDb::Cat_GetNext(POSITION& pos)	
{ 
	return m_MatDb.Cat_GetNext(pos); 
}

inline POSITION CDataToolDb::Cat_AddTail(CCat* pCat)		
{ 
	return m_MatDb.Cat_AddTail(pCat); 
}

inline int CDataToolDb::Cat_GetCount()				
{ 
	return m_MatDb.Cat_GetCount(); 
}

inline CCat* CDataToolDb::Cat_RemoveHead()			
{ 
	return m_MatDb.Cat_RemoveHead(); 
}

inline CCat* CDataToolDb::Cat_GetHead()				
{ 
	return m_MatDb.Cat_GetHead(); 
}

inline POSITION CDataToolDb::MapCat_GetStartPosition() 
{ 
	return m_mapCat.GetStartPosition(); 
}

inline void CDataToolDb::MapCat_GetNextAssoc(POSITION pos, int nIdCat, CCat* pCat) 
{ 
	return m_mapCat.GetNextAssoc(pos, nIdCat, pCat); 
}

inline void CDataToolDb::MapCat_RemoveAll() 
{ 
	m_mapCat.RemoveAll(); 
}

inline void CDataToolDb::MapCat_SetAt(int nCat, CCat* pCat) 
{ 
	m_mapCat.SetAt(nCat, pCat); 
}

inline CCat* CDataToolDb::MapCat_GetAt(int nId) 
{ 
	return m_mapCat[nId]; 
}

inline void CDataToolDb::AddCat(CCat* pCat) 
{ 
	Cat_AddTail(pCat); MapCat_SetAt(pCat->m_nID, pCat); 
}

inline void CDataToolDb::GetMatFileComment(CString& strComment) 
{ 
	strComment=m_MatDb.m_strComment; 
}

inline void CDataToolDb::SetMatFileComment(const CString& strComment) 
{ 
	m_MatDb.m_strComment=strComment; 
}
