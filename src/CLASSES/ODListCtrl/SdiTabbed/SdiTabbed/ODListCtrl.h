#pragma once


// CODListCtrl

class CODListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CODListCtrl)

public:
	CODListCtrl();
	virtual ~CODListCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	// à appeler par la femêtre parente
	void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS);
	void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMI);

};


