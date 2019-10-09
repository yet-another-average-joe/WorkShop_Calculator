

#include "stdafx.h"
#include "CLASSES.h"
#include "CEFileFind.h"
#include "CLASSES_rc.h"


BOOL CalcDialogSize(HWND hWnd, CSize& size, UINT nIdTemplate)
{
	HINSTANCE hInst=::AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource(static_cast<HMODULE>(hInst), MAKEINTRESOURCE(nIdTemplate), RT_DIALOG);
	if(hRsrc == NULL) 
		return FALSE;

	HGLOBAL hGlobal = ::LoadResource(static_cast<HMODULE>(hInst), hRsrc);
	if(hGlobal == NULL)
		return FALSE;

	LPBYTE lpData = reinterpret_cast<LPBYTE>(::LockResource(hGlobal));
	if(lpData == NULL)
		return FALSE;
	
	LPDLGTEMPLATE lpTemplate = reinterpret_cast<LPDLGTEMPLATE>(lpData);

	CRect r;
	r.left=lpTemplate->x;;
	r.right=lpTemplate->cx;
	r.top=lpTemplate->y;;
	r.bottom=lpTemplate->cy;
		
	::MapDialogRect(hWnd, &r);

	size.cx=r.Width();
	size.cy=r.Height();

	return TRUE;
}

BOOL IsOldCE2003()
{
	DWORD dwVersion = GetVersion();
	DWORD dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
	DWORD dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
	return dwMajorVersion==4 && dwMinorVersion<21;
}

// y=f(x)
// double feed=f(double diam)
double lagrange(double* diam, double* feed, int n, double val) 
{ 
	int i,j; 
	double prod;double som; 
	som=0; 

	for(i=0;i<=n;i++) 
	{ 
		prod=1; 
		
		for(j=0;j<i;j++) 
			prod*=(val-diam[j])/(diam[i]-diam[j]); 
		
		for(j=i+1;j<=n;j++) 
			prod*=(val-diam[j])/(diam[i]-diam[j]); 
		
		som+=prod*feed[i]; 
	}

	return som; 
} 

double interlin(double* diam, double* feed, int n, double val) 
{ 
	if(val<diam[0])
		return feed[0];

	if(val>diam[n-1])
		return feed[n-1];

	for(int i=0; i<n; i++)
	{
		// si le diamètre est égal à un de ceux prédéfinis, retourner la valeur
		if(val==diam[i])
			return feed[i];
		else
		{
			if(val<diam[i]) // val est alors compris entre diam[i-1] et diam[i]
			{
				return feed[i-1] + (val-diam[i-1]) * (feed[i]-feed[i-1]) / (diam[i] - diam[i-1]);
			}
		}
	}

	ASSERT(0);

	return 0; 
}

void EnableWrkShpCalcBtn(HWND hWnd, int bEnable/*WRKSHPCALC_BTN_AUTO*/)
{
	ASSERT(hWnd!=NULL);

	switch(bEnable)
	{
	case WRKSHPCALC_BTN_DISABLED:
		{
			HWND hwndMB=SHFindMenuBar(hWnd);
			TBBUTTONINFO tbi;
			if(hwndMB)
			{
				memset(&tbi, 0, sizeof (tbi));
				tbi.cbSize=sizeof (tbi);
				tbi.dwMask=TBIF_STATE|TBIF_TEXT;
				tbi.pszText=_T("");
				if(::SendMessage(hwndMB, TB_GETBUTTONINFO, CLASSES_IDM_WRKSHPCALC, (LPARAM)&tbi))
				{
					tbi.fsState &= ~TBSTATE_ENABLED;
					::SendMessage (hwndMB, TB_SETBUTTONINFO, CLASSES_IDM_WRKSHPCALC, (LPARAM)&tbi);
				}
			}
		}
		break;
	case WRKSHPCALC_BTN_ENABLED:
		{
			HWND hwndMB=SHFindMenuBar(hWnd);
			TBBUTTONINFO tbi;
			if(hwndMB)
			{
				memset(&tbi, 0, sizeof (tbi));
				tbi.cbSize=sizeof (tbi);
				tbi.dwMask=TBIF_STATE|TBIF_TEXT;
				if(::SendMessage(hwndMB, TB_GETBUTTONINFO, CLASSES_IDM_WRKSHPCALC, (LPARAM)&tbi))
				{
					tbi.fsState |= TBSTATE_ENABLED;
					tbi.pszText=_T("WrkShpCalc");
					::SendMessage (hwndMB, TB_SETBUTTONINFO, CLASSES_IDM_WRKSHPCALC, (LPARAM)&tbi);
				}
			}
		}
		break;
	case WRKSHPCALC_BTN_AUTO:
		{
			CString strFilePath;
			::GetModuleFileName(NULL, strFilePath.GetBuffer(_MAX_PATH), _MAX_PATH);
			strFilePath.ReleaseBuffer();
			strFilePath = strFilePath.Left(strFilePath.ReverseFind('\\'));
			strFilePath += _T("\\");
			strFilePath += _T("WrkShpCalc.exe");

			CFileFind ff;
			BOOL bWrkShpCalc=ff.FindFile(strFilePath);

			HWND hwndMB=SHFindMenuBar(hWnd);
			TBBUTTONINFO tbi;
			if(hwndMB)
			{
				memset(&tbi, 0, sizeof (tbi));
				tbi.cbSize=sizeof (tbi);
				tbi.dwMask=TBIF_STATE|TBIF_TEXT;
				if(::SendMessage(hwndMB, TB_GETBUTTONINFO, CLASSES_IDM_WRKSHPCALC, (LPARAM)&tbi))
				{
					if(bWrkShpCalc)
					{
						tbi.pszText=_T("WrkShpCalc");
						tbi.fsState |= TBSTATE_ENABLED;
					}
					else
					{
						tbi.pszText=_T("");
						tbi.fsState &= ~TBSTATE_ENABLED;
					}

					::SendMessage (hwndMB, TB_SETBUTTONINFO, CLASSES_IDM_WRKSHPCALC, (LPARAM)&tbi);
				}
			}
		}
		break;
	default:
		ASSERT(0);
		break;
	}


}