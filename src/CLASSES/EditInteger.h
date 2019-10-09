#pragma once

#include "EditEx.h"

class AFX_EXT_CLASS CEditInteger : public CEditEx
{
	DECLARE_DYNAMIC(CEditInteger)
// Construction
public:
	CEditInteger();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
public:
	virtual ~CEditInteger();

	// Generated message map functions
protected:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};

