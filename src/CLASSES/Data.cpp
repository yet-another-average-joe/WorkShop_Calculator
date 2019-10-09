// Data.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "Data.h"
#include "CEFileFind.h"

// CData

BOOL FindFile(UINT nIdFileExt)
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	CString strFileExt;
	strFileExt.LoadStringW(nIdFileExt);
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strFind = strAppDir + _T("\\*.") + strFileExt;

	CFileFind ff;

	return ff.FindFile(strFind);
}

IMPLEMENT_DYNCREATE(CData, CObject)

CData::CData()
{
	m_nVersion=0;
	m_bModified=FALSE;
	//m_strFileName=_T(""); // nom du fichier sans chemin ni extension
	//m_strFileExt=_T("");
	m_strComment=_T("");
}

CData::~CData()
{
	DeleteContents();
}

BOOL CData::IsEmpty()
{
	return FALSE;
}

void CData::DeleteContents()
{
//	SetFileName(_T(""));
	m_strFilePath=_T("");
	m_strComment=_T("");
}

#ifdef _DEBUG
void CData::AssertValid() const
{
	CObject::AssertValid();
}
#endif //_DEBUG

// Sérialisation de CData
void CData::Serialize(CArchive& ar)
{
	// afx.inl : /* CObject does not serialize anything by default */
	// CObject::Serialize(ar); // INUTILE

	if (ar.IsStoring())
	{
		ar << m_nVersion;
		ar << m_strComment;
	}
	else
	{
		ar >> m_nVersion;
		ar >> m_strComment;
	}
}

