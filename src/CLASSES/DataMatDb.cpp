// MatDbData.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "DataMatDb.h"

#ifdef WINCE
//#include "textfile.h" // pour la cr�ation � partir d'un ficheir texte
#include "CEFileFind.h"
#include "CLASSES_rc.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAlloy

IMPLEMENT_SERIAL(CAlloy, CObjNamed, 0);

CAlloy::CAlloy()
{
	m_pCat=NULL;
	m_nVersion=1;
}

CAlloy::CAlloy(CString& strName, CCat* pCat):
	CObjNamed(strName),
	m_pCat(pCat)
{
	m_nVersion=1;
}

CAlloy::~CAlloy()
{
}

// Fonctions membres CAlloy

void CAlloy::Serialize(CArchive& ar)
{
	CObjNamed::Serialize(ar);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCat

IMPLEMENT_SERIAL(CCat, CObjNamed, 0);

CCat::CCat()
{
	m_fReadOnly=FALSE;
	m_nVersion=1;
}

CCat::CCat(CString& strName, int nID):
	CObjNamed(strName),
		m_nID(nID)
{
	m_fReadOnly=FALSE;
	m_nVersion=1;
}

CCat::~CCat()
{
	DeleteContents();
}

// Fonctions membres CCat

void CCat::DeleteContents()
{
	while(Alloy_GetCount())
	{
		CAlloy* pAlloy=Alloy_RemoveHead();
		ASSERT(pAlloy!=NULL);
		delete pAlloy;
	}
}

void CCat::Serialize(CArchive& ar)
{
	CObjNamed::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_nID;
		ar << m_fReadOnly;

		ar << Alloy_GetCount();

		POSITION posAlloy = Alloy_GetHeadPosition();
		while(posAlloy)
		{
			CAlloy* pAlloy = Alloy_GetNext(posAlloy);
			ASSERT(pAlloy!=NULL);
			pAlloy->Serialize(ar);
		}
	}
	else
	{
		DeleteContents();

		ar >> m_nID;
		ar >> m_fReadOnly;

		int nCountNorm;

		ar >> nCountNorm;

		for(int i=0; i<nCountNorm; i++)
		{
			CAlloy* pAlloy = new CAlloy();
			pAlloy->Serialize(ar);
			pAlloy->m_pCat=this;
			Alloy_AddTail(pAlloy);
		}
	}
}

// CDataMatDb

IMPLEMENT_SERIAL(CDataMatDb, CData, 0);

CDataMatDb::CDataMatDb()
{
	m_nVersion=1;
	m_pCurSelCat=NULL;
	m_pCurSelAlloy=NULL;
	m_nNextID=1;
//	m_strFileExt.LoadString(CLASSES_IDS_MATFILE_EXT);
}

CDataMatDb::~CDataMatDb()
{
	CDataMatDb::DeleteContents();
}

BOOL CDataMatDb::IsEmpty() // TRUE si liste de mati�res non vide
{
	return m_listCat.IsEmpty();
}

void CDataMatDb::FileNew()
{
}

// diagnostics pour CDataMatDb

#ifdef _DEBUG
void CDataMatDb::AssertValid() const
{
	CObject::AssertValid();
}
#endif //_DEBUG


// commandes pour CDataMatDb

void CDataMatDb::DeleteContents()
{
	CData::DeleteContents();

	// vider la liste
	int nCount=Cat_GetCount();

	while(Cat_GetCount())
	{
		CCat* pCat=Cat_RemoveHead();
		ASSERT_VALID(pCat);
		delete pCat;
	}

	m_pCurSelCat=NULL;
	m_pCurSelAlloy=NULL;
	m_nNextID=1;
	m_bModified=FALSE;
	m_strComment=_T("");
//	m_strFileName=_T("");
}

// s�rialisation de CDataMatDb

