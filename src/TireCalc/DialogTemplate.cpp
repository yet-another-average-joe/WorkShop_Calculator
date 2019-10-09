// DialogTemplate.cpp: implementation of the CDialogTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TireCalc.h"
#include "DialogTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//---------------------------------------------------------------------------
//
//	CDialogTemplate constructors and destructor
//
//---------------------------------------------------------------------------


// CDialogTemplate::CDialogTemplate
//
//		Default constructor
//
CDialogTemplate::CDialogTemplate()
{
	Construct();
}


// CDialogTemplate::CDialogTemplate
//
//		Populating constructor
//
CDialogTemplate::CDialogTemplate(LPCTSTR	pszCaption, 
								 DWORD		dwStyle,
								 int		x, 
								 int		y,
								 int		w,
								 int		h,
								 LPCTSTR	pszFontName,
								 WORD		wFontSize)
{
	Construct();

	Header(pszCaption, dwStyle, x, y, w, h, pszFontName, wFontSize);
}


// CDialogTemplate::~CDialogTemplate
//
//		Destructor
//
CDialogTemplate::~CDialogTemplate()
{
	delete [] m_pBuf;
}


// CDialogTemplate::Construct
//
//		Constructor workhorse
//
void CDialogTemplate::Construct()
{
	m_nMax	= 1024;
	m_pBuf	= new char[m_nMax];
	m_nPos	= sizeof(DLGTEMPLATE);

	if(m_pBuf)
		memset(m_pBuf, 0, 1024);
}


// CDialogTemplate::Header
//
//		Defines the header
//
void CDialogTemplate::Header(LPCTSTR	pszCaption, 
							 DWORD		dwStyle,
							 int		x, 
							 int		y,
							 int		w,
							 int		h,
							 LPCTSTR	pszFontName,
							 WORD		wFontSize)
{
	DLGTEMPLATE*	pDlg;

	ASSERT(IsValid());

	if(m_pBuf)
	{
		pDlg = (DLGTEMPLATE*)m_pBuf;

		if(pszFontName)
			dwStyle |= DS_SETFONT;

		pDlg->style				= dwStyle;
		pDlg->dwExtendedStyle	= 0;
		pDlg->x					= x;
		pDlg->y					= y;
		pDlg->cx				= w;
		pDlg->cy				= h;
		pDlg->cdit				= 0;

		Add(_T("\0"), 2);
		Add(_T("\0"), 2);

		Add(pszCaption);

		if(pszFontName)
		{
			Add(wFontSize);
			Add(pszFontName);
		}
	}
}


// CDialogTemplate::AddButton
//
//		Adds a button to the dialog
//
bool CDialogTemplate::AddButton(LPCTSTR	pszCaption, 
								DWORD	dwStyle, 
								DWORD	dwExStyle, 
								short	x, 
								short	y, 
								short	cx, 
								short	cy, 
								WORD	nID)
{
	DLGITEMTEMPLATE	item;

	item.style				= dwStyle;
	item.dwExtendedStyle	= dwExStyle;
	item.id					= nID;
	item.x					= x;
	item.y					= y;
	item.cx					= cx;
	item.cy					= cy;

	return AddControl(0x0080, pszCaption, item);
}


// CDialogTemplate::AddEdit
//
//		Adds an edit box to the dialog
//
bool CDialogTemplate::AddEdit(LPCTSTR	pszCaption, 
							  DWORD		dwStyle, 
							  DWORD		dwExStyle, 
							  short		x, 
							  short		y, 
							  short		cx, 
							  short		cy, 
							  WORD		nID)
{
	DLGITEMTEMPLATE	item;

	item.style				= dwStyle;
	item.dwExtendedStyle	= dwExStyle;
	item.id					= nID;
	item.x					= x;
	item.y					= y;
	item.cx					= cx;
	item.cy					= cy;

	return AddControl(0x0081, pszCaption, item);
}


// CDialogTemplate::AddStatic
//
//		Adds a static to the dialog
//
bool CDialogTemplate::AddStatic(LPCTSTR	pszCaption, 
								DWORD	dwStyle, 
								DWORD	dwExStyle, 
								short	x, 
								short	y, 
								short	cx, 
								short	cy, 
								WORD	nID)
{
	DLGITEMTEMPLATE	item;

	item.style				= dwStyle;
	item.dwExtendedStyle	= dwExStyle;
	item.id					= nID;
	item.x					= x;
	item.y					= y;
	item.cx					= cx;
	item.cy					= cy;

	return AddControl(0x0082, pszCaption, item);
}


