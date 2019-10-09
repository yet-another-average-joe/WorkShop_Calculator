#pragma once


// CScrollPad

class CScrollPad : public CStatic
{
	DECLARE_DYNAMIC(CScrollPad)

public:
	CScrollPad();
	virtual ~CScrollPad();
	// "sensibilité" : nb de pixels de déplacement entrainant
	// l'envoi de messages WM_VSCROLL ; 10px par défaut
	int m_nSensitivity;

private:
	int m_dy;
	CPoint m_pt;
	CBrush m_br;
	CBrush m_brHilight;
	bool SetThumb(const CPoint& pt);
	void PostMessageToParent();
	bool m_bDragging;
	bool m_bDragChanged;

	void PaintGradient(CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


