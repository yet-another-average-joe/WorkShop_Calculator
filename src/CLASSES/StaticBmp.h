#pragma once


// CBmpStatic

class CStaticBmp : public CStatic
{
	DECLARE_DYNAMIC(CStaticBmp)

public:
	CStaticBmp(BOOL bSquare=FALSE);
	virtual ~CStaticBmp();

	void SetBmp(int nID);

protected:
	int	m_nBmpID;
	BOOL m_bSquare;


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
protected:
	virtual void PreSubclassWindow();
};