// CDialogTemplate::AddList
//
//		Adds a list box to the dialog
//
bool CDialogTemplate::AddList(LPCTSTR	pszCaption, 
							  DWORD		dwStyle, 
							  DWORD		dwExStyle, 
							  short		x, 
							  short		y, 
							  short		cx, 
							  short		cy, 
							  WORD		nID)
{
	DLGITEMTEMPLATE	item;

	item.style				= dwStyle;
	item.dwExtendedStyle	= dwExStyle;
	item.id					= nID;
	item.x					= x;
	item.y					= y;
	item.cx					= cx;
	item.cy					= cy;

	return AddControl(0x0083, pszCaption, item);
}


// CDialogTemplate::AddScroll
//
//		Adds a static to the dialog
//
bool CDialogTemplate::AddScroll(LPCTSTR	pszCaption, 
								DWORD	dwStyle, 
								DWORD	dwExStyle, 
								short	x, 
								short	y, 
								short	cx, 
								short	cy, 
								WORD	nID)
{
	DLGITEMTEMPLATE	item;

	item.style				= dwStyle;
	item.dwExtendedStyle	= dwExStyle;
	item.id					= nID;
	item.x					= x;
	item.y					= y;
	item.cx					= cx;
	item.cy					= cy;

	return AddControl(0x0084, pszCaption, item);
}


// CDialogTemplate::AddCombo
//
//		Adds a static to the dialog
//
bool CDialogTemplate::AddCombo(LPCTSTR	pszCaption, 
							   DWORD	dwStyle, 
							   DWORD	dwExStyle, 
							   short	x, 
							   short	y, 
							   short	cx, 
							   short	cy, 
							   WORD		nID)
{
	DLGITEMTEMPLATE	item;

	item.style				= dwStyle;
	item.dwExtendedStyle	= dwExStyle;
	item.id					= nID;
	item.x					= x;
	item.y					= y;
	item.cx					= cx;
	item.cy					= cy;

	return AddControl(0x0085, pszCaption, item);
}


// CDialogTemplate::AddControl
//
//		Adds a windows standard control
//
bool CDialogTemplate::AddControl(WORD					wType,
								 LPCTSTR				pszCaption,
								 const DLGITEMTEMPLATE&	item)
{
	WORD			wPreType	= 0xFFFF,
					wDataLen	= 0;
	DLGTEMPLATE*	pDlg		= (DLGTEMPLATE*) m_pBuf;
	bool			bOk;

	ASSERT(IsValid());

	bOk =	Align(sizeof(DWORD))				&&
			Add(&item, sizeof(DLGITEMTEMPLATE))	&&
			Add(wPreType)						&&
			Add(wType)							&&
			Add(pszCaption)						&&
			Add(wDataLen);

	if(bOk)
		pDlg->cdit += 1;

	return bOk;
}


// CDialogTemplate::AddItem
//
//		Adds a non-standard control to the dialog
//
bool CDialogTemplate::AddItem(LPCTSTR					pszType, 
							  LPCTSTR					pszCaption, 
							  const DLGITEMTEMPLATE&	item)
{
	WORD			wDataLen	= 0;
	DLGTEMPLATE*	pDlg		= (DLGTEMPLATE*) m_pBuf;
	bool			bOk;

	ASSERT(IsValid());

	bOk =	Align(sizeof(DWORD))				&&
			Add(&item, sizeof(DLGITEMTEMPLATE))	&&
			Add(pszType)						&&
			Add(pszCaption)						&&
			Add(wDataLen);

	if(bOk)
		pDlg->cdit += 1;

	return bOk;
}


// CDialogTemplate::Add
//
//		Adds data to the dialog template
//
bool CDialogTemplate::Add(const void *pData, int nSize)
{
	bool	bOk;

	ASSERT(IsValid());

	bOk = Alloc(nSize);
	if(bOk)
	{
		memcpy(m_pBuf + m_nPos, pData, nSize);
		m_nPos += nSize;
	}

	return bOk;
}


// CDialogTemplate::Alloc
//
//		Check if the buffer needs to be reallocated
//
bool CDialogTemplate::Alloc(int nSize)
{
	int		nMax	= max(1024, nSize);
	bool	bOk		= false;

	if(m_nPos + nSize >= m_nMax)
	{
		char*	pNew = new char[m_nMax + nMax];

		if(pNew)
		{
			memcpy(pNew, m_pBuf, m_nMax);
			delete [] m_pBuf;
			m_pBuf = pNew;
			bOk = true;
		}
	}
	else
		bOk = true;

	return bOk;
}


// CDialogTemplate::Align
//
//		Aligns the insertion point
//
bool CDialogTemplate::Align(int nSize)
{
	int		nPad	= m_nPos % nSize;
	bool	bOk		= true;

	if(nPad)
	{
		bOk = Alloc(nPad);
		m_nPos += nPad;
	}

	return bOk;
}
