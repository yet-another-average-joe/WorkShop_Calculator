// CEFileFind.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "CEFileFind.h"


// CCEFileFind


IMPLEMENT_DYNAMIC(CCEFileFind, CObject)


// Fonctions membres CCEFileFind


CCEFileFind::CCEFileFind()
{
	m_pFoundInfo = NULL;
	m_pNextInfo = NULL;
	m_hContext = NULL;
	m_chDirSeparator = '\\';
}

CCEFileFind::~CCEFileFind()
{
	Close();
}

void CCEFileFind::Close()
{
	if (m_pFoundInfo != NULL)
	{
		delete m_pFoundInfo;
		m_pFoundInfo = NULL;
	}

	if (m_pNextInfo != NULL)
	{
		delete m_pNextInfo;
		m_pNextInfo = NULL;
	}

	if (m_hContext != NULL)
	{
		if (m_hContext != INVALID_HANDLE_VALUE)
			CloseContext();
		m_hContext = NULL;
	}
}

void CCEFileFind::CloseContext()
{
	::FindClose(m_hContext);
	return;
}

BOOL CCEFileFind::FindFile(LPCTSTR pstrName /* = NULL */,
	DWORD dwUnused /* = 0 */)
{
	UNUSED_ALWAYS(dwUnused);
	Close();

	if (pstrName == NULL)
		pstrName = _T("*.*");
	else if (lstrlen(pstrName) >= (_countof(((WIN32_FIND_DATA*) m_pNextInfo)->cFileName)))
	{
		::SetLastError(ERROR_BAD_ARGUMENTS);
		return FALSE;		
	}
	
	m_pNextInfo = new WIN32_FIND_DATA;

	WIN32_FIND_DATA *pFindData = (WIN32_FIND_DATA *)m_pNextInfo;

	Checked::tcscpy_s(pFindData->cFileName, _countof(pFindData->cFileName), pstrName);

	m_hContext = ::FindFirstFile(pstrName, (WIN32_FIND_DATA*) m_pNextInfo);

	if (m_hContext == INVALID_HANDLE_VALUE)
	{
		DWORD dwTemp = ::GetLastError();
		Close();
		::SetLastError(dwTemp);
		return FALSE;
	}

	LPTSTR pstrRoot = m_strRoot.GetBufferSetLength(_MAX_PATH);

	// pour CFileFind
	//LPCTSTR pstr = _tfullpath(pstrRoot, pstrName, _MAX_PATH);

	// pour CCEFileFind
	CString str;
	str.Format(_T("%s\\%s"), pstrRoot, pstrName);
	LPCTSTR pstr = str;

	// passed name isn't a valid path but was found by the API
	ASSERT(pstr != NULL);
	if (pstr == NULL)
	{
		m_strRoot.ReleaseBuffer(0);
		Close();
		::SetLastError(ERROR_INVALID_NAME);
		return FALSE;
	}
	else
	{
		TCHAR strDrive[_MAX_DRIVE], strDir[_MAX_DIR];
		Checked::tsplitpath_s(pstrRoot, strDrive, _MAX_DRIVE, strDir, _MAX_DIR, NULL, 0, NULL, 0);
		Checked::tmakepath_s(pstrRoot, _MAX_PATH, strDrive, strDir, NULL, NULL);
		m_strRoot.ReleaseBuffer(-1);
	}

	return TRUE;
}

BOOL CCEFileFind::MatchesMask(DWORD dwMask) const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	if (m_pFoundInfo != NULL)
		return (!!(((LPWIN32_FIND_DATA) m_pFoundInfo)->dwFileAttributes & dwMask));
	else
		return FALSE;
}

