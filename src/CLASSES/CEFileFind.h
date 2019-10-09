#pragma once

// Cible de la commande CCEFileFind

#ifdef WINCE
#define CFileFind CCEFileFind
#endif

class /*AFX_EXT_CLASS*/ CCEFileFind : public CObject
{
	DECLARE_DYNAMIC(CCEFileFind)
public:
	CCEFileFind();
	virtual ~CCEFileFind();

// Attributes
public:
	ULONGLONG GetLength() const;
	virtual CString GetFileName() const;
	virtual CString GetFilePath() const;
	virtual CString GetFileTitle() const;
	virtual CString GetFileURL() const;
	virtual CString GetRoot() const;

	virtual BOOL GetLastWriteTime(FILETIME* pTimeStamp) const;
	virtual BOOL GetLastAccessTime(FILETIME* pTimeStamp) const;
	virtual BOOL GetCreationTime(FILETIME* pTimeStamp) const;
	virtual BOOL GetLastWriteTime(CTime& refTime) const;
	virtual BOOL GetLastAccessTime(CTime& refTime) const;
	virtual BOOL GetCreationTime(CTime& refTime) const;

	virtual BOOL MatchesMask(DWORD dwMask) const;
	virtual BOOL IsDots() const;

	// these aren't virtual because they all use MatchesMask(), which is
	BOOL IsReadOnly() const
		{ return MatchesMask(FILE_ATTRIBUTE_READONLY); }
	BOOL IsDirectory() const
		{ return MatchesMask(FILE_ATTRIBUTE_DIRECTORY); }
	BOOL IsCompressed() const
		{ return MatchesMask(FILE_ATTRIBUTE_COMPRESSED); }
	BOOL IsSystem() const
		{ return MatchesMask(FILE_ATTRIBUTE_SYSTEM); }
	BOOL IsHidden() const
		{ return MatchesMask(FILE_ATTRIBUTE_HIDDEN); }
	BOOL IsTemporary() const
		{ return MatchesMask(FILE_ATTRIBUTE_TEMPORARY); }
	BOOL IsNormal() const
		{ return MatchesMask(FILE_ATTRIBUTE_NORMAL); }
	BOOL IsArchived() const
		{ return MatchesMask(FILE_ATTRIBUTE_ARCHIVE); }

// Operations
	void Close();
	virtual BOOL FindFile(LPCTSTR pstrName = NULL, DWORD dwUnused = 0);
	virtual BOOL FindNextFile();

protected:
	virtual void CloseContext();

// Implementation
protected:
	void* m_pFoundInfo;
	void* m_pNextInfo;
	HANDLE m_hContext;
	CString m_strRoot;
	TCHAR m_chDirSeparator;     // not '\\' for Internet classes
};


