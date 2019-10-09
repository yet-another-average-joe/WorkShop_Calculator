// NamedObject.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ObjNamed.h"

#define VERSION_OBJNAMED	0
//#define VERSION_SAVE
//#define VERSION_LOAD

IMPLEMENT_SERIAL(CObjNamed, CObject, 0);

// CObjNamed

CObjNamed::CObjNamed(CString& strName)
{
	m_strName=strName;
	m_nVersion=VERSION_OBJNAMED;
}

CObjNamed::CObjNamed()
{
	m_nVersion=VERSION_OBJNAMED;
}

CObjNamed::CObjNamed(CObjNamed* pNamedObject)
{
	ASSERT(pNamedObject!=NULL);
	m_strName=pNamedObject->m_strName;
	m_nVersion=pNamedObject->m_nVersion;
}

CObjNamed::~CObjNamed()
{
}


// Fonctions membres CObjNamed

void CObjNamed::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_nVersion;
		ar << m_strName;
	}
	else
	{
		ar >> m_nVersion;
		ar >> m_strName;
	}
}
