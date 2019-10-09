#pragma once

// Cible de la commande CObjNamed

#define VERSION_SAVE
#define VERSION_LOAD

// version 0 : les classes d�riv�es doivent d�finir leur propre version 
class CObjNamed : public CObject
{
public:
	CObjNamed();
	CObjNamed(CString& strName);
	CObjNamed(CObjNamed* PNamedObject);
	virtual ~CObjNamed();

	CString	m_strName;
	int m_nVersion;

	virtual void Serialize(CArchive& ar);
	DECLARE_SERIAL(CObjNamed);
};

// liste d'objets nomm�s
typedef CList<CObjNamed*, CObjNamed*> CNamedObList;

