// EditFileName.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "EditFileName.h"


// CEditFileName

IMPLEMENT_DYNAMIC(CEditFileName, CEdit)

CEditFileName::CEditFileName()
{

}

CEditFileName::~CEditFileName()
{
}


BEGIN_MESSAGE_MAP(CEditFileName, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// Gestionnaires de messages de CEditFileName


void CEditFileName::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)
	{
	//case '\\': n'existe pas sous CE ?
	case '/':
	case ':':
	case '*':
	case '<':
	case '>' :
		MessageBeep(0);
		return;  
	default:
		break;
	}

	CString strFileName;
	GetWindowText(strFileName);

	// si le nom de fichier a atteint le maximum
	if(strFileName.GetLength()==_MAX_FNAME)
	{
		MessageBeep(0);
		return;  
	}

	CEdit::OnChar(nChar , nRepCnt,  nFlags);
}

