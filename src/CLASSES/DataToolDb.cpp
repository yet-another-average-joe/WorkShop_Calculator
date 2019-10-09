// DrillCalcDoc.cpp : implémentation de la classe CDataToolDb
//

#include "stdafx.h"
#include "DataToolDb.h"

#ifdef WINCE
#include "textfile.h"
#include "CEFileFind.h"
#include "PropSheetEx.h"
#include "DlgMatFileLoad.h"
#include "CLASSES_rc.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TRACE_IMPORT
#define TRACE_IMPORT_AUTRES
#undef TRACE_READ

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CTool

IMPLEMENT_SERIAL(CTool, CObjNamed, 0);

CTool::CTool()
{
	m_nVersion=1;
	m_fCatMissing=FALSE;
	m_ae=0;
	m_ap=0;
}

CTool::CTool(CString& strName):
	CObjNamed(strName)
{
	m_nVersion=1;
}

CTool::CTool(CTool& tool):
	CObjNamed(tool.m_strName)
{
	m_nVersion=tool.m_nVersion;

	// copier pointeur m_pMatDb;
	m_pMatDb=tool.m_pMatDb;

	m_ae=tool.m_ae;
	m_ap=tool.m_ap;


	// copier m_listCatId
	POSITION posCat = tool.CatId_GetHeadPosition();

	while(posCat)
	{
		int nIdCat=tool.CatId_GetNext(posCat); 
		CCut* pCut=tool.m_mapCatCut[nIdCat];
		CCut* pCutNew=new CCut;
		ASSERT(pCutNew!=NULL);
		ASSERT_VALID(pCutNew);
		*pCutNew=*pCut;
		AddCut(nIdCat, pCutNew);
	}
}

CTool::~CTool()
{
	while(Cut_GetCount())
		delete Cut_RemoveHead();

	MapCatCut_RemoveAll();
}

CTool& CTool::operator = (CTool& tool)
{
	m_nVersion=tool.m_nVersion;
	// copier pointeur m_pMatDb;
	m_pMatDb=tool.m_pMatDb;
	m_strName=tool.m_strName;
	m_ae=tool.m_ae;
	m_ap=tool.m_ap;

	// copier m_listCatId
	POSITION posCat = tool.CatId_GetHeadPosition();

	while(posCat)
	{
		int nIdCat=tool.CatId_GetNext(posCat); 
		CCut* pCut=tool.m_mapCatCut[nIdCat];
		CCut* pCutNew=new CCut;
		*pCutNew=*pCut;
		AddCut(nIdCat, pCutNew);
	}

	return *this;
}

// Fonctions membres CTool