//BOOL CData::GetFileName(CString& strFileName)
//{
//	strFileName=m_strFileName;
//	if(m_strFileName.GetLength()==0)
//		return FALSE;
//	else
//		return TRUE;
//}
/*
BOOL CData::FileExist(const CString& strFileName)
{
	CString strAppDir;
	::GetModuleFileName(NULL, strAppDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strAppDir.ReleaseBuffer();
	strAppDir = strAppDir.Left(strAppDir.ReverseFind('\\'));
	CString strFind = strAppDir + _T("\\") + strFileName + _T(".") + m_strFileExt;
	CString strFileNameExt=strFileName + _T(".") + m_strFileExt;

	CFileFind ff;

	if (!ff.FindFile(strFind)) 
		return FALSE;
	
	BOOL bNext;

	do 
	{
		bNext=ff.FindNextFile();
		CString str=ff.GetFileName();
		if(strFileNameExt == str)
			return TRUE;
	} while (bNext);

	return FALSE;
}

// strFileName = nom sans chemin ni extension
// strFilePath = chemin complet
void CData::GetDataPath(CString& strFilePath, const CString strFileName)
{
	// strFilePath = strAppDir + strFileName + strFileExt

	::GetModuleFileName(NULL, strFilePath.GetBuffer(_MAX_PATH), _MAX_PATH);
	strFilePath.ReleaseBuffer();
	strFilePath = strFilePath.Left(strFilePath.ReverseFind('\\'));
	strFilePath += _T("\\");
	strFilePath += strFileName;
	strFilePath += _T(".");
	strFilePath += m_strFileExt;
}

void CData::New()
{
	if(IsModified())
		switch(AfxMessageBox(CLASSES_IDS_SAVE_MODIFIED, 
						MB_ICONEXCLAMATION | MB_YESNOCANCEL | MB_DEFBUTTON3))
		{
			case IDCANCEL:
				return;
			case IDYES:
				SaveAs();
				break;
			default:
				break;
		}

	DeleteContents();
	m_fModified=FALSE;
}

BOOL CData::FileRead(const CString& strFileName)
{
	/////////////////////////////////////////////////////////////////////////////////////
	if(IsModified())
		switch(AfxMessageBox(CLASSES_IDS_SAVE_MODIFIED, 
						MB_ICONEXCLAMATION | MB_YESNOCANCEL | MB_DEFBUTTON3))
		{
			case IDCANCEL:
				return TRUE;
			case IDYES:
				FileSave();
				break;
			default:
				break;
		}

	///////////////////////////////////////////////////////////////////////////////////////////
	DeleteContents();
	CString strFilePath;
	GetDataPath(strFilePath, strFileName);

	CRuntimeClass* pClass=GetRuntimeClass();
	CString strClassName(pClass->m_lpszClassName);
	TRACE(_T("%s::FileRead(%s)\n"), strClassName, strFilePath);

	// si le fichier n'existe pas, inutile de continuer
#ifdef _DEBUG

	CFileFind ff;

	if (!ff.FindFile(strFilePath)) 
	{
		ASSERT(0);
		return FALSE;
	}
#endif

	CFile* pFile = NULL;
	// Constructing a CFile object with this override may throw
	// a CFile exception and won't throw any other exceptions.
	// Calling CString::Format( ) may throw a CMemoryException,
	// so we have a catch block for such exceptions, too. Any
	// other exception types this function throws will be
	// routed to the calling function.

	TRY
	{
		pFile = new CFile(strFilePath, CFile::modeRead | CFile::shareDenyWrite);
	}

	CATCH( CFileException, pEx )
	{
		// Simply show an error message to the user.
		pEx->ReportError();
	}

	AND_CATCH(CMemoryException, pEx)
	{
		// We can't recover from this memory exception, so we'll
		// just terminate the app without any cleanup. Normally, 
		// an application should do everything it possibly can to
		// clean up properly and not call AfxAbort().
		AfxAbort();
	}

	END_CATCH
	// If an exception occurs in the CFile constructor,
	// the language will free the memory allocated by new
	// and will not complete the assignment to pFile.
	// Thus, our cleanup code needs to test for NULL.
	if(pFile)   
	{
		// problème : doit retourner FALSE si
		// - fichier d'outils introuvable
		// - fichier d'outils illisible
		// et le fichier ne doit pas apparaitre dans la liste
		m_fModified=FALSE;
		CArchive ar(pFile, CArchive::load);
		TRY
		{
			Serialize(ar);
		}
		CATCH(CArchiveException, pEx)
		{
			//pEx->ReportError();
			return FALSE;
		}
		END_CATCH
		ar.Close();
		delete pFile;
		m_strFileName=strFileName;
		return TRUE;
	}

	return FALSE;
}

void CData::SaveAs(const CString& strFileName)
{
	CString strFilePath;
	GetDataPath(strFilePath, strFileName);

	CFile* pFile = NULL;
	// Constructing a CFile object with this override may throw
	// a CFile exception and won't throw any other exceptions.
	// Calling CString::Format( ) may throw a CMemoryException,
	// so we have a catch block for such exceptions, too. Any
	// other exception types this function throws will be
	// routed to the calling function.

	TRY
	{
		pFile = new CFile(strFilePath, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
	}

	CATCH( CFileException, pEx )
	{
		// Simply show an error message to the user.
		pEx->ReportError();
	}

	AND_CATCH(CMemoryException, pEx)
	{
		// We can't recover from this memory exception, so we'll
		// just terminate the app without any cleanup. Normally, 
		// an application should do everything it possibly can to
		// clean up properly and not call AfxAbort().
		AfxAbort();
	}

	END_CATCH
	// If an exception occurs in the CFile constructor,
	// the language will free the memory allocated by new
	// and will not complete the assignment to pFile.
	// Thus, our cleanup code needs to test for NULL.
	if(pFile)   
	{
		CArchive ar(pFile, CArchive::store);
		Serialize(ar);
		ar.Close();
		delete pFile;
		m_strFileName=strFileName;
		SetModifiedFlag(FALSE);
	}
}

void CData::SaveCopyAs(const CString& strFileName)
{
	CString strFilePath;
	GetDataPath(strFilePath, strFileName);

	CFile* pFile = NULL;
	// Constructing a CFile object with this override may throw
	// a CFile exception and won't throw any other exceptions.
	// Calling CString::Format( ) may throw a CMemoryException,
	// so we have a catch block for such exceptions, too. Any
	// other exception types this function throws will be
	// routed to the calling function.

	TRY
	{
		pFile = new CFile(strFilePath, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
	}

	CATCH( CFileException, pEx )
	{
		// Simply show an error message to the user.
		pEx->ReportError();
	}

	AND_CATCH(CMemoryException, pEx)
	{
		// We can't recover from this memory exception, so we'll
		// just terminate the app without any cleanup. Normally, 
		// an application should do everything it possibly can to
		// clean up properly and not call AfxAbort().
		AfxAbort();
	}

	END_CATCH
	// If an exception occurs in the CFile constructor,
	// the language will free the memory allocated by new
	// and will not complete the assignment to pFile.
	// Thus, our cleanup code needs to test for NULL.
	if(pFile)   
	{
		CArchive ar(pFile, CArchive::store);
		Serialize(ar);
		ar.Close();
		delete pFile;
	}
}

void CData::FileSave()
{
	if(m_strFileName.IsEmpty())
		SaveAs(); // nom obligatoire pour fermer le dialogue Save As, donc pas de pb
	else
		SaveAs(m_strFileName);
}

void CData::Save()
{
	CString strFileName;
	if(!GetFileName(strFileName)) // si pas de nom de fichier
		SaveAs();
	else // il y a un nom de fichier, enregistrer
		FileSave();

	m_fModified=FALSE;
}

void CData::SaveAs()
{
	CDlgSave dlgSave;
	dlgSave.m_nIDTitle=CLASSES_IDS_SAVE_AS;
	CString strFileName;
	GetFileName(strFileName);
	dlgSave.m_strFileName=strFileName;
	dlgSave.m_strFileExt=m_strFileExt;
	if(dlgSave.DoModal()==IDOK)
	{
		// si le fichier existe déjà
		if(FileExist(dlgSave.m_strFileName))
		{
			if(AfxMessageBox(CLASSES_IDS_PROMPT_OVERWRITE, 
				MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2)==IDNO)
				return;
		}

		SaveAs(dlgSave.m_strFileName);
		m_fModified=FALSE;
	}
}

void CData::SaveCopyAs()
{
	// proposer un nom par défaut : copie de trucmuche
	CDlgSave dlgSave;
	dlgSave.m_nIDTitle=CLASSES_IDS_SAVE_COPY_AS;
	CString strFileName;
	GetFileName(strFileName);
	dlgSave.m_strFileName.LoadStringW(CLASSES_IDS_COPY_OF);
	dlgSave.m_strFileName+=strFileName;
	dlgSave.m_strFileExt=m_strFileExt;
	if(dlgSave.DoModal()==IDOK)
	{
		// si le fichier existe déjà
		if(FileExist(dlgSave.m_strFileName))
		{
			if(AfxMessageBox(CLASSES_IDS_PROMPT_OVERWRITE, 
				MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2)==IDNO)
				return;
		}

		SaveCopyAs(dlgSave.m_strFileName);
	}
}
*/
BOOL CData::FileWrite(const CString& strFilePath)
{
	CFile* pFile = NULL;
	// Constructing a CFile object with this override may throw
	// a CFile exception and won't throw any other exceptions.
	// Calling CString::Format( ) may throw a CMemoryException,
	// so we have a catch block for such exceptions, too. Any
	// other exception types this function throws will be
	// routed to the calling function.

	TRY
	{
		pFile = new CFile(strFilePath, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
	}

	CATCH( CFileException, pEx )
	{
		// Simply show an error message to the user.
		pEx->ReportError();
	}

	AND_CATCH(CMemoryException, pEx)
	{
		// We can't recover from this memory exception, so we'll
		// just terminate the app without any cleanup. Normally, 
		// an application should do everything it possibly can to
		// clean up properly and not call AfxAbort().
		AfxAbort();
		return FALSE;
	}

	END_CATCH
	// If an exception occurs in the CFile constructor,
	// the language will free the memory allocated by new
	// and will not complete the assignment to pFile.
	// Thus, our cleanup code needs to test for NULL.
	if(pFile)   
	{
		CArchive ar(pFile, CArchive::store);
		Serialize(ar);
		ar.Close();
		delete pFile;
		return TRUE;
	}

	return FALSE;
}

BOOL CData::FileRead(const CString& strFilePath)
{
	DeleteContents(); // efface m_strFilePath

	CRuntimeClass* pClass=GetRuntimeClass();
	CString strClassName(pClass->m_lpszClassName);
	TRACE(_T("%s::FileRead(%s)\n"), strClassName, strFilePath);

	// si le fichier n'existe pas, inutile de continuer
#ifdef _DEBUG

	CFileFind ff;

	if (!ff.FindFile(strFilePath)) 
	{
		ASSERT(0);
		return FALSE;
	}
#endif

	CFile* pFile = NULL;
	// Constructing a CFile object with this override may throw
	// a CFile exception and won't throw any other exceptions.
	// Calling CString::Format( ) may throw a CMemoryException,
	// so we have a catch block for such exceptions, too. Any
	// other exception types this function throws will be
	// routed to the calling function.

	TRY
	{
		pFile = new CFile(strFilePath, CFile::modeRead | CFile::shareDenyWrite);
	}

	CATCH( CFileException, pEx )
	{
		// Simply show an error message to the user.
		pEx->ReportError();
	}

	AND_CATCH(CMemoryException, pEx)
	{
		// We can't recover from this memory exception, so we'll
		// just terminate the app without any cleanup. Normally, 
		// an application should do everything it possibly can to
		// clean up properly and not call AfxAbort().
		AfxAbort();
	}

	END_CATCH
	// If an exception occurs in the CFile constructor,
	// the language will free the memory allocated by new
	// and will not complete the assignment to pFile.
	// Thus, our cleanup code needs to test for NULL.
	if(pFile)   
	{
		// problème : doit retourner FALSE si
		// - fichier d'outils introuvable
		// - fichier d'outils illisible
		// et le fichier ne doit pas apparaitre dans la liste
		m_bModified=FALSE;
		CArchive ar(pFile, CArchive::load);
		TRY
		{
			Serialize(ar);
		}
		CATCH(CArchiveException, pEx)
		{
			//pEx->ReportError();
			return FALSE;
		}
		END_CATCH
		ar.Close();
		delete pFile;
		m_strFilePath=strFilePath;
		return TRUE;
	}

	return FALSE;
}

BOOL CData::GetFileName(CString& strFileName)
{
	strFileName = m_strFilePath.Left(m_strFilePath.ReverseFind('.'));
	strFileName = strFileName.Right(strFileName.GetLength()-1-strFileName.ReverseFind('\\'));
	return TRUE;
}
