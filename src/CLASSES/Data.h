#pragma once


// Cible de la commande CData

// pour WinCE,
// donn�es avec des fonctionnalit�s calqu�es sur
// le m�me principe que Doc / View
// le "document" est m_pData de type CData
// la "vue" est une CPropSheetEx

// version 0 : les classes d�riv�es doivent d�finir la version

class CData : public CObject
{
	DECLARE_DYNCREATE(CData) // indispensable pour la s�rialisation

public:
	CData();
	virtual ~CData();

	int m_nVersion;
	CString	m_strComment;

	virtual void Serialize(CArchive& ar);   // substitu� pour le document d'E/S
	void SetModifiedFlag(BOOL fModified=TRUE);
	BOOL IsModified();
	// ne peut pas �tre virtuelle ; retourne FALSE par d�faut
	virtual BOOL IsEmpty();
	virtual void DeleteContents();

protected:
	BOOL	m_bModified;
	CString m_strFilePath; // nom complet : chemin + nom + extension

// fonctions fichiers
// int�grer la gestion du chemin complet
// et des fonctions FileRead / FileWrite sans param�tre 

	// extension
//protected:
public:
	//CString	m_strFileExt;	// extension de fichier
	//CString m_strFolder;	// dossier du fichier
public:
//	void SetFileExt(const CString& strFileExt);
//	void SetFileExt(UINT nIDFileExt); // nIDFileExt = ID de resource
//	void GetFileExt(CString& strFileExt);

	// nom sans extension
protected:
	//CString	m_strFileName;	// nom du fichier sans chemin ni extension
public:
	void SetFilePath(const CString& strFilePath) { m_strFilePath=strFilePath; }
	// retourne le nom de ficheir sans chemin ni extension
	BOOL GetFileName(CString& strFileName);
	//BOOL GetFilePath(CString& strFilePath) { strFilePath=m_strFilePath; }

public:
	// STOCKER LE NOM DE FICHIER COMPLET LORS DE LA LECTURE ET LORS DE L'ECRITURE WriteAs()

	// lit un fichier, ne change aucun attribut (nom, extension, etc.)
	// v�rifier que le nom est valide !
	virtual BOOL FileRead(const CString& strFilePath);
	// enregistre dans un fichier, ne change aucun attribut (nom, extension, etc.)
	// v�rifier que le nom est valide !
	virtual BOOL FileWrite() { return FileWrite(m_strFilePath); }
	// enregistre une copie, ne change aucun attribut (nom, extension, etc.)
	// v�rifier que le nom est valide !
	virtual BOOL FileWrite(const CString& strFilePath);

	// fonctions g�rant le fichier et g�rant l'interface
	// (dialogues) en fonction de l'�tat de la base de donn�es
protected:
// ---------------------------------------------------------------------------------------------------
// VARIABLE A PROBLEMES : 
// utilise des resources d�pendant de la plateforme

	// strFileName = nom sans chemin ni extension
	// strFilePath = chemin complet
	//void GetDataPath(CString& strFilePath, const CString strFileName);

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif
};

// retourne TRUE si au moins un fichier de mati�res
// est pr�sent dans le dossier de l'application
BOOL FindFile(UINT nIDFileExt);


inline void CData::SetModifiedFlag(BOOL fModified/*=TRUE*/)
{ 
	m_bModified = fModified; 
}

inline BOOL CData::IsModified() 
{ 
	return m_bModified; 
}

//inline void CData::SetFileName(const CString& strFileName) 
//{ 
//	m_strFileName=strFileName; 
//}
//
//inline void CData::SetFileExt(const CString& strFileExt) 
//{ 
//	m_strFileExt=strFileExt; 
//}
//
//inline void CData::SetFileExt(UINT nIDFileExt) 	
//{
//	VERIFY(m_strFileExt.LoadString(nIDFileExt));
//}
//
//inline void CData::GetFileExt(CString& strFileExt)
//{
//	strFileExt=m_strFileExt;
//}