void CTool::Serialize(CArchive& ar)
{
	CObjNamed::Serialize(ar);

	if (ar.IsStoring())
	{
		ar<<m_ae;
		ar<<m_ap;
		// déterminer le nombre de CCut non vides
		POSITION posCut=Cut_GetHeadPosition();
		int nCount=0;
		while(posCut)
		{
			CCut* pCut=Cut_GetNext(posCut);
			ASSERT(pCut!=NULL);
			if(pCut->IsValid())
				nCount++;
		}

		// enregistrer le nombre de matières
		ar << nCount;

		POSITION posCat = CatId_GetHeadPosition();

		while(posCat)
		{
			int nCat = CatId_GetNext(posCat);
			// enregistrer l'objet CCut associé
			CCut* pCut=MapCatCut_GetAt(nCat);
			ASSERT(pCut!=NULL);
			if(pCut->IsValid())
			{
				// enregistrer l'Id de la matière
				ar << nCat;
				pCut->Serialize(ar);
			}
		}
	}
	else // lecture
	{
		ar>>m_ae;
		ar>>m_ap;
		// ajouter un nouveau pCut vide pour chaque matière
		POSITION posCat=m_pMatDb->Cat_GetHeadPosition();
		while(posCat)
		{
			// objet CCut vide
			CCat* pCat=m_pMatDb->Cat_GetNext(posCat);
			CCut* pEmptyCut=new CCut;
			AddCut(pCat->m_nID, pEmptyCut);
		}

		// lire le fichier
		int nCountCat; // nombre de catégories pour l'outil
		ar >> nCountCat;

		for(int i=0; i<nCountCat; i++)
		{
			// lire l'Id de matière
			int nCatId;
			ar >> nCatId;
			// récupérer l'objet cut correspondant à l'Id
			POSITION posCat=m_pMatDb->Cat_GetHeadPosition();

			BOOL bFound=FALSE;
			while(posCat)
			{
				CCat* pCat=m_pMatDb->Cat_GetNext(posCat);
				if(pCat->m_nID==nCatId)
				{
					CCut* pCut=MapCatCut_GetAt(nCatId);
					ASSERT(pCut!=NULL);
					pCut->Serialize(ar);
					bFound=TRUE;
				}
			}
			// si la catégorie n'a pas été trouvée
			if(!bFound)
			{
				TRACE(_T("CTool::Serialize() : Matière introuvable %d\n"), nCatId);
				// lire le CCut sans l'ajouter
				CCut dummy;
				dummy.Serialize(ar);
				SetCatMissingFlag(TRUE);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCut

IMPLEMENT_SERIAL(CCut, CObject, 0);

CCut::CCut()
{
	m_nVersion=1;
	nVcmin=0;
	nVcmax=0;

	for(int i=0; i<GRID_LINES; i++)
	{

		diam[i]=0; 
		fmin[i]=0; 
		fmax[i]=0;
	}
}

CCut::CCut(CCut& cut)
{
	m_nVersion=cut.m_nVersion;
	nVcmin=cut.nVcmin;
	nVcmax=cut.nVcmax;

	for(int i=0; i<GRID_LINES; i++)
	{

		diam[i]=cut.diam[i]; 
		fmin[i]=cut.fmin[i]; 
		fmax[i]=cut.fmax[i];
	}
}

CCut::~CCut()
{
}

void CCut::Clear()
{
	nVcmin=0;
	nVcmax=0;

	for(int i=0; i<GRID_LINES; i++)
	{

		diam[i]=0; 
		fmin[i]=0; 
		fmax[i]=0;
	}
}

CCut& CCut::operator = (const CCut& cut)
{
	m_nVersion=cut.m_nVersion;
	nVcmin=cut.nVcmin;
	nVcmax=cut.nVcmax;

	for(int i=0; i<GRID_LINES; i++)
	{

		diam[i]=cut.diam[i]; 
		fmin[i]=cut.fmin[i]; 
		fmax[i]=cut.fmax[i];
	}

	return *this;
}

// retourne le nombre de lignes contenant un diamètre
int CCut::GetDataDim()
{
	int i=0;
	while(i<GRID_LINES && diam[i]>0)
	{
		i++;
	}
	return i;
}

// Fonctions membres CCut

void CCut::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_nVersion;
		ar << nVcmin;
		ar << nVcmax;

		for(int i=0; i<8; i++)
		{
			ar << diam[i]; 
			ar << fmin[i]; 
			ar << fmax[i];
		}
	}
	else
	{
		ar >> m_nVersion;
		ar >> nVcmin;
		ar >> nVcmax;

		for(int i=0; i<8; i++)
		{
			ar >> diam[i]; 
			ar >> fmin[i]; 
			ar >> fmax[i];
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDataToolDb

IMPLEMENT_SERIAL(CDataToolDb, CData, 0);

// construction ou destruction de CDataToolDb

CDataToolDb::CDataToolDb()
{
	m_nVersion=1;
	m_pCurSelTool=NULL;
	m_strFileName=_T("");
	m_fCatMissing=FALSE;
}

CDataToolDb::~CDataToolDb()
{
	DeleteContents();
}

void CDataToolDb::DeleteContents()
{
	CData::DeleteContents();

	// destruction de la liste d'outils
	while(Tool_GetCount())
	{
		CTool* pTool=Tool_RemoveHead();
		ASSERT_VALID(pTool);
		delete pTool;
	}

	m_pCurSelTool=NULL;

	// destruction de la liste de matières
	m_MatDb.DeleteContents();
}

BOOL CDataToolDb::IsEmpty() // TRUE si liste d'outil non vide
{
	return m_listTool.IsEmpty();
}

BOOL CDataToolDb::GetMatFileName(CString& strMatFileName)
{
	CString str;
	
	if(!m_MatDb.GetFileName(str))
		return FALSE;
	else
	{
		strMatFileName=str;
		return TRUE;
	}
}

// sérialisation de CDataToolDb

void CDataToolDb::Serialize(CArchive& ar)
{
	CData::Serialize(ar);

	if (ar.IsStoring())
	{
		CString str;
		m_MatDb.GetFileName(str);
		ar << str;
		ar << Tool_GetCount();

		POSITION posTool = Tool_GetHeadPosition();

		while(posTool)
		{
			CTool* pTool = Tool_GetNext(posTool);
			ASSERT(pTool!=NULL);
			pTool->Serialize(ar);
		}
	}
	else
	{
		CString strMatFileName;
		ar >> strMatFileName;
		m_MatDb.SetFileName(strMatFileName);
		m_MatDb.SetFileExt(CLASSES_IDS_MATFILE_EXT);

		// charger les matières
		CString strAppDir;
		::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
		strAppDir.ReleaseBuffer();
		strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
		CString strMatFileExt;
		m_MatDb.GetFileExt(strMatFileExt);
		//strFileExt.LoadString(m_nIdFileExt);
		CString strFilePath = strAppDir + _T("\\") + strMatFileName + _T(".") + strMatFileExt;

		// vérifier l'existence du fichier de matières
		//CString strFilePath;
		//GetDataPath(strFilePath, strMatFileName);
		CFileFind ff;
		if (!ff.FindFile(strFilePath)) 
		{
			//CString strMsg;
			//strMsg.Format(_T("Fichier de matières introuvable : %s"), strFilePath);
			//AfxMessageBox(strMsg);
			TRACE(_T("Fichier de matières introuvable : %s\n"), strFilePath);
			//AfxThrowFileException(CFileException::fileNotFound);//,0,NULL);
			AfxThrowArchiveException(CArchiveException::genericException,strFilePath);

			return;
		}

		if(!m_MatDb.FileRead(strMatFileName))
		{
			//CString strMsg;
			//strMsg.Format(_T("Fichier de matières corrompu : %s"), strFilePath);
			//AfxMessageBox(strMsg);
			TRACE(_T("Fichier de matières corrompu : %s\n"), strFilePath);
			AfxThrowArchiveException(CArchiveException::badIndex,strFilePath);

			return;
		}

		int nCountTool;
		ar >> nCountTool;

		for(int i=0; i<nCountTool; i++)
		{
			
			CTool* pTool = new CTool;
			pTool->m_pMatDb = &m_MatDb;
			pTool->Serialize(ar);
			// vérifier la cohérence par rapport aux matières
			if(pTool->GetCatMissingFlag())
				SetCatMissingFlag(TRUE);

			Tool_AddTail(pTool);
		}

		Cat_SetCurSel(NULL);
		CTool* pTool=Tool_GetHead();

		if(pTool!=NULL)
		{
			Tool_SetCurSel(pTool);

			// sélectionner la première catégorie avec conditions de coupe

			POSITION pos=Cat_GetHeadPosition();
			while(pos)
			{
				CCat* pCat=Cat_GetNext(pos);
				if(pCat!=NULL)
				{
					CCut* pCut=pTool->MapCatCut_GetAt(pCat->m_nID);
					if(pCut!=NULL)
					{
						if(pCut->nVcmin!=0)
						{
							Cat_SetCurSel(pCat);
							break;
						}
					}
				}
			}
		}
	}
}

// diagnostics pour CDataToolDb

#ifdef _DEBUG
void CDataToolDb::AssertValid() const
{
	CObject::AssertValid();
}
#endif //_DEBUG

