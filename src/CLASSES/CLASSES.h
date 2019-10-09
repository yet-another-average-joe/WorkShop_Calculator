
#pragma once

// active ou d�sactive le bouton "WrkShpCalc" de la barre de menu
// selon que le programme WrkShpCalc.exe est pr�sent ou non

#define WRKSHPCALC_BTN_DISABLED	0	// bouton gris�
#define WRKSHPCALC_BTN_ENABLED	1	// bouton activ�
#define WRKSHPCALC_BTN_AUTO		2	// automatique : cherche WrkShpCalc.exe

void EnableWrkShpCalcBtn(HWND hWnd, int bEnable=WRKSHPCALC_BTN_AUTO);

// calcul des dumensions d'un dialogue � partir du template

BOOL CalcDialogSize(CSize& size, UINT nIdTemplate);

// retourne TRUE si WinCE 2003 v. 4.20 (c.a.d. avant 2003 SE)

BOOL IsOldCE2003();

double interlagrange(double* diam, double* feed, int n, double val);
double interlin(double* diam, double* feed, int n, double val);

#define INTERPOL interlin
/*
// change le texte d'une classe d�riv�e de CEdit en emp�chant le traitement de EN_CHANGE
// dans la message map de la fen�tre parente
// accepte un pointeur NULL -> _T("")

#define DECLARE_SETWINDOWTEXT_NOMAP \
	void SetWindowText_NoMap(LPCTSTR pszText);

//#define IMPLEMENT_SETWINDOWTEXT_NOMAP(classname) \
//void classname::SetWindowText_NoMap(LPCTSTR pszText)							\
//{																				\
//	if(pszText==NULL)															\
//		SetWindowText(_T(""));													\
//	else																		\
//		SetWindowText(pszText);													\
//	TRACE(_T("SetWindowText_NoMap\n"));											\
//}					


#define IMPLEMENT_SETWINDOWTEXT_NOMAP(classname) \
void classname::SetWindowText_NoMap(LPCTSTR pszText)							\
{																				\
	CWnd* pParent=GetParent();													\
	ASSERT_VALID(pParent);														\
	HWND hWndParent=pParent->m_hWnd;											\
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();						\
	HWND hWndOldLockout = pThreadState->m_hLockoutNotifyWindow;					\
	ASSERT(hWndOldLockout != hWndParent);										\
	pThreadState->m_hLockoutNotifyWindow = hWndParent;							\
	if(pszText==NULL)															\
		SetWindowText(_T(""));													\
	else																		\
		SetWindowText(pszText);													\
	TRACE(_T("SetWindowText_NoMap\n"));											\
	pThreadState->m_hLockoutNotifyWindow = hWndOldLockout;						\
}					

#define BEGIN_NO_EN_CHANGE														\
	CWnd* ____pParent=GetParent();												\
	ASSERT_VALID(____pParent);													\
	HWND ____hWndParent=____pParent->m_hWnd;									\
	_AFX_THREAD_STATE* ____pThreadState = AfxGetThreadState();					\
	HWND ____hWndOldLockout = ____pThreadState->m_hLockoutNotifyWindow;			\
	ASSERT(____hWndOldLockout != ____hWndParent);								\
	____pThreadState->m_hLockoutNotifyWindow = ____hWndParent;					


#define END_NO_EN_CHANGE														\
	____pThreadState->m_hLockoutNotifyWindow = ____hWndOldLockout;				
*/