void CDataMatDb::Serialize(CArchive& ar)
{
	CData::Serialize(ar);

	if (ar.IsStoring())
	{
		int nCountCat = Cat_GetCount();
		ar << nCountCat;

		POSITION posMat = Cat_GetHeadPosition();

		while(posMat)
		{
			CCat* pCat = Cat_GetNext(posMat);
			ASSERT(pCat!=NULL);
			pCat->Serialize(ar);
		}

		ar << m_nNextID;
	}
	else
	{
		// DeleteContents(); ne pas placer �a ici : sinon impossible de fusionner des fichiers

		int nCountCat;
		ar >> nCountCat;

		for(int i=0; i<nCountCat; i++)
		{
			
			CCat* pCat = new CCat;
			pCat->Serialize(ar);
			Cat_AddTail(pCat);
		}

		ar >> m_nNextID;

		m_pCurSelCat = Cat_GetHead();
	}
}

/*
void CDataMatDb::ImportTxtFile(const CString& strFileName)
{
	CTextFileRead file(strFileName);

	CString s;
	while (file.ReadLine(s)) // tant qu'il y a des lignes
	{
		// chercher le d�but d'une d�finition de mati�re
		// tant que la ligne ne contient pas [MATIERE], continuer
		if(s.Find(_T("[MATIERE]"))==-1)
			continue;

		// la ligne suivante est le nom de la cat�gorie ; ce sera celui de l'objet nomm�
		// la ligne suivante est le code de la cat�gorie

		CString strName, strID;

		file.ReadLine(strID); strID.Trim();
		file.ReadLine(strName); strName.Trim();

		// les deux lignes suivantes sont la r�sistance

		CString strResMore;
		CString strResLess;
		int nResMore;
		int nResLess;

		file.ReadLine(strResMore); strResMore.Trim();
		file.ReadLine(strResLess); strResLess.Trim();

		nResMore=_wtoi(strResMore);
		nResLess=_wtoi(strResLess);

		CString str;

		if(nResMore!=0 && nResLess!=0)
			str.Format(_T("%s %d-%d N/mm�"), strName, nResMore, nResLess);
		else
			if(nResMore==0 && nResLess!=0)
				str.Format(_T("%s < %d N/mm�"), strName, nResLess);
			else
			if(nResMore!=0 && nResLess==0)
				str.Format(_T("%s > %d N/mm�"), strName, nResMore);

		int nID=_wtoi(strID);

		CCat* pCat = new CCat(str,nID);
		pCat->m_fReadOnly=TRUE;

		// les lignes suivantes sont les noms d'alliages jusqu'au tag de fin
		while(s.Find(_T("[/MATIERE]"))==-1)
		{
			file.ReadLine(s); s.Trim();
			if(s.Find(_T("[/MATIERE]"))!=-1)
				break;
			// ajouter l'alliage � la liste des alliages
			CAlloy* pAlloy = new CAlloy(s, pCat);
			pCat->Alloy_AddTail(pAlloy);
		}
		Cat_AddTail(pCat);
	}
	
	file.Close();

	m_pCurSelCat = Cat_GetHead();
	m_pCurSelAlloy = m_pCurSelCat->Alloy_GetHead();
}

void CDataMatDb::OnFileOpenTxt()
{

	// CDocument::SaveModified()
	if(SaveModified()==FALSE)
		return;

	TCHAR	szFile[MAX_PATH] = TEXT("\0");

	OPENFILENAME		ofn;
	memset( &(ofn), 0, sizeof(ofn));
	ofn.lStructSize	= sizeof(ofn);

	CString strFilter;
	CString strTitle;
	CString strDefExt;
	strFilter.LoadString(IDS_TXTFILE_FILTER);	// "Fichier texte (*.txt)\0*.txt\0"	
	strTitle.LoadString(IDS_TXTFILE_DLGTITLE);	// "Ouvrir un fichier texte"
	strDefExt.LoadString(IDS_TXTFILE_EXT);		// "txt"
	ofn.lpstrFilter = strFilter;
	ofn.lpstrTitle = strTitle;
	ofn.lpstrDefExt = strDefExt;
	ofn.hwndOwner = AfxGetApp()->GetMainWnd()->m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;	
			

	//ofn.Flags = OFN_HIDEREADONLY; 

	// le focus n'est pas restaur� correctement, 
	// ce qui fait que le bouton ok ou X ne r�apparait
	HWND hWnd=::GetFocus();

	if(GetOpenFileName(&ofn)==IDOK)
	{
		DeleteContents();
		ImportTxtFile(ofn.lpstrFile);
//		UpdateAllViews(NULL);
		SetModifiedFlag(FALSE);
	}

	::SetFocus(hWnd);

}
*/