BOOL CCEFileFind::GetLastAccessTime(FILETIME* pTimeStamp) const
{
	ASSERT(m_hContext != NULL);
	ASSERT(pTimeStamp != NULL);
	ASSERT_VALID(this);

	if (m_pFoundInfo != NULL && pTimeStamp != NULL)
	{
		*pTimeStamp = ((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastAccessTime;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CCEFileFind::GetLastWriteTime(FILETIME* pTimeStamp) const
{
	ASSERT(m_hContext != NULL);
	ASSERT(pTimeStamp != NULL);
	ASSERT_VALID(this);

	if (m_pFoundInfo != NULL && pTimeStamp != NULL)
	{
		*pTimeStamp = ((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastWriteTime;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CCEFileFind::GetCreationTime(FILETIME* pTimeStamp) const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	if (m_pFoundInfo != NULL && pTimeStamp != NULL)
	{
		*pTimeStamp = ((LPWIN32_FIND_DATA) m_pFoundInfo)->ftCreationTime;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CCEFileFind::GetLastAccessTime(CTime& refTime) const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	if (m_pFoundInfo != NULL)
	{
		if (CTime::IsValidFILETIME(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastAccessTime))
		{
			refTime = CTime(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastAccessTime);
		}
		else
		{
			refTime = CTime();
		}
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CCEFileFind::GetLastWriteTime(CTime& refTime) const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	if (m_pFoundInfo != NULL)
	{
		if (CTime::IsValidFILETIME(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastWriteTime))
		{
			refTime = CTime(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastWriteTime);
		}
		else
		{
			refTime = CTime();
		}
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CCEFileFind::GetCreationTime(CTime& refTime) const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	if (m_pFoundInfo != NULL)
	{
		if (CTime::IsValidFILETIME(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftCreationTime))
		{
			refTime = CTime(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftCreationTime);
		}
		else
		{
			refTime = CTime();
		}
		return TRUE;
	}
	else
		return FALSE;
}

// manque IsDirectory()

/*
BOOL CCEFileFind::IsDots() const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	// return TRUE if the file name is "." or ".." and
	// the file is a directory

	BOOL bResult = FALSE;
	if (m_pFoundInfo != NULL && IsDirectory())
	{
		LPWIN32_FIND_DATA pFindData = (LPWIN32_FIND_DATA) m_pFoundInfo;
		if (pFindData->cFileName[0] == '.')
		{
			if (pFindData->cFileName[1] == '\0' ||
				(pFindData->cFileName[1] == '.' &&
				 pFindData->cFileName[2] == '\0'))
			{
				bResult = TRUE;
			}
		}
	}

	return bResult;
}
*/
BOOL CCEFileFind::FindNextFile()
{
	ASSERT(m_hContext != NULL);

	if (m_hContext == NULL)
		return FALSE;
	if (m_pFoundInfo == NULL)
		m_pFoundInfo = new WIN32_FIND_DATA;

	ASSERT_VALID(this);

	void* pTemp = m_pFoundInfo;
	m_pFoundInfo = m_pNextInfo;
	m_pNextInfo = pTemp;

	return ::FindNextFile(m_hContext, (LPWIN32_FIND_DATA) m_pNextInfo);
}

CString CCEFileFind::GetFileURL() const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	CString strResult("file://");
	strResult += GetFilePath();
	return strResult;
}

CString CCEFileFind::GetRoot() const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	return m_strRoot;
}

CString CCEFileFind::GetFilePath() const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	CString strResult = m_strRoot;
	LPCTSTR pszResult;
	LPCTSTR pchLast;
	pszResult = strResult;
	pchLast = _tcsdec( pszResult, pszResult+strResult.GetLength() );
    ENSURE(pchLast!=NULL);
	if ((*pchLast != _T('\\')) && (*pchLast != _T('/')))
		strResult += m_chDirSeparator;
	strResult += GetFileName();
	return strResult;
}

CString CCEFileFind::GetFileTitle() const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	CString strFullName = GetFileName();
	CString strResult;

	Checked::tsplitpath_s(strFullName, NULL, 0, NULL, 0, 
		strResult.GetBuffer(_MAX_FNAME), _MAX_FNAME, NULL, 0);

	strResult.ReleaseBuffer();
	return strResult;
}

CString CCEFileFind::GetFileName() const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	CString ret;

	if (m_pFoundInfo != NULL)
		ret = ((LPWIN32_FIND_DATA) m_pFoundInfo)->cFileName;
	return ret;
}

ULONGLONG CCEFileFind::GetLength() const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

   ULARGE_INTEGER nFileSize;

	if (m_pFoundInfo != NULL)
   {
	  nFileSize.LowPart = ((LPWIN32_FIND_DATA) m_pFoundInfo)->nFileSizeLow;
	  nFileSize.HighPart = ((LPWIN32_FIND_DATA) m_pFoundInfo)->nFileSizeHigh;
   }
   else
   {
	  nFileSize.QuadPart = 0;
   }

   return nFileSize.QuadPart;
}

BOOL CCEFileFind::IsDots() const
{
	ASSERT(m_hContext != NULL);
	ASSERT_VALID(this);

	// return TRUE if the file name is "." or ".." and
	// the file is a directory

	BOOL bResult = FALSE;
	if (m_pFoundInfo != NULL && IsDirectory())
	{
		LPWIN32_FIND_DATA pFindData = (LPWIN32_FIND_DATA) m_pFoundInfo;
		if (pFindData->cFileName[0] == '.')
		{
			if (pFindData->cFileName[1] == '\0' ||
				(pFindData->cFileName[1] == '.' &&
				 pFindData->cFileName[2] == '\0'))
			{
				//bResult = FALSE;

			}
		}
	}

	return bResult;
}
/*
#ifdef _DEBUG
void CCEFileFind::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
	dc << "\nm_hContext = " << (void*) m_hContext;
}

void CCEFileFind::AssertValid() const
{
	// if you trip the ASSERT in the else side, you've called
	// a Get() function without having done at least one
	// FindNext() call

	if (m_hContext == NULL)
		ASSERT(m_pFoundInfo == NULL && m_pNextInfo == NULL);
	else
		ASSERT(m_pFoundInfo != NULL && m_pNextInfo != NULL);

}
#endif
*/


