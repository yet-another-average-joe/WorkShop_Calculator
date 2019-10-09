#pragma once


// CEditFileName

class CEditFileName : public CEdit
{
	DECLARE_DYNAMIC(CEditFileName)

public:
	CEditFileName();
	virtual ~CEditFileName();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


