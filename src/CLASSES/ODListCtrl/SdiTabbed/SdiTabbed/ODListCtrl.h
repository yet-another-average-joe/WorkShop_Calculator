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
	// � appeler par la fem�tre parente
	void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS);
	void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMI);

};


